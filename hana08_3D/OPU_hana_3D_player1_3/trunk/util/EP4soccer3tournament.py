#!/usr/bin/python

import copy
from EP import EP4S3D
import random
from math import pi
from subprocess import Popen, PIPE
import sys, os, time
import select
import subprocess
import signal

if (len(sys.argv) < 2):
	procnumber = 0
else:
	procnumber = sys.argv[1]

procdir    = "pop%s" % procnumber

timeOut = 30 #Seconds
fileName		=      'conf_evo.xml'
generations		=	100
populationSize		=	120
populationType		=	'ea'
theTournamentSize		=	2
minTotal = 1000000

# The directories.
if (os.path.exists("/home/mart")):
	SIMSDIR  = "/home/mart/downloads/rcsoccersim/rcssserver3D/app/simspark"
	POPDIR   = "/home/mart/RoboCup/trunk/pop%s" % procnumber
	TRUNKDIR = "/home/mart/RoboCup/trunk"
	LIBPATH  = ""
elif (os.path.exists("/home/rugrchpc")):
	SIMSDIR  = "/home/rugrchpc/arnold/tijn/sparks/rcssserver3D/app/simspark"
	POPDIR   = "/home/rugrchpc/arnold/tijn/sparks/agent/trunk/exp1/pop%s" % procnumber
	TRUNKDIR = "/home/rugrchpc/arnold/tijn/sparks/agent/trunk/exp1"
	LIBPATH  = "/home/rugrchpc/arnold/tijn/sparks/lib"
elif (os.path.exists("/share/home/robocup")):
	SIMSDIR  = "/share/home/robocup/downloads/rcsoccersim/rcssserver3D/app/simspark"
	POPDIR   = "/share/home/robocup/trunk/exp1/pop%s" % procnumber
	TRUNKDIR = "/share/home/robocup/trunk/exp1"
	LIBPATH  = "/share/home/robocup/lib"
	
# The agent and simulator startup commands.
#startsim   = "LD_LIBRARY_PATH=%s w=%s ./simspark 2> %s/sim.out &" % (LIBPATH,procnumber,POPDIR)
startsim   = "%s/simspark" % SIMSDIR
startagent = "%s/humanoidbat" % TRUNKDIR
#startagent = "%s/temp" % TRUNKDIR
agentargs  = [startagent,'-c',"%s/%s" %(POPDIR, fileName),'-p',"%d" % (3100 + int(procnumber)),'-f','walk']

sim   = None
agent = None

os.system('rm -rf %s' % procdir)
os.system('mkdir %s' % procdir)
os.system("cp EP4soccer3tournament.py %s" % procdir)

# /dev/null file.
fnull = open("/dev/null","w")
#fnull = open("bla.log","w")
#aerr = sys.stderr
aerr = open("/dev/null","w")

# 'gene':[amplitude (0, 180) per 1/2 graad, fase (-16, 16) * Pi, offset (-180,180) per 1/2 graad]
geneTemplates 	= 	{'period':[50,350],'arm1':[0,360,-16,16,-360,360,0,360,-16,16,-360,360], 'leg2':[0,360,-16,16,-360,360,0,360,-16,16,-360,360], 'leg3':[0,360,-16,16,-360,360,0,360,-16,16,-360,360], 'leg4':[0,360,-16,16,-360,360,0,360,-16,16,-360,360], 'leg5':[0,360,-16,16,-360,360,0,360,-16,16,-360,360], 'leg6':[0,360,-16,16,-360,360,0,360,-16,16,-360,360]}
geneTemplatesSimpleWalk 	= 	{'period':[80,300],'arm1':[-20, 20,-16,16,0,90,-30,30,-16,16,-30,30],'leg2':[-180,180,-16,16,-90,90, -30,30, -16, 16,-30,30],'leg4':[-135, 135,-16,16, -10,10,  -30,30, -16, 16,-30,30]}
geneTemplatesSimpleWalkFeet 	= 	{'period':[50,350],'arm1':[0,120,-16,16,-90,180,0,0,0,0,0,0],'leg2':[-90,90,-16,16,-90,90, 0,0,0,0,0,0],'leg4':[-90, 30,-16,16, -90, 30,  0,0,0,0,0,0], 'leg5':[-40, 40, -16,16, -20, 20, 0,0,0,0,0,0]}
geneTemplatesNeatCrouch	= 	{'period':[50,350],'arm1':[-180,180,-16,16,-90,90, 0,0,0,0,0,0],'arm4':[0, 80,-16,16, 0,80,  0,0,0,0,0,0], 'leg2':[0, 180, -16,16, 0, 180, 0,0,0,0,0,0], 'leg4':[120, 240, -16,16, -80, 80, 0,0,0,0,0,0]}
geneTemplatesMowCrouch	= 	{'period':[50,350],'arm1':[-360,360,-16,16,-360,360, 0,0,0,0,0,0],'leg2':[0, 180,-16,16, 0,180,  0,0,0,0,0,0], 'leg4':[-180, 0, -16,16, -180, 0, 0,0,0,0,0,0]}


geneTemplatesWalkThree 	= 	{'period':[80,300],'leg2':[0,135,-16,16,-90,90, 0,20, -16, 16,-20,20],'leg4':[0, 320,-16,16, -320,2,  0,20, -16, 16,-20,2],'leg5':[0,90,-16,16,-90,90,0,20,-16,16,-20,20]}


ep 				= 	EP4S3D( geneTemplatesWalkThree, popSize = populationSize, popType = populationType, tournamentSize = theTournamentSize, mutBaseRate = 0.5,  crossOverBaseRate = 0.5 )


def startSimulation():
	global sim
	# Start the simulator
	#	print "Starting server.. ", startsim, " ", 
	#	sim = subprocess.Popen([startsim],0,None,None,PIPE,subprocess.STDOUT,None,True,False,SIMSDIR,{'LD_LIBRARY_PATH':"%s"%LIBPATH,'w':"%s"%procnumber},False,None,0)

	sim = subprocess.Popen([startsim],0,None,None,fnull,PIPE,None,False,False,SIMSDIR,{'LD_LIBRARY_PATH':"%s"%LIBPATH,'w':"%s"%procnumber},False,None,0)
	time.sleep(1)

def startAgent():
	global agent
	#	print "Starting agent.. (%s %s) [%s]" % (startagent, agentargs,TRUNKDIR)
	agent = subprocess.Popen(agentargs,0,startagent,None,PIPE,aerr,None,False,False,TRUNKDIR,None,False,None,0)
	time.sleep(1)

def killPid(thing):
	print "Killing (%d)" % thing.pid
	if (os.path.exists("/proc/%d" % thing.pid)):
		os.system("kill -s KILL %d" % thing.pid)
		#time.sleep(1)
		#ret = os.waitpid(thing.pid,os.WNOHANG)
		ret = os.wait3(os.WNOHANG)
		#print "Wait return code: ",ret

def killSimulation():
	global sim
	killPid(sim)

def killAgent():
	global agent
	killPid(agent)

def sigTERM():
	print "Sig Term, stopping..."
	
	if (sim != None):
		killSimulation()
		
	if (agent != None):
		killAgent()

	sys.exit(1)

def sigKILL(a,b):
	print "Sig Kill, stopping..."
	
	if (sim != None):
		killSimulation()
		
	if (agent != None):
		killAgent()

	sys.exit(2)

def sigINT(a,b):
	print "Sig Int, stopping..."

	if (agent != None):
		killAgent()
	
	if (sim != None):
		killSimulation()

	sys.exit(3)

def sigCHLD(a,b):
	print "Waiting on finished process"
	os.wait()

def rewrite( chrom ):
	chrom.sort()
	for c in chrom:
		if c[0] == 'period':
			period = c[1]
	chrom.pop()     # removing period from list
	ret = "\t       <settings> \n"
	for c in chrom:        # inserting period in xml
		c.insert( 2, period )
		c.insert( 6, period )
		for i in range(len(c)):
			if i == 1:
				c[i] = c[i]/ 2.0
			if i == 2:
				c[i] = c[i]/ 100.0
			if i == 3:
				c[i] = c[i] / 16.0 * pi
			if i == 4:
				c[i] = c[i] / 2.0
			if i == 5:
				c[i] = c[i]/ 2.0
			if i == 6:
				c[i] = c[i]/ 100.0
			if i == 7:
				c[i] = c[i] / 16.0 * pi
			if i == 8:
				c[i] = c[i] / 2.0
	for c in chrom:
		d = [0,0,0,0,0,0,0,0,0]
		ret = ret + "\n"
		ap1 = ''
		ap2 = ''
		if c[0] == 'arm1':
			for i in range(1,9):
				d[i] = str( - c[i] )
				c[i] = str(c[i])
			ap1 = '&larm1;: ' + ' '.join([ c[1], c[2],c[3], c[4] ]) + ',' + ' '.join( [c[5], c[6], c[7], c[8]]) + ';' +'\n'
			ap2 = '&rarm1;: ' + ' '.join([ c[1], c[2],c[3], d[4] ]) + ',' + ' '.join( [ c[5], c[6], c[7], d[8] ]) +';' + '\n'
		if c[0] == 'leg2':
			for i in range(1,9):
				d[i] = str( c[i] + pi )
				c[i] = str( c[i] )
			ap1 = '&lleg2;: ' + ' '.join([ c[1], c[2],c[3], c[4] ]) + ',' + ' '.join( [ c[5], c[6], c[7], c[8]]) +';' + '\n'
			ap2 = '&rleg2;: ' + ' '.join([ c[1], c[2],d[3], c[4] ]) + ',' + ' '.join( [ c[5], c[6], d[7], c[8] ]) +';' + '\n'
		if c[0] == 'leg4':
			for i in range(1,9):
				d[i] = str( c[i] + pi )
				c[i] = str( c[i] )
			ap1 = '&lleg4;: ' + ' '.join([ c[1], c[2],c[3], c[4] ]) + ',' + ' '.join( [ c[5], c[6], c[7], c[8]]) +';' + '\n'
			ap2 = '&rleg4;: ' + ' '.join([ c[1], c[2],d[3], c[4] ]) + ',' + ' '.join( [ c[5], c[6], d[7], c[8] ]) +';' + '\n'
		if c[0] == 'leg5':
			for i in range(1,9):
				d[i] = str( c[i] + pi )
				c[i] = str( c[i] )
			ap1 = '&lleg5;: ' + ' '.join([ c[1], c[2],c[3], c[4] ]) + ',' + ' '.join( [ c[5], c[6], c[7], c[8]]) +';' + '\n'
			ap2 = '&rleg5;: ' + ' '.join([ c[1], c[2],d[3], c[4] ]) + ',' + ' '.join( [ c[5], c[6], d[7], c[8] ]) +';' + '\n'
		if c[0] == 'leg3':
			for i in range(1,9):
				c[i] = str(c[i])
			ap1 = '&lleg3;: ' + ' '.join([ c[1], c[2],c[3], c[4] ]) + ',' + ' '.join( [ c[5], c[6], c[7], c[8]]) +';' + '\n'
			ap2 = '&rleg3;: ' + ' '.join([ c[1], c[2],c[3], c[4] ]) + ',' + ' '.join( [ c[5], c[6], c[7], c[8] ]) +';' + '\n'
		if c[0] == 'leg6':
			for i in range(1,9):
				c[i] = str(c[i])
			ap1 = '&lleg6;: ' + ' '.join([ c[1], c[2],c[3], c[4] ]) + ',' + ' '.join( [ c[5], c[6], c[7], c[8]]) +';' + '\n'
			ap2 = '&rleg6;: ' + ' '.join([ c[1], c[2],c[3], c[4] ]) + ',' + ' '.join( [ c[5], c[6], c[7], c[8] ]) +';' + '\n'
		ret = ret + ap1 + ap2
	ret = ret +  '\t </settings> \n \t <transitionTime>' +str( period / 100.0 ) + '\n\t</transitionTime>\n\n'

	return ret
		

Out = r'''<?xml version="1.0" encoding="ISO-8859-1"?>
<!DOCTYPE confdoc [
<!ENTITY head_1 "0"> <!-- , /// Torso to head, X-Axis (not used) -->
<!ENTITY lleg1 "1"> <!-- , /// Torso to left hip, Z-Axis (twist left/right) -->
<!ENTITY lleg2 "2"> <!-- , /// Left hip to Left thigh, X-Axis (backward/forward) -->
<!ENTITY lleg3 "3"> <!-- , /// Left hip to Left thigh, Y-Axis (spread/close) -->
<!ENTITY lleg4 "4"> <!-- , /// Left thigh to Left shank, X-Axis (bend/stretch) -->
<!ENTITY lleg5 "5"> <!-- , /// Left shank to Left foot, X-Axis (forward/backward) -->
<!ENTITY lleg6 "6"> <!-- , /// Left shank to Left foot, Y-Axis (left/right) -->
<!ENTITY rleg1 "7"> <!-- , /// Torso to right hip, Z-Axis (twist left/right) -->
<!ENTITY rleg2 "8"> <!-- , /// Right hip to Right thigh, X-Axis (backward/forward) -->
<!ENTITY rleg3 "9"> <!-- , /// Right hip to Right thigh, Y-Axis (spread/close) -->
<!ENTITY rleg4 "10"> <!-- , /// Right thigh to Right shank, X-Axis (bend/stretch) -->
<!ENTITY rleg5 "11"> <!-- , /// Right shank to Right foot, X-Axis (forward/backward) -->
<!ENTITY rleg6 "12"> <!-- , /// Right shank to Right foot, Y-Axis (left/right) -->
<!ENTITY larm1 "13"> <!-- , /// Torso to Left shoulder, X-Axis (forward/backward) -->
<!ENTITY larm2 "14"> <!-- , /// Torso to Left shoulder, Y-Axis (out/in) -->
<!ENTITY larm3 "15"> <!-- , /// Left shoulder to Left upper arm, Z-Axis (twist left/right) -->
<!ENTITY larm4 "16"> <!-- , /// Left upper arm to Left lower arm, X-Axis -->
<!ENTITY rarm1 "17"> <!-- , /// Torso to Right shoulder, X-Axis (forward/backward) -->
<!ENTITY rarm2 "18"> <!-- , /// Torso to Right shoulder, Y-Axis (out/in) -->
<!ENTITY rarm3 "19"> <!-- , /// Right shoulder to Right upper arm, Z-Axis (twist left/right) -->
<!ENTITY rarm4 "20"> <!--  /// Right upper arm to Right lower arm, X-Axis -->
<!ENTITY wait "21"> <!--  /// Wait n seconds -->
]>

<conf xmlns:xi="http://www.w3.org/2003/XInclude">
  <player-class id="default">
    <xi:include href="../movejointbehaviors.xml"/>
<behaviors>
  <behavior type="Sine" id="win">
    <param>
      <!-- Settings format:
        j: A1 T1 phi1 alpha1, A2 T2 phi2 alpha2
        where j is the joint number, A the amplitude, T the period, phi the phase and alpha the offset. Sinoides seperated by ,-s are added.
        So the angle of a joint theta at time t is:
        theta(t) = A1 * sin(t / T1 * 2 *pi + phi1) + alpha1 + A2 * sin(t / T2 * 2 *pi + phi2) + alpha2 + ...
      -->

          continue;

      %s
      
    </param>
    
    <slot index="0-0">
    </slot>
    <slot index="0-1">
            <behavior refid="moveLeftHipTo"/>
    </slot>
    <slot index="0-2">
            <behavior refid="moveLeftThighXTo"/>
    </slot>
    <slot index="0-3">
            <behavior refid="moveLeftThighYTo"/>
    </slot>
    <slot index="0-4">
            <behavior refid="moveLeftKneeTo"/>
    </slot>
    <slot index="0-5">
            <behavior refid="moveLeftAnkleXTo"/>
    </slot>
    <slot index="0-6">
            <behavior refid="moveLeftAnkleYTo"/>
    </slot>
    <slot index="0-7">
            <behavior refid="moveRightHipTo"/>
    </slot>
    <slot index="0-8">
            <behavior refid="moveRightThighXTo"/>
    </slot>
    <slot index="0-9">
            <behavior refid="moveRightThighYTo"/>
    </slot>
    <slot index="0-10">
            <behavior refid="moveRightKneeTo"/>
    </slot>
    <slot index="0-11">
            <behavior refid="moveRightAnkleXTo"/>
    </slot>
    <slot index="0-12">
            <behavior refid="moveRightAnkleYTo"/>
    </slot>
    <slot index="0-13">
            <behavior refid="moveLeftShoulderXTo"/>
    </slot>
    <slot index="0-14">
            <behavior refid="moveLeftShoulderYTo"/>
    </slot>
    <slot index="0-15">
            <behavior refid="moveLeftShoulderZTo"/>
    </slot>
    <slot index="0-16">
            <behavior refid="moveLeftElbowTo"/>
    </slot>
    <slot index="0-17">
            <behavior refid="moveRightShoulderXTo"/>
    </slot>
    <slot index="0-18">
            <behavior refid="moveRightShoulderYTo"/>
    </slot>
    <slot index="0-19">
            <behavior refid="moveRightShoulderZTo"/>
    </slot>
    <slot index="0-20">
            <behavior refid="moveRightElbowTo"/>
    </slot>
  
  </behavior>

</behaviors>


  </player-class>
  
  <include file="keeper.xml"/>
  
  <player id="0" class="default"/>
  <player id="1" class="default"/>
</conf>
'''

def writeInd(name, ind):
	f = open( name, 'w' )
	f.write( Out % rewrite(  copy.deepcopy(ind) ) )
	f.close()

def saveRun( i, dist ):
	f = open( "%s/run" % procdir, 'a' )
	wr = time.strftime('%X') + ' ' + str(i) + '\t' + str(dist) + '\n'
	f.write( wr )
	f.close()

def doOneInd( ind ):
	global agent, sim
	
	writeInd ( procdir + '/' + fileName, ind )

	agentTrail = 0
	p = None
	q = None

	# We had a problem that when the server or agent crashes or when something
	# goes wrong with the communication (socket was still registered or something),
	# we lose potentially (onetime the best so far and untill the end of the run)
	# good genes. So now we do up to 5 runs is something goes wrong..
	while (agentTrail < 5):
		try:
			# Initiallie everything is really bad! :)
			minDist = 10000000

			# Start the simulator
			startSimulation();

			# Remember the start time
			start = time.time()

			# Start the agent and create and register a poll object.
			startAgent()

			# Create polling object for agent
			p = select.poll();
			p.register(agent.stdout,select.POLLIN)

			# Create polling object for simserver
			q = select.poll();
			q.register(sim.stderr,select.POLLIN)

			# Start with a error distance.
			dist = '10000000'

			evt = q.poll(100)

			while (len(evt) != 0):
				something = False

				for e in evt:
					#print e[1]
					if (e[1] == select.POLLIN):	
						line = sim.stderr.readline()
						#print "SIMS: ", line
						something = True

				if (not something):
					break

				evt = q.poll(100)
	
			# As long as we haven't passed the timeout gather distance information from the agent.
			while (time.time() - start < timeOut):

				#print "# ", time.time() - start, " - ", timeOut

				# Check if the server has got anything to say.
				evt = q.poll(10)
				if (len(evt) != 0):
					for e in evt:
						if (e[1] & select.POLLIN):
							line = sim.stderr.readline()
							#print "Sims: ", line
							if (line[0:11] == 'ODE Message'):
								# Error, agent has exploded.
								dist = 'ode'
								saveRun('error','ODE Message: '+line)
								break

					if (dist == 'ode'):
						dist = 'nan'
						break

				evt = p.poll(5000)

				if (len(evt) == 0):
					# Error, the agent did not respond for more than a second!
					print 'E: agent does not respond'
					saveRun('error','agent unresponsive')
					dist = ''
					break
				else:
					# OK, we have some input!
					for e in evt:
						if (e[1] & select.POLLIN):
							dist = agent.stdout.readline().rstrip()
							#print "D: ", dist
						elif (e[1] & select.POLLHUP):
							dist = agent.stdout.readline().rstrip()
							print "Hung up: (", e, ") ", dist
							dist = 'hup'
							break
					if (dist == 'nan'):
						saveRun('error','agent exploded')
						break
					elif (dist == 'hup'):
						saveRun('error','agent hung up')
						dist = ''
						break


		except SystemExit:
			raise SystemExit
		except ValueError:
			saveRun('error','agent gave strange value')
			dist = ''
		except Exception, inst:
			saveRun('error',"unknown exception: %s" % str(inst))
			dist = ''

		# Unregister the filedescriptor from the poll object.
		if (p != None):
			p.unregister(agent.stdout)

		# Close file descriptors (probable FIX for to many open files bug)
		if (agent != None):
			if (agent.stdout):
				agent.stdout.close()

			if (sim.stdout):
				sim.stdout.close()

		#print "Distance: ", dist

		# We have to kill the specific pid, because more than one server can run
		# on the same computer (multiple cores).
		killAgent()
		killSimulation()

		if dist == '':
			# Something went wrong, so try again!
			agentTrail += 1
		elif dist == 'nan':
			# The agent exploded (server had a physiscs problem...)
			minDist = 100000.0
			break
		else:
			# Yeey, it worked so far!
			try:
				minDist = float(dist)
				if (minDist > 600.0 or minDist < 10.0):
					# Assume failure (like explosion)
					saveRun('error','agent probably exploded')
					minDist = 1000000
			except Exception, inst:
				print "Exception: ", inst
				agentTrail += 1
			else:
				break


	return minDist

# Register some signal handlers...
signal.signal(signal.SIGTERM,sigTERM);
signal.signal(signal.SIGINT ,sigINT);
#signal.signal(signal.SIGCHLD ,sigCHLD);
#signal.signal(signal.SIGKILL,sigKILL);


saveRun( 'populationSize' , populationSize  )
saveRun( 'generations' , generations  )

try:

	for i in range( populationSize * generations / 2):
		print "\t\tgeneration : \t" , (i+1) / (populationSize/2) , " \t round (total): \t", i
		#ind1, ind2, ind3		= map ( lambda x : x.getGenes() , copy.deepcopy( ep.select() ) )
		indx = map ( lambda x : x.getGenes() , copy.deepcopy( ep.select() ) )

		bestx = []

		for j in range(0,len(indx)):
			print "\n RUNNING HUMANOID %d \n" % j
			best = doOneInd(indx[j])
			bestx.append(best)
			saveRun(i, best)
			saveRun('genes:  ', indx[j])

		verybest  = 1000000
		verybestx = 0

#		print "\n\t\tgeneration : \t" , (i+1) / (populationSize/2) , " \t round (total): \t", i
		for j in range(0,len(indx)):
			if (bestx[j] < verybest):
				verybest = bestx[j]
				verybestx = j
#			print '\t\t\t HUMANOID %d: \t' % j, bestx[j]
#			print 'ind%d:\t' % j, indx[j]

		ep.setWinner(verybestx)
		print "\t\t HUMANOID %d WINS:\t distance = \t" % verybestx, verybest
		if verybest < minTotal:
			minTotal = verybest
			writeInd( procdir + '/' + str(minTotal) + '.xml', indx[verybestx] )

		print "\t\toveral minimum :: %.2f \n" % minTotal
	
except SystemExit:
	print "Exiting..."
	
	
fnull.close()
aerr.close()

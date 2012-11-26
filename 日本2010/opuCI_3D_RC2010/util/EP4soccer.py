#!/usr/bin/python

import copy
from EP import EP4S3D
import random
from math import pi
from subprocess import Popen, PIPE
import sys, os, time
import select
import subprocess

if (len(sys.argv) < 2):
	procnumber = 0
else:
	procnumber = sys.argv[1]

procdir    = "pop%s" % procnumber

timeOut = 20 #Seconds
fileName			=      'conf_evo.xml'
generations		=	200
populationSize		=	300
populationType		=	'ea'
minTotal = 1000000

startsim = './startnovis'  # start or startnovis
os.system('rm -rf %s' % procdir)
os.system('mkdir %s' % procdir)
os.system("cp EP4soccer.py %s" % procdir)

# 'gene':[amplitude (0, 180) per 1/2 graad, fase (-16, 16) * Pi, offset (-180,180) per 1/2 graad]
geneTemplates 	= 	{'period':[50,350],'arm1':[0,360,-16,16,-360,360,0,360,-16,16,-360,360], 'leg2':[0,360,-16,16,-360,360,0,360,-16,16,-360,360], 'leg3':[0,360,-16,16,-360,360,0,360,-16,16,-360,360], 'leg4':[0,360,-16,16,-360,360,0,360,-16,16,-360,360], 'leg5':[0,360,-16,16,-360,360,0,360,-16,16,-360,360], 'leg6':[0,360,-16,16,-360,360,0,360,-16,16,-360,360]}
geneTemplatesSimpleWalk 	= 	{'period':[80,300],'arm1':[-90, 90,-16,16,-90,90,0,0,0,0,0,0],'leg2':[-135,135,-16,16,-90,90, -20,20, -16, 16,-20,20],'leg4':[-135, 135,-16,16, -30,30,  -20,20, -16, 16,-20,20]}
geneTemplatesSimpleWalkFeet 	= 	{'period':[50,350],'arm1':[0,120,-16,16,-90,180,0,0,0,0,0,0],'leg2':[-90,90,-16,16,-90,90, 0,0,0,0,0,0],'leg4':[-90, 30,-16,16, -90, 30,  0,0,0,0,0,0], 'leg5':[-40, 40, -16,16, -20, 20, 0,0,0,0,0,0]}
geneTemplatesNeatCrouch	= 	{'period':[50,350],'arm1':[-180,180,-16,16,-90,90, 0,0,0,0,0,0],'arm4':[0, 80,-16,16, 0,80,  0,0,0,0,0,0], 'leg2':[0, 180, -16,16, 0, 180, 0,0,0,0,0,0], 'leg4':[120, 240, -16,16, -80, 80, 0,0,0,0,0,0]}
geneTemplatesMowCrouch	= 	{'period':[50,350],'arm1':[-360,360,-16,16,-360,360, 0,0,0,0,0,0],'leg2':[0, 180,-16,16, 0,180,  0,0,0,0,0,0], 'leg4':[-180, 0, -16,16, -180, 0, 0,0,0,0,0,0]}




ep 				= 	EP4S3D( geneTemplatesSimpleWalk, popSize = populationSize, popType = populationType, tournamentSize = 2, mutBaseRate = 0.5,  crossOverBaseRate = 0.5 )


def rewrite( chrom ):
	chrom.sort()
	period = chrom[-1][1]
	chrom.pop()
	ret = "\t       <settings> \n"
	for c in chrom:
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

      
      %s
      
    </param>
    
    <slot index="0-0">
            <behavior refid="moveHeadTo"/>
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
	minDist = 10000000
	writeInd ( procdir + '/' + fileName, ind )
	sim = subprocess.Popen(startsim,0,None,None,PIPE,subprocess.STDOUT,None,False,True,None,None,False,None,0)
	#sim = os.popen( startsim )
	time.sleep(1)
	cmd = "./humanoidbat -c %s/%s -u 100 -p %d" % (procdir, fileName, (3100 + int(procnumber)))
	start = time.time()
	minimum = os.popen( cmd )

	p = select.poll();
	#p2 = select.poll();
	#p3 = select.poll();

	p.register(minimum,select.POLLIN)
	#p2.register(sim,select.POLLIN)
	#p3.register(sim,select.POLLERR | select.POLLHUP | select.POLLNVAL);

	#dist = []
	dist = '10000000'	
	
	while(time.time() - start < timeOut):
		#		print "# ", time.time(), " - "#, sim.poll()
		if (len(p.poll(1000)) != 0):
			if not sim.poll():
				#dist.append( minimum.readline().rstrip())
				dist = minimum.readline().rstrip()
			else:
				saveRun('error','simspark terminated')
		else:
			# Agent didn't respond for more than a second.
			dist = ''
			break
	#if dist.pop(-1) == '':
	if dist == '':
		minDist = 10000000
	else:
		#minDist =  float( dist.pop() )
		minDist = float(dist)

	p.unregister(minimum)

	os.system('killall -9 lt-simspark')
	return minDist

saveRun( 'populationSize' , populationSize  )
saveRun( 'generations' , generations  )


for i in range( populationSize * generations / 2):
	print "\t\tgeneration : \t" , (i+1) / (populationSize/2) , " \t round (total): \t", i
	ind1, ind2		= map ( lambda x : x.getGenes() , copy.deepcopy( ep.select() ) )
	best1 = doOneInd(  ind1 )
	print '\t\t\t HUMANOID 1: \t', best1
	saveRun( i, best1 )
	saveRun('genes:  ', ind1)
	print 'ind1:\t', ind1
	best2 = doOneInd(  ind2 )
	print '\t\t\t HUMANOID 2: \t', best2
	saveRun( i, best2 )
	saveRun('genes:  ', ind2)
	print 'ind2:\t', ind2
	if best1 < best2:
		ep.setWinner(0)
		print "\t FIRST HUMANOID WINS:\t distance = \t", best1
		if best1 < minTotal:
			minTotal = best1
			writeInd( procdir + '/' + str(minTotal) + '.xml', ind1 )
	elif best2 <= best1:
		ep.setWinner(1)
		print "\t SECOND HUMANOID WINS:\t distance = \t", best2
		if best2 < minTotal:
			minTotal = best2
			writeInd( procdir + '/' + str(minTotal) + '.xml', ind1 )
	print "\t\toveral minimum :: ", minTotal
	
			
	

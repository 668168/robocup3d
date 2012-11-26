#
# apollo3d.rb
#

run 'soccersim-apollo.rb'

#sparkLogErrorToCerr()

time = 0.0
#host = ''
#host = ''
host = ''
port = 3100

DEBUG = 0
VERSUS = 1
WALK = 2
KICK = 3

challenge = VERSUS

#if challenge == KICK || challenge == WALK
#	time = 3.0
#end

createVariable('Agent.ThinkingTime', time)
createVariable('Agent.Host', host)
createVariable('Agent.Port', port)
createVariable('Agent.Challenge', challenge)
createVariable('Agent.AttackMode', 0)

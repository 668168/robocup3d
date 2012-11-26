#!/bin/bash
#
# RoboCup
# 2008 sample start script for 3D Simulation Competitions
#
export LD_LIBRARY_PATH=.
AGENT_BINARY=penalty-attacker

#killall -9 $AGENT_BINARY

#sed -i "s/host = '.*'/host = '$1'/" apollo3d.rb

./$AGENT_BINARY --host $1 > /dev/null 2> /dev/null &
         


#!/bin/bash
#
# RoboCup
# 2008 sample start script for 3D Simulation Competitions
#
if [ -z "$1" ]; then
	host="127.0.0.1"
else
	host="$1"
fi


export LD_LIBRARY_PATH=.
AGENT_BINARY=apollo3d
#killall -9 $AGENT_BINARY

sed -i "s/host = '.*'/host = '$1'/" apollo3d.rb

./$AGENT_BINARY  $1 > /dev/null 2> /dev/null &
sleep 1          
./$AGENT_BINARY  $1 > /dev/null 2> /dev/null &
sleep 1          
./$AGENT_BINARY  $1 > /dev/null 2> /dev/null &
sleep 1          
./$AGENT_BINARY  $1 > /dev/null 2> /dev/null &
sleep 1          
./$AGENT_BINARY  $1 > /dev/null 2> /dev/null &
sleep 1          
./$AGENT_BINARY  $1 > /dev/null 2> /dev/null &
sleep 1          
./$AGENT_BINARY  $1 > /dev/null 2> /dev/null &
sleep 1          
./$AGENT_BINARY  $1 > /dev/null 2> /dev/null &
sleep 1          
./$AGENT_BINARY  $1 > /dev/null 2> /dev/null &

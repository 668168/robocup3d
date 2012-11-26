#!/bin/bash
#
# RoboCup 2009 sample start script for the 3D Simulation Competitions
#
BINARY=opuciplayer
TEAMNAME=opuCI_3D

HOST=${1:-localhost}
PLAYER=${2:-6} # the number of players
OTHEROPT=${3:-}

i=1
killall -9 $BINARY > /dev/null

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

while (( $i < $PLAYER+1 ))
do

./$BINARY -h $HOST -t $TEAMNAME -u $i $OTHEROPT > /dev/null &

sleep 2

i=$(( $i + 1 ))
done

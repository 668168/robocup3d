#!/bin/bash
###########################################
# Starts a magmaOffenburg RoboCup client
# example: ./startTeam.sh
###########################################


CLSPTH=./magmaOffenburg.jar
CLSPTH=${CLSPTH}:./commons-math-1.2.jar
CLSPTH=${CLSPTH}:./vecmath.jar

TEAMNAME=magmaOffenburg
SERVER_IP=$1
SERVER_PORT=3100
LOGLEVEL=severe

java -cp $CLSPTH magma.agent.general.RoboCupClient $TEAMNAME 1 $SERVER_IP $SERVER_PORT $LOGLEVEL &
sleep 4
java -cp $CLSPTH magma.agent.general.RoboCupClient $TEAMNAME 2 $SERVER_IP $SERVER_PORT $LOGLEVEL &
sleep 4
java -cp $CLSPTH magma.agent.general.RoboCupClient $TEAMNAME 3 $SERVER_IP $SERVER_PORT $LOGLEVEL &
#sleep 4
#java -cp $CLSPTH magma.agent.general.RoboCupClient $TEAMNAME 4 $SERVER_IP $SERVER_PORT $LOGLEVEL &


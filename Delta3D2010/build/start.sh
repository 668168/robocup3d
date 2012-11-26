#!/bin/bash

# Delta3D 2009 Startup Script

AGENT_BINARY=Delta3D
Goalie=1

LeftDefense=3

RightDefense=5

Center=7

LeftForward=10

RightForward=11


killall -9 $AGENT_BINARY

./$AGENT_BINARY --unum $Goalie --host=$1> /dev/null &
sleep 1
./$AGENT_BINARY --unum $LeftDefense --host=$1> /dev/null &
sleep 1
./$AGENT_BINARY --unum $RightDefense --host=$1> /dev/null &
sleep 1
./$AGENT_BINARY --unum $Center --host=$1> /dev/null &
sleep 1
./$AGENT_BINARY --unum $LeftForward --host=$1> player10 2 &
sleep 1
./$AGENT_BINARY --unum $RightForward --host=$1> /dev/null &

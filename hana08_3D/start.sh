#!/bin/sh

if [ $# = 0 ]
then
    HOST_IP="localhost"
else
    HOST_IP=$1
fi

HomeDir=`pwd`
echo $HOST_IP
cd $HomeDir/OPU_hana_3D_player1_3/trunk

./humanoidbat -c OPU_hana_3D_conf.xml -u 1 -h $HOST_IP -t OPU_hana_3D &

sleep 1

./humanoidbat -c OPU_hana_3D_conf.xml -u 3 -h $HOST_IP -t OPU_hana_3D &

sleep 1

cd $HomeDir/OPU_hana_3D_player2/trunk

./humanoidbat -c OPU_hana_3D_conf.xml -u 2 -h $HOST_IP -t OPU_hana_3D &


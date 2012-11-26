@echo off
rem ###########################################
rem # Starts a magmaOffenburg RoboCup client
rem ###########################################

cd ..

set CLSPTH=./build/classes;
set CLSPTH=%CLSPTH%;./lib/commons-math-1.2.jar
set CLSPTH=%CLSPTH%;./lib/vecmath.jar

set TEAMNAME=magmaOffenburg
set SERVER_IP=127.0.0.1
set SERVER_PORT=3100

start java -cp %CLSPTH% magma.agent.general.RoboCupClient %TEAMNAME% 1 %SERVER_IP% %SERVER_PORT%
pause
start java -cp %CLSPTH% magma.agent.general.RoboCupClient %TEAMNAME% 2 %SERVER_IP% %SERVER_PORT%
pause
start java -cp %CLSPTH% magma.agent.general.RoboCupClient %TEAMNAME% 3 %SERVER_IP% %SERVER_PORT%
rem pause
rem start java -cp %CLSPTH% magma.agent.general.RoboCupClient %TEAMNAME% 4 %SERVER_IP% %SERVER_PORT%

cd bin
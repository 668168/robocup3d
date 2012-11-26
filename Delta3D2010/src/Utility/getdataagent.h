/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef GETDATAAGENT_H
#define GETDATAAGENT_H

#include "../WorldModel/WorldModel.h"
#include "../Effectors/Effectors.h"
#include "../Connection/Connection.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

class GetDataAgent{
public:
    GetDataAgent(WorldModel *worldmodel, Effectors *effectors, Connection *connection);

    ~GetDataAgent();

	bool	openFile(char* fileName1, char* fileName2, char* Beam);
	
	bool	closeFile();
	
	bool	putDataJointIntoFile();
	
	bool	putGyroIntoFile();
	
	bool	putFRPIntoFile();
	
	bool	beamRandomAgent();
	
	bool	putDataSimulationTime();
	
	bool	putAllOfDataOnTheFile(int sideDown);
	
	bool	sideFallDown(int side);
	
	bool	putDataJointIntoFile_MATLAB();
	
	bool	putGyroIntoFile_MATLAB();
	
	bool	putFRPIntoFile_MATLAB();
	
	bool	putAllOfDataOnTheFile_MATLAB(int sideDown);
	
	bool	sideFallDown_MATLAB(int side);

private:
	boost::shared_ptr <Connection> 	con;	
	boost::shared_ptr <WorldModel>	wm;
	boost::shared_ptr <Effectors>	ef;	
	std::ofstream		dataFile1,dataFile2,beam;
	long		sysTime;
	int		intSysTime;
	
};

#endif // GETDATAAGENT_H

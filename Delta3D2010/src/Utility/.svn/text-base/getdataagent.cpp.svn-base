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

#include "getdataagent.h"


GetDataAgent::GetDataAgent(WorldModel *worldmodel, Effectors *effectors, Connection *connection)
{
	wm  = boost::shared_ptr <WorldModel> (worldmodel);
	con = boost::shared_ptr <Connection> (connection);
	ef = boost::shared_ptr <Effectors> (effectors);
}


GetDataAgent::~GetDataAgent()
{
}


bool	GetDataAgent::openFile(char* fileName1, char* fileName2, char* Beam ){
dataFile1.open(fileName1 , ios::app);
dataFile2.open(fileName2 , ios::app);
beam.open(Beam , ios::app);
return true;
}
	
bool	GetDataAgent::closeFile(){
dataFile1.close();
dataFile2.close();
beam.close();
return true;
}

bool	GetDataAgent::putDataSimulationTime(){
dataFile1 << wm->getSimulationTime()<<'\n';
//dataFile2 << wm->getSimulationTime()<<" ";
}
	
bool	GetDataAgent::putDataJointIntoFile(){
dataFile1 <<"Joints Sense :"<<'\n'<< wm->getHJoint(JID_HEAD_1).angle <<" "<< wm->getHJoint(JID_HEAD_2).angle <<" "<< wm->getHJoint(JID_LARM_1).angle <<" "<< wm->getHJoint(JID_LARM_2).angle <<" "<< wm->getHJoint(JID_LARM_3).angle <<" "<< wm->getHJoint(JID_LARM_4).angle <<" "<< wm->getHJoint(JID_LLEG_1).angle <<" "<< wm->getHJoint(JID_LLEG_2).angle <<" "<< wm->getHJoint(JID_LLEG_3).angle <<" " << wm->getHJoint(JID_LLEG_5).angle <<" "<< wm->getHJoint(JID_LLEG_6).angle <<" " << wm->getHJoint(JID_RARM_1).angle <<" " << wm->getHJoint(JID_RARM_2).angle <<" " << wm->getHJoint(JID_RARM_3).angle <<" " << wm->getHJoint(JID_RARM_4).angle <<" " << wm->getHJoint(JID_RLEG_1).angle <<" " << wm->getHJoint(JID_RLEG_2).angle <<" " << wm->getHJoint(JID_RLEG_3).angle <<" " << wm->getHJoint(JID_RLEG_4).angle <<" " << wm->getHJoint(JID_RLEG_5).angle <<" " << wm->getHJoint(JID_RLEG_6).angle <<'\n';

dataFile2 << wm->getHJoint(JID_HEAD_1).angle <<" "<< wm->getHJoint(JID_HEAD_2).angle <<" "<< wm->getHJoint(JID_LARM_1).angle <<" "<< wm->getHJoint(JID_LARM_2).angle <<" "<< wm->getHJoint(JID_LARM_3).angle <<" "<< wm->getHJoint(JID_LARM_4).angle <<" "<< wm->getHJoint(JID_LLEG_1).angle <<" "<< wm->getHJoint(JID_LLEG_2).angle <<" "<< wm->getHJoint(JID_LLEG_3).angle <<" " << wm->getHJoint(JID_LLEG_5).angle <<" "<< wm->getHJoint(JID_LLEG_6).angle <<" " << wm->getHJoint(JID_RARM_1).angle <<" " << wm->getHJoint(JID_RARM_2).angle <<" " << wm->getHJoint(JID_RARM_3).angle <<" " << wm->getHJoint(JID_RARM_4).angle <<" " << wm->getHJoint(JID_RLEG_1).angle <<" " << wm->getHJoint(JID_RLEG_2).angle <<" " << wm->getHJoint(JID_RLEG_3).angle <<" " << wm->getHJoint(JID_RLEG_4).angle <<" " << wm->getHJoint(JID_RLEG_5).angle <<" " << wm->getHJoint(JID_RLEG_6).angle <<" ";
return true;
}
	
bool	GetDataAgent::putGyroIntoFile(){
dataFile1 <<"Geyro Sense:" << '\n' <<wm->getGyr().x << " " << wm->getGyr().y << " " << wm->getGyr().z << '\n';
dataFile2 << wm->getGyr().x << " " << wm->getGyr().y << " " << wm->getGyr().z << " ";
return true;
}
	
bool	GetDataAgent::putFRPIntoFile(){
dataFile1 <<"Frp sense : "<<'\n'<< wm->getFRP(FID_LF).c_x << " " << wm->getFRP(FID_LF).c_y << " " << wm->getFRP(FID_LF).c_z << " " << wm->getFRP(FID_LF).f_x << " " << wm->getFRP(FID_LF).f_y << " " << wm->getFRP(FID_LF).f_z << " " << wm->getFRP(FID_RF).c_x << " " << wm->getFRP(FID_RF).c_y << " " << wm->getFRP(FID_RF).c_z << " " << wm->getFRP(FID_RF).f_x << " " << wm->getFRP(FID_RF).f_y << " " << wm->getFRP(FID_RF).f_z << '\n';

dataFile2 <<wm->getFRP(FID_LF).c_x << " " << wm->getFRP(FID_LF).c_y << " " << wm->getFRP(FID_LF).c_z << " " << wm->getFRP(FID_LF).f_x << " " << wm->getFRP(FID_LF).f_y << " "  << wm->getFRP(FID_LF).f_z << " " << wm->getFRP(FID_RF).c_x << " " << wm->getFRP(FID_RF).c_y << " " << wm->getFRP(FID_RF).c_z << " " << wm->getFRP(FID_RF).f_x << " " << wm->getFRP(FID_RF).f_y << " " << wm->getFRP(FID_RF).f_z << " ";
return true;
}
	
bool	GetDataAgent::beamRandomAgent(){
sysTime = time(NULL);
intSysTime = (unsigned) sysTime/2;
srand(intSysTime);
float x = -abs((rand()%60000)/10000.0);
float y;
if (rand()%2==0)
	y = (rand()%40000)/10000.0;
else
	y = -(rand()%40000)/10000.0;
float a = (rand()%3600000)/10000.0;
dataFile1 << '\n' << "Bean Point :" << '\n' << x <<" "<< y <<" "<< a <<'\n';
beam << x  <<" "<< y <<" "<< a <<'\n';
//ef->beam(x,y,a);
return true;
}

bool	GetDataAgent::sideFallDown(int side){
dataFile1 << "Side Fall Down :"<<" " << side <<'\n';
dataFile2 << side ;
return true;
}

bool	GetDataAgent::sideFallDown_MATLAB(int side){
dataFile1 << "Side Fall Down :"<<" " << side <<'\n';
dataFile2 << side ;
return true;
}

bool	GetDataAgent::putFRPIntoFile_MATLAB(){
dataFile1 <<"Frp sense : "<<'\n'<< wm->getFRP(FID_LF).c_x << " " << wm->getFRP(FID_LF).c_y << " " << wm->getFRP(FID_LF).c_z << " " << wm->getFRP(FID_LF).f_x << " " << wm->getFRP(FID_LF).f_y << " " << wm->getFRP(FID_LF).f_z << " " << wm->getFRP(FID_RF).c_x << " " << wm->getFRP(FID_RF).c_y << " " << wm->getFRP(FID_RF).c_z << " " << wm->getFRP(FID_RF).f_x << " " << wm->getFRP(FID_RF).f_y << " " << wm->getFRP(FID_RF).f_z << '\n';

dataFile2 <<wm->getFRP(FID_LF).c_x << " " << wm->getFRP(FID_LF).c_y << " " << wm->getFRP(FID_LF).c_z << " " << wm->getFRP(FID_LF).f_x << " " << wm->getFRP(FID_LF).f_y << " "  << wm->getFRP(FID_LF).f_z << " " << wm->getFRP(FID_RF).c_x << " " << wm->getFRP(FID_RF).c_y << " " << wm->getFRP(FID_RF).c_z << " " << wm->getFRP(FID_RF).f_x << " " << wm->getFRP(FID_RF).f_y << " " << wm->getFRP(FID_RF).f_z << " ";
return true;
}

bool	GetDataAgent::putGyroIntoFile_MATLAB(){
dataFile1 <<"Geyro Sense:" << '\n' <<wm->getGyr().x << " " << wm->getGyr().y << " " << wm->getGyr().z << '\n';
dataFile2 << wm->getGyr().x << " " << wm->getGyr().y << " " << wm->getGyr().z << " ";
return true;
}

bool	GetDataAgent::putDataJointIntoFile_MATLAB(){
dataFile1 <<"Joints Sense :"<<'\n'<< wm->getHJoint(JID_HEAD_1).angle <<" "<< wm->getHJoint(JID_HEAD_2).angle <<" "<< wm->getHJoint(JID_LARM_1).angle <<" "<< wm->getHJoint(JID_LARM_2).angle <<" "<< wm->getHJoint(JID_LARM_3).angle <<" "<< wm->getHJoint(JID_LARM_4).angle <<" "<< wm->getHJoint(JID_LLEG_1).angle <<" "<< wm->getHJoint(JID_LLEG_2).angle <<" "<< wm->getHJoint(JID_LLEG_3).angle <<" " << wm->getHJoint(JID_LLEG_5).angle <<" "<< wm->getHJoint(JID_LLEG_6).angle <<" " << wm->getHJoint(JID_RARM_1).angle <<" " << wm->getHJoint(JID_RARM_2).angle <<" " << wm->getHJoint(JID_RARM_3).angle <<" " << wm->getHJoint(JID_RARM_4).angle <<" " << wm->getHJoint(JID_RLEG_1).angle <<" " << wm->getHJoint(JID_RLEG_2).angle <<" " << wm->getHJoint(JID_RLEG_3).angle <<" " << wm->getHJoint(JID_RLEG_4).angle <<" " << wm->getHJoint(JID_RLEG_5).angle <<" " << wm->getHJoint(JID_RLEG_6).angle <<'\n';

dataFile2 << wm->getHJoint(JID_HEAD_1).angle <<" "<< wm->getHJoint(JID_HEAD_2).angle <<" "<< wm->getHJoint(JID_LARM_1).angle <<" "<< wm->getHJoint(JID_LARM_2).angle <<" "<< wm->getHJoint(JID_LARM_3).angle <<" "<< wm->getHJoint(JID_LARM_4).angle <<" "<< wm->getHJoint(JID_LLEG_1).angle <<" "<< wm->getHJoint(JID_LLEG_2).angle <<" "<< wm->getHJoint(JID_LLEG_3).angle <<" " << wm->getHJoint(JID_LLEG_5).angle <<" "<< wm->getHJoint(JID_LLEG_6).angle <<" " << wm->getHJoint(JID_RARM_1).angle <<" " << wm->getHJoint(JID_RARM_2).angle <<" " << wm->getHJoint(JID_RARM_3).angle <<" " << wm->getHJoint(JID_RARM_4).angle <<" " << wm->getHJoint(JID_RLEG_1).angle <<" " << wm->getHJoint(JID_RLEG_2).angle <<" " << wm->getHJoint(JID_RLEG_3).angle <<" " << wm->getHJoint(JID_RLEG_4).angle <<" " << wm->getHJoint(JID_RLEG_5).angle <<" " << wm->getHJoint(JID_RLEG_6).angle <<" ";
return true;
}

bool	GetDataAgent::putAllOfDataOnTheFile(int sideDown){
putDataSimulationTime();
putDataJointIntoFile();
putFRPIntoFile();
putGyroIntoFile();
sideFallDown(sideDown);
dataFile1<<'\n'<<'\n';
dataFile2<<'\n';
return true;
}

bool	GetDataAgent::putAllOfDataOnTheFile_MATLAB(int sideDown){
putDataSimulationTime();
putDataJointIntoFile();
putFRPIntoFile();
putGyroIntoFile();
sideFallDown(sideDown);
dataFile1<<'\n'<<'\n';
dataFile2<<'\n';
return true;
}

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

#include "AngularMotor.h"


#include "AngularMotor.h"
#include <stdlib.h>


AngularMotor::AngularMotor()
{
	addllj1=0;
        addllj2=0;
        addllj3=0;
        addllj4=0;
        addllj5=0;
        addllj6=0;
        addrlj1=0;
        addrlj2=0;
        addrlj3=0;
        addrlj4=0;
        addrlj5=0;
        addrlj6=0;
        addlaj1=0;
        addlaj2=0;
        addlaj3=0;
        addlaj4=0;
        addraj1=0;
        addraj2=0;
        addraj3=0;
        addraj4=0;
        flag = true;
        count = 66;
}


AngularMotor::~AngularMotor()
{
}

AngularMotor& AngularMotor::instance()
{
   static AngularMotor sAngularMotor;
   return sAngularMotor;
}

std::string AngularMotor::stringify(  float value )
  {
          stringstream ss;
          ss << value;
          return ss.str();
  }



void AngularMotor::add(std::string msg)
{

    effect << msg;
    // return true;

}

void AngularMotor::moveArm(side s, float aj1, float aj2, float aj3, float aj4 )
{
if( s == right_side ){
   effect << " (" <<  "rae1 " <<  stringify(aj1) << ") ";
   effect << " (" <<  "rae2 " <<  stringify(aj2)  << ") ";
   effect << " (" <<  "rae3 " <<  stringify(aj3)  << ") ";
   effect << " (" <<  "rae4 " <<  stringify(aj4)  << ") ";
}else if ( s == left_side ){
   effect << " (" <<  "lae1 " <<  stringify(aj1) << ") ";
   effect << " (" <<  "lae2 " <<  stringify(aj2)  << ") ";
   effect << " (" <<  "lae3 " <<  stringify(aj3)  << ") ";
   effect << " (" <<  "lae4 " <<  stringify(aj4)  << ") ";
}
//return true;

}

bool AngularMotor::moveArm(side s,Arm A){
if( s == right_side ){
   effect << " (" <<  "rae1 " <<  A.getaj1() << ") ";
   effect << " (" <<  "rae2 " <<  A.getaj2()  << ") ";
   effect << " (" <<  "rae3 " <<  A.getaj3()  << ") ";
   effect << " (" <<  "rae4 " <<  A.getaj4()  << ") ";
}else if ( s == left_side ){
   effect << " (" <<  "lae1 " <<  A.getaj1() << ") ";
   effect << " (" <<  "lae2 " <<  A.getaj2()  << ") ";
   effect << " (" <<  "lae3 " <<  A.getaj3()  << ") ";
   effect << " (" <<  "lae4 " <<  A.getaj4()  << ") ";
}
return true;

}

void AngularMotor::moveLeg(side s, float lj1, float lj2, float lj3, float lj4, float lj5, float lj6){
 	if( s == right_side ){
	   effect << " (" <<  "rle1 " <<  stringify(lj1) << ") ";
	   effect << " (" <<  "rle2 " <<  stringify(lj2)  << ") ";
	   effect << " (" <<  "rle3 " <<  stringify(lj3)  << ") ";
	   effect << " (" <<  "rle4 " <<  stringify(lj4)  << ") ";
	   effect << " (" <<  "rle5 " <<  stringify(lj5)  << ") ";
	   effect << " (" <<  "rle6 " <<  stringify(lj6)  << ") ";
	}else if ( s == left_side ){
	   effect << " (" <<  "lle1 " <<  stringify(lj1) << ") ";
	   effect << " (" <<  "lle2 " <<  stringify(lj2)  << ") ";
	   effect << " (" <<  "lle3 " <<  lj3  << ") ";
	   effect << " (" <<  "lle4 " <<  stringify(lj4)  << ") ";
	   effect << " (" <<  "lle5 " <<  stringify(lj5)  << ") ";
	   effect << " (" <<  "lle6 " <<  stringify(lj6)  << ") ";
	}
	//return true;
}

bool AngularMotor::moveLeg(side s, Leg leg){
 	if( s == right_side ){
	   effect << " (" <<  "rle1 " <<  leg.getlj1() << ") ";
	   effect << " (" <<  "rle2 " <<  leg.getlj2()  << ") ";
	   effect << " (" <<  "rle3 " <<  leg.getlj3()  << ") ";
	   effect << " (" <<  "rle4 " <<  leg.getlj4()  << ") ";
	   effect << " (" <<  "rle5 " <<  leg.getlj5()  << ") ";
	   effect << " (" <<  "rle6 " <<  leg.getlj6()  << ") ";
	}else if ( s == left_side ){
	   effect << " (" <<  "lle1 " <<  leg.getlj1() << ") ";
	   effect << " (" <<  "lle2 " <<  leg.getlj2()  << ") ";
	   effect << " (" <<  "lle3 " <<  leg.getlj3()  << ") ";
	   effect << " (" <<  "lle4 " <<  leg.getlj4()  << ") ";
	   effect << " (" <<  "lle5 " <<  leg.getlj5()  << ") ";
	   effect << " (" <<  "lle6 " <<  leg.getlj6()  << ") ";
	}
	return true;
}

bool AngularMotor::moveHead(float j1, float j2){
	effect <<  " (" << "he1 " << j1 << ") ";
	effect <<  " (" << "he2 " << j2 << ") ";
	return true;
}


void AngularMotor::clear(){
	effect.str("");
}

bool AngularMotor::allJointsOff(){
	effect.str("");
	moveArm(right_side, 0, 0, 0, 0);
	moveArm(left_side, 0, 0, 0, 0);
	moveLeg(right_side, 0, 0, 0, 0, 0, 0);
	moveLeg(left_side, 0, 0, 0, 0, 0, 0);
	moveHead(0, 0);
	return true;
}


bool AngularMotor::endOfAnglesLeg(float lj1, float lj2, float lj3, float lj4, float lj5, float lj6  ){
	
}

bool AngularMotor::endOfAnglesArm(float aj1, float aj2, float aj3, float aj4){

}

std::string AngularMotor::str(){
	return effect.str();
}

bool  AngularMotor::setInitialStandUpBack(){
	effect.str("");
	addvalue();
	moveArm(right_side, addraj1, addraj2, addraj3, addraj4);
	moveLeg(right_side, addrlj1, addrlj2, addrlj3, addrlj4, addrlj5, addrlj6);
	moveArm(left_side, addlaj1, addlaj2, addlaj3, addlaj4);
	moveLeg(left_side, addllj1, addllj2, addllj3, addllj4, addllj5, addllj6);
	return true;
}

void  AngularMotor::addvalue()
    {	
        addllj1=(0-WorldModel::instance().getHJoint(JID_LLEG_1).angle)/count;
        addllj2=(0-WorldModel::instance().getHJoint(JID_LLEG_2).angle)/count;
        addllj3=(3.75-WorldModel::instance().getHJoint(JID_LLEG_3).angle)/count;
        addllj4=(0-WorldModel::instance().getHJoint(JID_LLEG_4).angle)/count;
        addllj5=(-5.74-WorldModel::instance().getHJoint(JID_LLEG_5).angle)/count;
        addllj6=(0-WorldModel::instance().getHJoint(JID_LLEG_6).angle)/count;
        addrlj1=(0-WorldModel::instance().getHJoint(JID_RLEG_1).angle)/count;
        addrlj2=(0-WorldModel::instance().getHJoint(JID_RLEG_2).angle)/count;
        addrlj3=(3.75-WorldModel::instance().getHJoint(JID_RLEG_3).angle)/count;
        addrlj4=(0-WorldModel::instance().getHJoint(JID_RLEG_4).angle)/count;
        addrlj5=(-5.74-WorldModel::instance().getHJoint(JID_RLEG_5).angle)/count;
        addrlj6=(0-WorldModel::instance().getHJoint(JID_RLEG_6).angle)/count;
        addlaj1=(-70.15-WorldModel::instance().getHJoint(JID_LARM_1).angle)/count;
        addlaj2=(0-WorldModel::instance().getHJoint(JID_LARM_2).angle)/count;
        addlaj3=(0-WorldModel::instance().getHJoint(JID_LARM_3).angle)/count;
        addlaj4=(0-WorldModel::instance().getHJoint(JID_LARM_4).angle)/count;
        addraj1=(-70.15-WorldModel::instance().getHJoint(JID_RARM_1).angle)/count;
        addraj2=(0-WorldModel::instance().getHJoint(JID_RARM_2).angle)/count;
        addraj3=(0-WorldModel::instance().getHJoint(JID_RARM_3).angle)/count;
        addraj4=(0-WorldModel::instance().getHJoint(JID_RARM_4).angle)/count;
        count--;
	if (count<1)
		count = 66;
        }

void AngularMotor::printAngles(){
	cout << "Left Arm : "<< endl 
	     << "joint 1 = "  << WorldModel::instance().getHJoint(JID_LLEG_1).angle << endl
	     << "Joint 2 = "  << WorldModel::instance().getHJoint(JID_LLEG_2).angle << endl
	     << "Joint 3 = "  << WorldModel::instance().getHJoint(JID_LLEG_3).angle << endl
	     << "Joint 4 = "  << WorldModel::instance().getHJoint(JID_LLEG_4).angle << endl << endl
	     << "Right Arm : "<< endl
	     << "joint 1 = "  << WorldModel::instance().getHJoint(JID_RLEG_1).angle << endl
	     << "Joint 2 = "  << WorldModel::instance().getHJoint(JID_RLEG_2).angle << endl
	     << "Joint 3 = "  << WorldModel::instance().getHJoint(JID_RLEG_3).angle << endl
	     << "Joint 4 = "  << WorldModel::instance().getHJoint(JID_RLEG_4).angle << endl << endl
	     << "Left Leg : " << endl
	     << "joint 1 = "  << WorldModel::instance().getHJoint(JID_LLEG_1).angle << endl
	     << "Joint 2 = "  << WorldModel::instance().getHJoint(JID_LLEG_2).angle << endl
	     << "Joint 3 = "  << WorldModel::instance().getHJoint(JID_LLEG_3).angle << endl
	     << "Joint 4 = "  << WorldModel::instance().getHJoint(JID_LLEG_4).angle << endl
	     << "joint 5 = "  << WorldModel::instance().getHJoint(JID_LLEG_5).angle << endl
	     << "Joint 6 = "  << WorldModel::instance().getHJoint(JID_LLEG_6).angle << endl << endl
	     << "Rihgt Leg : " << endl
	     << "joint 1 = "  << WorldModel::instance().getHJoint(JID_RLEG_1).angle << endl
	     << "Joint 2 = "  << WorldModel::instance().getHJoint(JID_RLEG_2).angle << endl
	     << "Joint 3 = "  << WorldModel::instance().getHJoint(JID_RLEG_3).angle << endl
	     << "Joint 4 = "  << WorldModel::instance().getHJoint(JID_RLEG_4).angle << endl
	     << "joint 5 = "  << WorldModel::instance().getHJoint(JID_RLEG_5).angle << endl
	     << "Joint 6 = "  << WorldModel::instance().getHJoint(JID_RLEG_6).angle << endl << endl;
}

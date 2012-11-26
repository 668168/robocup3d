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

#ifndef ANGULARMOTOR_H
#define ANGULARMOTOR_H

#include <string>
#include <sstream>
#include <iostream>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include "arm.h"
#include "leg.h" 
#include "../WorldModel/WorldModel.h"



enum side{
	right_side = 0,
	left_side = 1
};

using namespace std;

//#include "AngularMotor.h"
class AngularMotor
{
public:
     AngularMotor();

    ~AngularMotor();

    static AngularMotor& instance();

    static const AngularMotor& i(){ return instance();}

    std::string stringify(float value);

    void add(std::string msg);

    void clear();

    void moveArm(side s, float aj1, float aj2, float aj3, float aj4 );

    bool moveArm(side s, Arm a);

    void moveLeg(side s, float lj1, float lj2, float lj3, float lj4, float lj5, float lj6);

    bool moveHead(float j1, float j2);

    bool moveLeg(side s, Leg l);

    bool endOfAnglesLeg(float lj1, float lj2, float lj3, float lj4, float lj5, float lj6  );

    bool endOfAnglesArm(float aj1, float aj2, float aj3, float aj4);

    bool allJointsOff();

    std::string  str();
    
    bool setInitialStandUpBack();
    
    void printAngles();
    


private:
   boost::shared_ptr <WorldModel> wm;
   stringstream  effect;
   Arm arm;
   Leg leg;
   float addllj1;
   float addllj2;
   float addllj3;
   float addllj4;
   float addllj5;
   float addllj6;
   float addrlj1;
   float addrlj2;
   float addrlj3;
   float addrlj4;
   float addrlj5;
   float addrlj6;
   float addlaj1;
   float addlaj2;
   float addlaj3;
   float addlaj4;
   float addraj1;
   float addraj2;
   float addraj3;
   float addraj4;
   bool  flag;
   int count;
   void addvalue();

};


#endif // ANGULARMOTOR_H

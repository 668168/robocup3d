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

#ifndef BHVBASICWALK_H
#define BHVBASICWALK_H

#include "../salt/vector.h"
#include "SoccerBehavior.h"

class BhvBasicWalk: public SoccerBehavior 
{
private:

//      bool             isOmnidirectional(float ang, float distance);

//      float            decSpeed         (float endSpeed, int dec);

     float          getDistance()const;

     float          getAngle()const;

     Vector2f        mTargetPos;

     static ESide    mWalkType;

     static float    mSpeed;

//      Vector2f        stopPos;
//      Vector2f        lookAt;
     bool            mIsToBall;
     bool            mIsChecking;

 //    float           calSpeed (float distance,bool isInc = true);

//      ESide           calWalkType(float angDeg, float distance);


     ESide           calType ();
     double          calAngle(const double& speed);
     double          calSpeed();
     void            manageSpeed(double* speed);

   //  void            reset();

public:

     BhvBasicWalk (bool isCheck):mIsToBall(true), mIsChecking(isCheck){};

     BhvBasicWalk(const Vector2f& target, const bool &isChek =true ):mTargetPos(target),mIsToBall(false),mIsChecking(isChek){}
     virtual bool            execute();


 };

#endif // BHVBASICWALK_H

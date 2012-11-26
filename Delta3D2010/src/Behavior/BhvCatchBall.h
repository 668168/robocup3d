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

#ifndef BHVCATCHBALL_H
#define BHVCATCHBALL_H

#include "SoccerBehavior.h"
#include "../Skills/Walk.h"
#include "../Effectors/Effectors.h"
#include "../Skills/Walk.h"
#include "../WorldModel/WorldModel.h"
#include "BhvBasicWalk.h"

class BhvCatchBall: public SoccerBehavior {

private:
   
    float               mSlowGain;
   
    salt::Matrix        mTorsoMatrix;

    salt::Matrix        mHoldFootMatrix;

    Vector3f mLeftPosition   ;
    
    Vector3f mCenterPosition ;
    
    Vector3f mRightPosition  ;
    
    Vector3f mTelorans       ;
    
    EGkHomePos homePosition;
    
    EGkHomePos getHomePosition();
    
    Vector3f BallPos()
    {
         
       Vector3f tmpballpos = Vector3f(WorldModel::instance().getBallPos().x()+WorldModel::instance().getMyPos().x(),
                                   WorldModel::instance().getBallPos().y()+WorldModel::instance().getMyPos().y(),
                                   WorldModel::instance().getBallPos().z()+WorldModel::instance().getMyPos().z()
                                  );
       return tmpballpos;
    }

public:

     BhvCatchBall();
     
     static BhvCatchBall& instance (                                            );
     
     virtual bool execute();

     void sitDown();
     
     void calculatePosition();
     
     bool isInHomePosition();
     
     void setBehavior();
     
     
     
     void getPrepareMatrix();
     
     void ApplyJVel(bool left);
     

 };

#endif // BHVCATCHBALL_H

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

#include "BhvBasicWalk.h"
#include <cmath>
using namespace salt;

ESide BhvBasicWalk::mWalkType = SIDE_NONE;
float BhvBasicWalk::mSpeed = MaxWalkSpeedForward;

bool BhvBasicWalk::execute()
{
   //     static const unsigned int stableCycle = 200 ;
    static WorldModel&  wm              = WorldModel::instance();
    static Walk&        walk            = Walk::instance();



//    float              distance        = getDistance();
    float               angGoal         = getAngle();
    static unsigned int startWalkCycle;
    static double       speed           = walk.getSpeed(); //return mspeed walk in walk class
    static double       maxTurnAviable  = walk.getTurnAngle();//angle of turn in walk
    static unsigned int lastRun         = wm.getCurrentCycle();
    double              turnAng         = 0.0;
    static ESide        type            = SIDE_FORWARD;
//    ESide               currentType     = type;

    if ( wm.getCurrentCycle() % 20 == 0 || ( lastRun+4 < (wm.getCurrentCycle() )))///select 4 for may be skiping time happen
    {
         speed          = calSpeed();
         manageSpeed (&speed);
         type           = calType();
         if (type == SIDE_BACKWARD) speed =MaxWalkSpeedBackward;
         maxTurnAviable = calAngle(speed);
    }
    if (mWalkType != type )
    {
        mWalkType = type;
        walk.setWalkPhase(Walk::PREPARE);
        walk.Execute(0.0,MinWalkSpeedForward,SIDE_FORWARD);
        Effectors::instance().setActionCommand();
        return true;
    }
    if ( lastRun >= (wm.getCurrentCycle() ))
        startWalkCycle = wm.getCurrentCycle();  /// walk reseted
    lastRun = wm.getCurrentCycle(); 
    cout<<endl<<"in before analize speed: "<<speed<<" maxTurnAviable: "<< maxTurnAviable <<" type: "<<type<<endl;
    double analizedSpeed = abs(speed);
    if ( type == SIDE_FORWARD)
    {
        analizedSpeed = speed + MinWalkSpeedForward ;
        if ( analizedSpeed < MinWalkSpeedForward ) analizedSpeed =MinWalkSpeedForward;///set speed in range
//         if ((( wm.getCurrentCycle() - startWalkCycle) < stableCycle)  &&
             //( analizedSpeed > 90.0f) ) analizedSpeed = 90.0f;/// no takeoff
        if ( Walk::instance().getPhase() != Walk::NORMAL_STEP && angGoal < 0.0f)
            turnAng = 0.0f;
        else
            turnAng = ( abs(angGoal) < maxTurnAviable)?angGoal: sign(angGoal) * maxTurnAviable;
    }
    else
    {
        analizedSpeed = MaxWalkSpeedBackward ;
        turnAng = ( abs(angGoal) < maxTurnAviable)?angGoal: sign(angGoal) * maxTurnAviable;
    }
    cout<<"in after analize speed: "<<analizedSpeed<<
          " turnAng: "<< turnAng <<" type: "<<type<<endl<<endl;
    if (type == SIDE_FORWARD || type == SIDE_BACKWARD)
    {
        walk.Execute( turnAng, analizedSpeed, type);
    }
    else
    {
        turnAng = 0.0f;
        analizedSpeed = 90.0f;
    }
    walk.Execute( turnAng, analizedSpeed, type);
    Effectors::instance().setActionCommand();
    return true;
}
void BhvBasicWalk::manageSpeed(double* speed)
{
    static const double speialDistance = 1.0f;
    static const double subDistance = 0.001;
    float               tmpSpeed       = abs(*speed);
    if ( mIsChecking)
    {
      if ( (getDistance() < speialDistance) )
         tmpSpeed = ((getDistance()-subDistance) / speialDistance ) * tmpSpeed;      
    }
    else if( mIsToBall)
    {
      tmpSpeed = 70;
    }
    *speed = sign(*speed) * tmpSpeed;

}

ESide BhvBasicWalk::calType()
{
    float               distance       = getDistance();
    float               angGoal        = getAngle();
    static const double speialDistance = 1.0f;
    double              angMin         = 70.0f,
                        angMax         = 90.0f,
                        angBackward    = 120.0f;

    if ( mWalkType == SIDE_RIGHT || mWalkType == SIDE_LEFT)
    {
        angMin = 40.0f;
        angMax = 100.0f;
    }
    if ( (distance < speialDistance) &&
         (abs(angGoal) > angMin) &&
         (abs(angGoal)  < angMax))
    {
         return (angGoal < 0.0 )? SIDE_RIGHT : SIDE_LEFT;
    }
    if ( mWalkType == SIDE_BACKWARD && distance < 1.0 ) angBackward = 70.0f;

//     if (abs (angGoal)> angBackward && distance < 2)
    return ( abs(angGoal) > angBackward  )? SIDE_BACKWARD: SIDE_FORWARD;

      //return SIDE_LEFT;
}

double BhvBasicWalk::calAngle(const double& speed)
{
    double x0 = speed - 5.0f;
    double x1 = x0 / MaxWalkTurn;
    return ( MaxWalkTurn - x1 );
}

///calculate walk speed
double BhvBasicWalk::calSpeed()
{
    float         angGoal       = getAngle();
    double  speed;
    /*if (abs(angGoal) > 90.0f && abs(angGoal) < 100.0f)
        angGoal = 90.0f;*/
    if (mWalkType == SIDE_FORWARD)
      speed = (cosDeg(abs(angGoal))* (MaxWalkSpeedForward - MinWalkSpeedForward));
    else
      speed = (cosDeg(abs(angGoal))* (MaxWalkSpeedBackward - MinWalkSpeedBackward));
      
    cout<<"angle for calculate speed is:"<<angGoal<<" -> "<<abs(angGoal)<<endl;
    return abs(speed);
}

float BhvBasicWalk::getDistance() const
{
      WorldModel& wm = WorldModel::instance();
      if ( mIsToBall )
      {
         cout<<"in BhvBasicWalk::getDistance: return distance :"<<wm.getPolarBallPos().distance<<endl;
         return wm.getPolarBallPos().distance;
      }
      else
      {
          Vector2f myPos(wm.getMyPos().x(),wm.getMyPos().y());
          cout<<"in BhvBasicWalk::getDistance: return distance :"<<(mTargetPos - myPos).Length()<<endl;
          return ((mTargetPos - myPos).Length());
      }
//          return wm.getObject(BALL).distance;
}


///give the angle of ball or other object to me
float BhvBasicWalk::getAngle() const
{
     WorldModel& wm = WorldModel::instance();
     if ( mIsToBall )
     {
         cout<<"in BhvBasicWalk::getAngle: return angle :"<<wm.getPolarBallPos().theta<<endl;
         return wm.getPolarBallPos().theta;
     }
     else
     {
         Vector2f myPos(wm.getMyPos().x(),wm.getMyPos().y());
         cout<<"in BhvBasicWalk::getAngle: return angle :"<<-(wm.getMyPos().z() -getVector2fAngleDeg (mTargetPos - myPos))<<endl;
	 return ( degNormalizeAngle( getVector2fAngleDeg (mTargetPos - myPos))- degNormalizeAngle( wm.getMyPos().z()));
         
     }
     //return WorldModel::i().getObject(BALL).theta;
}
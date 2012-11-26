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

#include "BhvDribble.h"
#include "../Skills/SuperKick.h"
#include "math.h"

EDribblePhase BhvDribble::mPhase;
int BhvDribble::mStartPhase;
bool BhvDribble::execute()
{
  WorldModel& wm      = WorldModel::instance();
  float       angBall = wm.getPolarBallPos().theta;

//      if ( mPhase != getPhase() && ! wm.isStable() )
//      {
//          Walk::instance().setWalkPhase(Walk::PREPARE);
//          Walk::instance().Execute(0.0,0.0,SIDE_FORWARD);
//          Effectors::instance().setActionCommand();
//          return true;
//      }

  mPhase = getPhase();
  
  cout<<"in BhvDribble::execute : Phase = "<<getPhase()<<endl;
  switch (mPhase)
  {
    case GO_TO_BALL:

      if(WorldModel::instance().getCurrentAction()!=ACT_KICK);
      {
	ResetTurnParam();
	BhvBasicWalk(calPoint()).execute();
      }
      break;
    case SETUP:
      if(WorldModel::instance().getCurrentAction()!=ACT_KICK);
      {
	SetupTurnParam();
	BhvBehindBallSetup(5*sign(angBall)).execute();//angBall
      }
      //             BhvBasicWalk(true).execute();
      break;
    case GO_TO_GOAL:
      
      //BhvBasicWalk(false).execute();
      if(WorldModel::instance().getCurrentAction()!=ACT_KICK)
      {
	ResetTurnParam();
	//BhvBasicWalk(calPoint()).execute();
	BhvBasicWalk(true).execute();/// is beter than befor
      }
    default:
      break;
  }
  return true;
}

Vector2f BhvDribble::calPoint()const
{
  static const float backOfBall = 0.09f;
  Line               line       = Line::makeLineFromTwoPoints ( mGoal , WorldModel::instance().getBallPos() );
  float              x          = WorldModel::instance().getConstBallPos().x() - backOfBall;
  float              y          = line.yGivenX(x);
  cout<<"in BhvDribble::calPoint : x = "<<x<<" y = "<<y<<endl;
  return Vector2f(x,y);
}

bool  BhvDribble::isAriveTo(const Vector2f& point )const
{
  static const float telorans = 0.1;
  Vector3f myPos = WorldModel::instance().getMyPos();
  float x = myPos.x();
  float y = myPos.y();
  bool ret= ((x > (point.x() - telorans)) && (x < (point.x() + telorans)) &&
             (y > (point.y() - telorans)) && (y < (point.y() + telorans)) );
  cout<<"in BhvDribble::isAriveTo :ariveto = "<<ret<<" posMe.x = "<<x<<" posMe.y = "<<y<<" point.x="<<point.x() <<" point.y="<<point.y()<<endl;
  return ret;
}

EDribblePhase BhvDribble::getPhase()const
{
    WorldModel&  wm  = WorldModel::instance();
    Line         lineMeToBall = Line::makeLineFromTwoPoints(wm.getBallPos(),wm.getMyPos());
    Vector2f     mypos(wm.getMyPos().x(),wm.getMyPos().y());
    Vector2f     targetPos(mGoal.x(),mGoal.y());
//     float        angGoal = getVector2fAngleDeg (targetPo);
    if ( (abs(lineMeToBall.yGivenX(9.0)) < 1.65f) && wm.getMyPos().x() < wm.getBallPos().x())
    {
        if (abs(wm.getPolarBallPos().theta) > 45.0f && wm.getPolarBallPos().distance < 0.3)
        {
            return SETUP;
        }
        mStartPhase = wm.getCurrentCycle();
        return GO_TO_GOAL;
    }
    return GO_TO_BALL;
//return SETUP;
}

double BhvDribble::minus(const float& num1, const float& num2)const
{
   return (num1 > num2)? num1 - num2 : num2 - num1;
}

void BhvDribble::SetupTurnParam()
{
  cout<<"SEtup Turn Param Executed";
    
    Trajectory::instance().Qf= 0.0;

    Trajectory::instance().Qb= 0.0;

    WalkParams::instance().Hao=0.01;
    WalkParams::instance().Tc=0.23;
    
    WalkParams::instance().Xsd          =  0.01f;  //max = 0.07
    WalkParams::instance().Xed          =  0.01f;  //max = 0.07
}

void BhvDribble::ResetTurnParam()
{
    
    Trajectory::instance().Qf= 0.2;

    Trajectory::instance().Qb= 0.2;

    WalkParams::instance().Hao=0.10;
    
    WalkParams::instance().Tc=0.2;

}
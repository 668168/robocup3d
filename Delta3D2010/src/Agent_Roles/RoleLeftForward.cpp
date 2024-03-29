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

#include "RoleLeftForward.h"

#include "../Behavior/BhvDribble.h"
#include "../Behavior/BhvBasicTurn.h"
#include <iomanip>

using namespace std;
const double nearConst = 1.0 ;///meter
void RoleLeftForward::execute() 
{
  
   WorldModel & wm = WorldModel::instance();
   if(wm.getPlayMode()==PM_BeforeKickOff)
     wm.setCurrentAction(ACT_STOP);
   
   
   
   if (  wm.isFellDown())  /// agar zamin khorde bodam
      wm.setCurrentAction(ACT_STANDUP);
   else if (SuperKick::instance().isKickDone() && wm.getCurrentAction() == ACT_KICK) ///agar dar mode kick bodim va kareman tamam shod
     wm.setCurrentAction(ACT_STOP);  
   else if (wm.isBallKickable() && wm.isForwardOpponentGoal()) /// agar mitavanim kick konim
   {
     if (wm.isStable() || wm.getCurrentAction() == ACT_KICK) /// agar stable bodim ya dar hal kick kardan bodim 
       wm.setCurrentAction(ACT_KICK);
     else   
       wm.setCurrentAction(ACT_STOP);
   }
   switch (wm.getCurrentAction() ) 
   {
     case ACT_WALK:
       doMove();
       break;
     case ACT_STANDUP:
       doStandUp();
       break;
     case ACT_KICK:
       doKick();
       break;
     case ACT_STOP:
       doStop();
       break;
     default:
       doMove();
   }
   
//    BhvBasicTurn(10).execute();
}

void RoleLeftForward::doKick()
{
    if(TS_LEFT== WorldModel::instance().getTeamSide())
        SuperKick::instance().execute(true);
    else if(TS_RIGHT==WorldModel::instance().getTeamSide())
     SuperKick::instance().execute(false);
   if (SuperKick::instance().isKickDone())
   {
     WorldModel::instance().setCurrentAction(ACT_STOP);
     SuperKick::instance().setKickDone(false);
   }   
   std::cout<<"RoleLeftForward doKick execute"<<std::endl;   
};
 
void RoleLeftForward::doMove()
{
    BhvFocusBall().execute();
    WorldModel& wm = WorldModel::instance();
   
    wm.setCurrentAction(ACT_WALK);
   
    
     
//     else
     if( Strategy::instance().isInRange() )
    {   
      std::cout<<"in doMove player near: "<<wm.isPlayerNearBall(OPPONENT_SET,nearConst)<<" || in penalti :"<<Strategy::instance().isInOppPenaltyArea(wm.getBallPos()) <<" && forwardGoal: "<<wm.isForwardOpponentGoal()<<" true is:<<"<<true<<std::endl;
      EFieldArea area = wm.getArea(wm.getBallPos());
      bool isCorner = (area == FORWARD_LEFT || area == FORWARD_RIGHT);
      if ((wm.isPlayerNearBall(OPPONENT_SET,nearConst) || Strategy::instance().isInOppPenaltyArea(wm.getBallPos()) || isCorner )&& wm.isForwardOpponentGoal())
      {
	BhvBasicWalk(false).execute();
      }
      else
      {
	BhvDribble( Vector3f(9.0f,0.0f,0.0f) ).execute();
      }
     
    }
     else if(!Strategy::instance().isInHomePos() )
         Strategy::instance().gotoStrategyPos();
     
     else if(Strategy::instance().isInHomePos() && abs( WorldModel::instance().getPolarBallPos().theta)<10 )
        doStop();
     else  
       BhvBasicTurn(10*sign(WorldModel::instance().getPolarBallPos().theta)).execute();//angBall
    
          
};

void RoleLeftForward::doStandUp()
{
    std::cout<<"RoleLeftForward doStandup execute"<<std::endl;
    WorldModel::instance().setCurrentAction(ACT_STANDUP);
    BhvBasicStandup().execute();
    if(!WorldModel::instance().isFellDown() )//StandUp::instance().isStandUpFinished())
      WorldModel::instance().setCurrentAction(ACT_STOP);
};

void RoleLeftForward::doStop()
{
//     BhvFocusBall().execute();
    std::cout<<"RoleLeftForward doStop execute"<<std::endl;
    WorldModel& wm   = WorldModel::instance();
    Walk&       walk = Walk::instance();

    if (walk.IsPrepareDone() && wm.isStable())
    {
        cout <<"RoleLeftForward::doStop : 'prepare walk done' "<<endl;
        //if(WorldModel::instance().getCurrentAction()!=ACT_KICK)
        wm.setCurrentAction(ACT_WALK);
    }
    else
    {
        cout <<"RoleLeftForward::doStop : 'prepare walk done' "<<endl;
        wm.setCurrentAction(ACT_STOP);
        walk.setWalkPhase(Walk::PREPARE);
        walk.Execute(0.0,0.0,SIDE_FORWARD);
        Effectors::instance().setActionCommand();
    }
}
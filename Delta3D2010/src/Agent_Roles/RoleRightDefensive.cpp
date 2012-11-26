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

#include "RoleRightDefensive.h"

#include "../Behavior/BhvDribble.h"
#include "../Behavior/BhvBasicTurn.h"
#include <iomanip>

using namespace std;
const double nearConst = 1.0 ;///meter
void RoleRightDefensive::execute() 
{
  WorldModel & wm = WorldModel::instance();
   if(wm.getPlayMode()==PM_BeforeKickOff)
     wm.setCurrentAction(ACT_STOP);
   
   if (  WorldModel::i().isFellDown())  /// agar zamin khorde bodam
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
}

void RoleRightDefensive::doKick()
{
   if(TS_LEFT== WorldModel::instance().getTeamSide())
        SuperKick::instance().execute(false);
    else if(TS_RIGHT==WorldModel::instance().getTeamSide())
     SuperKick::instance().execute(true);
   if (SuperKick::instance().isKickDone())
   {
     WorldModel::instance().setCurrentAction(ACT_STOP);
     SuperKick::instance().setKickDone(false);
   }   
   std::cout<<"RoleRightDefensive doKick execute"<<std::endl;   
};

void RoleRightDefensive::doMove()
{
    BhvFocusBall().execute();
    WorldModel& wm = WorldModel::instance();
    wm.setCurrentAction(ACT_WALK);
    
    
    if( Strategy::instance().isInRange() )
    {   
    
      
       if (wm.isPlayerNearBall(OPPONENT_SET,nearConst))
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
      BhvBasicTurn(15*sign(WorldModel::instance().getPolarBallPos().theta)).execute();//angBall
};

void RoleRightDefensive::doStandUp()
{
    std::cout<<"RoleRightDefensive doStandup execute"<<std::endl;
    WorldModel::instance().setCurrentAction(ACT_STANDUP);
    BhvBasicStandup().execute();
    if(StandUp::instance().isStandUpFinished())
      WorldModel::instance().setCurrentAction(ACT_STOP);
};

void RoleRightDefensive::doStop()
{
//     BhvFocusBall().execute();
    std::cout<<"RoleRightDefensive doStop execute"<<std::endl;
    WorldModel& wm   = WorldModel::instance();
    Walk&       walk = Walk::instance();

    if (walk.IsPrepareDone() && wm.isStable())
    {
        cout <<"RoleRightDefensive::doStop : 'prepare walk done' "<<endl;
        //if(WorldModel::instance().getCurrentAction()!=ACT_KICK)
        wm.setCurrentAction(ACT_WALK);
    }
    else
    {
        cout <<"RoleRightDefensive::doStop : 'prepare walk done' "<<endl;
        wm.setCurrentAction(ACT_STOP);
        walk.setWalkPhase(Walk::PREPARE);
        walk.Execute(0.0,0.0,SIDE_FORWARD);
        Effectors::instance().setActionCommand();
    }
}
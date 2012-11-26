//
// C++ Implementation: TeamPlayer
//
// Description: 
//
//
// Author: delta3d team 2009 <deltateams2009@gmail.com>, (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//


#include "TeamPlayer.h"
#include "../Strategy/Strategy.h"

TeamPlayer::TeamPlayer()
{
}

TeamPlayer::~TeamPlayer()
{
}

TeamPlayer& TeamPlayer::instance()
{
    static TeamPlayer sTeamPlayer;
    return sTeamPlayer;
}

void TeamPlayer::doStop()
{
  WorldModel& wm   = WorldModel::instance();
    Walk&       walk = Walk::instance();
  
        wm.setCurrentAction(ACT_STOP);
        walk.setWalkPhase(Walk::PREPARE);
        walk.Execute(0.0,0.0,SIDE_FORWARD);
        Effectors::instance().setActionCommand();
    
}


/** the paly-on mode, mainly loop */
void TeamPlayer::playPlayOn()
{
    Strategy::instance().executeRole();
}

/** before kick off */
void TeamPlayer::playBeforeKickOff()
{
      
    playPlayOn();
}

/** kick off */
void TeamPlayer::playOurKickOff()
{
    playPlayOn();
}

void TeamPlayer::playOppKickOff()
{
  doStop();  
}


/** kick in */
void TeamPlayer::playOurKickIn()
{
    playPlayOn();
}


void TeamPlayer::playOppKickIn()
{
    doStop();  
}

/** corner kick */
void TeamPlayer::playOurCornerKick()
{
    playPlayOn();
}


void TeamPlayer::playOppCornerKick()
{
    doStop();  
}

/** goal kick */
void TeamPlayer::playOurGoalKick()
{
    playPlayOn();
}


void TeamPlayer::playOppGoalKick()
{
     doStop();  
}


/** offside */
void TeamPlayer::playOurOffSide()
{
     playPlayOn();
}


void TeamPlayer::playOppOffSide()
{
       doStop();  
}


/** game over */
void TeamPlayer::playGameOver()
{
    //playPlayOn();
}


/** Gooooooooooooooooal */
void TeamPlayer::playOurGoal()
{
    playPlayOn();
}


void TeamPlayer::playOppGoal()
{

  doStop();  
}


/** free kick */
void TeamPlayer::playOurFreeKick()
{
   playPlayOn();
}

    
void TeamPlayer::playOppFreeKick()
{
   doStop();  
}

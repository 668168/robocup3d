/*****************************************************************************************
 *                                      SEU-3D
 *                     -------------------------------------------------
 * Copyright (c) 2005, Yuan XU<xychn15@yahoo.com.cn>,Chang'e SHI<evelinesce@yahoo.com.cn>
 * Copyright (c) 2006, Yuan XU<xuyuan.cn@gmail.com>,Chunlu JIANG<JamAceWatermelon@gmail.com>
 * Southeast University ,China
 * All rights reserved.
 *
 * Additionally,this program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 ****************************************************************************************/

 
#include "BasicPlayer.h"
#include "Formation.h"

#ifdef ENABLE_LOG
extern FileLogger msgLog;
#endif

BasicPlayer::BasicPlayer()
{
#ifdef JOYSTICK
	isJoystickLive = false;
#endif
}

BasicPlayer::~BasicPlayer()
{
#ifdef JOYSTICK
	if ( isJoystickLive )
	{
		reomveJoystick();
	}
#endif
}

void BasicPlayer::playMatch()
{
#ifdef JOYSTICK
	if ( FM->getMyType() == PT_JOYSTICK )
	{
		joystickPlay();
	}
	else
	{
#endif
#ifdef TRAINING_MODE
		playTraining();
#else
	GL_PRINT("PlayMode","PM:%d",WM->getPlayMode() );
		switch ( WM->getPlayMode() )
        	{
        	case PM_BeforeKickOff :
				playBeforeKickOff();
            	break;

        	case PM_KickOff_Left :
        	case PM_KickOff_Right :
            	playKickOff();
            	break;

        	case PM_PlayOn :
				playPlayOn();
            	break;

        	case PM_KickIn_Left :
        	case PM_KickIn_Right :
            	playKickIn();
            	break;
		
			case PM_CORNER_KICK_LEFT:
			case PM_CORNER_KICK_RIGHT:
				playCornerKick();
				break;
		
			case PM_GOAL_KICK_LEFT:
			case PM_GOAL_KICK_RIGHT:		
				playGoalKick();
				break;

			case PM_OFFSIDE_LEFT:
			case PM_OFFSIDE_RIGHT:
				playOffsideKick();
				break;
			
        	default:
				playPlayOn();
            	break;
        	}
#endif /* TRAINING_MODE */
#ifdef JOYSTICK
	}
#endif /* JOYSTICK */
}

void BasicPlayer::playBeforeKickOff()
{	
	WM->setBallBeforeKickOff();
	
	
	Vector3f posInit = FM->getInitPosition( WM->getMyNum() );
	Action action;
	action.setTime(  WM->getRealTime()+10);
	action.setDriveForce( Vector3f(1,0,0) );
	action.setBeam(posInit);
	putActionInQueue( action );
}

void BasicPlayer::playKickOff()
{
	TTeamIndex ti = WM->getTeamIndex();
    if (ti == TI_NONE)
        {
            return;
        }

    TPlayMode myKickOff = ( WM->getTeamIndex() == TI_LEFT) ?
        PM_KickOff_Left : PM_KickOff_Right;

    if ( WM->getPlayMode() == myKickOff)
        {
            playMyKickOff();
        } 
		else
        {
            playTheirKickOff();
        }
}

void BasicPlayer::playMyKickOff()
{
	// for now, just the same as playOn
    playPlayOn();
}

void BasicPlayer::playTheirKickOff()
{
	WM->setBallBeforeKickOff();
	
	Vector3f posInit = FM->getInitPosition( WM->getMyNum() );
	if ( WM->getMyNum() ==10 )
	{
		posInit.x()-=12;
	}
	
	putActionInQueue( SKILL->runTo(posInit,Vector3f(0,0,0)));
}

void BasicPlayer::playPlayOn()
{
	Action act;
	if ( WM->isFastestOur() )
	{
		act = SKILL->interceptBall();
	}
	else
	{
		act = SKILL->runStrategicPos();
	}
	
	if ( WM->isKickable() 
		&& WM->getMyGlobalPos()[0] < WM->getBallGlobalPos()[0] - 0.05 )
	{
		float kickAngle =  50;
		if ( WM->getBallGlobalPos()[0] > 35 )
			kickAngle = 0;
		act.setKick( kickAngle, 100 );
		act.setTime( WM->getRealTime() +5 );
	}
	
	act.setTime(  WM->getRealTime()+10);
	putActionInQueue( act );
	
}
    
void BasicPlayer::playKickIn()
{
	TTeamIndex ti = WM->getTeamIndex();
    if (ti == TI_NONE)
        {
            return;
        }

    TPlayMode myKickIn = ( ti == TI_LEFT) ?
        PM_KickIn_Left : PM_KickIn_Right;

    if ( WM->getPlayMode() == myKickIn )
    {
        playMyKickIn();
    } 
	else
    {
        playTheirKickIn();
    }
}
    
void BasicPlayer::playMyKickIn()
{
    if ( WM->isFastestOur() )
	{
		if ( abs(WM->getMyGlobalPos().y()) < abs(WM->getBallGlobalPos().y()) )
		{
			int side = sign(WM->getBallGlobalPos().y());
			Vector3f posOut = WM->getBallGlobalPos()+Vector3f(0,side*2,0);
			while ( isThreePointOneLine(WM->getMyGlobalPos(),WM->getBallGlobalPos(),posOut,20) )
			{
				posOut.x()--;
			}
			putActionInQueue( SKILL->runTo(posOut,Vector3f(0,0,0)) );
		}
		else
		{
			playPlayOn();
		}
	}
	else
	{
		putActionInQueue( SKILL->runStrategicPos() );
	}
}
    
void BasicPlayer::playTheirKickIn()
{
	// do nothing, just runStrategicPos
	putActionInQueue( SKILL->runStrategicPos() );
}
	
void BasicPlayer::playCornerKick()
{
	TTeamIndex ti = WM->getTeamIndex();
    if (ti == TI_NONE)
        {
            return;
        }

    TPlayMode myCornerKick = ( ti == TI_LEFT) ?
        PM_CORNER_KICK_LEFT : PM_CORNER_KICK_RIGHT;

    if ( WM->getPlayMode() == myCornerKick)
        {
            playMyCornerKick();
        } 
	else
        {
            playTheirCornerKick();
        }
}
	
void BasicPlayer::playMyCornerKick()
{
	if ( WM->isFastestOur() )
	{
		if ( abs(WM->getMyGlobalPos().y()) < abs(WM->getBallGlobalPos().y()) 
			|| WM->getMyGlobalPos().x() < WM->getBallGlobalPos().x()
			)
		{
			int side = sign(WM->getBallGlobalPos().y());
			Vector3f posOut = WM->getBallGlobalPos()+Vector3f(2,side*2,0);
			while ( isThreePointOneLine(WM->getMyGlobalPos(),WM->getBallGlobalPos(),posOut,20) )
			{
				posOut.x()++;
			}
			putActionInQueue( SKILL->runTo(posOut,Vector3f(0,0,0)) );
		}
		else
		{
			playPlayOn();
		}
	}
	else
	{
		putActionInQueue( SKILL->runStrategicPos() );
	}
}
	
void BasicPlayer::playTheirCornerKick()
{
	// do nothing, just runStrategicPos
	putActionInQueue( SKILL->runStrategicPos() );
}
	
void BasicPlayer::playGoalKick()
{
	TTeamIndex ti = WM->getTeamIndex();
    if (ti == TI_NONE)
        {
            return;
        }

    TPlayMode myGoalKick = ( ti == TI_LEFT) ?
        PM_GOAL_KICK_LEFT : PM_GOAL_KICK_RIGHT;

    if ( WM->getPlayMode() == myGoalKick)
        {
            playMyGoalKick();
        } 
	else
        {
            playTheirGoalKick();
        }
}
	
void BasicPlayer::playMyGoalKick()
{
	if ( FM->getMyType() == PT_GOALKEEPER )
	{
		putActionInQueue( SKILL->kickBetween(WM->getOppGoalLeft(),WM->getOppGoalRight(),max_kick_force,25) );
	}
	else
	{
		putActionInQueue( SKILL->runStrategicPos(WM->getBallGlobalPos()+Vector3f(20,0,0)) );
	}
}

void BasicPlayer::playTheirGoalKick()
{
	// do nothing, just runStrategicPos
	Vector3f posBias(-10,0,0);
	if ( FM->getMyType() > PT_MIDFIELDER_SWEEPER )
		posBias.x()-=10;
	if ( FM->getMyType() > PT_MIDFIELDER_WING )
		posBias.x()-=10;
	putActionInQueue( SKILL->runStrategicPos(WM->getBallGlobalPos()+posBias) );
}

void BasicPlayer::playOffsideKick()
{
	TTeamIndex ti = WM->getTeamIndex();
    if (ti == TI_NONE)
        {
            return;
        }

    TPlayMode myOffsideKick = ( ti == TI_LEFT) ?
        PM_OFFSIDE_LEFT : PM_OFFSIDE_RIGHT;

    if ( WM->getPlayMode() == myOffsideKick)
        {
            playMyOffsideKick();
        } 
	else
        {
            playTheirOffsideKick();
        }
}

void BasicPlayer::playMyOffsideKick()
{
	// just as playOn
	playPlayOn();
}

void BasicPlayer::playTheirOffsideKick()
{
	// do nothing, just runStrategicPos
	putActionInQueue( SKILL->runStrategicPos() );
}

#ifdef JOYSTICK
//////////// Joystick Player //////////////////
bool BasicPlayer::setupJoystick()
{
	//Initialisation of Joystick
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) < 0)
	{
		LOGERR( "Couldn't initialize SDL:");
		cerr<<SDL_GetError()<<"\n";
		return false;
	}
	SDL_JoystickEventState(SDL_ENABLE);
	joystick = SDL_JoystickOpen(0);
	return true;
}

void BasicPlayer::reomveJoystick()
{
	//Closing Joystick subsystem
	SDL_JoystickClose(joystick);
	SDL_QuitSubSystem(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK);
}

void BasicPlayer::joystickPlay()
{
	if ( !isJoystickLive )
	{
		isJoystickLive = setupJoystick();
		if ( !isJoystickLive ) exit(1);
	}
	
	// initialize moving Vectors
	int move_x;
	int move_y;
	int move_lr;
	int move_ud;
	
	// event loop
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		//axis aligned movements of agent (all Events tested on BTP-C036)
			case SDL_JOYAXISMOTION:
				switch(event.jaxis.axis){
					// slow but precise move left-right
					case 0:
					move_x= SDL_JoystickGetAxis(joystick,0);
		            move_lr= move_x/500;
		            drive(Vector3f(move_lr,0,0));
					cout<<"axis 0\n";
	                break;
	 
		            // slow but precise move up-down
		            case 1:
	                move_y= SDL_JoystickGetAxis(joystick,1);
	                move_ud= -(move_y/500);
	                drive(Vector3f(0,move_ud,0));
					cout<<"axis 1\n";
	                break;
                    // fast but unprecise move up-down
                    case 2:
					move_y= SDL_JoystickGetAxis(joystick,2);
					move_ud= -(move_y/100);
					drive(Vector3f(0,move_ud,0));
					cout<<"axis 2\n";
					break;
					// fast but unprecise move left-right
	                case 3:
					move_x= SDL_JoystickGetAxis(joystick,3);
					move_lr= move_x/100;
					drive(Vector3f(move_lr,0,0));
					cout<<"axis 3\n";
					break;
 
                    default:
						drive(Vector3f(0,0,0));
                          cout<< "axis motion default\n";
                          break;
                          }
             break;

			// events which occur if certain buttons are pressed
			case SDL_JOYBUTTONDOWN:
				switch(event.jbutton.button)
				{
					//low kick
					case 2:
					kick(90,20);
					LOG( 99,"low kick");
					break;
					
					//normal kick
					case 3:
					kick(90,50);
					LOG( 99,"normal kick");
					break;

					//hard kick
					case 5:
					kick(90,70);
					LOG( 99,"hard kick");
					break;
					
					//jumping; is not functional yet
					/* case 0:
					drive(Vector3f(0,0,10));
					break;*/
					default:
					LOG( 99,"kick default");
					break;
				}
					
					break;
					
					default:
						cout << "event default\n";
					break;
		}
	}
}
#endif //JOYSTICK

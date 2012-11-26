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

 
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::playPlayOn()
{
	
	int num = WM->getMyNum();
	PlayerType myType = FM->getPlayerType(num);
	
	switch ( myType )
	{
		case PT_GOALKEEPER:
			goaliePlayOn();
			break;
		
		case PT_DEFENDER_CENTRAL:
		case PT_DEFENDER_SWEEPER:
		case PT_DEFENDER_WING:
			defenderPlayOn();
			break;
		
		case PT_MIDFIELDER_SWEEPER:
			midfielderSweeperPlayOn();
			break;
		
		case PT_MIDFIELDER_CENTER:
		case PT_MIDFIELDER_WING:
			midfielderAttackPlayOn();
			break;
		
		case PT_ATTACKER_CENTRAL:
		case PT_ATTACKER_WING:
			attackerPlayOn();
			break;
		
		default:
			defaultPlayOn();
			break;
	}

	
}

void Player::goaliePlayOn()
{
		//Rectangle dangerArea(WM->getOurBaseLine(),half_penalty_width,WM->getOurBaseLine()+6.0f,-half_penalty_width);

	if ( WM->isFastestOur())//||dangerArea[WM->getBallGlobalPos()] )
	{
		//if()
		GL_PRINT("goalie","fastest");
		putActionInQueue(SKILL->clearBall());
		//putActionInQueue( SKILL->defendGoal() );
		//GL_PRINT("test","defendGoal");
	}
	else
	{
		GL_PRINT("goalie","runStrategicPos");
		putActionInQueue( SKILL->defendGoal() );
		//putActionInQueue(SKILL->clearBall());
		
	}
}

void Player::defenderPlayOn()
{
	//defaultPlayOn();
	//testSkill();
	Rectangle dangerArea(WM->getOurBaseLine(),2*half_penalty_width,WM->getOurBaseLine()+17,-2*half_penalty_width);
	Num teammateNum=4;
	if(WM->getInterceptBallPos().y()>0) teammateNum=5;	
	if ( WM->isFastestOur())
	{			
		if(dangerArea[WM->getInterceptBallPos()]||dangerArea[WM->getBallGlobalPos()])
 		{
			
				if(WM->getMyFreedom()>5)
				{
					putActionInQueue(SKILL->pass(teammateNum));	
				}					
				GL_PRINT("test","clearBall");
				putActionInQueue(SKILL->clearBall(teammateNum));
			
		}
		else 
		{
			Rectangle shootArea(WM->getOppBaseLine()-13.0f,2*half_penalty_width,WM->getOppBaseLine(),-2*half_penalty_width);
	    	if(shootArea[WM->getInterceptBallPos()]||shootArea[WM->getBallGlobalPos()])
			{
				GL_PRINT("test","shoot");
				if(WM->getMyGlobalPos().y()<-2)
				{	
					putActionInQueue(SKILL->kickTo(WM->getOppGoalRight(),100,0,20));
				}
				else if(WM->getMyGlobalPos().y()<2)
				{
					putActionInQueue(SKILL->kickTo(WM->getOppGoalCenter(),100,0,20));
				}
				else
				{
					putActionInQueue(SKILL->kickTo(WM->getOppGoalLeft(),100,0,20));
				}
			}
			else if(WM->getMyFreedom()>-3)
			{
					putActionInQueue(SKILL->dribble(Vector3f(20,0,0)));
			}
			else
			{
				/*if(WM->getTeammateGlobalPos(teammateNum).x()>10)
				{
					putActionInQueue(SKILL->directPass(teammateNum));
				}
				else
				{
					putActionInQueue(SKILL->pass(teammateNum));	
				}*/
				putActionInQueue(SKILL->pass(teammateNum));
			}
     	}
	}
	else
	{
		GL_PRINT("test","runStrategicPos");
		/*if(WM->getMyNum()==2)
		putActionInQueue(SKILL->dashTo((WM->getBallGlobalPos()+WM->getOurGoalCenter())/2));
		else*/
			putActionInQueue(SKILL->runStrategicPos());
		
	}
}
	//test pass
	/*teammateNum=2;
	if(WM->getMyNum()==2) teammateNum=3;
	if(WM->isFastestOur())
	{
		putActionInQueue(SKILL->safePass(teammateNum));
	}
	else
	{
		putActionInQueue(SKILL->runStrategicPos());
	}*/

void Player::midfielderSweeperPlayOn()
{
	defenderPlayOn();
	//testSkill();
}

void Player::midfielderAttackPlayOn()
{
	//testSkill();
	attackerPlayOn();
}

void Player::attackerPlayOn()
{
	//defaultPlayOn();
	int teammateNum=4;
	if(WM->getMyNum()==4) {teammateNum=5;}
	Rectangle shootArea(WM->getOppBaseLine()-13.0f,1.9*half_penalty_width,WM->getOppBaseLine(),-1.9*half_penalty_width);
	Rectangle sideArea1(13.0f,15.0f,WM->getOppBaseLine(),9.5f);
	Rectangle sideArea2(13.0f,-9.5f,WM->getOppBaseLine(),-15.0f);

	if(WM->isFastestOur())
		
	    if(shootArea[WM->getInterceptBallPos()]||shootArea[WM->getBallGlobalPos()])
		{
			GL_PRINT("test","shoot");
			if(WM->getMyGlobalPos().y()<0)
			{
				putActionInQueue(SKILL->kickTo(WM->getOppGoalRight(),100,0,15));
			}
			else
			{
				putActionInQueue(SKILL->kickTo(WM->getOppGoalLeft(),100,0,15));
			}
		}
		else 
			if(WM->getMyFreedom()>0)
			{
				if(sideArea1[WM->getInterceptBallPos()]||sideArea2[WM->getInterceptBallPos()])
				{
					/*if(WM->getMyGlobalPos().y()<0)
					{
						putActionInQueue(SKILL->kickTo(WM->getOppGoalRight(),100,40,15));
					}
					else
					{
						putActionInQueue(SKILL->kickTo(WM->getOppGoalLeft(),100,40,15));
					}*/
					putActionInQueue(SKILL->kickBetween(WM->getOppGoalLeft(),WM->getOppGoalRight(),100,30));
				}
				else
				{
					putActionInQueue(SKILL->dribble(Vector3f(20,0,0)));
				}
			}
			else
			{
				/*if(WM->getTeammateGlobalPos(teammateNum).x()>10)
				{
					putActionInQueue(SKILL->directPass(teammateNum));
				}
				else
				{
					putActionInQueue(SKILL->pass(teammateNum));	
				}*/
				putActionInQueue(SKILL->pass(teammateNum));
			}
     	
	else
	{
		GL_PRINT("test","runStrategicPos");
		putActionInQueue(SKILL->runStrategicPos());
	}
	//testSkill();
}

void Player::defaultPlayOn()
{
	if ( WM->isFastestOur() )
	{
		GL_PRINT("test","fastest");
		putActionInQueue( SKILL->kickBetween(WM->getOppGoalLeft(),WM->getOppGoalRight(),max_kick_force,25) );
	}
	else
	{
		GL_PRINT("test","runStrategicPos");
		putActionInQueue( SKILL->runStrategicPos() );
	}
}

//////////////////////////// TEST ////////////////////////////
void Player::testIntercept()
{
}

void Player::testTurnCycle()
{
}

void Player::testSkill()
{
	if ( WM->isFastestOur() )
	{
		GL_PRINT("test","fastest");
		putActionInQueue( SKILL->dribble(WM->getOppGoalLeft()));//WM->getOppGoalRight(),max_kick_force,25) );
	}
	else
	{
		GL_PRINT("test","runStrategicPos");
		putActionInQueue( SKILL->runStrategicPos() );
	}
}

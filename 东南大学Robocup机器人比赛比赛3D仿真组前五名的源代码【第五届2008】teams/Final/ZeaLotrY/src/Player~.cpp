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
		Rectangle dangerArea(WM->getOurBaseLine(),half_penalty_width,WM->getOurBaseLine()+13,-half_penalty_width);

	if ( WM->isFastestOur()||dangerArea[WM->getBallGlobalPos()] )
	{
		GL_PRINT("goalie","fastest");
		putActionInQueue(SKILL->clearBall());
		GL_PRINT("test","defendGoal");
	}
	else
	{
		GL_PRINT("goalie","runStrategicPos");
		putActionInQueue( SKILL->defendGoal() );
	}
}

void Player::defenderPlayOn()
{
	//defaultPlayOn();
	//testSkill();
	Rectangle dangerArea(WM->getOurBaseLine(),half_penalty_width,WM->getOurBaseLine()+10,-half_penalty_width);
	Num teammateNum=2;
	if(WM->getInterceptBallPos().y()>0) teammateNum=3;	
	if ( WM->isFastestOur()||(WM->isFastestMyType()&&(WM->getMyFreedom()>5.0f||dangerArea[WM->getInterceptBallPos()]||dangerArea[WM->getBallGlobalPos()])) )
	{
		GL_PRINT("test","action");
		if(WM->getMyFreedom()>5.0f)
		{
		GL_PRINT("test","pass");
		putActionInQueue( SKILL->fastPass(4));
		}
		else
		{
			GL_PRINT("test","clearBall");
			putActionInQueue(SKILL->clearBall(teammateNum));
		}
	}
	else
	{
		GL_PRINT("test","runStrategicPos");
		putActionInQueue( SKILL->runStrategicPos() );
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
}

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
	if(WM->getMyNum()==4) teammateNum=5;
	Rectangle shootArea(WM->getOppBaseLine()-15.0f,1.5*half_penalty_width,WM->getOppBaseLine(),-1.5*half_penalty_width);
	if(WM->isFastestOur())//||(WM->isFastestMyType()&&(abs(WM->getBallGlobalPos().x())<0.5f&&abs(WM->getBallGlobalPos().y())<0.5f)))
	{
		/*if(WM->isSpaceAhead()&&!(shootArea[WM->getInterceptBallPos()]||shootArea[WM->getMyGlobalPos()]))
		{
			putActionInQueue(SKILL->dribble(WM->getOppGoalCenter()));
		}   */
	    if(shootArea[WM->getInterceptBallPos()]||shootArea[WM->getBallGlobalPos()])
		{
			GL_PRINT("test","shoot");
			putActionInQueue(SKILL->kickTo(WM->getOppGoalCenter(),100,0,20));
		}
     	else if(WM->getMyFreedom()<0)
		{	
			putActionInQueue(SKILL->clearBall());
		}
		else
		{
			if(WM->getBallGlobalPos().x()>(WM->getOppBaseLine()-15))
			{
				putActionInQueue(SKILL->directPass(2));
			}
			AngDeg angLeft=getVector3fHorizontalAng(WM->getOppGoalLeft()-WM->getBallGlobalPos());
			AngDeg angRight=getVector3fHorizontalAng(WM->getOppGoalRight()-WM->getBallGlobalPos());
			if(WM->getTeammateGlobalPos(teammateNum).x()>WM->getMyGlobalPos().x()||(WM->getBallGlobalPos().x()>(WM->getOppBaseLine()-13)&&abs(WM->getBallGlobalPos().y())>8&&WM->getMyFreedom()<8)||(WM->getBallGlobalPos().x()>(WM->getOppBaseLine()-10)&&abs(normalizeAngle(angLeft-angRight))<30))
			{
				/*if(WM->getTeammateGlobalPos(teammateNum).x()<12)
				{
					putActionInQueue(SKILL->fastPass(teammateNum));
				}
				else
				{
					putActionInQueue(SKILL->directPass(teammateNum));
				}*/
				putActionInQueue(SKILL->pass(teammateNum));
			}
			
			//if(WM->isSpaceAhead())
			else
			{
				Vector3f goal(15,0,0);
				GL_PRINT("test","dribble");
				putActionInQueue(SKILL->dribble(goal));
			}
		
			/*else 
			{
				if(WM->getMyNum()==5)
				{
					GL_PRINT("test","fastpass");
					putActionInQueue(SKILL->pass(4));
				}
				else
				{
					putActionInQueue(SKILL->pass(5));
				}
			}*/
		}
	}
		/*else if(WM->getMyNum()==5) 
		{	//if(WM->isSpaceAhead(WM->getTeammateGlobalPos(9)))
			putActionInQueue(SKILL->pass(4));
		}	//else putActionInQueue(SKILL->pass(9));
		else putActionInQueue(SKILL->pass(1));
		*/
	
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

#include "decision.h"
#include <sstream>
#include <string>
#include <iostream>

#include "acthandle.h"

#include "timer.h"
#include "worldmodel.h"
#include "robot.h"

extern Timer timer;
extern ActHandle ACT;
extern WorldModel wm;
extern Robot robot;


bool Decision::FreeMan_DO()
{
    static bool bBeamOver = false;
	
	if (wm.IsBeforeKickOff())
	{
		Vector v(-2,0,0);
		if (wm.GetUnum() == 1)
				v = Vector(-2,1,0);
		else if (wm.GetUnum() == 2)
				v = Vector(-2,-1,0);
		else if (wm.GetUnum() == 3)
				v = Vector(-2.5,0.5,0);
		else if (wm.GetUnum() == 4)
				v = Vector(-2.5,-0.5,0);
		else if (wm.GetUnum() == 5)
				v = Vector(-3,0,0);
		else if (wm.GetUnum() == 6)
				v = Vector(-3,1.5,0);
		else if (wm.GetUnum() == 7)
				v = Vector(-3,-1.5,0);
		else if (wm.GetUnum() == 8)
				v = Vector(-2,0,0);

		if (!bBeamOver) bBeamOver = ACT.BeamAfterDelay(v,10,5);
		
	}
	//else{ACT.KickSmallLeft();}/*
	else if (wm.IsPlayOn())
	{
		
		
		if ( wm.m_FallState != FALL_NONE || Motion_State == CLIMB_PERIOD)	
		{	
			cout<<"倒下 爬起"<<endl;
			bActionFinish = skill.ClimbOnGround();
			if (bActionFinish)
			{
				Motion_State = SQUAT_PERIOD;
				bActionFinish =  false;
			}
			else
				Motion_State = CLIMB_PERIOD;
			return true;
		}
		if (Motion_State == SQUAT_PERIOD) 
		{
			cout<<"蹲下 "<<endl;
			bActionFinish = ACT.Squat();
			if (bActionFinish)
			{
				Motion_State = ACTION_READY;
				bActionFinish =  false;
			}
			return true;
		} 
		if (Motion_State == STOP_WALK_PERIOD)
		{
			cout<<"停止走路 "<<endl;
			bActionFinish = skill.WalkForwardStop();
			if (bActionFinish)
			{
				Motion_State = ACTION_READY;
				bActionFinish = false;
			}
			return true;
		}
		if (Motion_State == STOP_MICRO_PERIOD)
		{
			cout<<"停止微调"<<endl;
			bActionFinish = skill.MicroAdjustForShoot(Vector(0,0,0),true,false);
			if (bActionFinish)
			{
				Motion_State = ACTION_READY;
				bActionFinish = false;
			}
			return true;
		}
		EstimateSituationUpdate_FreeMan();// should add if situation changed , initail all skill and ACT
		switch (Freeman_Situation)
		{
			case ATTACK : 
				FreeMan_Attack(); 
				break;
			case ASSIST_ATTACK : break;
			case DEFEND : break;
			case ASSIST_DEFEND : break;
			case URGENCY_DEFEND : break;
		}

		if(ShallISaySomething())
			Freeman_Say();

		/* For test say effector
		//wm.LogTeammateSay(1,ssay.str());
		//cout<<" i say "<<wm.GetAllSay()<<endl;
		//cout<<" people say "<<wm.GetOthersSay()<<endl;
		*/
	}
	else return true;
}

void Decision::EstimateSituationUpdate_FreeMan()
{
	SITUATION_FREEMAN situation_decision = UNKNOWN_SITUATION;
	Vector m_vBallPosm_vBallPos = wm.m_vBallPos;
	bool bTeammate = false;
	double dClosestDistTeammate=0;double dClosestDistPlayer=0;
	int iClosestTeammate=0; int iClosestPlayer=0; int iClosestOpp=0;
	dClosestDistTeammate = wm.GetClosestToBallTeammate(iClosestTeammate);
	dClosestDistPlayer = wm.GetClosestToBallPlayer(iClosestPlayer,bTeammate);
	//if ( (iClosestTeammate==wm.GetUnum() || (iClosestTeammate!=wm.GetUnum()  && wm.IsTeammateAbnormal(iClosestTeammate) && fabs(dClosestDistTeammate-wm.GetMeToBallDistInXY())<1.0 ) ) && !wm.IsBallInOurFA())
	if (1)
	{	
		situation_decision = ATTACK;
		goto CheckSituation_Change;
	}
	if ( iClosestTeammate!=wm.GetUnum() &&  ((wm.IsBallInOurFA() && !wm.IsTeammateAbnormal(iClosestTeammate)) || !wm.IsBallInOurFA()) )
	{	
		situation_decision = ASSIST_ATTACK;
		goto CheckSituation_Change;
	}
	if ((wm.IsBallInOurFA() && wm.IsTeammateAbnormal(3)) || (wm.GetClosestToBallOpp(iClosestOpp)<0.3 && wm.IsTeammateAbnormal(iClosestTeammate)))
	{
		situation_decision = URGENCY_DEFEND;
		goto CheckSituation_Change;		
	}
	else 
		situation_decision = ASSIST_DEFEND;
CheckSituation_Change:
	if (situation_decision != Freeman_Situation) //When Situation Changed , Consider about Action Over
	{
		if (Motion_State == WALK_PERIOD)
			Motion_State = STOP_WALK_PERIOD;
		else if (Motion_State == MICRO_PERIOD)
			Motion_State = STOP_MICRO_PERIOD;
		else
			Motion_State = ACTION_READY;
	}	
	Freeman_Situation = situation_decision;	
	return;
}

void Decision::FreeMan_Attack()
{	

	if (Motion_State == ACTION_READY)	
	{
		cout<<"ACTION_READY"<<endl;
		Attack_Point = EstimateAttackPoint();
		skill.ClearAll();
		ACT.ClearAll();
		Motion_State = WALK_PERIOD;
		bActionFinish = true;
	}	
	if (Motion_State == WALK_PERIOD)
	{	
		
		Attack_Point = EstimateAttackPoint();
		cout<<"WALK_PERIOD"<<Attack_Point<<endl;
		bActionFinish = skill.WalkToForward(Attack_Point);
		if (bActionFinish)
		{				
			skill.ClearAll();
			ACT.ClearAll();
			Motion_State = MICRO_PERIOD;
			bActionFinish =  false;
			return;
		}
		
	}
	if (Motion_State == MICRO_PERIOD)
	{
		cout<<"MICRO_PERIOD"<<endl;
		if (wm.GetDistInXY(wm.m_vSelfPos, Attack_Point) < 0.3)
		{	
			bActionFinish = skill.MicroAdjustForShoot();
			if (bActionFinish)
			{
				Motion_State = SQUAT_PERIOD;
				//Attack_Point = EstimateAttackPoint();
				skill.ClearAll();
				ACT.ClearAll();
				bActionFinish =  false;
				return;
			}
		}
		else
		{
			bActionFinish = skill.MicroAdjustForShoot(Vector(0,0,0),true,false);
			if (!bActionFinish)
			{
				//Attack_Point = EstimateAttackPoint();
				//cout<<"---------------停止微调---------"<<endl;
				Motion_State = STOP_MICRO_PERIOD;
			}
			else 
			{
				Attack_Point = EstimateAttackPoint();
				skill.ClearAll();
				ACT.ClearAll();
				bActionFinish = skill.WalkToForward(Attack_Point);
				Motion_State = WALK_PERIOD;
			}
		}
	}

	
}

void Decision::Freeman_Say()
{
	wm.MySayInfo.SayToWho = 6;
	wm.MySayInfo.WhoAmI  = wm.GetUnum();
	wm.MySayInfo.State = -1;
	wm.MySayInfo.CurrentTar = 0;
	wm.MySayInfo.SuggestMate1 = 1;
	robot.Say(wm.GenerateSayInfomation());
}


void Decision::FreeMan_AssistAttack()
{
	if (Motion_State == ACTION_READY)	
	{
		cout<<" Motion_State  ACTION_READY"<<endl;
		Assist_Attack_Point = EstimateAssistAttackPoint();
		skill.ClearAll();
		ACT.ClearAll();
		Motion_State = WALK_PERIOD;
		bActionFinish = true;
	}
	if (Motion_State == WALK_PERIOD)
	{	
		
		Assist_Attack_Point = EstimateAssistAttackPoint();
		cout<<"WALK_PERIOD"<<Assist_Attack_Point<<endl;
		bActionFinish = skill.WalkToForward(Assist_Attack_Point);
		if (bActionFinish)
		{				
			skill.ClearAll();
			ACT.ClearAll();
			Motion_State = ACTION_READY;
			bActionFinish =  false;
			return;
		}
		
	}
}

void Decision::FreeMan_Defend()
{
	if (Motion_State == ACTION_READY)	
	{
		cout<<" Motion_State  ACTION_READY"<<endl;
		Defend_Point = EstimateDefendPoint();
		skill.ClearAll();
		ACT.ClearAll();
		Motion_State = WALK_PERIOD;
		bActionFinish = true;
	}
	if (Motion_State == WALK_PERIOD)
	{	
		
		Defend_Point = EstimateDefendPoint();
		cout<<"WALK_PERIOD"<<Defend_Point<<endl;
		bActionFinish = skill.WalkToForward(Defend_Point);
		if (bActionFinish)
		{				
			skill.ClearAll();
			ACT.ClearAll();
			Motion_State = ACTION_READY;
			bActionFinish =  false;
			return;
		}
		
	}
	
}

void Decision::FreeMan_AssistDefend()
{
	if (Motion_State == ACTION_READY)	
	{
		cout<<" Motion_State  ACTION_READY"<<endl;
		Assist_Defend_Point = EstimateAssistDefendPoint();
		skill.ClearAll();
		ACT.ClearAll();
		Motion_State = WALK_PERIOD;
		bActionFinish = true;
	}
	if (Motion_State == WALK_PERIOD)
	{	
		
		Assist_Defend_Point = EstimateAssistDefendPoint();
		cout<<"WALK_PERIOD"<<Assist_Defend_Point<<endl;
		bActionFinish = skill.WalkToForward(Assist_Defend_Point);
		if (bActionFinish)
		{				
			skill.ClearAll();
			ACT.ClearAll();
			Motion_State = ACTION_READY;
			bActionFinish =  false;
			return;
		}
		
	}
}

void Decision::FreeMan_UgencyDefend()
{
	if (Motion_State == ACTION_READY)	
	{
		cout<<" Motion_State  ACTION_READY"<<endl;
		Urgency_Defend_Point = EstimateUgencyDefendPoint();
		skill.ClearAll();
		ACT.ClearAll();
		Motion_State = WALK_PERIOD;
		bActionFinish = true;
	}
	if (Motion_State == WALK_PERIOD)
	{	
		
		Urgency_Defend_Point = EstimateUgencyDefendPoint();
		cout<<"WALK_PERIOD"<<Urgency_Defend_Point<<endl;
		bActionFinish = skill.WalkToForward(Urgency_Defend_Point);
		if (bActionFinish)
		{				
			skill.ClearAll();
			ACT.ClearAll();
			Motion_State = ACTION_READY;
			bActionFinish =  false;
			return;
		}
		
	}
	if (Motion_State == MICRO_PERIOD)
	{
		cout<<"MICRO_PERIOD"<<endl;
		if (wm.GetDistInXY(wm.m_vSelfPos, Urgency_Defend_Point) < 0.25)
		{	
			bActionFinish = skill.MicroAdjustForShoot();
			if (bActionFinish)
			{
				Motion_State = SQUAT_PERIOD;
				//Attack_Point = EstimateAttackPoint();
				skill.ClearAll();
				ACT.ClearAll();
				bActionFinish =  false;
				return;
			}
		}
		else
		{
			bActionFinish = skill.MicroAdjustForShoot(Vector(0,0,0),true,false);
			if (!bActionFinish)
			{
				//Attack_Point = EstimateAttackPoint();
				//cout<<"---------------停止微调---------"<<endl;
				Motion_State = STOP_MICRO_PERIOD;
			}
			else 
			{
				Urgency_Defend_Point = EstimateUgencyDefendPoint();
				skill.ClearAll();
				ACT.ClearAll();
				bActionFinish = skill.WalkToForward(Urgency_Defend_Point);
				Motion_State = WALK_PERIOD;
			}
		}
	}
}



Vector Decision::EstimateAssistDefendPoint()
{
return Vector(-2,-2,0);
}

Vector Decision::EstimateAttackPoint()
{
	return wm.GetShootPos();//should discuss with yuan xing nowwork
}

Vector Decision::EstimateAssistAttackPoint()
{
	
	return Vector(3,-2,0);
	
}

Vector Decision::EstimateDefendPoint()
{
	return Vector(-2,0,0);
}

Vector Decision::EstimateUgencyDefendPoint()
{
	return Vector(-6,0,0);
}



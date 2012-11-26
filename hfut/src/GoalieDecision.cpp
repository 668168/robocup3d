#include "decision.h"
#include <sstream>

#include "soccertypes.h"
#include "acthandle.h"
#include "geometry.h"
#include "timer.h"
#include "worldmodel.h"
#include "robot.h"
//#define TRAIN
extern Timer timer;
extern ActHandle ACT;
extern WorldModel wm;
extern Geometry geometry;

extern Robot robot;

/**
 * Alex
 */
bool Decision::Goalie_Do()
{
	static bool bBeamOver = false;
	static bool actready = false;
	static bool Kick = false;
	static bool LogTrain = false;
	if (wm.IsBeforeKickOff())
	{
		//Vector v(-0.15,0.15,-15);
		//cout<<wm.m_vBeamPos<<endl;
		if (!bBeamOver) bBeamOver = ACT.BeamAfterDelay(Vector(-5, -3, 0),10,5);
		
		//cout<<" My Pos is "<<wm.m_vBeamPos.GetVx()<<" "<<wm.m_vBeamPos.GetVy()<<" "<<wm.m_vBeamPos.GetVz()<<"; WorldModel shows DistInXY "<<wm.GetMeToBallDistInXY()<<"; RelXYAngle"<<wm.GetBallRelMeXYAngle()<<"; Kick Dist "<<"\n";
			
			
	}
	else if (!wm.IsGoalKickUs())
	{	
		//cout<<" 球速 "<<wm.CalcBallSpeed().GetVx()<<", "<< wm.CalcBallSpeed().GetVy()<<endl;
		if ( (wm.m_FallState != FALL_NONE || Motion_State == CLIMB_PERIOD) && !(wm.m_FallState != FALL_NONE && Motion_State == CATCH_PERIOD))	
		{	
			//cout<<"倒下 爬起"<<endl;
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
			//cout<<"蹲下 "<<endl;
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
			//cout<<"停止走路 "<<endl;
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
			//cout<<"停止微调射门"<<endl;
			bActionFinish = skill.MicroAdjustForShoot(Vector(0,0,0),true,false);
			if (bActionFinish)
			{
				Motion_State = ACTION_READY;
				bActionFinish = false;
			}
			return true;
		}
		if (Motion_State == STOP_MICRO_FREEKICK_PREIOD)
		{
			//cout<<" 停止微调任意球"<<endl;
			bActionFinish = skill.MicroAdjustForFreeKick(Vector(0,0,0),true,false);
			if (bActionFinish)
			{
				Motion_State = ACTION_READY;
				bActionFinish = false;
			}
			return true;
		}
		if (Motion_State == CATCH_PERIOD)
		{
			//cout<<"扑救"<<endl;
			bActionFinish = ACT.Catch(Vector(0,0,0));
			if (bActionFinish)
			{
				Motion_State = CLIMB_PERIOD;
				bActionFinish = false;
			}
			return true;
		}
		//cout<<" 队友高度 "<<wm.m_TeamMate[0].vPos.GetVz()<<endl;
		EstimateSituationUpdate_Goalie ();
		
		switch (DEFEND_GOALIE)
		{
			case DEFEND_GOALIE : 
				Goalie_Defend(); 
				break;
			case RESCUE_GOALIE : 
				Goalie_Rescue();
				break;
			case CATCH_GOALIE :
				Goalie_Catch();
				break;

		}
		return true;

	}
	return true;
}

void Decision::EstimateSituationUpdate_Goalie()
{
	SITUATION_GOALIE  situation_decision=UNKNOWN_SITUATION_GOALIE;

	situation_decision = DEFEND_GOALIE;

CheckSituation_Change:
	if (situation_decision != Goalie_Situation) //When Situation Changed , Consider about Action Over
	{
		if (Motion_State == WALK_PERIOD)
			Motion_State = STOP_WALK_PERIOD;
		else if (Motion_State == MICRO_PERIOD)
			Motion_State = STOP_MICRO_PERIOD;
		else if (Motion_State == MICRO_FREEKICK_PERIOD)
			Motion_State = STOP_MICRO_FREEKICK_PREIOD;
		else if (Motion_State == MICRO_WALK_PERIOD)
			Motion_State = STOP_MICRO_WALK_PERIOD;
		else
			Motion_State = ACTION_READY;
	}	
	Goalie_Situation = situation_decision;	
}

void Decision::Goalie_Defend()
{
	if (Motion_State == ACTION_READY)	
	{
		//cout<<"ACTION_READY"<<endl;
		Defend_Point = EstimateDefindPoint_G();
		skill.ClearAll();
		ACT.ClearAll();
		Motion_State = MICRO_WALK_PERIOD;
		bActionFinish = true;
	}
	if (Motion_State == MICRO_WALK_PERIOD)
	{	
		
		Defend_Point = EstimateDefindPoint_G();
		//cout<<"MICRO_WALK_PERIOD"<<Defend_Point<<endl;
		bActionFinish = skill.MicroAdjustForGoalKeeper(Defend_Point); 
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

void Decision::Goalie_Rescue()
{
	if (Motion_State == ACTION_READY)	
	{
		cout<<"ACTION_READY"<<endl;
		Rescue_Point = EstimateRescuePoint();
		skill.ClearAll();
		ACT.ClearAll();
		Motion_State = MICRO_FREEKICK_PERIOD;
		bActionFinish = true;
	}	
	if (Motion_State == MICRO_FREEKICK_PERIOD)
	{
		cout<<"MICRO_PERIOD"<<endl;
		if (wm.GetDistInXY(wm.m_vSelfPos, Rescue_Point) < 0.5)
		{	
			bActionFinish = skill.MicroAdjustForFreeKick(Rescue_Point);
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
			bActionFinish = skill.MicroAdjustForFreeKick(Rescue_Point,true,false);
			if (!bActionFinish)
			{
				//Attack_Point = EstimateAttackPoint();
				//cout<<"---------------停止微调---------"<<endl;
				Motion_State = STOP_MICRO_FREEKICK_PREIOD;
			}
			else 
			{
				Rescue_Point = EstimateRescuePoint();
				skill.ClearAll();
				ACT.ClearAll();
				bActionFinish = skill.WalkToForward(Rescue_Point);
				Motion_State = WALK_PERIOD;
			}
		}
	}
	if (Motion_State == WALK_PERIOD)
	{	
		
		Rescue_Point = EstimateRescuePoint();
		cout<<"WALK_PERIOD"<<Rescue_Point<<endl;
		bActionFinish = skill.WalkToForward(Rescue_Point);
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

void Decision::Goalie_Catch()
{

	cout<<"CATCH_PERIOD"<<endl;
	Rescue_Point = EstimateRescuePoint();
	skill.ClearAll();
	ACT.ClearAll();
	Motion_State = CATCH_PERIOD;
	bActionFinish = true;
	
	return;
	
}

Vector Decision::EstimateDefindPoint_G()
{
	Vector vBallPos = wm.m_vBallPos;
	Vector vAgentPos = wm.m_vSelfPos;
	Line lShootLine = geometry.MakeLineWithTwoVec(wm.GetMyGoalPos(),vBallPos);
	Vector vCalcDefinePoint = geometry.GetFootPointToLine(vAgentPos , lShootLine);
	//return vCalcDefinePoint;
	if (vCalcDefinePoint.GetVx()<-5.5 && vCalcDefinePoint.GetVx() >= -6 && !wm.IsBallInOurFA())
		return vCalcDefinePoint;
	return geometry.GetIntersectionPoint(geometry.MakeLineWithTwoVec(wm.GetMyGoalPos(),Vector(-6,-2,0)),lShootLine);
}

Vector Decision::EstimateRescuePoint()
{
	return EstimateAttackPoint();
}


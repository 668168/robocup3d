#include "decision.h"
#include <sstream>


#include "acthandle.h"
#include "skill.h"
#include "timer.h"
#include "worldmodel.h"
#include "robot.h"

extern Timer timer;
extern ActHandle ACT;
extern WorldModel wm;
extern Robot robot;

Decision::Decision()
{
	bHaveIntro = false;
	Freeman_Situation = ATTACK;
	Goalie_Situation = DEFEND_GOALIE;
	Motion_State = SQUAT_PERIOD;
	Attack_Point = Vector(0,0,-1);
	Assist_Attack_Point = Vector(0,0,-1);
	Defend_Point = Vector(0,0,-1);
	Assist_Defend_Point = Vector(0,0,-1);
	Urgency_Defend_Point = Vector(0,0,-1);
	bActionFinish = false;
}

Decision::~Decision()
{

}

/*
bool Decision::Do()
{
	static bool bDelayOver = false;
	static bool bSquatOver = false;
	static bool bCatchReady = false;
	static bool bCatchOver = false;
	static bool bMove = false;

	if (!bDelayOver)
	{
		Vector v(-2,-3,0);
		bDelayOver = ACT.BeamAfterDelay(v, 10, 5);//skill.Delay(20);
		return true;
	}

	if (!bSquatOver)
	{
		bSquatOver = ACT.Squat();
		return true;
	}

	if (!bMove)
	{
		 bMove = skill.MicroAdjustForGoalKeeper(EstimateDefindPoint_G()); 
	}

}
*/

bool Decision::Do()
{
	

	if (!bHaveIntro)
	{	//Vector vKickPos = wm.GetShootPos();
		//cout<<"vKickPos::"<<vKickPos<<endl;
		bHaveIntro = true;
		cout<<" My Num is "<<wm.GetUnum()<<" from Team "<<wm.GetTeamName()<<endl;
	}
	if (wm.GetUnum() == 9) return Goalie_Do();
	else return FreeMan_DO();
}


bool Decision::ShallISaySomething ()
{
	return false;
}





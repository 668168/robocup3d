#ifndef DECISION_H
#define DECISION_H
#include <string>
#include "soccertypes.h"
#include "skill.h"


extern Skill skill;
using namespace std;

enum MOTION_STATE
{
	ACTION_READY = 0,
	SQUAT_PERIOD,	
	WALK_PERIOD,
	MICRO_PERIOD,
	MICRO_FREEKICK_PERIOD,
	CLIMB_PERIOD,
	CATCH_PERIOD,
	MICRO_WALK_PERIOD,
	STOP_MICRO_WALK_PERIOD,
	STOP_WALK_PERIOD,
	STOP_MICRO_FREEKICK_PREIOD,
	STOP_MICRO_PERIOD,
	
	
	UNKNOWN_PERIOD
};

enum SITUATION_FREEMAN
{
	ATTACK = 0,
	ASSIST_ATTACK,
	DEFEND,
	ASSIST_DEFEND,
	URGENCY_DEFEND,
	UNKNOWN_SITUATION
};

enum SITUATION_GOALIE
{
	DEFEND_GOALIE = 0,
	CATCH_GOALIE,
	RESCUE_GOALIE,
	GOAL_KICK,
	UNKNOWN_SITUATION_GOALIE
};

extern Geometry geometry;
/**
	@author hfut
*/
class Decision{
public:
	Decision();
	~Decision();
	bool Do();
	bool bHaveIntro;
private: 
	/** Goalie Decision */
	bool Goalie_Do();
	void EstimateSituationUpdate_Goalie();
	void Goalie_Defend();
	void Goalie_Rescue();
	void Goalie_Catch();
	Vector EstimateDefindPoint_G();
	Vector EstimateRescuePoint();

	/** Free Man Decision */
	bool FreeMan_DO();
	bool bActionFinish;
	void EstimateSituationUpdate_FreeMan();

	void FreeMan_Attack();
	void Freeman_Say();
	void FreeMan_AssistAttack();	
	void FreeMan_Defend();
	void FreeMan_AssistDefend();
	void FreeMan_UgencyDefend();

	Vector EstimateDefendPoint();
	Vector EstimateAssistAttackPoint();
	Vector EstimateAttackPoint();
	Vector EstimateAssistDefendPoint();
	Vector EstimateUgencyDefendPoint();

	SITUATION_FREEMAN Freeman_Situation;
	SITUATION_GOALIE Goalie_Situation;
	MOTION_STATE Motion_State;
	Vector Attack_Point;
	Vector Assist_Attack_Point;
	Vector Defend_Point;
	Vector Catch_Point;
	Vector Rescue_Point;
	Vector Assist_Defend_Point;
	Vector Urgency_Defend_Point;

public:
	bool ShallISaySomething ();	
	
};



#endif

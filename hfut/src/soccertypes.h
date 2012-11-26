#ifndef SOCCERTYPES_H
#define SOCCERTYPES_H

#include <iostream>
#include <string>
#include "geometry.h"
#define PI 3.1415926

#define NAO_MODEL


using namespace std;


    enum JointID
    {
        JID_HEAD_1 = 0, 
        JID_HEAD_2 = 1,
     
        JID_LARM_1 = 2,
        JID_RARM_1 = 3,
        JID_LARM_2 = 4,
        JID_RARM_2 = 5,
        JID_LARM_3 = 6,
        JID_RARM_3 = 7,
        JID_LARM_4 = 8,
        JID_RARM_4 = 9,
     
        JID_LLEG_1 = 10,
        JID_RLEG_1 = 11,
        JID_LLEG_2 = 12,
        JID_RLEG_2 = 13,
        JID_LLEG_3 = 14,
        JID_RLEG_3 = 15,
        JID_LLEG_4 = 16,
        JID_RLEG_4 = 17,
        JID_LLEG_5 = 18,
        JID_RLEG_5 = 19,
        JID_LLEG_6 = 20,
        JID_RLEG_6 = 21,
        JID_UNKNOW

    };

    enum H_ID
    {
    	ID_LLEG_1 = 0,
    	ID_RLEG_1,
    	ID_LLEG_4,
    	ID_RLEG_4,
    	ID_LARM_3,
    	ID_RARM_3,
    	ID_LARM_4,
    	ID_RARM_4,
    	ID_LARM_5,
    	ID_RARM_5
    	
    };
    
    enum U_ID
    {
    	ID_LLEG_2_3 = 0,
    	ID_RLEG_2_3,
    	ID_LLEG_5_6,
    	ID_RLEG_5_6,
    	ID_LARM_1_2,
    	ID_RARM_1_2
    };

    enum Flag_ID
    {
	     F_F1L = 0,
	     F_G1L,
	     F_G2L,
	     F_F2L,
	     F_F1R,
	     F_G1R,
	     F_G2R,
	     F_F2R
    };
    
    enum CMD_TYPE
    {
	CMD_NONE = 0,
	CMD_KICK,
	CMD_WALK,
	CMD_STANDUP,
	CMD_TURNLEFT,
	CMD_TURNRIGHT,
	CMD_DEMO,
	CMD_GOALIER,
	CMD_SMALLWALK
    };

	enum LOCATE_GET_TYPE
	{
		THREEFLAGS = 0,
		TWOFLAGS,
		HEAR,
		TURNNECK,
		LOCATE_TYPE_NONE

	};

	enum TRIANER_TYPE
	{
		KICK_BALL = 0
	};

    struct SysTime
    {
    	int year, month, day;
    	int hour, minute, second;
    	SysTime() : year(0), month(0), day(0), hour(0), minute(0), second(0) {}
    };
    
    
    enum FALLTYPE
    {
    	FALL_NONE = 0,
    	FALL_UP,
    	FALL_DOWN,
	FALL_CLIMBING,
    	FALL
    };

    struct HJCtrl
	{
           double fAngle;
           string sName;  /** PerceptorName */
           bool bCtrled;
           bool bChanged;
           HJCtrl() : fAngle(0), sName(""), bCtrled(false), bChanged(false) {}       
    };

    struct UJCtrl
	{
           double fAngle1, fAngle2;
           string sName;
           bool bCtrled;
           bool bChanged;
           UJCtrl() : fAngle1(0), fAngle2(0), sName(""), bCtrled(false), bChanged(false) {}       
    };

    struct HJInfo
    {
           int ID;
           string sPerceptorName;
           string sEffectorName;
           double fAngle;
           double fAngleRate;
           double dTime;
           HJInfo() : ID(JID_UNKNOW), sPerceptorName(""), sEffectorName(""), fAngle(0), fAngleRate(0), dTime(0) {} 
    };

    struct UJInfo
    {
           int ID;
           string sPerceptorName;
           string sEffectorName;
           double fAngle1, fAngle2;
           double fAngleRate1, fAngleRate2;
           double dTime;
           UJInfo() : ID(JID_UNKNOW), sPerceptorName(""), sEffectorName(""), fAngle1(0), fAngle2(0), fAngleRate1(0), fAngleRate2(0), dTime(0) {} 
    };

    struct GyroInfo
    {
           string sName;
           double dx, dy, dz;
           double dTime;
           GyroInfo() : sName(""), dx(0), dy(0), dz(0), dTime(0) {}
    };
    
    struct FRPInfo
    {
           double cx, cy, cz;
           double dx, dy, dz;
           double dTime;
           FRPInfo() : cx(0), cy(0), cz(0), dx(0), dy(0), dz(0), dTime(0) {}
    };
    
    struct ObjPosInfo
    {
           Vector vPos;
           Polar PolPos;
           double dTime;
           ObjPosInfo() : vPos(Vector()), PolPos(Polar()), dTime(0) {}
    };

    struct AgentInfo
    {
           Vector vPos;
           Polar PolPos;
           double dTime;
           bool bValid;
           bool bIsOpp;
           int iNum;
           AgentInfo() : vPos(Vector()), PolPos(Polar()), dTime(0), bValid(false), bIsOpp(false), iNum(0) {}
    };

    struct VecPosInfo
    {
           Vector vPos;
           double dTime;
           bool bValid;
           VecPosInfo() : vPos(Vector()), dTime(0), bValid(false) {}
    };
    
    struct PolPosInfo
    {
           Polar PolPos;
           double dTime;
           bool bCanSee;
           PolPosInfo() : PolPos(Polar()), dTime(0), bCanSee(false) {}
    };

	struct HearInfo
    {
           string sMsg;
           double dDirection;
           bool bIsHeardfromSelf;
           bool bValid;
           double dHeardTime;  /** gametime (not servertime)when heard the message */
           HearInfo() : sMsg(""), dDirection(0), bValid(false), bIsHeardfromSelf(false), dHeardTime(0) {}
    };

    struct strSayInfo
   {
	bool bValid;
	string identification;
	int SayToWho; /* 0: broadcast; 1: num1;... */
	int WhoAmI;
	int State;
	int CurrentTar;
	int SuggestMate1;
	int SuggestMate2;
	int PredictOpp1State;
	int PredictOpp1Act;
	int PredictOpp2State;
	int PredictOpp2Act;
	int PredictOpp3State;
	int PredictOpp3Act;

	double dHeardTime;  /** gametime (not servertime)when heard the message */
	double dDirection;
	strSayInfo() : bValid(false),SayToWho(0),State(-1),dHeardTime(0),dDirection(0){}
	
   };

	struct HearInfoItem
	{
		string sCmd;
		int iFromWho;
		bool bHaveCmd;
		bool bHavePos;
		bool bHaveBallPos;
		bool bValid;
		double dTime;
		Vector vPos[11];
		Vector vBallPos;
		bool bPosFlag[11];
		HearInfoItem() : sCmd(""), iFromWho(0), bHaveCmd(false), bHavePos(false), bHaveBallPos(false), bValid(false), dTime(0) {}
	};

	struct AngleInfo
	{
		double dAngle;
		double dTime;
		AngleInfo() : dAngle(0), dTime(0) {}
	};

	struct LocationInfo
	{
		Polar ObjPolPos[8];
		bool ObjCanSee[8];
		int iLeftNum;
		int iRightNum;
		int iTotalNum;
		double dTime;
		LocationInfo() : iLeftNum(0), iRightNum(0), iTotalNum(0), dTime(0) {}

	};

	struct MyPosInfo
	{
		Vector vPos;
		bool IsXAccurate;
		bool IsYAccurate;
		double dTime;
		LOCATE_GET_TYPE LocateType;
		MyPosInfo() : vPos(Vector()), IsXAccurate(false), IsYAccurate(false), dTime(0), LocateType(LOCATE_TYPE_NONE) {}
	};


#endif

#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <sstream>
#include <cmath>
#include "soccertypes.h"
#include "msgparse.h"
#include "myQueue.h"

extern MsgParse SenseParse;

class WorldModel{
public:
	WorldModel();
	~WorldModel();
	
	/** Set and Get Basic Info of field and goal which will be used to locate postion */
	void SetFieldLength(double fl) { m_dFieldLength = fl; }
	void SetFieldWidth(double fw) { m_dFieldWidth = fw; }
	void SetGoalWidth(double gw) { m_dGoalWidth = gw; }
	void SetGoalHeight(double gh) { m_dGoalHeight = gh; }
	
	double GetFieldLength() { return m_dFieldLength; }
	double GetFieldWidth() { return m_dFieldWidth; }
	double GetGoalWidth() { return m_dGoalWidth; }
	double GetGoalHeight() { return m_dGoalHeight; }
	
	/** function for team and player */
	void SetTeamName(string stn) { m_sTeamName = stn; SenseParse.SetTeamName(stn); }
	string GetTeamName() { return m_sTeamName; }
	void SetUnum(int iunum) { m_iUnum = iunum; }
	int GetUnum() { return m_iUnum; }
	void SetCmdUnum(int iunum) { m_iCmdUnum = iunum; }
	int GetCmdUnum() { return m_iCmdUnum; }
	void SetBeamPos(double dx, double dy, double dz) { m_vBeamPos = Vector(dx,dy,dz); }
	Vector GetBeamPos() { return m_vBeamPos; }
	void SetCmdType(CMD_TYPE t) { m_CmdType = t ;}
	CMD_TYPE GetCmdType() { return m_CmdType; }
	
	/**                                */
	double GetServerTime() { return m_dServerTime; }
	double GetGameTime() { return m_dGameTime; }
	string GetOppTeamName() { return m_sOppTeamName; }
	string GetPlayMode() { return m_sPlayMode; }
	int GetMyScore() { return m_iMyScore; }
	int GetOppScore() { return m_iOppScore; }
	Vector GetMyGoalPos() { return m_vMyGoalPos; }
	Vector GetOppGoalPos() { return m_vOppGoalPos; }
	
	/** Set and Get Basic Info of Ball */
	void SetBallRadius(double br) { m_dBallRadius = br; }
	void SetBallMass(double bm) { m_dBallMass = bm; }
	double GetBallRadius() { return m_dBallRadius; }
	double GetBallMass() { return m_dBallMass; }

	/** Get Object Pos */
	Vector GetOppPos ( int iOppNum) { return m_Opponent[iOppNum-1].bValid? m_Opponent[iOppNum-1].vPos : Vector(0,0,-1.0) ;}
	Vector GetTeammatePos ( int iTeammateNum) { return m_TeamMate[iTeammateNum-1].bValid? m_TeamMate[iTeammateNum-1].vPos : Vector(0,0,-1.0);}


	/** Update the worldmodel */
	void UpdateAll();

	/** relate to the state of robot */
	FALLTYPE DetectFallState_GYRO(bool bClear = false);
	FALLTYPE CheckIsFall(bool bClear = false);
	void UpdateFallState(int iClearType = 0);

private:

	/** Update the worldmodel */
	void UpdateBasicInfo();
	void UpdateScore();
	void UpdateSelfPos();
	void UpdatePlayerPos();
	void UpdateBallPos();
	void UpdateAngle();
	void UpdateHearMsg ();//TODO

	/** for location */
	void InitFlagPos();
	bool CalcSelfPosX(int iFlag1, int iFlag2, double &);
	bool CalcSelfPosY(int iFlag1, int iFlag2, double &);
	bool CalcSelfPosZ_F(int iFlag, double &);
	bool CalcSelfPosZ_G(int iFlag, double &);
	bool CalcSelfPosZ(double &);
	
	double NormalizeAng(double dAng);
	void NormalizeAngle(double &dAng);
	double GetFaceAngInGlobal(int iFlagID);
	double GetFaceAngInGlobalEx();
	double GetBodyAng(double dFaceAngInGlobal);
	//double GetHeadTiltAng_F(int iFlagID);
	//double GetHeadTiltAng_G(int iFlagID);
	//double GetHeadTiltAngInGlobal();
	//double GetBodyTiltAng(double dHeadTiltAngInGlobal);

	//Vector GetObjPos(Vector vMyPos, Polar PolPos);
	Vector GetObjPos(Polar PolPos);
	Vector GetBallPosInXY();
	void Location();

	double squ(double x) { return x*x; }
	double Round(double, int);

public:

    /** GameState functions */
	bool IsKickOff();
	bool IsKickOffUs();
	bool IsKickOffOpp();
	bool IsKickIn();
	bool IsKickInUs();
	bool IsKickInOpp();
	bool IsCornerKick();
	bool IsCornerKickUs();
	bool IsCornerKickOpp();
	bool IsGoalKick();
	bool IsGoalKickUs();
	bool IsGoalKickOpp();
	bool IsFreeKick();
	bool IsFreeKickUs();
	bool IsFreeKickOpp();
	bool IsOffside();
	bool IsOffsideUs();
	bool IsOffsideOpp();
	bool IsGoal();
	bool IsGoalUs();
	bool IsGoalOpp();
	bool IsBeforeKickOff();
	bool IsPlayOn();
	bool IsGameOver();

	/** WorldModel HighLevel*/
	double GetDist(Vector v1, Vector v2);
	double GetDistInXY(Vector v1, Vector v2);
	double GetXYAngle(Vector v1, Vector v2);
	double GetXYAngleToPos(Vector vPos);
	double GetMeToBallDist();
	double GetMeToBallDistInXY();
	double GetBallRelMeXYAngle();
	Vector GetTentativePosForOmdiWalk(Vector vDestinationPos, double dDestinationAng, Vector vCurrentPos, double dCurrentAng);
	Vector GetTentativePosForOmdiWalk(Vector vDestinationPos, double dDestinationAng);

//////////////////////////////////////////////////////////////////
	Vector GetMeRelBall(Vector vTarget);
	bool IsKickable(Vector vTarget);
	double GetDisToBall();
	int InWhichArea(Vector vTarget);
	bool IsFaceBall(Vector vTarget);
	bool IsTurnToKick(Vector vTarget);
	Vector GetShootPos(Vector vTarget = Vector(6, 0, 0), double dis = 0.2);

     /**  ------------------------  */
	#ifdef NAO_MODEL
	HJInfo m_HJ[22];
	#else
	HJInfo m_HJ[8];
	UJInfo m_UJ[6];
	#endif
	
	FRPInfo m_frp_lf;
	FRPInfo m_frp_rf;
	GyroInfo m_Gyro;
	
	strSayInfo MySayInfo;                   /** for agent put say infomation */
	strSayInfo OtherSayInfoTeam[11];
	strSayInfo OtherSayInfoOpp[11];
	//HearInfo m_HearMsg[22];
	//HearInfoItem m_HearInfo[22];

	Vector m_vSelfPos;
	double m_dFaceAng;
	double m_dBodyAng;
	double m_dStandHeight;

	Vector m_vBeamPos;

	Vector m_vBallPos;
	VecPosInfo m_TeamMate[11];
	VecPosInfo m_Opponent[11];

	FALLTYPE m_FallState;

	bool m_bIsKicking;
public:

	/**Team StrategyBase*/
	bool IsMeGoalie (); 
	bool IsBallInOurProcession ();  //TODO
	bool IsTeammateAbnormal (  int iTeammateNum ); 
	bool IsOppAbnormal ( int iOppNum ); 


	Vector CalcMySpeed ();//TODO
	Vector CalcTeammateSpeed (int iTeammateNum);//TODO
	Vector CalcOppSpeed (int iOppNum);//TODO
	Vector CalcBallSpeed ();
	Vector PredictBallPosAfterCycles (int iCycles);

	double GetOppDistToBall ( int iOppNum );
	double GetTeammateDistToBall ( int iTeammateNum );	

	double GetClosestToBallTeammate( int &iTeammateNum );
	double GetClosestToBallOpp ( int &iOppNum );
	double GetClosestToBallPlayer ( int &iPlayerNum, bool &bTeamPlayer);

	double GetTeammateDistToOwnGoal (int iTeammateNum);
	double GetOppDistToOwnGoal ( int iOppNum);

	double GetClosestToOwnGoalTeammate( int &iTeammateNum );
	double GetClosestToOwnGoalOpp( int &iOppNum );
	double GetClosestToOwnGoalPlayer ( int &iPlayerNum, bool &bTeamPlayer);

	double GetTeammateDistToOppGoal (int iTeammateNum);
	double GetOppDistToOppGoal ( int iOppNum);

	double GetClosestToOppGoalTeammate( int &iTeammateNum );
	double GetClosestToOppGoalOpp ( int &iOppNum );
	double GetClosestToOppGoalPlayer ( int &iPlayerNum, bool &bTeamPlayer);

	double GetTeammateDistToMe (int iTeammateNum);
	double GetOppDistToMe ( int iOppNum);

	double GetClosestToMeTeammate (  int &iTeammateNum );
	double GetClosestToMeOpp ( int &iOppNum );
	double GetClosestToMePlayer ( int &iPlayerNum, bool &bTeamPlayer);

	bool IsBallInOurFA();

public:
	/** hear module */
	string GetOthersSay ();
	string GetMySay ();
	string GetTeammateSay (int iTeammateNum);//TODO
	string GetOppSay (int iOppNum);//TODO
	char C2EC(char c);
	char EC2C(char c);
	void EnCodeInfo ( int iIndex);//TODO
	void DeCodeInfo ( int iIndex);//TODO
	string GenerateSayInfomation();
	void AnslyzeTeammateSay();
	bool FindString(string sMsg,string sFindMsg);
	bool LogTeammateSay (bool bToFile, string FileName="" );
	
	

private:

	double m_dFieldLength;
	double m_dFieldWidth;
	double m_dGoalWidth;
	double m_dGoalHeight;

	string m_sTeamName;
	int m_iUnum;
	int m_iCmdUnum;
	bool m_bIsLeft;

	double m_dBallRadius;
	double m_dBallMass;
	
	double m_dServerTime;
	double m_dGameTime;
	string m_sOppTeamName;
	string m_sPlayMode;
	int m_iMyScore;
	int m_iOppScore;

	Vector m_vOppGoalPos;
	Vector m_vMyGoalPos;

	CMD_TYPE m_CmdType;
	Vector m_vFlagPos[8];

	queue <VecPosInfo> BallPosQ;
	queue <VecPosInfo> MyPosQ;

};


#endif

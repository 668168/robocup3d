#ifndef ACTHANDLE_H
#define ACTHANDLE_H

#include "soccertypes.h"
#include "string.h"

class ActHandle
{
public:
	ActHandle();
	~ActHandle();
	
	void Beam(Vector vPos);
	bool Beam(Vector vPos, int BeamNum, bool Clear = false);
	bool BeamAfterDelay(Vector vPos, int DelayTime, int BeamNum, bool Clear = false);
	void ClearControl();
	string MakeCommand();
	#ifdef NAO_MODEL
	HJCtrl HJControl[22];
	#else
	HJCtrl HJControl[8];
	UJCtrl UJControl[6];
	#endif


	bool KickLeft();
	bool KickRight();
	bool KickSmallRight();
	bool KickSmallLeft();
	bool Step(int i);
	bool StaticWalk();
	bool StaticWalk(int iNum);
	bool WalkSmall();
	bool Move(int iType);
	

	bool Squat();
	bool TurnLeft(int iType = 0);
	bool TurnRight(int iType = 0);
	void ClearAll();
	 bool FootFall();
	bool WalkBackSmall() ;

bool FallDownForTest(double speed,bool forward=true);

	bool PrepareToGetUp();  /** 向前倒爬起时的预备动作  */
	bool Climb_FaceDown();            /** 向前倒爬起 */
	bool Climb_FaceUp();        /** 向后倒爬起 */


bool TestAct();
bool Catch (Vector vCatchPos);

	bool Walk(int iWalkType = 0, bool bClear = false);
	bool WalkBackEx(int iWalkType = 0, bool bClear = false);
	bool WalkBack(double & speed);
	bool WalkBackLeft(double & speed);
	bool WalkBackRight(double & speed);
	bool StopWalkBack(double & speed);
    
private:
	bool DoAction(double laj1, double laj2, double laj3, double laj4,
			 double raj1 ,double raj2, double raj3, double raj4,
			 double llj1, double llj2, double llj3, double llj4, double llj5, double llj6,
			 double rlj1, double rlj2, double rlj3, double rlj4, double rlj5, double rlj6,
				double speed
			);
    bool AdjustHJ(int iID, double dNewAng, double dSpeed, double dAccurate = 1);
    #ifndef NAO_MODEL
    bool AdjustUJ_1(int iID, double dNewAng, double dSpeed, double dAccurate = 1);
    bool AdjustUJ_2(int iID, double dNewAng, double dSpeed, double dAccurate = 1);
    #endif
    
};


#endif

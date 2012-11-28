/***************************************************************************
 *   Copyright (C) 2008 by root   *
 *   root@localhost.localdomain   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "skill.h"
#include "worldmodel.h"
#include "acthandle.h"
#include "timer.h"

extern WorldModel wm;
extern ActHandle ACT;
extern Timer timer;


Skill::Skill()
{
}


Skill::~Skill()
{
}


bool Skill::Delay(int iCycle)
{
	if (!timer.IsTimerRun()) timer.SetTimer();
	if (timer.GetTime() < iCycle) return false;
	timer.ClearTimer();
	return true;
}


double Skill::NormalizeAng(double &dAng)
{
	while (dAng > 180) dAng -= 360;
	while (dAng < -180) dAng += 360;
	return dAng;
}


bool Skill::CheckClimbSucc(bool &bSucc, bool bClear)
{
	static int iCheckTime = 0;
	static int iVz_OK = 0;
	static int iGYRO_OK = 0;

	#define MIN_H 0.25

	if (bClear)
	{
		iCheckTime = 0;
		iVz_OK = 0;
		iGYRO_OK = 0;
		return true;
	}

	iCheckTime++;

	Vector v(wm.m_Gyro.dx, wm.m_Gyro.dy, 0);
	if (v.GetMod() < 1.5) iGYRO_OK++;

	
	if (iCheckTime < 20)
	{
		if (iGYRO_OK > 15)
		{
			bSucc = (wm.m_vSelfPos.Vz > MIN_H);
			if (bSucc)
			{
				iCheckTime = 0;
				iVz_OK = 0;
				iGYRO_OK = 0; 
				return true;
			}
		}

		if (wm.m_vSelfPos.Vz > MIN_H) iVz_OK++;

		if (iCheckTime == 19)
		{
			if (iVz_OK < 10)
			{
				bSucc = false;
				iCheckTime = 0;
				iVz_OK = 0;
				iGYRO_OK = 0;
				return true;
			}
			iGYRO_OK = 0;
		}
	}
	else if (iCheckTime < 40)
	{
		if (iCheckTime == 39)
		{
			bSucc = (iGYRO_OK > 15 && wm.m_vSelfPos.Vz > MIN_H);
			iCheckTime = 0;
			iVz_OK = 0;
			iGYRO_OK = 0;
			if (bSucc) return true;
		}
	}
	else
	{
		if (wm.m_vSelfPos.Vz < MIN_H)
		{
			bSucc = false;
			iCheckTime = 0;
			iVz_OK = 0;
			iGYRO_OK = 0;
			return true;
		}

		if (v.GetMod() < 0.5)
		{
			bSucc = true;
			iCheckTime = 0;
			iVz_OK = 0;
			iGYRO_OK = 0;
			return true;
		}
	}

	bSucc = false;
	return false;

}


 
bool Skill::ClimbOnGround(bool bClear) //Climb dunqiaobao
{
	static int iDoNum = 0;
	static int iCheckGyro = 0;
	static FALLTYPE FallType = FALL;
	static bool bFirstGetFallType = false;
	static bool bInitOver = false;
	static bool bClimbOver = false;
	static bool bCheckSuccOver = false;
	static bool bSucc = false;
	static bool bDelayOver = false;

	if (bClear)
	{
		iDoNum = 0;
		iCheckGyro = 0;
		FallType = FALL;
		bFirstGetFallType = false;
		bInitOver = false;
		bClimbOver = false;
		bCheckSuccOver = false;
		bSucc = false;
		return true;
	}

	if (!bFirstGetFallType)
	{
		FallType = wm.m_FallState;
		bFirstGetFallType = true;
	}

	if (!bDelayOver)
	{
		bDelayOver = Delay(150);
		if (!bDelayOver) return false;
	}

	if (!bInitOver)
	{
		if (FallType == FALL_DOWN)
		{
			/** 判断是面朝下倒，这时需要先做预备动作，但可能判断有误，所以中途可以检测某些量，如果有问题就不是面朝下倒，而是面朝上倒 */
			bInitOver = ACT.PrepareToGetUp();
			if (fabs(wm.m_Gyro.dx) < 5)
			{
				iCheckGyro++;
				if (iCheckGyro > 15)
				{
					bInitOver = true;
					iCheckGyro = 0;
					FallType = FALL_UP;
				}
			}
		}
		else if (FallType == FALL_UP)
		{
			/** 现在没有问题，这时判断错了也可以爬起 */
			bInitOver = true;
		}
		if (!bInitOver) return false;
	}

	if (!bClimbOver)
	{
		bClimbOver = (FallType == FALL_UP ? ACT.Climb_FaceUp() : ACT.Climb_FaceDown());
		if (!bClimbOver) return false; 
	}

/**
	if (!bCheckSuccOver)
	{
		bCheckSuccOver = CheckClimbSucc(bSucc);
		if (bCheckSuccOver) iDoNum++;
		if (!bCheckSuccOver) return false;
	}
*/
	bSucc = true;

	if (bSucc)
	{
		iDoNum = 0;
		iCheckGyro = 0;
		FallType = FALL;
		bFirstGetFallType = false;
		bInitOver = false;
		bClimbOver = false;
		bCheckSuccOver = false;
		bSucc = false;
		bDelayOver = false;
		wm.UpdateFallState(1);
		return true;
	}

	return false;

}



bool Skill::TurnTo(double dBodyAngle, bool bClear)
{
	static int iFirstTurnNum = 0;
	static int iTurnType = 0;
	static bool bFirstCheckOver = false;
	static bool bFirstTurnOver = false;
	static bool bUseSmallTurn = true;
	static bool bTurnOnceOver = true;
	static bool bLastTurn = false;

	double dTurnAngle = dBodyAngle - wm.m_dBodyAng;
	NormalizeAng(dTurnAngle);
	double dAbsAngle = fabs(dTurnAngle);

	if (bClear) goto CLEAR;

	if (!bFirstCheckOver)
	{
		if (dAbsAngle < 3) return true;
		if (dAbsAngle < 8) iFirstTurnNum = 1;
		else iFirstTurnNum = 2;
		if (dAbsAngle > 40) bUseSmallTurn = false;
		bFirstCheckOver = true;
	}

	if (!bFirstTurnOver)
	{
		if (bTurnOnceOver)
		{
			if (iFirstTurnNum == 0)
			{
				bFirstTurnOver = true;
				goto CHECK;
			}
			else iTurnType = dTurnAngle > 0 ? 1 : -1;
		}
		goto DO;
	}

	if (!bTurnOnceOver) goto DO;

CHECK:

	if (dTurnAngle > 0)
	{
		iTurnType = bUseSmallTurn ? 1 : 2;
	}
	else iTurnType = bUseSmallTurn ? -1 : -2;

	if (dAbsAngle < 10)
	{
		iTurnType = dTurnAngle > 0 ? 1 : -1;
	}

DO:
	switch (iTurnType)
	{
		case 1:   bTurnOnceOver = ACT.TurnLeft();  break;
		case 2:   bTurnOnceOver = ACT.TurnLeft(1);  break;
		case -1:  bTurnOnceOver = ACT.TurnRight();  break;
		case -2:  bTurnOnceOver = ACT.TurnRight(1);  break;
	}

	if (bLastTurn && bTurnOnceOver) goto CLEAR;

	if (bTurnOnceOver)
	{
		if (dAbsAngle < 5) goto CLEAR;
		if (dAbsAngle < 10) bLastTurn = true;
		iFirstTurnNum--;
	}

	return false;

CLEAR:

//	iFirstTurnNum = 0;
//	iTurnType = 0;
	bFirstCheckOver = false;
	bFirstTurnOver = false;
	bUseSmallTurn = true;
	bTurnOnceOver = true;
	bLastTurn = false;

	return true;

}


bool Skill::WalkToForward(Vector vTargetPos, bool bClear)
{
	static bool bNeedCheckTurn = true;
	static bool bNeedTurn = false;
	static bool bTurnOver = false;
	static bool bNeedDelay = false;
	static bool bDelayOver = false;
	static bool bWalkOnceOver = true;
	static bool bNeedEnd = false;
	static bool bEndOver = false;
	static bool bLastWalkOver = false;
	static bool bCheckLastWalkNum = false;
	static int iLastWalk = 2;
	static bool bDoLastAct = false;
	static bool bSquatOver = true;
	static bool bLastActOver = false;

/**  走1步的距离为0.15左右 */

	Vector vMeToPos = vTargetPos - wm.m_vSelfPos;
	vMeToPos.SetVz(0);
	double dMeToPosXYAngle = vMeToPos.GetXYAngle();
	double dDeltaAngle = dMeToPosXYAngle - wm.m_dBodyAng;
	NormalizeAng(dDeltaAngle);
	double dDist = vMeToPos.GetMod();

	if (bClear) goto CLEAR;
	if (bDoLastAct) goto LASTACT;
	if (bNeedEnd) goto LASTWALK;

	if (bNeedCheckTurn && bWalkOnceOver)
	{
		if (dDist < 0.08) goto CLEAR;

		if (fabs(dDeltaAngle) > 20)
		{
			bNeedTurn = true;
			bTurnOver = false;
		}
		bNeedCheckTurn = false;
	}

	if (bNeedTurn && !bTurnOver)
	{
		bTurnOver = TurnTo(dMeToPosXYAngle);
		if (bTurnOver)
		{
			bNeedTurn = false;
			bNeedDelay = true;
			bDelayOver = false;
		}
		return false;
	}


	if (bNeedDelay && !bDelayOver)
	{
		bDelayOver = ACT.Squat();//Delay(10); //10
		if (bDelayOver)
		{
			bNeedDelay = false;
		}
		return false;
	}


	if (fabs(dDeltaAngle) > 30 && bWalkOnceOver)
	{
		bNeedCheckTurn = true;
		return false;
	}

	if (dDeltaAngle > 10) bWalkOnceOver = ACT.Walk(1);
	else if (dDeltaAngle < -10) bWalkOnceOver = ACT.Walk(-1);
	else bWalkOnceOver = ACT.Walk();

	if (dDist < 0.6 && bWalkOnceOver) bNeedEnd = true;

	return false;


LASTWALK:

	if (!bEndOver)
	{
		if (!bCheckLastWalkNum)
		{
			if (dDist < 0.2) bEndOver = true;
			else if (dDist < 0.4) iLastWalk = 1;
			else if (dDist < 0.6) iLastWalk = 2;
			bCheckLastWalkNum = true;
		}

		if (iLastWalk > 0) bLastWalkOver = ACT.Walk();
		if (bLastWalkOver) iLastWalk--;
		if (iLastWalk <= 0 && bLastWalkOver) bEndOver = true;

	}

	if (bEndOver)
	{
		bDoLastAct = true;
		bNeedEnd = false;
		goto LASTACT;
	}

	return false;

LASTACT:

	if (!bLastActOver)
	{
		bLastActOver = ACT.Walk(10);
		if (!bLastActOver) return false;
		else bSquatOver = false;
	}

	if (!bSquatOver)
	{
		bSquatOver = ACT.Squat();
		if (!bSquatOver) return false;
		else goto CLEAR;
	}

	return false;

CLEAR:

	bNeedCheckTurn = true;
	bNeedTurn = false;
	bTurnOver = false;
	bNeedDelay = false;
	bDelayOver = false;
	bWalkOnceOver = true;
	bNeedEnd = false;
	bEndOver = false;
	bLastWalkOver = false;
	bCheckLastWalkNum = false;
	iLastWalk = 2;
	bSquatOver = true;
	bDoLastAct = false;
	bLastActOver = false;
	ACT.Walk(0, true);

cout<<"*******************************************                  "<<endl;
	return true;
}



bool Skill::WalkForwardStop(bool bClear)
{
	static bool bLastWalkOver = false;
	static bool bSquatOver = true;

	if (bClear)
	{
		bLastWalkOver = false;
		bSquatOver = true;
		return true;
	}

	if (!bLastWalkOver) bLastWalkOver = ACT.Walk(10);
	if (bLastWalkOver) bSquatOver = false;
	else return false;
	if (!bSquatOver)
	{
		bSquatOver = ACT.Squat();
		if (bSquatOver)
		{
			bLastWalkOver = false;
			return true;
		}
		else return false;
	}
}


bool Skill::StopWalkBack( bool bClear)
{
	static bool bStep1 = false;
	static bool bStep2 = false;
	if (bClear) goto CLEAR;
	
	if(!bStep1)
		bStep1 = ACT.WalkBackEx(2);
	if(bStep1 && !bStep2)
		bStep2 = ACT.Squat();
	if(bStep2)
		return true;
	else return false;

CLEAR:

	bStep1 = false;
	bStep2 = false;
	return true;
}


bool Skill::TurnToForDynamicWalk(double dBodyAngle, bool bClear)
{
	static bool bTurnOver = false;
	static bool bSquatOver = true;

	if (bClear)
	{
		bTurnOver = false;
		bSquatOver = true;
		return true;
	}

	if (!bTurnOver) bTurnOver = TurnTo(dBodyAngle);
	if (bTurnOver) bSquatOver = true;
	else return false;
	if (!bSquatOver)
	{
		bSquatOver = ACT.Squat();
		if (bSquatOver)
		{
			bTurnOver = false;
			return true;
		}
		else return false;
	}
}


bool Skill::WalkToForwardEx(Vector vTargetPos, Vector vTempPos, double dDestinationAng, bool bClear)
{
	static bool bFirstCheck = false;
	static bool bNeedCheckTurn = true;
	static bool bNeedTurn = false;
	static bool bTurnOver = false;
	static bool bNeedSquat = false;
	static bool bSquatOver = false;
	static bool bWalkOnceOver = true;
	static bool bNeedDoLastWalk = false;
	static bool bLastWalkOver = false;
	static bool bNeedWalkStop = false;
	static bool bWalkStopOver = false;

/**  走1步的距离为0.15左右 */

	Vector vMeToPos = vTempPos - wm.m_vSelfPos;
	vMeToPos.SetVz(0);
	double dMeToPosXYAngle = vMeToPos.GetXYAngle();
	double dDeltaAngle = dMeToPosXYAngle - wm.m_dBodyAng;
	NormalizeAng(dDeltaAngle);
	double dDist = vMeToPos.GetMod();

	if (bClear) goto CLEAR;
	if (bNeedWalkStop) goto WALKSTOP;
	if (bNeedDoLastWalk) goto LASTWALK;

	if (!bFirstCheck)
	{
		if (dDist < 0.08) goto CLEAR;
		
		if (fabs(dDeltaAngle) > 20)
		{
			bNeedTurn = true;
			bTurnOver = false;
		}
		bNeedCheckTurn = false;
		bFirstCheck = true;
	}

	if (bNeedCheckTurn && bWalkOnceOver)
	{
		if (dDist < 0.08) goto CLEAR;

		if (fabs(dDeltaAngle) > 20)
		{
			bNeedTurn = true;
			bTurnOver = false;
			bNeedWalkStop = true;
		}
		bNeedCheckTurn = false;
	}

	if (bNeedTurn && !bTurnOver)
	{
		if (dDist > 0.3)
			bTurnOver = TurnToForDynamicWalk(dMeToPosXYAngle);
		else bTurnOver = TurnToForDynamicWalk(dDestinationAng);

		if (bTurnOver)
		{
			bNeedTurn = false;
		}
		else return false;
	}

	if (fabs(dDeltaAngle) > 30 && bWalkOnceOver)
	{
		bNeedCheckTurn = true;
		bNeedWalkStop = true;
		return false;
	}


WALK:
cout<<"WALK WALK WALK WALK WALK WALK "<<endl;
	if (dDeltaAngle > 5) bWalkOnceOver = ACT.Walk(1);
	else if (dDeltaAngle < -5) bWalkOnceOver = ACT.Walk(-1);
	else bWalkOnceOver = ACT.Walk();

	if (dDist < 0.2 && bWalkOnceOver) bNeedDoLastWalk = true;

	return false;


LASTWALK:
cout<<"LASTWALK LASTWALK LASTWALK LASTWALK "<<endl;
	if (!bLastWalkOver)
	{
		double dLastDeltaAng = dDestinationAng - wm.m_dBodyAng;

		if (dLastDeltaAng > 5) bLastWalkOver = ACT.Walk(1);
		else if (dLastDeltaAng < -5) bLastWalkOver = ACT.Walk(-1);
		else bLastWalkOver = ACT.Walk();

		if (bLastWalkOver)
		{
			bNeedWalkStop = true;
		}
		return false;
	}

	if (bNeedWalkStop) goto WALKSTOP;
	else goto CLEAR;

	return false;

WALKSTOP:
cout<<"WALKSTOP WALKSTOP WALKSTOP WALKSTOP "<<endl;
	if (bNeedWalkStop && !bWalkStopOver)
	{
		bWalkStopOver = WalkForwardStop();
		if (bWalkStopOver)
		{
			bNeedWalkStop = false;
			bWalkStopOver = false;
		}
		else return false;

	}

	return false;


CLEAR:

	bFirstCheck = false;
	bNeedCheckTurn = true;
	bNeedTurn = false;
	bTurnOver = false;
	bNeedSquat = false;
	bSquatOver = false;
	bWalkOnceOver = true;
	bNeedDoLastWalk = false;
	bLastWalkOver = false;
	bNeedWalkStop = false;
	bWalkStopOver = false;

	ACT.Walk(0, true);

cout<<"****************************************************************************"<<endl;
	return true;
}


bool Skill::WalkToForwardEx(Vector vTargetPos, double dDestinationAng)//walk_2    dunqiaobao
{
	return WalkToForwardEx(vTargetPos, wm.GetTentativePosForOmdiWalk(vTargetPos, dDestinationAng), dDestinationAng);
}


bool Skill::WalkToBack(Vector vTargetPos, bool bClear)  //walk_back  dunqiaobao
{
	static bool bNeedCheckTurn = true;
	static bool bNeedTurn = false;
	static bool bTurnOver = false;
	static bool bNeedDelay = false;
	static bool bDelayOver = false;
	static bool bWalkOnceOver = true;
	static bool bNeedEnd = false;
	static bool bEndOver = false;
	static bool bLastWalkOver = false;
	static bool bCheckLastWalkNum = false;
	static int iLastWalk = 2;
	static int iWalkType = 0;
	static bool bDoLastAct = false;
	bool bLastActOver;

/**  走1步的距离为0.15左右 */

	Vector vMeToPos = vTargetPos - wm.m_vSelfPos;
	vMeToPos.SetVz(0);
	double dMeToPosXYAngle = vMeToPos.GetXYAngle();
	double dMyBodyBackAngle = wm.m_dBodyAng + 180;
	NormalizeAng(dMyBodyBackAngle);
	double dDeltaAngle = dMeToPosXYAngle - dMyBodyBackAngle;
	NormalizeAng(dDeltaAngle);

	double dDist = vMeToPos.GetMod();

	if (bClear) goto CLEAR;
	if (bDoLastAct) goto LASTACT;
	if (bNeedEnd) goto LASTWALK;

	if (bNeedCheckTurn && bWalkOnceOver)
	{
		if (dDist < 0.08) goto CLEAR;

		if (fabs(dDeltaAngle) > 20)
		{
			bNeedTurn = true;
			bTurnOver = false;
		}
		bNeedCheckTurn = false;
	}

	if (bNeedTurn && !bTurnOver)
	{
		bTurnOver = TurnTo(dMeToPosXYAngle + 180);
		if (bTurnOver)
		{
			bNeedTurn = false;
			bNeedDelay = true;
			bDelayOver = false;
		}
		return false;
	}




	if (bNeedDelay && !bDelayOver)
	{
		bDelayOver = ACT.Squat();//Delay(10); //10
		if (bDelayOver)
		{
			bNeedDelay = false;
		}
		return false;
	}


	if (fabs(dDeltaAngle) > 30 && bWalkOnceOver)
	{
		bNeedCheckTurn = true;
		return false;
	}


	if (bWalkOnceOver)
	{
		if (dDeltaAngle > 5) iWalkType = -1;
		else if (dDeltaAngle < -5)  iWalkType = 1;
		else  iWalkType = 0;
	}

DO:

	bWalkOnceOver = ACT.WalkBackEx(iWalkType);


	if (dDist < 0.5 && bWalkOnceOver) bNeedEnd = true;

	return false;


LASTWALK:

	if (!bEndOver)
	{
		if (!bCheckLastWalkNum)
		{
			if (dDist < 0.1) bEndOver = true;
			else if (dDist < 0.25) iLastWalk = 1;
			else if (dDist < 0.4) iLastWalk = 2;
			bCheckLastWalkNum = true;
		}

		if (iLastWalk > 0) bLastWalkOver = ACT.WalkBackEx();
		if (bLastWalkOver) iLastWalk--;
		if (iLastWalk <= 0 && bLastWalkOver) bEndOver = true;

	}

	if (bEndOver)
	{
		bDoLastAct = true;
		bNeedEnd = false;
		goto LASTACT;
	}

	return false;

LASTACT:

	bLastActOver = StopWalkBack();
	if (bLastActOver) goto CLEAR;//bDoLastAct = false;
	
	return false;

CLEAR:

	bNeedCheckTurn = true;
	bNeedTurn = false;
	bTurnOver = false;
	bNeedDelay = false;
	bDelayOver = false;
	bWalkOnceOver = true;
	bNeedEnd = false;
	bEndOver = false;
	bLastWalkOver = false;
	bCheckLastWalkNum = false;
	iLastWalk = 2;
	iWalkType = 0;
	bDoLastAct = false;
	ACT.WalkBackEx(0, true);

cout<<"****************************************************************************"<<endl;
	return true;
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
bool Skill::KickBall(bool clear)
{
	if(clear) goto CLEAR;
	static bool bStep1 = false;
	static bool bStep2 = false;
	if(!bStep1) bStep1 = ACT.Squat();//ACT.StaticWalk(3);
	if(bStep1 && !bStep2)
	{	
		if(SenseParse.m_PolBallPos.PolPos.Py < 0) bStep2 =ACT.KickRight();
		else bStep2 = ACT.KickLeft();
	
	}
	if(bStep2)
	{
		goto CLEAR;
	}
	return false;
CLEAR:
	bStep1 = bStep2 = false;
	return true;
}

bool Skill::KickBallSmall(bool clear)
{
	if(clear) goto CLEAR;
	static bool bStep1 = false;
	static bool bStep2 = false;
	if(!bStep1) bStep1 = ACT.Squat(); //ACT.StaticWalk(3);
	if(bStep1 && !bStep2)
	{	
		if(SenseParse.m_PolBallPos.PolPos.Py < 0) bStep2 =ACT.KickSmallRight();
		else bStep2 = ACT.KickSmallLeft();
	
	}
	if(bStep2)
	{
		goto CLEAR;
	}
	return false;
CLEAR:
	bStep1 = bStep2 = false;
	return true;
}

bool Skill::StepToKick(Vector vTarget, bool clear)
{
	static bool bDone = false;
	static bool bLastAct = false;
	static bool bFirstCheck = false;
	static int iMoveType = 0;
	static bool bIsSquatOver = false;
	Vector vMeRelBall = wm.GetMeRelBall(vTarget);
	double dis = vMeRelBall.Vx;
	if(clear) goto CLEAR;

	if (!bFirstCheck)
	{
		if(!bIsSquatOver)
		{
			bIsSquatOver = true;//ACT.Squat();
			return false;
		}
		if (dis > -0.22 && dis < -0.16) return true;
		else bFirstCheck = true;
	}

	if (!bLastAct && dis > -0.22 && dis < -0.16)
	{
		if (bDone) goto CLEAR;
			else bLastAct = true;
	}

	if (bLastAct && bDone) goto CLEAR;

	if (!bLastAct)
	{
		if(dis < -0.22) iMoveType = 1;//Forward
		else iMoveType = 2;//Back
	}
DO:
	switch (iMoveType)
	{
		case 1: bDone = ACT.WalkSmall();break;//ACT.Step(0);break; //
		case 2: bDone = ACT.WalkBackSmall();//ACT.Step(6);
	}
	return false;
	
CLEAR:
	bDone = false;
	bLastAct = false;
	bFirstCheck = false;
	bIsSquatOver = false;
	iMoveType = 0;
	return true;
}

bool Skill::TurnToKick(Vector vTarget, bool clear)
{	
	cout<<"I'm doing TurnToKick"<<endl;
	bool bTurnToKick = false;
	Vector vBallToGoal = vTarget - wm.m_vBallPos;
	vBallToGoal.SetVz(0);
	double dAngle = vBallToGoal.GetXYAngle();
	bTurnToKick = TurnTo(dAngle,clear);
	if(bTurnToKick) return true;
	return false;
 }

bool Skill::MoveToKick(Vector vTarget, bool clear)
{
	cout<<"I'm doing MoveToKick"<<endl;
	Vector vMeRelBall = wm.GetMeRelBall(vTarget);
	double dCalcMove = vMeRelBall.Vy;
	static bool bDone = false;
	static bool bLastAct = false;
	static bool bFirstCheck = false;
	static int iMoveType = 0;
	static bool bIsSquatOver = false;
	if(clear) goto CLEAR;
	if (!bFirstCheck)
	{
		if ( (dCalcMove > 0.01 && dCalcMove < 0.06) || (dCalcMove > -0.06 && dCalcMove < - 0.01) ) return true;
		else bFirstCheck = true;
	}

	if (dCalcMove > 0 && iMoveType == 2 && !bDone)
		goto DO;
	else if (dCalcMove < 0 && iMoveType == 1 && !bDone)
		goto DO;

	if (!bLastAct &&  ( (dCalcMove > 0.01 && dCalcMove < 0.06) || (dCalcMove > -0.06 && dCalcMove < - 0.01) ) )
	{
		if (bDone) goto CLEAR;
			else bLastAct = true;
	}

	if (bLastAct && bDone) goto CLEAR;

	if (!bLastAct)
	{
		if(dCalcMove > 0 && dCalcMove < 0.01 || dCalcMove < -0.06)
			iMoveType = 1;//Left
		else	
			iMoveType = 2;//Right
	}
	
DO:
	switch (iMoveType)
	{
		case 1: bDone = ACT.Move(1);break;//ACT.Step(9); break;
		case 2: bDone = ACT.Move(-1);//ACT.Step(3);
	}
	return false;
	
CLEAR:
	bDone = false;
	bLastAct = false;
	bFirstCheck = false;
	bIsSquatOver = false;
	iMoveType = 0;
	return true;
}

bool Skill::MoveOutBall(Vector vTarget, bool clear)
{
	cout<<"I'm doing MoveOutBall"<<endl;
	Vector vMeRelBall = wm.GetMeRelBall(vTarget);
	double dCalcMove = vMeRelBall.Vy;
	static bool bDone = false;
	static bool bLastAct = false;
	static bool bFirstCheck = false;
	static int iMoveType = 0;
	static bool bIsSquatOver = false;
	if(clear) goto CLEAR;
	if (!bFirstCheck)
	{
		if (abs(dCalcMove) - 0.3 > 0) return true;
		else bFirstCheck = true;
	}

	if (dCalcMove > 0 && iMoveType == 2 && !bDone)
		goto DO;
	else if (dCalcMove < 0 && iMoveType == 1 && !bDone)
		goto DO;

	if (!bLastAct && abs(dCalcMove) - 0.3 > 0)
	{
		if (bDone) goto CLEAR;
			else bLastAct = true;
	}

	if (bLastAct && bDone) goto CLEAR;

	if (!bLastAct)
	{
		if(dCalcMove > 0)
			iMoveType = 1;//Left
		else	
			iMoveType = 2;//Right
	}
	
DO:
	switch (iMoveType)
	{
		case 1: bDone = ACT.Move(1);break;//ACT.Step(9); break;
		case 2: bDone = ACT.Move(-1);//ACT.Step(3);
	}
	return false;
	
CLEAR:
	bDone = false;
	bLastAct = false;
	bFirstCheck = false;
	bIsSquatOver = false;
	iMoveType = 0;
	return true;
}

bool Skill::StepBack(Vector vTarget, bool clear)
{
	cout<<"I'm doing StepBack"<<endl;
	Vector vMeRelBall = wm.GetMeRelBall(vTarget);
	double vDis = vMeRelBall.Vx;
	static bool bDone = false;
	static bool bLastAct = false;
	static bool bFirstCheck = false;
	static int iMoveType = 0;
	static bool bIsSquatOver = false;
	if(clear) goto CLEAR;
	
 	//cout<<"Dis:::::::::::;"<<vDis<<endl;
	if (!bFirstCheck)
	{
		if (vDis < -0.2) return true;
		else bFirstCheck = true;
	}

	if (!bLastAct && vDis < -0.2)
	{
		if (bDone) goto CLEAR;
			else bLastAct = true;
	}

	if (bLastAct && bDone) goto CLEAR;

	if (!bLastAct)
	{
		//if(dDisToBall > 0.1)
			iMoveType = 1;//Left
	}
	
DO:
	switch (iMoveType)
	{
		case 1: bDone = ACT.WalkBackSmall();//ACT.Step(6);
	}
	return false;
	
CLEAR:
	bDone = false;
	bLastAct = false;
	bFirstCheck = false;
	bIsSquatOver = false;
	iMoveType = 0;
	return true;
}

bool Skill::MoveToPos(Vector vTarget, bool clear)
{
	
	Vector vMeRelPos = vTarget - wm.m_vSelfPos;
	double dMoveDis = vMeRelPos.Vy;
	static bool bDone = false;
	static bool bLastAct = false;
	static bool bFirstCheck = false;
	static int iMoveType = 0;
	static bool bIsSquatOver = false;
	if(clear) goto CLEAR;
	cout<<"I'm doing MoveToPos"<<endl;
	if (!bFirstCheck)
	{
		if ( fabs(dMoveDis) < 0.02 ) return true;
		else bFirstCheck = true;
	}

	if (!bLastAct &&  (fabs(dMoveDis) < 0.02) )
	{
		if (bDone) goto CLEAR;
			else bLastAct = true;
	}

	if (bLastAct && bDone) goto CLEAR;

	if (!bLastAct)
	{
		if(dMoveDis > 0)
			iMoveType = 1;//Left
		else	
			iMoveType = 2;//Right
	}
	
DO:
	switch (iMoveType)
	{
		case 1: bDone = ACT.Move(1);break;//ACT.Step(9); break;
		case 2: bDone = ACT.Move(-1);//ACT.Step(3);
	}
	return false;
	
CLEAR:
	bDone = false;
	bLastAct = false;
	bFirstCheck = false;
	bIsSquatOver = false;
	iMoveType = 0;
	return true;
}

bool Skill::StepToPos(Vector vTarget, bool clear)
{
	static bool bDone = false;
	static bool bLastAct = false;
	static bool bFirstCheck = false;
	static int iMoveType = 0;
	static bool bIsSquatOver = false;
	Vector vMeRelPos = vTarget - wm.m_vSelfPos;
	double dis = vMeRelPos.Vx;
	if(clear) goto CLEAR;

	if (!bFirstCheck)
	{
		if(!bIsSquatOver)
		{
			bIsSquatOver = true;//ACT.Squat();
			return false;
		}
		if (fabs(dis) < 0.02) return true;
		else bFirstCheck = true;
	}

	if (!bLastAct && (fabs(dis) < 0.02))
	{
		if (bDone) goto CLEAR;
			else bLastAct = true;
	}

	if (bLastAct && bDone) goto CLEAR;

	if (!bLastAct)
	{
		if(dis > 0) iMoveType = 1;//Forward
		else iMoveType = 2;//Back
	}
DO:
	switch (iMoveType)
	{
		case 1: bDone = ACT.WalkSmall();break;//ACT.Step(0);break; //
		case 2: bDone = ACT.WalkBackSmall();//ACT.Step(6);//
	}
	return false;
	
CLEAR:
	bDone = false;
	bLastAct = false;
	bFirstCheck = false;
	bIsSquatOver = false;
	iMoveType = 0;
	return true;
}

bool Skill::MicroAdjustForShoot(Vector vTarget, bool stop,bool clear)
{
	static bool bTurnToKick = false;
	static bool bMoveOutBall = false;
	static bool bMoveToKick = false;
	static bool bStepToKick = false;
	static bool bKickBall = false;
	static bool bStepBack = false;
	static bool bCanKick = false;
	static bool bFaceBall = false;
	static bool bCheckFaceBall = false;
	static bool checkArea = false;
	static bool bDoingSquat = false;
	static bool bSquat = false;
	static bool bDelay = false;
	static bool bSquat2 = false;
	static bool bStandUp_Fast = false;
	static bool bCheckKick = false;

	static bool bCanStepBack = false;
	static bool bCanMoveToKick = false;
	static bool bCanStepToKick = false;

	static int areaType;
	static int againNum = 0;
	static bool	isOnce = false;	
	if(clear) goto CLEAR;
	if(stop) goto STOP;
	
	if(bDoingSquat && againNum < 4) goto AGAIN;

	if(againNum > 3) {bTurnToKick = bMoveOutBall = bMoveOutBall = bStepBack = bCanKick = bDelay = bCanStepBack = bCanMoveToKick = bCanStepToKick = true;}

	if(!isOnce)
	{
		//记录当前的Skill
		//CurrSkill = ADJUST_SKILL;
		isOnce = true;
	}
	if(!checkArea)
	{
		areaType = wm.InWhichArea(vTarget);
		checkArea = true;
	}

	//if(areaType == 0) return true;
	if(areaType == 1) { bMoveOutBall = true; bStepBack = true;}
	else if(areaType == 2) { bMoveOutBall = true;}
	else if(areaType == 3) {}

	if(checkArea && !bDoingSquat){

	if(!bTurnToKick)
	{
		bTurnToKick = TurnToKick(vTarget);
	}

	if(bTurnToKick && !bMoveOutBall)
	{
		if(wm.IsTurnToKick(vTarget)) bMoveOutBall = MoveOutBall(vTarget);
		else
		{
			cout<<"I will do TurnToKick() again."<<endl;
			bDoingSquat = true;
			goto AGAIN;
		}
	}
	
	if(bTurnToKick && bMoveOutBall && !bStepBack)
	{
		if(wm.IsTurnToKick(vTarget))
		{	
			if(!bCanStepBack)
			{
				//double banlance = wm.m_torso.dx * wm.m_torso.dx + wm.m_torso.dy * wm.m_torso.dy;
				//cout<<"Torso::::::::"<<	banlance<<endl;
				//if(banlance < 0.7)
				bCanStepBack = true;
			}
			else bStepBack = StepBack(vTarget);
		}
		else
		{
			cout<<"I will do StepBack() again."<<endl;
			bDoingSquat = true;
			goto AGAIN;
		}
		
	}

	if(bTurnToKick && bStepBack && !bMoveToKick)
	{
		if(wm.IsTurnToKick(vTarget))
		{
			if(!bCanMoveToKick)
			{
				//double banlance = wm.m_torso.dx * wm.m_torso.dx + wm.m_torso.dy * wm.m_torso.dy;
				//cout<<"Torso::::::::"<<	banlance<<endl;
				//if(banlance < 0.2)
				 bCanMoveToKick = true;
			}
			else bMoveToKick = MoveToKick(vTarget);
		}
		else
		{
			cout<<"I will do MoveToKick() again."<<endl;
			bDoingSquat = true;
			goto AGAIN;
		}
		
	}

	if(bMoveToKick && !bStepToKick)
	{
		if(wm.IsFaceBall(vTarget))
		{
			if(!bCanStepToKick)
			{
				//double banlance = wm.m_torso.dx * wm.m_torso.dx + wm.m_torso.dy * wm.m_torso.dy;
				//cout<<"Torso::::::::"<<	banlance<<endl;
				//if(banlance < 0.2)
				 bCanStepToKick = true;
			}	
			bStepToKick = StepToKick(vTarget);
		}
		else
		{
			cout<<"I will do StepToKick() again."<<endl;
			bDoingSquat = true;
			goto AGAIN;
		}
	}

	if(bStepToKick && !bDelay)
	{
		cout<<"Footfall::::::::::"<<endl;
		//CurrSkill = NONE_SKILL;
		//act_kick = ACT_KICK;
		bDelay = TurnToKick(vTarget);//true;//Delay(400);
	}
	/*
	if(bDelay && !bSquat2)
	{
		bSquat2 = ACT.Squat();
	}
	
	if(bSquat2 && !bStandUp_Fast)
	{
		bStandUp_Fast = ACT.StandUp_Fast();
	}
	
	if(bStandUp_Fast && !bCheckKick)
	{
		//vMeRelBall = wm.GetMeRelBall();
		//dCalcMove = wm.CalcMoveToKick();
		//cout<<"vMeRelBall::::"<<vMeRelBall<<endl;
		//cout<<"vMySelfPos:::"<<wm.m_vSelfPos<<endl;
		double banlance = wm.m_torso.dx * wm.m_torso.dx + wm.m_torso.dy * wm.m_torso.dy;
		cout<<"Torso::::::::"<<	banlance<<endl;
		//dCalcMove  = SenseParse.m_pRelBallPos.pPos.Py;
		if(banlance < 0.05) bCheckKick = true;
		else bCheckKick = false;
	}*/

	if(bDelay && !bCanKick)
	{
		if(wm.IsKickable(vTarget)) {
			bCanKick = true;
			cout<<"Yes,I can kick ball!"<<endl;
		}
		else{
			cout<<"Sorry,I can't kick ball.I will do it again.";
			bDoingSquat = true;
			goto AGAIN;
		}
	}

	if(bCanKick && !bKickBall)
	{
		bKickBall = KickBall();
	}

	
	if(bKickBall) goto CLEAR;
		
	return false;
}

AGAIN:
	{
		if(!bSquat)
		{
			cout<<"Again:::::::::::::::::::"<<againNum<<endl;
			bDoingSquat = true;
			bSquat = Again();
		}
		else
		{
			againNum++;
			checkArea = bTurnToKick = bMoveOutBall = bMoveToKick
			= bStepToKick = bKickBall = bStepBack = bCanKick
			=bCheckFaceBall =bFaceBall= bSquat = bDoingSquat = bDelay = bCanStepBack = bCanMoveToKick = bCanStepToKick = bSquat2 = bStandUp_Fast = bCheckKick = false;
			//againNum = 0;
			TurnToKick(Vector(), true);
			MoveOutBall(Vector(),true);
			StepBack(Vector(),true);
			MoveToKick(Vector(),true);
			StepToKick(Vector(),true);
			KickBall(true);
			Again(true);
		}
		return false;
	}

CLEAR:
	{
		//CurrSkill = NONE_SKILL,act_kick = ACT_KICK_OVER;
		isOnce = checkArea = bTurnToKick = bMoveOutBall = bMoveToKick 
		= bStepToKick = bKickBall = bStepBack = bCanKick
		=bCheckFaceBall =bFaceBall= bSquat = bDoingSquat = bDelay = bCanStepBack =bCanMoveToKick = bCanStepToKick = bSquat2 = bStandUp_Fast = bCheckKick =false;
		againNum = 0;
		TurnToKick(Vector(),true);
		MoveOutBall(Vector(),true);
		StepBack(Vector(),true);
		MoveToKick(Vector(),true);
		StepToKick(Vector(),true);
		KickBall(true);
		Again(true);
		return true;
	}

STOP:
	
	{
		if(!bSquat)
		{
			cout<<"Stop:::::::::::::::::::"<<endl;
			bDoingSquat = true;
			bSquat = Again();
			return false;
		}
		else
		{
			//CurrSkill = NONE_SKILL;
			isOnce = checkArea = bTurnToKick = bMoveOutBall = bMoveToKick
			= bStepToKick = bKickBall = bStepBack = bCanKick
			=bCheckFaceBall =bFaceBall= bSquat = bDoingSquat = bDelay = bCanStepBack = bCanMoveToKick = bCanStepToKick = bSquat2 = bStandUp_Fast = bCheckKick = false;
			againNum = 0;
			TurnToKick(Vector(),true);
			MoveOutBall(Vector(),true);
			StepBack(Vector(),true);
			MoveToKick(Vector(),true);
			StepToKick(Vector(),true);
			KickBall(true);
			Again(true);
			return true;
		}
		return false;
	}	
}


bool Skill::MicroAdjustForFreeKick(Vector vTarget, bool stop,bool clear)
{
	static bool bTurnToKick = false;
	static bool bMoveOutBall = false;
	static bool bMoveToKick = false;
	static bool bStepToKick = false;
	static bool bKickBall = false;
	static bool bStepBack = false;
	static bool bCanKick = false;
	static bool bFaceBall = false;
	static bool bCheckFaceBall = false;
	static bool checkArea = false;
	static bool bDoingSquat = false;
	static bool bSquat = false;
	static bool bDelay = false;
	static bool bSquat2 = false;
	static bool bStandUp_Fast = false;
	static bool bCheckKick = false;

	static bool bCanStepBack = false;
	static bool bCanMoveToKick = false;
	static bool bCanStepToKick = false;

	static int areaType;
	static int againNum = 0;
	static bool	isOnce = false;	
	if(clear) goto CLEAR;
	if(stop) goto STOP;
	
	if(bDoingSquat && againNum < 4) goto AGAIN;

	if(againNum > 3) {bTurnToKick = bMoveOutBall = bMoveOutBall = bStepBack = bCanKick = bDelay = bCanStepBack = bCanMoveToKick = bCanStepToKick = true;}

	if(!isOnce)
	{
		//记录当前的Skill
		//CurrSkill = ADJUST_SKILL;
		isOnce = true;
	}
	if(!checkArea)
	{
		areaType = wm.InWhichArea(vTarget);
		checkArea = true;
	}

	//if(areaType == 0) return true;
	if(areaType == 1) { bMoveOutBall = true; bStepBack = true;}
	else if(areaType == 2) { bMoveOutBall = true;}
	else if(areaType == 3) {}

	if(checkArea && !bDoingSquat){

	if(!bTurnToKick)
	{
		bTurnToKick = TurnToKick(vTarget);
	}

	if(bTurnToKick && !bMoveOutBall)
	{
		if(wm.IsTurnToKick(vTarget)) bMoveOutBall = MoveOutBall(vTarget);
		else
		{
			cout<<"I will do TurnToKick() again."<<endl;
			bDoingSquat = true;
			goto AGAIN;
		}
	}
	
	if(bTurnToKick && bMoveOutBall && !bStepBack)
	{
		if(wm.IsTurnToKick(vTarget))
		{	
			if(!bCanStepBack)
			{
				//double banlance = wm.m_torso.dx * wm.m_torso.dx + wm.m_torso.dy * wm.m_torso.dy;
				//cout<<"Torso::::::::"<<	banlance<<endl;
				//if(banlance < 0.7)
				bCanStepBack = true;
			}
			else bStepBack = StepBack(vTarget);
		}
		else
		{
			cout<<"I will do StepBack() again."<<endl;
			bDoingSquat = true;
			goto AGAIN;
		}
		
	}

	if(bTurnToKick && bStepBack && !bMoveToKick)
	{
		if(wm.IsTurnToKick(vTarget))
		{
			if(!bCanMoveToKick)
			{
				//double banlance = wm.m_torso.dx * wm.m_torso.dx + wm.m_torso.dy * wm.m_torso.dy;
				//cout<<"Torso::::::::"<<	banlance<<endl;
				//if(banlance < 0.2)
				 bCanMoveToKick = true;
			}
			else bMoveToKick = MoveToKick(vTarget);
		}
		else
		{
			cout<<"I will do MoveToKick() again."<<endl;
			bDoingSquat = true;
			goto AGAIN;
		}
		
	}

	if(bMoveToKick && !bStepToKick)
	{
		if(wm.IsFaceBall(vTarget))
		{
			if(!bCanStepToKick)
			{
				//double banlance = wm.m_torso.dx * wm.m_torso.dx + wm.m_torso.dy * wm.m_torso.dy;
				//cout<<"Torso::::::::"<<	banlance<<endl;
				//if(banlance < 0.2)
				 bCanStepToKick = true;
			}	
			bStepToKick = StepToKick(vTarget);
		}
		else
		{
			cout<<"I will do StepToKick() again."<<endl;
			bDoingSquat = true;
			goto AGAIN;
		}
	}

	if(bStepToKick && !bDelay)
	{
		cout<<"Footfall::::::::::"<<endl;
		//CurrSkill = NONE_SKILL;
		//act_kick = ACT_KICK;
		bDelay = TurnToKick(vTarget);//true;//Delay(400);
	}
	/*
	if(bDelay && !bSquat2)
	{
		bSquat2 = ACT.Squat();
	}
	
	if(bSquat2 && !bStandUp_Fast)
	{
		bStandUp_Fast = ACT.StandUp_Fast();
	}
	
	if(bStandUp_Fast && !bCheckKick)
	{
		//vMeRelBall = wm.GetMeRelBall();
		//dCalcMove = wm.CalcMoveToKick();
		//cout<<"vMeRelBall::::"<<vMeRelBall<<endl;
		//cout<<"vMySelfPos:::"<<wm.m_vSelfPos<<endl;
		double banlance = wm.m_torso.dx * wm.m_torso.dx + wm.m_torso.dy * wm.m_torso.dy;
		cout<<"Torso::::::::"<<	banlance<<endl;
		//dCalcMove  = SenseParse.m_pRelBallPos.pPos.Py;
		if(banlance < 0.05) bCheckKick = true;
		else bCheckKick = false;
	}*/

	if(bDelay && !bCanKick)
	{
		if(wm.IsKickable(vTarget)) {
			bCanKick = true;
			cout<<"Yes,I can kick ball!"<<endl;
		}
		else{
			cout<<"Sorry,I can't kick ball.I will do it again.";
			bDoingSquat = true;
			goto AGAIN;
		}
	}

	if(bCanKick && !bKickBall)
	{
		bKickBall = KickBallSmall();
	}

	
	if(bKickBall) goto CLEAR;
		
	return false;
}

AGAIN:
	{
		if(!bSquat)
		{
			cout<<"Again:::::::::::::::::::"<<againNum<<endl;
			bDoingSquat = true;
			bSquat = Again();
		}
		else
		{
			againNum++;
			checkArea = bTurnToKick = bMoveOutBall = bMoveToKick
			= bStepToKick = bKickBall = bStepBack = bCanKick
			=bCheckFaceBall =bFaceBall= bSquat = bDoingSquat = bDelay = bCanStepBack = bCanMoveToKick = bCanStepToKick = bSquat2 = bStandUp_Fast = bCheckKick = false;
			//againNum = 0;
			TurnToKick(Vector(), true);
			MoveOutBall(Vector(),true);
			StepBack(Vector(),true);
			MoveToKick(Vector(),true);
			StepToKick(Vector(),true);
			KickBallSmall(true);
			Again(true);
		}
		return false;
	}

CLEAR:
	{
		//CurrSkill = NONE_SKILL,act_kick = ACT_KICK_OVER;
		isOnce = checkArea = bTurnToKick = bMoveOutBall = bMoveToKick 
		= bStepToKick = bKickBall = bStepBack = bCanKick
		=bCheckFaceBall =bFaceBall= bSquat = bDoingSquat = bDelay = bCanStepBack =bCanMoveToKick = bCanStepToKick = bSquat2 = bStandUp_Fast = bCheckKick =false;
		againNum = 0;
		TurnToKick(Vector(),true);
		MoveOutBall(Vector(),true);
		StepBack(Vector(),true);
		MoveToKick(Vector(),true);
		StepToKick(Vector(),true);
		KickBallSmall(true);
		Again(true);
		return true;
	}

STOP:
	
	{
		if(!bSquat)
		{
			cout<<"Stop:::::::::::::::::::"<<endl;
			bDoingSquat = true;
			bSquat = Again();
			return false;
		}
		else
		{
			//CurrSkill = NONE_SKILL;
			isOnce = checkArea = bTurnToKick = bMoveOutBall = bMoveToKick
			= bStepToKick = bKickBall = bStepBack = bCanKick
			=bCheckFaceBall =bFaceBall= bSquat = bDoingSquat = bDelay = bCanStepBack = bCanMoveToKick = bCanStepToKick = bSquat2 = bStandUp_Fast = bCheckKick = false;
			againNum = 0;
			TurnToKick(Vector(),true);
			MoveOutBall(Vector(),true);
			StepBack(Vector(),true);
			MoveToKick(Vector(),true);
			StepToKick(Vector(),true);
			KickBallSmall(true);
			Again(true);
			return true;
		}
		return false;
	}	
}

bool Skill::MicroAdjustForGoalKeeper(Vector vTarget, bool stop, bool clear)
{
	static bool bTurnTo = false;
	static bool bMoveToPos = false;
	static bool bStepToPos = false;
	static bool bOK = false;
	static bool bDoingSquat = false;
	static bool bSquat = false;
	static bool bDelay =false;
	static int againNum = 0;

	Vector vMeToPos = vTarget - wm.m_vSelfPos;
	//cout<<"My rel pos::::"<<vMeToPos<<endl;

	if(clear) goto CLEAR;
	if(stop) goto STOP;
	
	if(bDoingSquat && againNum < 4) goto AGAIN;

	if(againNum > 3) {
		/*if( (fabs(wm.m_dBodyAng) < 10) && (fabs(vMeToPos.Vy) < 0.2) && 
			(fabs(vMeToPos.Vx) < 0.2)) goto CLEAR;
			else goto AGAIN;*/
		goto CLEAR;
	}


	if(!bDoingSquat){

	if(!bTurnTo)
	{
		bTurnTo = TurnTo(0);
	}

	if(bTurnTo && !bDelay) bDelay = ACT.Squat();

	if(bDelay && !bMoveToPos)
	{
		if(fabs(wm.m_dBodyAng) < 20) bMoveToPos = MoveToPos(vTarget);
		else
		{
			cout<<"I will do TurnTo(0) again."<<endl;
			bDoingSquat = true;
			goto AGAIN;
		}
	}
	
	if(bMoveToPos && !bStepToPos)
	{
		if( (fabs(wm.m_dBodyAng) < 20) /*&& (fabs(vMeToPos.Vy) < 0.1)*/ )
		{
			bStepToPos = StepToPos(vTarget);
		}
		else
		{
			cout<<"I will do MoveTo() again."<<endl;
			bDoingSquat = true;
			goto AGAIN;
		}
	}

	if(bStepToPos && !bOK)
	{
		if( (fabs(wm.m_dBodyAng) < 20) && (fabs(vMeToPos.Vy) < 0.2) && 
			(fabs(vMeToPos.Vx) < 0.2) ){
			bOK = ACT.Squat();
			cout<<"Yes,I have walked to the pos."<<endl;
		}
		else{
			cout<<"Sorry,I have not walked to the pos.I will do it again.";
			bDoingSquat = true;
			goto AGAIN;
		}
	}

	if(bOK) goto CLEAR;

	return false;
	}

AGAIN:
	{
		if(!bSquat)
		{
			cout<<"Again:::::::::::::::::::"<<againNum<<endl;
			bDoingSquat = true;
			bSquat = Again();
			return false;
		}
		else
		{
			againNum++;
			bTurnTo = bMoveToPos = bStepToPos = bOK = bDoingSquat = bSquat = bDelay = false;
			TurnTo(true);
			MoveToPos(Vector(), true);
			StepToPos(Vector(), true);		
			Again(true);
			return false;
		}
		
}

CLEAR:
	{
		againNum =0;
		bTurnTo = bMoveToPos = bStepToPos = bOK = bDoingSquat = bSquat = bDelay = false;
		TurnTo(true);
		MoveToPos(Vector(), true);
		StepToPos(Vector(), true);
		Again(true);
		return true;
	}

STOP:
	{
		if(!bSquat)
		{
			cout<<"Stop:::::::::::::::::::"<<endl;
			bDoingSquat = true;
			bSquat = Again();
			return false;
		}
		else
		{
			againNum=0;
			bTurnTo = bMoveToPos = bStepToPos = bOK = bDoingSquat = bSquat = bDelay = false;
			TurnTo(true);
			MoveToPos(Vector(), true);
			StepToPos(Vector(), true);
			Again(true);
			return true;
		}
	}
}

bool Skill::Again(bool clear)
{
	static bool bStandUp = false;
	static bool bCheckTorso = false;
	static bool bSquat = false;
	if(clear)
	{
		bStandUp = bCheckTorso = bSquat;
		return true;
	}
	if(!bStandUp) bStandUp =true; //ACT.StandUp_Fast();
	if(bStandUp && !bCheckTorso)
	{
		bCheckTorso = true;
	}
	if(bCheckTorso && !bSquat)
	{
		bSquat = ACT.Squat();
	}
	if(bSquat)
	{
		bStandUp = bCheckTorso = bSquat = false;
		return true;
	}
	return false;
}
////////////////////////////////////////////////
//////////////////////////////// ///////////////



void Skill::ClearAll()  //clear static  dunqiaobao
{
	Vector o;
	ClimbOnGround(true);
	TurnTo(0, true);
	TurnToForDynamicWalk(0, true);
	WalkToForward(o, true);
	WalkForwardStop(true);
	WalkToForwardEx(o, o, 0, true);
	WalkToBack(o, true);
	bool r;
	CheckClimbSucc(r, true);
	MicroAdjustForShoot(Vector(), false,true);
	MicroAdjustForFreeKick(Vector(), false, true);
	MicroAdjustForGoalKeeper(Vector(), false, true);
}


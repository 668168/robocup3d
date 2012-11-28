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
#ifndef SKILL_H
#define SKILL_H

#include "soccertypes.h"

class Skill
{
public:
	Skill();
	~Skill();
	bool ClimbOnGround(bool bClear = false);
	bool Delay(int iCycle);
	bool TurnTo(double dBodyAngle, bool bClear = false);
	bool TurnToForDynamicWalk(double dBodyAngle, bool bClear = false);

	bool WalkToForward(Vector vPos, bool bClear = false);
	bool WalkForwardStop(bool bClear = false);
	bool WalkToForwardEx(Vector vTargetPos, Vector vTempPos, double dDestinationAng, bool bClear = false);
	bool WalkToForwardEx(Vector vTargetPos, double dDestinationAng);

	bool WalkToBack(Vector vPos, bool bClear = false);
	bool StopWalkBack( bool bClear = false);
///////////////////////////////////////////////////////
	bool KickBall(bool clear = false);
	bool KickBallSmall(bool clear = false);
	bool StepToKick(Vector vTarget, bool clear = false);
	bool TurnToKick(Vector vTarget, bool clear = false);
	bool MoveToKick(Vector vTarget, bool clear = false);
	bool MoveOutBall(Vector vTarget, bool clear = false);
	bool StepBack(Vector vTarget, bool clear = false);
	bool MoveToPos(Vector vTarget, bool clear = false);
	bool StepToPos(Vector vTarget, bool clear = false);

	bool MicroAdjustForShoot(Vector vTarget = Vector(6,0,0), bool stop = false,bool clear = false);
	bool MicroAdjustForFreeKick(Vector vTarget = Vector(6,0,0), bool stop = false,bool clear = false);
	bool MicroAdjustForGoalKeeper(Vector vTarget, bool stop = false, bool clear = false);
	bool Again(bool clear = false);



	void ClearAll();


private:
	bool CheckClimbSucc(bool &bSucc, bool bClear = false);
	double NormalizeAng(double &dAng);
};

#endif

/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef BHVDRIBBLE_H
#define BHVDRIBBLE_H

#include "../Math/Line.h"
#include "../WorldModel/WorldModel.h"
#include "../Utility/Types.h"
//#include "BhvBasicTurn.h"
#include "BhvBehindBallSetup.h"
#include "BhvFocusBall.h"
#include "BhvBasicWalk.h"
#include "BhvBasicKick.h"


enum EDribblePhase
{
        GO_TO_BALL,
        SETUP,
        GO_TO_GOAL
};

class BhvDribble
{

public :

     BhvDribble(Vector3f goal):mGoal(goal){};

     bool execute();

private :
    static EDribblePhase mPhase;

    static int mStartPhase;
    Vector3f   mGoal;

    Vector2f  calPoint()const;

    bool      isAriveTo(const Vector2f& point )const;

    EDribblePhase getPhase()const;

    double   minus(const float& num1, const float& num2)const;

    void SetupTurnParam();

    void ResetTurnParam();

};
#endif // BHVDRIBBLE_H

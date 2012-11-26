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

#ifndef BHVFOCUSBALL_H
#define BHVFOCUSBALL_H

#include "SoccerBehavior.h"
#include "../Effectors/AngularMotor.h"

class BhvFocusBall: public SoccerBehavior {

private:
    static float X2[2];

    static float Y2[2];

    static float Rotation2[2];

    static float Distance2[2];

    static float Phi2[2];

    static float Theta2[2];

    static int counter;

    static float X;

    static float Y;

    static float Rotation;

    static float Distance;

    static float Phi;

    static float Theta;

    static bool  flag;
   
    static bool  flag1;

public:

    BhvFocusBall();

    bool execute();

    void  focusBall(float VJ1,float VJ2 );

    void  searchBall(float VJ1,float VJ2,float Start,float End);

    void  searchBall(float VJ1,float VJ2);
 };

#endif // BHVFOCUSBALL_H

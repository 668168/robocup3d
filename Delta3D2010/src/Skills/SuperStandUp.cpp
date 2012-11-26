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

#include "SuperStandUp.h"

Skill::Skill() {
    //WM = wm;
        cout << "============================!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1";
    S << "24  0.0  0.3 0.6   1.2  1.3  1.7  1.9 2.0 3.0 3.2 11  0.3  0.6 1.2   1.3  1.7  1.9  2.0 3.0 3.2 3.3 0   0    0   0     0    0    0    0   0   0   0 1   0    0   0     0    0    0    0   0   0   0 2   0    0   0     0    0    0    0   0   0   0 3   0    0   0     0    0    0    0   0   0   0 4   0    0   0     0    0    0    0   0   0   0 5   0    0   0     0    0    0    0   0   0   0 6   0   90  90  90   90  95  90   0   0   0  7   0   90  90  90   90  95  90   0   0   0 8   0    0    0    0     0   0   0    0   0   0 9   0    0    0    0     0   0   0    0   0   0 10  0   0    0    20   20    4  -8   -3   0   0 11  0   0    0    20   20    4  -8   -3   0   0 12  0   0    0     0    0    0   0    0   0   0  13  0   0    0     0    0    0   0    0   0   0 14 -90 -90  -90   55   55    0   0    0   0   0 15 -90 -90  -90   55   55    0   0    0   0   0 16  0    0   90   90    0    0   0    0   0   0 17  0    0  -90  -90    0    0   0    0   0   0  18  0    0  -90  -90   -90   0   0    0   0   0 19  0    0   90   90    90   0   0    0   0   0  20  0    0   0    0     0    0   0    0   0   0 21  0    0   0    0     0    0   0    0   0   0";
    x = 24;
    y = 11;
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            S >> standupF[i][j];
}
////////////////////////////////////////////////////////////////////
Skill& Skill::instance()
{
	static Skill sSkill;
	return sSkill;
}

////////////////////////////////////////////////////////////////////

string Skill::moveJoint(string j, double val) {
    stringstream message;
    message << "(" << j << " " << val << ")";
    return message.str();
}

///////////////////////////////////////////////////////////////////
string Skill::act(double a[][24], int m, int n, double &time, bool &t, int &repeat) {
    if (t)
        return "";
    string ss = "";
    for (int i = 1; i < n; i++) {
        if (a[0][i] < time && time <= a[1][i]) {
            for (int j = 2; j < m; j++) {
                double speed = (a[j][i] - WorldModel::instance().getJointAngle(WorldModel::instance().num2Str(a[j][0]))) / (a[1][i] - time) / 40;
                if (fabs(a[j][i] - WorldModel::instance().getJointAngle(WorldModel::instance().num2Str(a[j][0]))) > .4) {
                    ss += moveJoint(WorldModel::instance().num2Str(a[j][0]), speed);
                } else
                    ss += fix(WorldModel::instance().num2Str(a[j][0]));
            }
            break;
        } else
            continue;
    }
    time += 0.02;
    if (time > a[1][n - 1]) {
        t = true;
        repeat++;
        return "";
    }
    return ss;
}//////////////////////////////////////////////////////////////////////

string Skill::fix() {
    stringstream ss;
    for (int i = 0; i < 22; i++)
        ss << moveJoint(WorldModel::instance().num2Str(i), 0);
    return ss.str();
}
//////////////////////////////////////////////////////////////////////
string Skill::fix(string j) {
    return moveJoint(j, 0);
}
////////////////////////////////////////////////////////////////////
string Skill::standUp(string s, bool &done, double &t,int &repeat) {
    if (done) {
        t = 0;
        return fix();
    }
        return act(standupF, standupF[0][0], standupF[1][0], t, done, repeat);
}

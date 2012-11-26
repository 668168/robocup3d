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


#include "BhvBasicTurn.h"
#include <cmath>


bool BhvBasicTurn::execute()
{
    WorldModel&   wm            = WorldModel::instance();
    Walk&         walk          = Walk::instance();

    float         myRotate      = 0.0;
    float         angle         = mAngle;//wm.getPolarBallPos().theta;//mAngle + myRotate;

    float         tmp           = (abs(angle) < 10)? angle :
                                   sign(angle) * 10;
    cout<<"********turn angle = "<<mAngle<<" tmp angle = "<<tmp<<endl;
    
    setupTurnParam();
    walk.Execute(tmp,1.0f,SIDE_FORWARD);
    walk.Execute(tmp,1.0f,SIDE_FORWARD);

    Effectors::instance().setActionCommand();
    resetTurnParam();
    return false;
}

void BhvBasicTurn::setupTurnParam()
{
   Trajectory::instance().Qf= 0.0;
   Trajectory::instance().Qb= 0.0;

   WalkParams::instance().Hao=0.01;
   WalkParams::instance().Tc=0.23;
    
//   WalkParams::instance().Xsd          =  0.01f;  //max = 0.07
  // WalkParams::instance().Xed          =  0.01f;  //max = 0.07
    

}

void BhvBasicTurn::resetTurnParam()
{
    Trajectory::instance().Qf= 0.2;
    
    Trajectory::instance().Qb= 0.2;
    
    WalkParams::instance().Hao=0.10;
    
    WalkParams::instance().Tc=0.2;

}

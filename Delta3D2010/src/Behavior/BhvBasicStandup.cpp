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

#include "BhvBasicStandup.h"

BhvBasicStandup::BhvBasicStandup()
{

}

bool  BhvBasicStandup::execute ()
{
if(WorldModel::instance().getCurrentCycle()>10)
     {WorldModel::instance().setFellDown(true);
      Walk::instance().Stop();
     if (((FallDownRecognition::instance().SideFallDown(WorldModel::instance().getCurrentCycle()) == FALL_BACK ) && !WorldModel::instance().flag2)||WorldModel::instance().flag1 )
     {
        WorldModel::instance().flag1 = true;
        std::cout<< "fall downing side : back " <<std::endl;
        Effectors::instance().mActionCommand="";
        float sa = WorldModel::instance().getHJoint(JID_HEAD_2).angle;
        Effectors::instance().mActionCommand=(StandUp::instance().backStart(WorldModel::instance().getCurrentCycle()));
        if(StandUp::instance().standupFinished)
        {
                 WorldModel::instance().flag1 = false; WorldModel::instance().flag2 = false;
		 StandUp::instance().brakenFrontflag = false;
                 std::cout<< "Reset walking ..."<<std::endl;
                 WorldModel::instance().setFellDown(false);
        }
     } 
     else if(((FallDownRecognition::instance().SideFallDown(WorldModel::i().getCurrentCycle())==FALL_FRONT 
 || FallDownRecognition::instance().SideFallDown(WorldModel::i().getCurrentCycle())==FALL_RIGHT  || FallDownRecognition::instance().SideFallDown(WorldModel::instance().getCurrentCycle()) == FALL_LEFT ) && !WorldModel::instance().flag1) || WorldModel::instance().flag2)
     {
             WorldModel::instance().flag2 = true;
             std::cout<< "fall downing side :front  "<< std::endl;
	     Effectors::instance().mActionCommand="";
            // if ((WorldModel::instance().getFRP(FID_RF).f_z +WorldModel::instance().getFRP(FID_LF).f_z) < 10.0)
             if (StandUp::instance().brakenFrontflag == true)
             Effectors::instance().mActionCommand=(StandUp::instance().backStart(WorldModel::instance().getCurrentCycle()));
             else
             Effectors::instance().mActionCommand=( StandUp::instance().fastFrontStart(WorldModel::instance().getCurrentCycle()));
        if(StandUp::instance().standupFinished)
        {
                 WorldModel::instance().setFellDown(false);
                 WorldModel::instance().flag1 = false; WorldModel::instance().flag2 = false;
                 StandUp::instance().brakenFrontflag = false;
                 std::cout<< "Reset walking ..."<<std::endl;
        }
     }
   }
      return false;
}
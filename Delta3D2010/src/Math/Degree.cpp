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


#include <cmath>

#include "Degree.h"
//#include <Basics.h>

using namespace std;
//using namespace Basics;

// namespace Degree

namespace Degree
{

  float normalizeAngle(float angle)
  {
    while (angle < -180) angle += 360;
    while (angle > 180) angle -= 360;
    return angle;
  }
  
  float absoluteAngle(float angle)
  {
    while (angle < 0) angle += 360;
    while (angle >= 360) angle -= 360;
    return angle;
  }

   bool isBetween(float angle1, float angle2, float checkAngle)
   {
     angle1 = absoluteAngle(angle1);
     angle2 = absoluteAngle(angle2);
     checkAngle = absoluteAngle(checkAngle);
     if (angle1 == angle2)
     {
       if (checkAngle == angle1)
	 return true;
       else
	 return false;
     }
     else if (angle1 < angle2)
     {
       if (checkAngle >= angle1 && checkAngle <= angle2)
	 return true;
       else
	 return false;
     }
     else
     {
       if (checkAngle <= angle2 || checkAngle >= angle1)
	 return true;
       else
	 return false;
     }
   }
   
   float getDeltaAngle(float angle1, float angle2)
   {
     angle1 = absoluteAngle(angle1);
     angle2 = absoluteAngle(angle2);
     return normalizeAngle(angle1 - angle2);
   }
   float getDegree(Vector pos1, Vector pos2, Vector pos3)
   {
     return normalizeAngle(-((pos2 - pos1).theta() - (pos2 - pos3).theta()) * RTD);
   }  
   
   Vector turn(Vector point, float deg)
   {
     float x = point.getX(), y = point.getY();
     deg *= DTR;
     point.setX(x * cos(deg) - y * sin(deg));
     point.setY(x * sin(deg) + y * cos(deg));
     return point;
   }
}

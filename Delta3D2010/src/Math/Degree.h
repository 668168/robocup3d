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

#ifndef DEGREE_H
#define DEGREE_H

#include "Vector.h"

namespace Degree
{
  extern float normalizeAngle(float angle);
  extern float absoluteAngle(float angle);
  extern bool isBetween(float angle1, float angle2, float checkAngle);
  extern float getDeltaAngle(float angle1, float angle2);  
  extern float getDegree(Vector pos1, Vector pos2, Vector pos3);
  extern Vector turn(Vector point, float deg);
}

#endif // DEGREE_H

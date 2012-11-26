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

#ifndef ARM_H
#define ARM_H

class Arm
{
public:
    Arm();

    ~Arm();
    void setValue(float j1, float j2, float j3, float j4);
    float getaj1();
    float getaj2();
    float getaj3();
    float getaj4();
private:

  float ae1;
  float ae2;
  float ae3;
  float ae4;
};

#endif // ARM_H

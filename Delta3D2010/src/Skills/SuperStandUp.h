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

#ifndef SKILL_H
#define SKILL_H

#include "../WorldModel/WorldModel.h"
#include <fstream>
#include <stdlib.h>
#include <sstream>
using namespace std;
class Skill{
	private :
		fstream f;
		string jointName[22];
		int x,y;
		double z;
		double standupF[24][24];
		stringstream S;
	public :
    static Skill& instance();
    static const Skill& i(){return instance();}
		Skill();
		string moveJoint(string,double);
		string act(double a[][24],int m,int n,double &time,bool &, int &);
		string fix();
		string set(string j,double ang,int cycle);
		string fix(string j);
		string standUp(string ,bool &,double &,int &);
};

#endif // SKILL_H

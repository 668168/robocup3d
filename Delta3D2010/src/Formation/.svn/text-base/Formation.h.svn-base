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

#ifndef FORMATION_H
#define FORMATION_H


#include "../Utility/Types.h"
#include <string>
#include <iostream>
#include <fstream> //for loading formation.conf
class Formation
{

private:           
   
   void setupPlayerTypeMap();
   	   
   void loadFormation(const std::string& filename);
   
   void parseOneFormation(string &sexp);

   FormationData parseFormationData(const string &sexp) const ;

   string getWord(int& pointer,string& sexp, bool let);

   float getNum(int& pointer, string& input);

   bool isChar(char chr);
   
   bool isNum(char chr);
	   
   string ss;
   
public:
   
   Formation  ();
   ~Formation ();
   static Formation& instance();
   static const Formation& i(){return instance();}
   TFormationDataMap  mFormationDataMap;
   TPlayerTypeMap     mPlayerTypeMap;
};
#endif // FORMATION_H

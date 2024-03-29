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

#include "Formation.h"

using namespace std;
Formation::Formation()
{
    setupPlayerTypeMap();
}

Formation::~Formation()
{
}

Formation& Formation::instance()
{
    static Formation sFormation;
    return sFormation;
}
void Formation::setupPlayerTypeMap()
{
   mPlayerTypeMap.clear();

   mPlayerTypeMap["1"]		= PT_GOALKEEPER;
   mPlayerTypeMap["3"]		= PT_LEFT_DEFENDER;
   mPlayerTypeMap["5"] 	=         PT_RIGHT_DEFENDER;
   mPlayerTypeMap["7"]		= PT_CENTER_MIDFIELDER;
   mPlayerTypeMap["10"]		= PT_LEFT_ATTACKER;
   mPlayerTypeMap["11"]		= PT_RIGHT_ATTACKER;
   mPlayerTypeMap["NONE"] 	= PT_NONE;
   loadFormation("Config/formation.conf");
}

void Formation::loadFormation(const string& filename)
{
   std::ifstream ifile(filename.c_str());
   
   string buf;
   string player;
    while( !ifile.eof() )
    {
        getline(ifile,buf);
        if(  buf == "basic formation"  ) 
        { 
           //parse goalie formation 
           getline(ifile,player);
	   parseOneFormation(player);
	   
	   //parse left defender formation 
	   getline(ifile,player);
	   parseOneFormation(player);
	   
	   //parse right defender formation
	   getline(ifile,player);
	   parseOneFormation(player);
	   
	   //parse center midfielder formation
	   getline(ifile,player);
	   parseOneFormation(player);
	   
	   //parse left attacker
	   getline(ifile,player);
	   parseOneFormation(player);
	   
	   //parse right attacker
	   getline(ifile,player);
	   parseOneFormation(player);
	 }
    }
}

void Formation::parseOneFormation(string &sexp)
{
    string name;
    FormationData formationdata;
    string result;
    int pointer=0;
   
   
   while( (unsigned int) pointer <= ( sexp . length() -1) )
   {       
      result = getWord( pointer, sexp, false);
        
      if( result.compare( "player" ) == 0 )
      {

         formationdata.type = (PlayerType)(getNum(pointer, sexp));
         std::cout<<"unum is:  "<<formationdata.type;
	 result = getWord( pointer, sexp, false);

       }
        
       if( result.compare( "beam" ) == 0 )
       {
          Vector3f tmpvector;
          tmpvector = Vector3f(getNum(pointer, sexp),
			       getNum(pointer, sexp), 
		               getNum(pointer, sexp) );
           
          formationdata.beamPos = Vector3f(tmpvector.z(),
           			            tmpvector.y(),
					    tmpvector.x() );
 	  std::cout<<"beam.x= "<<formationdata.beamPos.x()<<"beam.y= "<<formationdata.beamPos.y()<<"beam.z= "<<formationdata.beamPos.z();
          result = getWord( pointer, sexp, false);
       } 
       if( result.compare( "beforeKickOff" ) == 0 )
       {
          Vector3f tmpvector;
          tmpvector = Vector3f(getNum(pointer, sexp),
			       getNum(pointer, sexp), 
		               getNum(pointer, sexp) );
           
          formationdata.beforeKickOff = Vector3f(tmpvector.z(),
           			            tmpvector.y(),
					    tmpvector.x() );
 	  std::cout<<"befor.x= "<<formationdata.beforeKickOff.x()<<"befor.y= "<<formationdata.beforeKickOff.y()<<"befor.z= "<<formationdata.beforeKickOff.z();
          result = getWord( pointer, sexp, false); 
       }
       
       if( result.compare( "home" ) == 0 )
       {
          Vector3f tmpvector;
          tmpvector = Vector3f(getNum(pointer, sexp),
			       getNum(pointer, sexp), 
		               getNum(pointer, sexp) );
           
          formationdata.homePos = Vector3f(tmpvector.z(),
           			           tmpvector.y(),
					   tmpvector.x() );
 	  std::cout<<"home.x= "<<formationdata.homePos.x()<<"home.y= "<<formationdata.homePos.y()<<"home.z= "<<formationdata.homePos.z();
          result = getWord( pointer, sexp, false); 
      } 
       
       if( result.compare( "attraction" ) == 0 )
       {
          Vector2f tmpvector;
          tmpvector = Vector2f(getNum(pointer, sexp),
			       getNum(pointer, sexp) );
           
          formationdata.attraction = Vector2f(tmpvector.y(),
					      tmpvector.x() );
 	  std::cout<<"atraction.x= "<<formationdata.attraction.x()<<"atraction.y= "<<formationdata.attraction.y();
          result = getWord( pointer, sexp, false); 
      }
      
       if( result.compare( "xRange" ) == 0 )
       {
          Vector2f tmpvector;
          tmpvector = Vector2f(getNum(pointer, sexp),
			       getNum(pointer, sexp) );
           
          formationdata.xRange = Vector2f(tmpvector.y(),
					      tmpvector.x() );
 	  std::cout<<"xrange.x= "<<formationdata.xRange.x()<<"xrange.y= "<<formationdata.xRange.y();
          result = getWord( pointer, sexp, false); 
      } 
      
      if( result.compare( "yRange" ) == 0 )
       {
          Vector2f tmpvector;
          tmpvector = Vector2f(getNum(pointer, sexp),
			       getNum(pointer, sexp) );
           
          formationdata.yRange = Vector2f(tmpvector.y(),
					  tmpvector.x() );
 	  std::cout<<"yrange.x= "<<formationdata.yRange.x()<<"yrange.y= "<<formationdata.yRange.y();
          result = getWord( pointer, sexp, false); 
      }
      
      if( result.compare( "behindBall" ) == 0 )
      {

         formationdata.behindBall = getNum(pointer, sexp);
         std::cout<<"behind ball is:"<<formationdata.behindBall;
	 result = getWord( pointer, sexp, false);
      }  

   }
   mFormationDataMap[formationdata.type]=formationdata;
}


string Formation::getWord(int& pointer, string& input, bool let)
{
   string  word (32,' ');
   while(( !(isChar( input[ pointer ])) ) && ((unsigned int) pointer < input.length() ) )
   {
       pointer ++;
   }

   int index = 0;
   while( ((input[ pointer ] != ' ' && input[ pointer ] != ')') ||
          (let && input[ pointer ] != ')' ) )&& 
          ( (unsigned int) pointer < input.length() ))
   {
       word[ index ] = input[ pointer ];
       pointer ++;
       index ++;
   }
   word . resize(index);
   return ( word ) ;
}//end of getWord



///this function return the value of one perceptor
float Formation::getNum(int& pointer, string& input)
{
   while( (!(isNum(input[ pointer ]))) && (input[ pointer ] != '-') &&
          ( (unsigned int)pointer < input.length() ) )
   {
      pointer ++;
   }
   short int sign = 1;
   if (input[pointer] == '-')
   {
      pointer ++;
      sign = -1;
   }

   float tempFloat = 0.0;
   float divPoint  = 1.0;

   bool point = false;
   while( (isNum(input[ pointer ])) && ((unsigned int)pointer < input.length() ) )
   {
      if(input[ pointer ] == 46)// is .
      {
         point = true;
      }
      else
      {
          tempFloat = (tempFloat * 10.0) + (input[ pointer ] - 48);
          if(point == true)
          {
             divPoint *= 10.0;
          }
      }
      pointer++;
   }
   return (sign * tempFloat / divPoint);
}//end of getNum

///determine that chr is char or no. 
//02
bool Formation::isChar(char chr)
{
   if( ((chr >= 65) && (chr <= 90 )   )   ||//A..Z
     ( ((chr >= 97) && (chr <= 122))  )   ||//a..z
       (chr == 95)                    )     // _
   {
       return true;
   }
   else
       return false;
}//end of isChar


///determine that chr is number or no.
//03
bool Formation::isNum(char chr)
{
   if( ( (chr >= 48) && (chr <= 57) )  || //0..9
         (chr == 46) )                    // .
   {
     return true;
   }
   else
     return false;
}//end of isNum
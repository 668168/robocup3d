/*
<one line to give the program's name and a brief idea of what it does.>
Copyright (C) <year> <name of author>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
 
#include "Perceptors.h"
/** map of VisionObject, Visionsense for use in perceptors class*/
///**********************************************************************
///******************************PARSE***********************************
 
Perceptors::Perceptors()
{
  mTeamSide = TS_NONE;
}
 
void Perceptors::parse(string& input)
{
  int pointer = 0;//pointer for Perceptors string
  
  while(true)//loop for parse entire Perceptors string
  {
    /*! if our pointer was longer than Perceptors string break pars*/
    if( ((unsigned int) pointer > (input . length()-1)) )
      break;
    /**Time perceptor**/
    string result = getWord( pointer, input, false);
    if( result.compare( "time" ) == 0 )
    {
      result = getWord( pointer, input, false );
      mSimTime = getNum(pointer, input);
    }
    /**Game state perceptor**/
    if( result.compare( "GS" ) == 0 )
    {
      result = getWord( pointer, input, false );
      mTime = getNum(pointer, input);
      if (mTeamSide == TS_NONE)
	setTeamSide(pointer,input);
    }
    /**PlayMode perceptor**/
    if( result.compare( "pm" ) == 0 )
    {
      setPlayMode (pointer,input);
    }
    /**Gyroscope perceptor**/
    if( result.compare( "GYR" ) == 0 )
    {
      mGyrSense.x = getNum(pointer, input);
      mGyrSense.y = getNum(pointer, input);
      mGyrSense.z = getNum(pointer, input);
    }
    
    if( result.compare( "ACC" ) == 0 )
    {
      mAccSense.x = getNum(pointer, input);
      mAccSense.y = getNum(pointer, input);
      mAccSense.z = getNum(pointer, input); 
    }
    /**See perceptor**/
    if (result.compare("See") == 0)
    {
      std::string  tmpString ="";
      do
      {
	if( result.compare( "G1L" ) == 0 )
	{
	  setFlag(pointer, input, result );
	}
	else if( result.compare( "G2L" ) == 0 )
	{
	  setFlag(pointer, input, result );
	}
	if( result.compare( "G2R" ) == 0 )
	{
	  setFlag(pointer, input, result );
	}
	if( result.compare( "G1R" ) == 0 )
	{
	  setFlag(pointer, input, result );
	}
	else if(result . compare("F1L") == 0)
	{
	  setGoal(pointer, input, result );
	}
	else if(result . compare("F2L") == 0)
	{
	  setGoal(pointer, input, result );
	}
	else if(result . compare("F1R") == 0)
	{
	  setGoal(pointer, input, result );
	}
	else if(result . compare("F2R") == 0)
	{
	  setGoal(pointer, input, result );
	}
	else if(result . compare("B") == 0)
	{
	  setBall(pointer, input);
	}
	else if(result.compare("P") == 0)
	{
	  tmpString = setPlayer(pointer, input);
	}
	/// agar hinge joint o player ra getword kard  digar nabayad an ra getword kard

	if (tmpString != "HJ" && tmpString != "P") /// 
	{
	  result = getWord(pointer, input, false);
	}
	else
	{
	  result = tmpString;
	}
      }
      while ((result .compare("HJ") !=0) &&
	((unsigned int)pointer < input.length() - 1));//end of See do
    }//End of See If
    /**frp perceptor**/
    if(result.compare("FRP") == 0)
    {
      result = getWord( pointer, input, false );
      result = getWord( pointer, input, false );
      if(result.compare("rf") == 0)
      {
	setFRP(pointer, input,result);
	bFrpSense[FID_RF] = true;
      }
      else if(result.compare("lf") == 0)
      {
	setFRP(pointer, input,result);
	bFrpSense[FID_LF] = true;
      }
    }//end of FRP if
    /**HingJoint perceptor**/
    if( result . compare( "HJ" ) == 0)
    {
      result = getWord(pointer, input, false);
      result = getWord(pointer, input, false );
      setHJoint( pointer, input, result );
    }//end of HJ if
  }//End of while
} //End of parse
///*************************Ending Parse*********************************
///**********************************************************************
 
///this function return the name of one perceptor
//04
string Perceptors::getWord(int& pointer, string& input, bool let)
{
  string word (32,' ');
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
//05
float Perceptors::getNum(int& pointer, string& input)
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
  float divPoint = 1.0;
  
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
 
void Perceptors::setTeamSide( int & pointer,string& input)
{
  std::string result= getWord(pointer,input,false);
  if(result == "team")
  {
    result = getWord(pointer,input,false);
    if(result == "left")
    {
      mTeamSide = TS_LEFT;
    }
    else if (result == "right")
    {
      mTeamSide = TS_RIGHT;
    }
    else
      mTeamSide = TS_NONE;
  }
}
 
/**this method return the polar coordinate from one Agent to flags that agent see in one cycle and set this polar coordinate in a sense object that makes from VisionSense struct in types.h**/
void Perceptors::setFlag(int& pointer, string& input , string& name)
{
  ++mTotalFlagSeen;
  // VisionSense sense;
  TVisionObjectMap::iterator iter = mVisionObjectMap.find(name);
  if (iter == mVisionObjectMap . end())
  {
    std::cout<<"Flags sense error"<<std::endl;
    return;
  }
  EVisionObject VO = (*iter).second;
  mObjectToSenseMap[VO].distance = getNum( pointer, input );
  mObjectToSenseMap[VO].theta = getNum( pointer, input );
  mObjectToSenseMap[VO].phi = getNum( pointer, input );
  mObjectToSenseMap[VO].lastTimeSeen = mTime;
  //mObjectToSenseMap[VO] = sense;
}
 
 
/**this method return the polar coordinate from one Agent to corner flags that agent see in one cycle and set this polar coordinate in a sense object that makes from VisionSense struct in types.h**/
 
void Perceptors::setGoal(int& pointer, string& input, string& name )
{
  ++mTotalFlagSeen;
  // VisionSense sense;
  TVisionObjectMap :: iterator iter = mVisionObjectMap.find(name);
  if (iter == mVisionObjectMap . end())
  {
    std::cout<<"Goal Flags sense error"<<std::endl;
    return;
  }
  EVisionObject VO = (*iter).second;
  mObjectToSenseMap[VO].distance = getNum( pointer, input );
  mObjectToSenseMap[VO].theta = getNum( pointer, input );
  mObjectToSenseMap[VO].phi = getNum( pointer, input );
  mObjectToSenseMap[VO].lastTimeSeen = mTime;
//mObjectToSenseMap[VO] = sense;
 
}
 
/**this method return the polar coordinate from one Agent to ball that
agent see in one cycle and set this polar coordinate in a sense
object that makes from VisionSense struct in types.h**/
void Perceptors::setBall(int& pointer, string& input)
{
  // VisionSense sense;
  string name = "B" ;
  

  TVisionObjectMap :: iterator iter = mVisionObjectMap.find(name);
  if (iter == mVisionObjectMap . end())
  {
    std::cout<<"Ball sense error"<<std::endl;
    return;
  } 
 
 EVisionObject VO = (*iter).second;
 mObjectToSenseMap[VO].distance = getNum( pointer, input );
 mObjectToSenseMap[VO].theta = getNum( pointer, input );
 mObjectToSenseMap[VO].phi = getNum( pointer, input );
 mObjectToSenseMap[VO].lastTimeSeen = mTime; 
//mObjectToSenseMap[VO] = sense;
}
 
/**this method return the FRP information from that agent percept in one cycle and set sense object that makes from FRPSense structure in types.h**/
 
void Perceptors::setFRP(int& pointer, string& input, string& name)
{
  FRPSense sense;
  TFRPIDMap :: iterator iter = mFRPIDMap.find(name);
  
  if (iter == mFRPIDMap . end())
  {
    std::cout<<"FRP sense error"<<std::endl;
    return;
  }
  EFRPID FRP = (*iter).second;
  sense.c_x = getNum( pointer, input );
  sense.c_y = getNum( pointer, input );
  sense.c_z = getNum( pointer, input );
  sense.f_x = getNum( pointer, input );
  sense.f_y = getNum( pointer, input );
  sense.f_z = getNum( pointer, input );
  
  mFRPSenseMap[FRP] = sense;
}
void Perceptors::setPlayMode(int& pointer, string& input )
{
  std::string PMName = getWord(pointer,input,false);
  TPlayModeMap::iterator iter = mPlayModeMap.find(PMName);
  if(iter == mPlayModeMap.end())
  {
    std::cout<<"Play Mode sense error"<<std::endl;
    return;
  }
  EPlayMode pm = (*iter).second;
  mPlayMode = pm;
}


std::string  Perceptors::setPlayer(int& pointer, string& input )
{
  
  std::string teamName;
  stringstream playerName;
  int id;
  VisionSense playerPos;
  std::string tmpPerceptors ="";

  getWord(pointer, input, false);
  teamName = getWord(pointer, input,false);
  id = (int)getNum(pointer,input);
  
  if (teamName == gTeamName)
  {
    playerName << "TEAMMATE";
    playerName << id;
  }
  else if (teamName == mOppTeamName)
  {
    playerName << "OPPONENT";
    playerName << id;
  }
  else
  {
    mOppTeamName = teamName;
    playerName << "OPPONENT";
    playerName << id;
  }
  std::string name = playerName.str();
  playerName.str("");
 
  EVisionObject vo;

  TVisionObjectMap::iterator vo_iter = mVisionObjectMap.find(name);
  if (vo_iter == mVisionObjectMap.end())
  {
    std::cout<<"Players sense error"<<std::endl;
    return "";
  }
  
  do
  {
    ///head perceptors
    if( tmpPerceptors == "head" )
    {
      playerPos.lastTimeSeen = mTime; /// becuse just see head of player confidence set to 10  
      playerPos.distance = getNum(pointer,input);
      playerPos.theta = getNum(pointer,input);
      playerPos.phi =getNum(pointer,input);
    }
    ///right arm perceptors	      
    
    else if( tmpPerceptors=="rlowerarm")
    {
      playerPos.distanceFromRightArm = getNum(pointer,input);
      playerPos.thetaFromRightArm = getNum(pointer,input);
      playerPos.phiFromRightArm=getNum(pointer,input);
    }
    
    ///left arm perceptors
    
    else if( tmpPerceptors=="llowerarm")
    {
      playerPos.distanceFromLeftArm = getNum(pointer,input);
      playerPos.thetaFromLeftArm = getNum(pointer,input);
      playerPos.phiFromLeftArm=getNum(pointer,input);
    }
    
    ///right foot perceptors
    else if( tmpPerceptors=="rfoot")
    {
      playerPos.distanceFromRightFoot = getNum(pointer,input);
      playerPos.thetaFromRightFoot = getNum(pointer,input);
      playerPos.phiFromRightFoot=getNum(pointer,input);
    }
    
    ///left foot perceptors
    
    else if( tmpPerceptors == "lfoot")
    {
      playerPos.distanceFromLeftFoot = getNum(pointer,input);
      playerPos.thetaFromLeftFoot = getNum(pointer,input);
      playerPos.phiFromLeftFoot=getNum(pointer,input);
    }
    
    tmpPerceptors = getWord(pointer, input, false);
  }while ((tmpPerceptors .compare("HJ") !=0) && (tmpPerceptors .compare("P") !=0) &&
  ((unsigned int)pointer < input.length() - 1));//end of See do
  vo = mVisionObjectMap[name];
  mObjectToSenseMap[vo] = playerPos;  
  return tmpPerceptors;
}

void Perceptors::setHJoint( int& pointer, string& input, string& name )
{
  HingeJointSense sense;
  TJointIDMap :: iterator iter = mJointIDMap.find(name);
  if (iter == mJointIDMap . end())
  {
    std::cout<<"HJoint sense error"<<std::endl;
    return;
  }
  JointID VO = (*iter).second;
  sense.angle = getNum( pointer, input );
  mHingeJointSenseMap[VO] = sense; /// for WorldModel Update
  Kinematic::instance().mHingeJointSenseMap[VO] = sense;/// for Kinematic Update
}
 

///determine that chr is char or no.
//02
bool Perceptors::isChar(char chr)
{
  if( ((chr >= 65) && (chr <= 90 ) ) ||//A..Z
    ( ((chr >= 97) && (chr <= 122)) ) ||//a..z
    (chr == 95) ) // _
    {
      return true;
    }
    else
      return false;
}//end of isChar
 
 
///determine that chr is number or no.
//03
bool Perceptors::isNum(char chr)
{
  if( ( (chr >= 48) && (chr <= 57) ) || //0..9
    (chr == 46) ) // .
    {
      return true;
    }
    else
      return false;
}//end of isNum
 
GyrSense Perceptors::getGyr()
{
  return mGyrSense;
}

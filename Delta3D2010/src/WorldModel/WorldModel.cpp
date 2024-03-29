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

#include "WorldModel.h"

#include "../Behavior/BhvBasicStandup.h"
#include <cstring>
#include <assert.h>

WorldModel :: WorldModel()
:mIsFellDown(false),flag1(false),flag2(false)
{
    maxdist=0.095;
    maxtheta=10;
    mCurentCycle=0;
    mCurrentAction = ACT_WALK;
    setupJointMap();
    setupJointEffectorMap();
    setupObjectToSenseMap();
    setupPlayModeMap();
    names[0] = "he1";
    names[1] = "he2";
    names[2] = "lle1";
    names[3] = "rle1";
    names[4] = "lle2";
    names[5] = "rle2";
    names[6] = "lle3";
    names[7] = "rle3";
    names[8] = "lle4";
    names[9] = "rle4";
    names[10] = "lle5";
    names[11] = "rle5";
    names[12] = "lle6";
    names[13] = "rle6";
    names[14] = "lae1";
    names[15] = "rae1";
    names[16] = "lae2";
    names[17] = "rae2";
    names[18] = "lae3";
    names[19] = "rae3";
    names[20] = "lae4";
    names[21] = "rae4";
    setCurrentAction(ACT_WALK);
    mConstBallPos = Vector3f(0.0,0.0,0.0);
}

WorldModel :: ~WorldModel()
{

}


WorldModel& WorldModel::instance()
{
   static WorldModel sInstance;
   return sInstance;
}


///**********************************************************************
///*************************WorldModel Update****************************
void WorldModel::update(string& input)
{
    std::cout<<"angle :"<<getHJoint(JID_HEAD_2).angle<<std::endl;
    setupVisionObjectMap();
    bFrpSense[FID_LF] = bFrpSense[FID_RF] = false;/// ebtedaye har cycle neshanehaye frp ra false mikonad ta moshakas shavad dar in cycle sense frp darim
    mTotalFlagSeen       = 0;
    if (getTime() >0.02) mCurentCycle++;
    if (getSimulationTime()>0.02) mCurentSimulationCycle++;
    parse(input);
    ///dar sorati ke sense frp nadashte bashim meghdar an ra 0 mikonim baraye har 2 pa
    FRPSense tmp;
    if (!isFrpSense(FID_RF))
      mFRPSenseMap[FID_RF] = tmp;
    if (!isFrpSense(FID_LF))
      mFRPSenseMap[FID_LF] = tmp;
    
    calcVisionObjectLocalPos();
    Kinematic::instance().updateLink(mVisionPerceptorMatrix);
    Realpos();
    if ( mTotalFlagSeen >= 2)
    {
      mLastLocalize = getTime();
      setBallPos();
      calcVisionObjectRealPos();     
      int index = ((int)BALL) + mINum;
      mObjectToSenseMap[static_cast<EVisionObject>(index)].realPos = Vector3f(getMyPos().x(),getMyPos().y(),0.52);
      mObjectToSenseMap[static_cast<EVisionObject>(index)].lastTimeSeen = mTime;
    }
    double dTmp;
    std::cout<<"my angle is :"<<getMyPos().z() <<" and my neck angle is:"<<getHJoint(JID1_HEAD_1).angle <<std::endl;
    std::cout <<"fastest to ball = "<<getFastestInSetTo(PLAYER_SET,BALL,&dTmp);
    std::cout <<" distance = "<<dTmp<<std::endl;        
    std::cout <<" ball position is = "<<getBallPos().x()<<" "<<getBallPos().y()<<std::endl;
    std::cout<<"current cycle========"<<getCurrentCycle();
}
///*********************Ending WorldModel Update************************
///**********************************************************************

void WorldModel::setupJointEffectorMap()
{

    mJointEffectorMap.clear();
    mJointEffectorMap[JID_ROOT]  = "root";

    ///Head
    
    mJointEffectorMap[JID_HEAD_1]  = "he1";
    mJointEffectorMap[JID_HEAD_2]  = "he2";
    
    ///Arms
    
    mJointEffectorMap[JID_LARM_1] = "lae1"; 
    mJointEffectorMap[JID_LARM_2] = "lae2";
    mJointEffectorMap[JID_LARM_3] = "lae3";
    mJointEffectorMap[JID_LARM_4] = "lae4";

    mJointEffectorMap[JID_RARM_1] = "rae1" ;
    mJointEffectorMap[JID_RARM_2] = "rae2";
    mJointEffectorMap[JID_RARM_3] = "rae3";
    mJointEffectorMap[JID_RARM_4] = "rae4";

    ///Legs
    mJointEffectorMap[JID_LLEG_1] = "lle1";
    mJointEffectorMap[JID_LLEG_2] = "lle2";
    mJointEffectorMap[JID_LLEG_3] = "lle3";
    mJointEffectorMap[JID_LLEG_4] = "lle4";
    mJointEffectorMap[JID_LLEG_5] = "lle5";
    mJointEffectorMap[JID_LLEG_6] = "lle6";

    mJointEffectorMap[JID_RLEG_1] = "rle1";
    mJointEffectorMap[JID_RLEG_2] = "rle2";
    mJointEffectorMap[JID_RLEG_3] = "rle3";
    mJointEffectorMap[JID_RLEG_4] = "rle4";
    mJointEffectorMap[JID_RLEG_5] = "rle5";
    mJointEffectorMap[JID_RLEG_6] = "rle6";

}



void WorldModel::setupJointMap()
{
    mJointIDMap.clear();

    ///Head
    mJointIDMap["hj2"]  = JID_HEAD_2;
    mJointIDMap["hj1"]  = JID_HEAD_1;

    ///Arms
    mJointIDMap["laj1"] = JID_LARM_1;
    mJointIDMap["laj2"] = JID_LARM_2;
    mJointIDMap["laj3"] = JID_LARM_3;
    mJointIDMap["laj4"] = JID_LARM_4;

    mJointIDMap["raj1"] = JID_RARM_1;
    mJointIDMap["raj2"] = JID_RARM_2;
    mJointIDMap["raj3"] = JID_RARM_3;
    mJointIDMap["raj4"] = JID_RARM_4;

    ///Legs
    mJointIDMap["llj1"] = JID_LLEG_1;
    mJointIDMap["llj2"] = JID_LLEG_2;
    mJointIDMap["llj3"] = JID_LLEG_3;
    mJointIDMap["llj4"] = JID_LLEG_4;
    mJointIDMap["llj5"] = JID_LLEG_5;
    mJointIDMap["llj6"] = JID_LLEG_6;

    mJointIDMap["rlj1"] = JID_RLEG_1;
    mJointIDMap["rlj2"] = JID_RLEG_2;
    mJointIDMap["rlj3"] = JID_RLEG_3;
    mJointIDMap["rlj4"] = JID_RLEG_4;
    mJointIDMap["rlj5"] = JID_RLEG_5;
    mJointIDMap["rlj6"] = JID_RLEG_6;

    ///FRP setup
    mFRPIDMap["lf"]     = FID_LF;
    mFRPIDMap["rf"]     = FID_RF;
}

void WorldModel::setupVisionObjectMap()
{
     mVisionObjectMap.clear();
    if ( getTeamSide()==TS_LEFT )
    {
       mVisionObjectMap["F1L"]  = FLAG_1_L;//0
       mVisionObjectMap["F1R"]  = FLAG_1_R;//1
       mVisionObjectMap["F2L"]  = FLAG_2_L;//2
       mVisionObjectMap["F2R"]  = FLAG_2_R;//3
       mVisionObjectMap["G1L"]  = GOAL_1_L;//4
       mVisionObjectMap["G1R"]  = GOAL_1_R;//5
       mVisionObjectMap["G2L"]  = GOAL_2_L;//6
       mVisionObjectMap["G2R"]  = GOAL_2_R;//7
       mVisionObjectMap["B"]    = BALL;//8

      mVisionObjectMap["TEAMMATE1"]   = TEAMMATE_1;
      mVisionObjectMap["TEAMMATE2"]   = TEAMMATE_2;
      mVisionObjectMap["TEAMMATE3"]   = TEAMMATE_3;
      mVisionObjectMap["TEAMMATE4"]   = TEAMMATE_4;
      mVisionObjectMap["TEAMMATE5"]   = TEAMMATE_5;
      mVisionObjectMap["TEAMMATE6"]   = TEAMMATE_6;
      mVisionObjectMap["TEAMMATE7"]   = TEAMMATE_7;
      mVisionObjectMap["TEAMMATE8"]   = TEAMMATE_8;
      mVisionObjectMap["TEAMMATE9"]   = TEAMMATE_9;
      mVisionObjectMap["TEAMMATE10"]  = TEAMMATE_10;
      mVisionObjectMap["TEAMMATE11"]  = TEAMMATE_11;

      mVisionObjectMap["OPPONENT1"]   = OPPONENT_1;
      mVisionObjectMap["OPPONENT2"]   = OPPONENT_2;
      mVisionObjectMap["OPPONENT3"]   = OPPONENT_3;
      mVisionObjectMap["OPPONENT4"]   = OPPONENT_4;
      mVisionObjectMap["OPPONENT5"]   = OPPONENT_5;
      mVisionObjectMap["OPPONENT6"]   = OPPONENT_6;
      mVisionObjectMap["OPPONENT7"]   = OPPONENT_7;
      mVisionObjectMap["OPPONENT8"]   = OPPONENT_8;
      mVisionObjectMap["OPPONENT9"]   = OPPONENT_9;
      mVisionObjectMap["OPPONENT10"]  = OPPONENT_10;
      mVisionObjectMap["OPPONENT11"]  = OPPONENT_11;
 }
 
 else if( getTeamSide()==TS_RIGHT )
 {
     mVisionObjectMap["F1L"]  = FLAG_2_R;//0
     mVisionObjectMap["F1R"]  = FLAG_2_L;//1
     mVisionObjectMap["F2L"]  = FLAG_1_R;//2
     mVisionObjectMap["F2R"]  = FLAG_1_L;//3
     mVisionObjectMap["G1L"]  = GOAL_2_R;//4
     mVisionObjectMap["G1R"]  = GOAL_2_L;//5
     mVisionObjectMap["G2L"]  = GOAL_1_R;//6
     mVisionObjectMap["G2R"]  = GOAL_1_L;//7
     mVisionObjectMap["B"]    = BALL;//8

     mVisionObjectMap["TEAMMATE1"]   = TEAMMATE_1;
     mVisionObjectMap["TEAMMATE2"]   = TEAMMATE_2;
     mVisionObjectMap["TEAMMATE3"]   = TEAMMATE_3;
     mVisionObjectMap["TEAMMATE4"]   = TEAMMATE_4;
     mVisionObjectMap["TEAMMATE5"]   = TEAMMATE_5;
     mVisionObjectMap["TEAMMATE6"]   = TEAMMATE_6;
     mVisionObjectMap["TEAMMATE7"]   = TEAMMATE_7;
     mVisionObjectMap["TEAMMATE8"]   = TEAMMATE_8;
     mVisionObjectMap["TEAMMATE9"]   = TEAMMATE_9;
     mVisionObjectMap["TEAMMATE10"]  = TEAMMATE_10;
     mVisionObjectMap["TEAMMATE11"]  = TEAMMATE_11;

     mVisionObjectMap["OPPONENT1"]   = OPPONENT_1;
     mVisionObjectMap["OPPONENT2"]   = OPPONENT_2;
     mVisionObjectMap["OPPONENT3"]   = OPPONENT_3;
     mVisionObjectMap["OPPONENT4"]   = OPPONENT_4;
     mVisionObjectMap["OPPONENT5"]   = OPPONENT_5;
     mVisionObjectMap["OPPONENT6"]   = OPPONENT_6;
     mVisionObjectMap["OPPONENT7"]   = OPPONENT_7;
     mVisionObjectMap["OPPONENT8"]   = OPPONENT_8;
     mVisionObjectMap["OPPONENT9"]   = OPPONENT_9;
     mVisionObjectMap["OPPONENT10"]  = OPPONENT_10;
     mVisionObjectMap["OPPONENT11"]  = OPPONENT_11;
 }
}

void WorldModel::setupPlayModeMap()
{
    mPlayModeMap.clear();

    mPlayModeMap["BeforeKickOff"]     = PM_BeforeKickOff;
    mPlayModeMap["KickOff_Left"]      = PM_KickOff_Left;
    mPlayModeMap["KickOff_Right"]     = PM_KickOff_Right;
    mPlayModeMap["PlayOn"]            = PM_PlayOn;
    mPlayModeMap["KickIn_Left"]       = PM_KickIn_Left;
    mPlayModeMap["KickIn_Right"]      = PM_KickIn_Right;
    mPlayModeMap["corner_kick_left"]  = PM_CORNER_KICK_LEFT;
    mPlayModeMap["corner_kick_right"] = PM_CORNER_KICK_RIGHT;
    mPlayModeMap["goal_kick_left"]    = PM_GOAL_KICK_LEFT;
    mPlayModeMap["goal_kick_right"]   = PM_GOAL_KICK_RIGHT;
    mPlayModeMap["offside_left"]      = PM_OFFSIDE_LEFT;
    mPlayModeMap["offside_right"]     = PM_OFFSIDE_RIGHT;
    mPlayModeMap["GameOver"]          = PM_GameOver;
    mPlayModeMap["Goal_Left"]         = PM_Goal_Left;
    mPlayModeMap["Goal_Right"]        = PM_Goal_Right;
    mPlayModeMap["free_kick_left"]    = PM_FREE_KICK_LEFT;
    mPlayModeMap["free_kick_right"]   = PM_FREE_KICK_RIGHT;
    mPlayModeMap["unknown"]           = PM_NONE;
}

void WorldModel::setupObjectToSenseMap()
{
    mObjectToSenseMap.clear();

    const float flagHeight = 0.0f; // 0.375f
    const float goalFlagX = FieldLength/2.0; // + mFieldInfo->goaldepth/2.0;
    const float goalFlagHeight = GoalHeight/2.0;

    mObjectToSenseMap[FLAG_1_L].realPos  = Vector3f(-FieldLength/2.0, +FieldWidth / 2.0, flagHeight);

    mObjectToSenseMap[FLAG_1_R].realPos  = Vector3f(+FieldLength/2.0, +FieldWidth / 2.0, flagHeight);
//    cout<<"flag 1 r: "<<mObjectToSenseMap[FLAG_1_R].realPos<<endl;
    mObjectToSenseMap[FLAG_2_L].realPos  = Vector3f(-FieldLength/2.0, -FieldWidth/2.0,flagHeight);
    mObjectToSenseMap[FLAG_2_R].realPos  = Vector3f(+FieldLength/2.0, -FieldWidth/2.0, flagHeight);
    mObjectToSenseMap[GOAL_1_L].realPos  = Vector3f(-goalFlagX, +GoalWidth/2.0, goalFlagHeight);
    mObjectToSenseMap[GOAL_1_R].realPos  = Vector3f(+goalFlagX, +GoalWidth/2.0, goalFlagHeight);
    mObjectToSenseMap[GOAL_2_L].realPos  = Vector3f(-goalFlagX, -GoalWidth/2.0, goalFlagHeight);
    mObjectToSenseMap[GOAL_2_R].realPos  = Vector3f(+goalFlagX, -GoalWidth/2.0, goalFlagHeight);
    
}

VisionSense WorldModel::getObject(const  EVisionObject ob )const
{
   TObjectToSenseMap::const_iterator iter = mObjectToSenseMap.find(ob);
   return ((VisionSense) (*iter).second);
}

double WorldModel::getConfidence()const
{
    return (10.0 - (getTime() - mLastLocalize));
}
double WorldModel::getConfidence(const VisionSense&  obj)const
{
    return (10.0 - (getTime() - obj.lastTimeSeen));
}

double WorldModel::getConfidence(const EVisionObject  obj)const
{
    return getConfidence(getObject(obj));
}

unsigned WorldModel::getCurrentCycle()const
{
   return mCurentCycle;
}

unsigned WorldModel::getCurrentSimulationCycle()const
{
    return mCurentCycle;
}


/**set uniform number for each agent*/
bool WorldModel::setUnum(std::string num)
{
    mUnum = num;
    int pointer = 0;
    mINum = getNum(pointer,num);
    return (mINum == 0);
}

std::string WorldModel::getUnum()const
{
    return mUnum;
}

/**get Ralative Position**/
Vector3f  WorldModel::getRelPos(const EVisionObject obj)const
{
    TObjectToSenseMap::const_iterator iter = mObjectToSenseMap.find(obj);
    if(iter == mObjectToSenseMap.end()) return Vector3f(0,0,0);

    VisionSense Sense = (*iter).second;

    return polToCart(Sense);
}

/**this method return current simulation time*/
double WorldModel::getSimulationTime()const
{
    return mSimTime;
}

/**this method return current play time*/
double WorldModel::getTime()const
{
    return mTime;
}

std::string WorldModel::getOpponentTeamName()const
{
    return mOppTeamName;
}

int WorldModel::getPart(Vector3f coordinate)const
{
    int part[(int)FieldLength+1][(int)FieldWidth+1];
    int counter=0; 
    int x;
    int y;

    double tmpx = coordinate.x();
    tmpx +=FieldLength/2;
    //not 19
    if( (int)tmpx!=FieldLength)
       x = int(tmpx)+1;
    
    
    double tmpy = coordinate.y();
    tmpy -=FieldWidth/2;
    tmpy=abs(tmpy);
    //not 13
    if( (int)tmpy!=FieldWidth)
       y=int(tmpy)+1;
       
    for(int col=1;col<=FieldLength;col++)
        for(int row=1;row<=FieldWidth;row++)
        {
            counter++;
            part[col][row]=counter;
        }      
    
    return part[x][y];
}
EFieldArea WorldModel::getArea(Vector3f coordinate)const
{
     int area[4][4];
      int counter=0; 
      int x;
      int y;

    double tmpx = coordinate.x();
    if( -(FieldLength/2) == tmpx || FieldLength/2 == tmpx )
        tmpx= tmpx - ( sign(tmpx)/10 );
    tmpx +=FieldLength/2;
    tmpx/=(FieldLength/3);
    x = int(tmpx)+1;
    
    
    double tmpy = coordinate.y();
    if( -(FieldWidth/2) == tmpy || FieldWidth/2 == tmpy )
        tmpy= tmpy - ( sign(tmpy)/10 );
    tmpy -=FieldWidth/2;
    tmpy=abs(tmpy);
    tmpy /=(FieldWidth/3);
    y= int(tmpy)+1;

    for(int col=1;col<=3;col++)
        for(int row=1;row<=3;row++)
        {
            counter++;
            area[col][row]=counter;
        }      
    
    return (EFieldArea)(area[x][y]);

}

/**localize With One Flag Sense**/

bool  WorldModel::localizeWithOneFlag(EVisionObject flag, VisionSense flagSense, Vector3f& newPos)
{
    Vector3f flagPos = getRealPos(flag);
    Vector3f rep = getRelPos(flag);
    newPos       = flagPos - rep;
    return true;

    VisionSense tmpSense;
    tmpSense.distance = flagSense.distance;
    tmpSense.theta    = flagSense.theta + 180.0;
    tmpSense.phi      = -flagSense.phi;

    Vector3f flag2Proj = flagPos - newPos;
    Vector3f pos2Flag  = polToCart(tmpSense);

    newPos   = flagPos + pos2Flag;
    return true;
}

float getMyAngle2Point(Vector3f point)
{
  Vector2f myPos ( WorldModel::instance().getMyPos().x(),WorldModel::instance().getMyPos().y());
  Vector2f tmp   ( point.x(),point.y());
  return ( degNormalizeAngle( getVector2fAngleDeg (tmp - myPos))- degNormalizeAngle( WorldModel::instance().getMyPos().z()));

}

/** agar dar daste 'set' nazdiktarin bazikon be top az fasele 'radus' kamtar bod angah true barmigardanad
*/
bool WorldModel::isPlayerNearBall(const EObjectSet& set,const double & radus)
{
  double dist;  
  EVisionObject vo= getFastestInSetTo(set,BALL,&dist,9.5);
  
  std::cout<<"in isPlayer Near : distance = "<<dist<<" & Object = " <<vo<<std::endl;
  if (vo != OBJECT_NONE)
    return (dist < radus);
  else
    return false;
  
}
/** 
    in tabe neshan midahad ke aya agent dar rastaye darvaze harif hast
*/
bool WorldModel::isForwardOpponentGoal()
{
  
      int iArea = getArea(getMyPos());
    Vector3f targetPos1,targetPos2;
    if ((iArea >= DEFENSIVE_LEFT && iArea <= MID_RIGHT))
    {
      if (getTeamSide() == TS_LEFT)
      {
	std::cout<<"team side LEFT"<< mObjectToSenseMap[FLAG_1_R].realPos<< mObjectToSenseMap[FLAG_2_R].realPos;
	targetPos1 = mObjectToSenseMap[FLAG_1_R].realPos;
	targetPos2 = mObjectToSenseMap[FLAG_2_R].realPos;
      }
      else if (getTeamSide() == TS_RIGHT)
      {
	std::cout<<"team side Right"<< mObjectToSenseMap[FLAG_1_L].realPos<< mObjectToSenseMap[FLAG_2_L].realPos;
	targetPos1 = mObjectToSenseMap[FLAG_1_L].realPos;
	targetPos2 = mObjectToSenseMap[FLAG_2_L].realPos;
      }
    }   
    else      
    {
      if (getTeamSide() == TS_LEFT)
      {
	std::cout<<"team side LEFT"<< mObjectToSenseMap[GOAL_1_R].realPos<< mObjectToSenseMap[GOAL_2_R].realPos;
	targetPos1 = mObjectToSenseMap[GOAL_1_R].realPos;
	targetPos2 = mObjectToSenseMap[GOAL_2_R].realPos;
      }
      else if (getTeamSide() == TS_RIGHT)
      {
	std::cout<<"team side Right"<< mObjectToSenseMap[GOAL_1_L].realPos<< mObjectToSenseMap[GOAL_2_L].realPos;
	targetPos1 = mObjectToSenseMap[GOAL_1_L].realPos;
	targetPos2 = mObjectToSenseMap[GOAL_2_L].realPos;
      }
      else
      {      
	std::cerr << "cannot find may team side"<<std::endl;
	return false; /// 
      }    
    }
    Vector2f myPos(getMyPos().x(),getMyPos().y());
    float angle1 = -(getMyPos().z() - getVector2fAngleDeg (Vector2f(targetPos1.x(),targetPos1.y()) - myPos));
    float angle2 = -(getMyPos().z() - getVector2fAngleDeg (Vector2f(targetPos2.x(),targetPos2.y()) - myPos));
    std::cout <<"in isForwardOpponentGoal angle 1= "<<angle1<<" & angle 2 = "<<angle2<<std::endl;
    return (sign(angle1)!= sign(angle2));
   
    
}





/**calculate the Object Local Position**/
void WorldModel::calcVisionObjectLocalPos()
{
    for (int i = (int)(FLAG_1_L); i < (int)(OPPONENT_11); ++i)
    {
        VisionSense& vs = mObjectToSenseMap[static_cast<EVisionObject>(i)];

        if (vs.distance < 0) continue;

        float distance = vs.distance;
        float theta    = gDegToRad(gNormalizeDeg(vs.theta + 90.0f));
        float phi      = gDegToRad(gNormalizeDeg(vs.phi));

        vs.localPos[0] = distance * gCos(phi) * gCos(theta);
        vs.localPos[1] = distance * gCos(phi) * gSin(theta);
        vs.localPos[2] = distance * gSin(phi);
        if (i < static_cast<int>(BALL))
            i % 2 == 0 ? ++mLeftFlagsSee : ++mRightFlagsSee;
    }
}

Vector3f WorldModel::getBallPos()
{   
    return mBallPos;
}
/**get My position**/
Vector3f WorldModel::getMyPos()
{
    return mMyPos;
}

EPlayMode WorldModel::getPlayMode()const
{
    return mPlayMode;
}

int WorldModel::getTotalFlagSeen()const
{
    return mTotalFlagSeen;
}

Vector3f  WorldModel::polToCart(const VisionSense vision)const
 {
    return Vector3f
    (
         vision.distance * cosDeg( vision.theta ) *
         sinDeg(90.0f - vision.phi),
         vision.distance * sinDeg(vision.theta) *
         sinDeg(90.0f - vision.phi),
         vision.distance * cosDeg(90.0f - vision.phi)
    );
 }

HingeJointSense WorldModel::getHJoint( EJointID hJoint ) const
 {
    HingeJointSense tmp;
    if( hJoint >= JID_HEAD_1 && hJoint <= JID_RLEG_6 )
    {
     THingeJointSenseMap::const_iterator iter = mHingeJointSenseMap.find( hJoint ); 
     if (iter == mHingeJointSenseMap . end())
       return tmp;

     HingeJointSense sense = ( *iter ) . second;
     return sense;
     }
     std::cout << "HJoint Not Valid" << std::endl; 
     return tmp;
  }

HingeJointSense WorldModel::getHJoint( EJointID1 hJoint ) const
 {
    HingeJointSense tmp;
    if( hJoint >= JID_HEAD_1 && hJoint <= JID_RLEG_6 )
    {
     THingeJointSenseMap::const_iterator iter = mHingeJointSenseMap.find( hJoint ); 
     if (iter == mHingeJointSenseMap . end())
       return tmp;

     HingeJointSense sense = ( *iter ) . second;
     return sense;
     }
     std::cout << "HJoint Not Valid" << std::endl; 
     return tmp;
  }

FRPSense WorldModel::getFRP( EFRPID frp )const
{
    FRPSense tmp;
    if( frp >= FID_RF && frp <= FID_LF )
    {
        TFRPSenseMap::const_iterator iter = mFRPSenseMap.find( frp );
        if (iter == mFRPSenseMap . end())
            return tmp;
        FRPSense sense =(* iter ).second;
        return sense;
    }
    std::cout << "FRP Not Valid" << std::endl;
    return tmp;
}

ETeamSide WorldModel::getTeamSide()const
{
   return mTeamSide;
}

GyrSense WorldModel::getGyr()const
{
   return   mGyrSense;
}

AccSense WorldModel::getAcc()const
{
   return mAccSense;
}
bool WorldModel::isFrpSense(EFRPID frp) const
{
  return bFrpSense[frp];
}
 bool WorldModel::isBallKickable()
 {
   double tmpmaxdist=maxdist;
   double tmpmaxtheta=maxtheta;
  if(getCurrentAction()!=ACT_KICK)
  {
    tmpmaxdist=maxdist;
    tmpmaxtheta=maxtheta;
  }
  else if(WorldModel::instance().getCurrentAction() == ACT_KICK)
   {  
      tmpmaxdist=1;
      tmpmaxtheta=40;
   }
  
   VisionSense ball=getPolarBallPos();
   if(ball.distance<tmpmaxdist && abs(ball.theta)<tmpmaxtheta)
   {      
      return true;
   }
   
   return false;
 
 }

bool  WorldModel::setFellDown (bool isFDown)
{
 return (mIsFellDown=isFDown); 
}


bool WorldModel::isFellDown()const
{
    if(getPlayMode()==PM_BeforeKickOff)
      return false;
    return ( FallDownRecognition::instance().isFallDown(getCurrentCycle(),85) ||  mIsFellDown);
}

bool WorldModel::isStable()const
{
    static const float fTlorans = 0.5;

    return ( //mGyrSense.x > -fTlorans && mGyrSense.x < fTlorans &&
             mGyrSense.y > -fTlorans && mGyrSense.y < fTlorans);// &&
             //mGyrSense.z > -fTlorans && mGyrSense.z < fTlorans );
}

bool  WorldModel::isIn(const Vector2f& point, const float& telorans )const
{
    float x = mMyPos.x();
    float y = mMyPos.y();
    return  ((x > (point.x() - telorans)) && (x < (point.x() + telorans)) &&
             (y > (point.y() - telorans)) && (y < (point.y() + telorans)) );
}

///**************************** fast in set to**********************
bool WorldModel::isFellDown(EVisionObject player)const
{
  return ((getObject(player).realPos.z() < 0.35)&& getObject(player).realPos.z() != -1000.0);   /// agar ertefa head player kamtar az 0.35m bod pas be ehtemal ziad zamin khorde  
}
EVisionObject WorldModel::getFastestInSetTo(EObjectSet set, EVisionObject obj, double *distance,double confThr )
{
  int iBegin,iEnd;
  
  if (PLAYER_SET == set)
  {
    iBegin = TEAMMATE_1;
    iEnd   = OPPONENT_11;    
  }
  else if (TEAMMATE_SET == set)
  {
    iBegin = TEAMMATE_1;
    iEnd   = TEAMMATE_11;    
  }
  else if (OPPONENT_SET == set)
  {
    iBegin = OPPONENT_1;
    iEnd   = OPPONENT_11;    
  }
  else
    return OBJECT_NONE;
  std::map<EVisionObject,double> distanceMap;
  EVisionObject tmpEvisionObject;
  double plus =0;
  for(int i=iBegin; i<=iEnd; i++)
  {
    plus = 0;
    tmpEvisionObject = static_cast<EVisionObject>(i);
    VisionSense & vs = mObjectToSenseMap[tmpEvisionObject];
//     std::cout<< "object # "<<tmpEvisionObject<< " # is checked & confidence is :"<< getConfidence(tmpEvisionObject)<<std::endl; 
    if ( isFellDown(tmpEvisionObject))
      plus = 4;  /// may be change this variable
    if (confThr <= getConfidence(vs))
    {
      distanceMap[tmpEvisionObject] = (vs.realPos - getObject(obj).realPos).Length() + plus;
      std::cout<<"in getFastest vs.real pos = "<<vs.realPos <<" and realpos obj ="<<getObject(obj).realPos<<std::endl;
    }
  }
  std::map<EVisionObject,double>::const_iterator iter = distanceMap.begin();
  if (iter == distanceMap.end())   /// if not found object to calculate
    return OBJECT_NONE;
  std::pair<EVisionObject,double> min =*iter;
  for(iter;iter != distanceMap.end();iter++)
  {
    if ((*iter).second < min.second) 
      min = *iter;     
  }
  *distance =min.second;
  return min.first;    
}
  

/////////////////////////
/// Convert a Str to Its Number (Used In ACT && fix && ...)
string WorldModel::num2Str(int i) {
    return names[i];
}

double WorldModel::getJointAngle(EJointID1 name) {
    return getHJoint(name).angle;
}

double WorldModel::getJointAngle(string name) {
    if (name == "lae1") 
       return WorldModel::instance().getHJoint(JID_LARM_1).angle;
    if (name == "rae1") 
       return WorldModel::instance().getHJoint(JID_RARM_1).angle;
    if (name == "lae2") 
       return WorldModel::instance().getHJoint(JID_LARM_2).angle;
    if (name == "rae2") 
       return WorldModel::instance().getHJoint(JID_RARM_2).angle;
    if (name == "lae3") 
       return WorldModel::instance().getHJoint(JID_LARM_3).angle;
    if (name == "rae3") 
       return WorldModel::instance().getHJoint(JID_RARM_3).angle;
    if (name == "lae4") 
       return WorldModel::instance().getHJoint(JID_LARM_4).angle;
    if (name == "rle6") 
       return WorldModel::instance().getHJoint(JID_RLEG_6).angle;
    if (name == "lle6") 
       return WorldModel::instance().getHJoint(JID_LLEG_6).angle;
    if (name == "rle5") 
       return WorldModel::instance().getHJoint(JID_RLEG_5).angle;
    if (name == "lle5") 
       return WorldModel::instance().getHJoint(JID_LLEG_5).angle;
    if (name == "rle4") 
       return WorldModel::instance().getHJoint(JID_RLEG_4).angle;
    if (name == "lle4") 
       return WorldModel::instance().getHJoint(JID_LLEG_4).angle;
    if (name == "rle3") 
       return WorldModel::instance().getHJoint(JID_RLEG_3).angle;
    if (name == "lle3") 
       return WorldModel::instance().getHJoint(JID_LLEG_3).angle;
    if (name == "rle2") 
       return WorldModel::instance().getHJoint(JID_RLEG_2).angle;
    if (name == "lle2") 
       return WorldModel::instance().getHJoint(JID_LLEG_2).angle;
    if (name == "rle1") 
       return WorldModel::instance().getHJoint(JID_RLEG_1).angle;
    if (name == "lle1") 
       return WorldModel::instance().getHJoint(JID_LLEG_1).angle;
    if (name == "he2") 
       return WorldModel::instance().getHJoint(JID_HEAD_2).angle;
    if (name == "he1") 
       return WorldModel::instance().getHJoint(JID_HEAD_1).angle;
    if (name == "rae4") 
       return WorldModel::instance().getHJoint(JID_RARM_4).angle;
}
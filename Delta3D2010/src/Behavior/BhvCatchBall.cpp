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

#include "BhvCatchBall.h"
#include <cmath>
#include "BhvDribble.h"

using namespace salt;

BhvCatchBall::BhvCatchBall()
{
    mLeftPosition   = Vector3f(-5.4,0.6,0);
    
    mCenterPosition = Vector3f(-5.4,0,0);
    
    mCenterPosition = Vector3f(-5.4,-0.6,0);
    
    mTelorans       = Vector3f(0.05,0.05,1);
}

BhvCatchBall& BhvCatchBall::instance()
{
    static BhvCatchBall sBhvCatchBall;
    return sBhvCatchBall;
}

bool BhvCatchBall::execute()
{
    
    //sitDown();
     if( (WorldModel::instance().getArea(WorldModel::instance().getBallPos() )>=DEFENSIVE_LEFT) &&     
         (WorldModel::instance().getArea(WorldModel::instance().getBallPos() )<=DEFENSIVE_RIGHT)
 
       )
            BhvBasicWalk(false).execute();

      else 
          BhvBasicWalk( Vector2f(-8.4,0) ).execute();
//     if(WorldModel::instance().getBallPos().x()<0)
//         calculatePosition();
// 
//     cout<<"home position is: "<<homePosition<<endl;
//     cout<<"is in home is: "<<isInHomePosition()<<endl;
//     
//     cout<<"area is: "<<WorldModel::instance().getArea( WorldModel::instance().getBallPos() );
//     
//    if( WorldModel::instance().getConfidence(BALL)>=9.94 )
//     {
//         cout<<"ball confidence is: "<< WorldModel::instance().getConfidence(BALL);
//         cout<<"ball polar is: "<<WorldModel::instance().getPolarBallPos().theta;
//     }
//     //BhvFocusBall::instance().searchBall(7,0);
//    // BhvCatchBall::instance().execute(); 
//    
//    
//    
//    
//     if (WorldModel::instance().getArea( WorldModel::instance().getBallPos() ) >= DEFENSIVE_LEFT && 
//            WorldModel::instance().getArea( WorldModel::instance().getBallPos() ) <= DEFENSIVE_RIGHT
//           )
//        {
//            cout<<"in area";
// //        BhvClearBall(Vector2f(WorldModel::instance().getBallPos().x(),WorldModel::instance().getBallPos().y())).execute();
//            //Effectors::instance().setActionCommand();
//        }
//  
//        else if( homePosition == LEFT)//  && (!isInHomePosition() ) )
//          {
//           cout<<"walk left executed";
//           Walk::instance().Execute(0,110,SIDE_LEFT);
//           Effectors::instance().setActionCommand();   
//        }
//        if( (homePosition == RIGHT) && (!isInHomePosition() ) )
//        {  
//          cout<<"walk right executed";
//          Walk::instance().Execute(0,110,SIDE_RIGHT);
//          Effectors::instance().setActionCommand();
//        }
//        
//        
//        else if( homePosition == CENTER) // && (!isInHomePosition() ) )
//        {  
//            cout<<"sitdown";
//            sitDown();
//        }
}



void BhvCatchBall::sitDown()
{
    WalkParams param1;
    ModelParams param2;
           
    param1.Xsd          = 110 * 0.07f /100.0;  //max = 0.07
    param1.Xed          = 110 * 0.07f /100.0;  //max = 0.07
    param1. Hnor        = 0.18; //zano
    param2.FootOffset_X = 0.18; //baz shodane pa
    Walk::instance().setParam(param2,param1,true);
                   
    Walk::instance().Prepare();

    //top && down
    Effectors::instance().calculateVel(JID_LARM_1,-45,20);
    Effectors::instance().calculateVel(JID_RARM_1,-45,20);
         
    //left && right
    Effectors::instance().calculateVel(JID_LARM_2, 60,20);
    Effectors::instance().calculateVel(JID_RARM_2,-60,20);
         
    //arm
    Effectors::instance().calculateVel(JID_LARM_4, -60,20);
    Effectors::instance().calculateVel(JID_RARM_4,  60,20);
         
     //thight
     Effectors::instance().calculateVel(JID_RLEG_3,85,5);
     Effectors::instance().calculateVel(JID_LLEG_3,85,5);
         
     //walk.Execute(4.5,110,SIDE_FORWARD);
     Effectors::instance().setActionCommand();
}

void BhvCatchBall::calculatePosition()
{
    int part=WorldModel::instance().getPart( WorldModel::instance().getBallPos() )  ;
      
      if(part==4  ||
         part==5  ||
         part==12 ||
         part==13 ||
         part==20 ||
         part==21 ||
         part==28 ||
         part==29 ||
         part==36 ||
         part==37 ||
         part==44 ||
         part==45 
     ) 
        homePosition=CENTER;
      
   else if(part==1  ||
           part==2  ||
           part==3  ||
           part==9  ||
           part==10 ||
           part==11 ||
           part==17 ||
           part==18 ||
           part==19 ||
           part==25 ||
           part==26 ||
           part==27 ||
           part==33 ||
           part==34 ||
           part==35 ||
           part==41 ||
           part==42 ||
           part==43 
          )
        homePosition=LEFT;

   else if(part==6  ||
           part==7  ||
           part==8  ||
           part==14 ||
           part==15 ||
           part==16 ||
           part==22 ||
           part==23 ||
           part==24 ||
           part==30 ||
           part==31 ||
           part==32 ||
           part==38 ||
           part==39 ||
           part==40 ||
           part==46 ||
           part==47 ||
           part==48 
          )
              homePosition=RIGHT;
    // sitDown();

}

bool BhvCatchBall::isInHomePosition()
{/*
    if( homePosition==LEFT )
    if(  ( (WorldModel::instance().getMyPos().x())<= (mLeftPosition.x()+mTelorans.x()) ) || 
         ( (WorldModel::instance().getMyPos().x())>= (mLeftPosition.x()-mTelorans.x() )  ))
    if(  ( (WorldModel::instance().getMyPos().y())<= (mLeftPosition.y()+mTelorans.y()) ) || 
         ( (WorldModel::instance().getMyPos().y())>= (mLeftPosition.y()-mTelorans.y() )  )) 
        return true;
 
    if( homePosition==CENTER )
    if(  ( (WorldModel::instance().getMyPos().x())<= (mCenterPosition.x()+mTelorans.x()) ) || 
         ( (WorldModel::instance().getMyPos().x())>= (mCenterPosition.x()-mTelorans.x() )  ))
    if(  ( (WorldModel::instance().getMyPos().y())<= (mCenterPosition.y()+mTelorans.y()) ) || 
         ( (WorldModel::instance().getMyPos().y())>= (mCenterPosition.y()-mTelorans.y() )  )) 
        return true;
    
    
    if( homePosition==RIGHT )
    if(  ( (WorldModel::instance().getMyPos().x())<= (mRightPosition.x()+mTelorans.x()) ) || 
         ( (WorldModel::instance().getMyPos().x())>= (mRightPosition.x()-mTelorans.x() )  ))
    if(  ( (WorldModel::instance().getMyPos().y())<= (mRightPosition.y()+mTelorans.y()) ) || 
         ( (WorldModel::instance().getMyPos().y())>= (mRightPosition.y()-mTelorans.y() )  )) 
        return true;
    */
    return false;
}

EGkHomePos BhvCatchBall::getHomePosition()
{
    return homePosition;
}


void BhvCatchBall::setBehavior()
{
    //if( homePosition==LEFT && isInHomePosition()
}
// void Kick::getPrepareMatrix()
// {
//     mTorsoMatrix.Identity();
//     mHoldFootMatrix.Identity();
//     mMoveFootMatrix.Identity();
//     salt::Vector3f torsoPos(0.0 , 0.0 , 0.3301),
//                    holdPos(-0.055, 0.0, 0.015),
//                    movePos(0.055, 0.0, 0.015);
//     mTorsoMatrix.Pos() = torsoPos;
//     mHoldFootMatrix.Pos() = holdPos;
//     mMoveFootMatrix.Pos() = movePos;
// }
// 
// void Kick::ApplyJVel(bool left)
// {
//     Effectors& eff = Effectors::instance();
//     boost::shared_array<float> IKJointAngle = Kinematic::instance().getIKJointAngle();
//     if (left) // left foot
//     {
//         eff.mJointVel[JID_LLEG_1] = (IKJointAngle[JID_LLEG_1] -
//                                          eff.mJointAngle[JID_LLEG_1])/ mSlowGain ;
// 
//         eff.mJointVel[JID_LLEG_2] = (IKJointAngle[JID_LLEG_2] -
//                                          eff.mJointAngle[JID_LLEG_2])/ mSlowGain ;
// 
//         eff.mJointVel[JID_LLEG_3] = (IKJointAngle[JID_LLEG_3] -
//                                          eff.mJointAngle[JID_LLEG_3])/ mSlowGain ;
// 
//         eff.mJointVel[JID_LLEG_4] = (IKJointAngle[JID_LLEG_4] -
//                                          eff.mJointAngle[JID_LLEG_4])/ mSlowGain ;
// 
//          eff.mJointVel[JID_LLEG_5] = (IKJointAngle[JID_LLEG_5] -
//                                           eff.mJointAngle[JID_LLEG_5])/ mSlowGain ;
// 
//         eff.mJointVel[JID_LLEG_6] = (IKJointAngle[JID_LLEG_6] -
//                                          eff.mJointAngle[JID_LLEG_6])/ mSlowGain ;
//     }
//     else // right foot
//     {
//         eff.mJointVel[JID_RLEG_1] = (IKJointAngle[JID_RLEG_1] -
//                                          eff.mJointAngle[JID_RLEG_1])/ mSlowGain ;
// 
//         eff.mJointVel[JID_RLEG_2] = (IKJointAngle[JID_RLEG_2] - 
//                                          eff.mJointAngle[JID_RLEG_2])/ mSlowGain ;
// 
//         eff.mJointVel[JID_RLEG_3] = (IKJointAngle[JID_RLEG_3] -
//                                          eff.mJointAngle[JID_RLEG_3])/ mSlowGain ;
// 
//         eff.mJointVel[JID_RLEG_4] = (IKJointAngle[JID_RLEG_4] -
//                                          eff.mJointAngle[JID_RLEG_4])/ mSlowGain ;
// 
//          eff.mJointVel[JID_RLEG_5] = (IKJointAngle[JID_RLEG_5] -
//                                           eff.mJointAngle[JID_RLEG_5])/ mSlowGain ;
// 
//         eff.mJointVel[JID_RLEG_6] = (IKJointAngle[JID_RLEG_6] -
//                                          eff.mJointAngle[JID_RLEG_6])/ mSlowGain ;
//     }
// }


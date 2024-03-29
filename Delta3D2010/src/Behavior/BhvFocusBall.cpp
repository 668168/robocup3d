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

#include "BhvFocusBall.h"

float BhvFocusBall::X2[2];
float BhvFocusBall::Y2[2];
float BhvFocusBall::Rotation2[2];
float BhvFocusBall::Distance2[2];
float BhvFocusBall::Phi2[2];
float BhvFocusBall::Theta2[2];
int   BhvFocusBall::counter;
float BhvFocusBall::X;
float BhvFocusBall::Y;
float BhvFocusBall::Rotation;
float BhvFocusBall::Distance;
float BhvFocusBall::Phi;
float BhvFocusBall::Theta;
bool  BhvFocusBall::flag;
bool  BhvFocusBall::flag1;

BhvFocusBall::BhvFocusBall()
{

}

bool BhvFocusBall::execute()
{
  if (WorldModel::i().getConfidence()<=9.7)
   if(WorldModel::i().getHJoint(JID_HEAD_1).angle<0)
   {
     Effectors::instance().calculateVel(JID_HEAD_1,90.0,10);
     Effectors::instance().setActionCommand();
   }
    else
    {
      Effectors::instance().calculateVel(JID_HEAD_1,-90,10);
      Effectors::instance().setActionCommand();
    }  
   else if ( (WorldModel::i().getConfidence(BALL) > 9.94))
    {
           Effectors::instance().calculateVel(JID_HEAD_1 ,
           WorldModel::instance().getPolarBallPos().theta,10);
            Effectors::instance().calculateVel(JID_HEAD_2 , -15.0,10);
            Effectors::instance().setActionCommand();
    }
    else
     {
        searchBall(7,3);
      }
}

void  BhvFocusBall::focusBall(float VJ1,float VJ2)
{

}

// void   BhvFocusBall::searchBall(float VJ1,float VJ2)
// {
//     if ( WorldModel::instance().getHJoint(JID_HEAD_1).angle >=-120 && flag)
//     {
//         AngularMotor::instance().moveHead(-1*VJ1,-1*VJ2);
//         Connection::instance().sendMessage(AngularMotor::instance().str());
//         if ( WorldModel::instance().getHJoint(JID_HEAD_1).angle <= -110)
//             flag = false;
//     }
//     else
//     {
//         AngularMotor::instance().moveHead(VJ1,VJ2);
//         Connection::instance().sendMessage(AngularMotor::instance().str());
//         if(WorldModel::instance().getHJoint(JID_HEAD_1).angle >= 110)
//             flag = true;
//     }
// }

void   BhvFocusBall::searchBall(float VJ1,float VJ2)
{
    if ( WorldModel::instance().getHJoint(JID_HEAD_1).angle >= -120 && flag)
    {
        AngularMotor::instance().moveHead(-1*VJ1,0);

	if ( WorldModel::instance().getHJoint(JID_HEAD_2).angle >=-16 && flag1)
	{
		AngularMotor::instance().moveHead(-1*VJ1,-1*VJ2);
		if ( WorldModel::instance().getHJoint(JID_HEAD_2).angle <= -15)
		flag1 = false;
	}
	else
	{
		AngularMotor::instance().moveHead(-1*VJ1,VJ2);
		if(WorldModel::instance().getHJoint(JID_HEAD_2).angle >= 0)
		flag1 = true;
	}
        Connection::instance().sendMessage(AngularMotor::instance().str());
        if ( WorldModel::instance().getHJoint(JID_HEAD_1).angle <= -119)
            flag = false;
    }
    else
    {
        AngularMotor::instance().moveHead(VJ1,0);
	if ( WorldModel::instance().getHJoint(JID_HEAD_2).angle >= -16 && flag1)
	{
		AngularMotor::instance().moveHead(VJ1,-1*VJ2);
		if ( WorldModel::instance().getHJoint(JID_HEAD_2).angle <= -15)
		flag1 = false;
	}
	else
	{
		AngularMotor::instance().moveHead(VJ1,VJ2);
		if(WorldModel::instance().getHJoint(JID_HEAD_2).angle >= 0)
		flag1 = true;
	}
        Connection::instance().sendMessage(AngularMotor::instance().str());
        if(WorldModel::instance().getHJoint(JID_HEAD_1).angle >= 119)
            flag = true;
    }
}

void   BhvFocusBall::searchBall(float VJ1,float VJ2,float Start,float End)
{
    if ( WorldModel::instance().getHJoint(JID_HEAD_1).angle >=(WorldModel::instance().getPolarBallPos().theta + End) && flag)
    {
        AngularMotor::instance().moveHead(-1*VJ1,-1*VJ2);
        Connection::instance().sendMessage(AngularMotor::instance().str());
        if ( WorldModel::instance().getHJoint(JID_HEAD_1).angle <= -120)
            flag = false;
    }
    else
    {
        AngularMotor::instance().moveHead(VJ1,VJ2);
        Connection::instance().sendMessage(AngularMotor::instance().str());
        if(WorldModel::instance().getHJoint(JID_HEAD_1).angle >= 120)
            flag = true;
    }
}


/*
#include "BhvFocusBall.h"
EState BhvFocusBall::mPrvAngle = NONE;
double BhvFocusBall::mCalculatedAngle = 0.0f;
const double BhvFocusBall::mRange = 55.0f;
bool BhvFocusBall::execute()
{
    return true;
}

float BhvFocusBall::calAngle ()
{
    static const float telorans = 5.0;
    float top  = mMidle + mRange;
    float down = mMidle - mRange;

    if ( mCalculatedAngle <  )
}

bool BhvFocusBall::doTurnNeck(const float& vertical ,
                              const float& horizontal,
                              const float& telorans  )
{
    double currentHorizontalAngle = WorldModel::i().getHJoint(JID_HEAD_1).angle;
    double currentVerticalAngle   = WorldModel::i().getHJoint(JID_HEAD_2).angle;
    if ( (currentHorizontalAngle < horizontal + telorans && 
          currentHorizontalAngle > horizontal - telorans )&&
         (currentVerticalAngle   < vertical + telorans &&
          currentVerticalAngle   > vertical - telorans ))
    {
        return true;
    }
    Effectors::instance().calculateVel(JID_HEAD_1,horizontal, 20);
    Effectors::instance().calculateVel(JID_HEAD_2,vertical, 20);
    Effectors::instance().setActionCommand();
    return false;
}

*/
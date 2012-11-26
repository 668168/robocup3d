/*****************************************************************************************
 *                                      SEU-3D
 *                     -------------------------------------------------
 * Copyright (c) 2005, Yuan XU<xychn15@yahoo.com.cn>,Chang'e SHI<evelinesce@yahoo.com.cn>
 * Copyright (c) 2006, Yuan XU<xuyuan.cn@gmail.com>,Chunlu JIANG<JamAceWatermelon@gmail.com>
 * Southeast University ,China
 * All rights reserved.
 *
 * Additionally,this program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 ****************************************************************************************/

 
#ifndef _SKILL_H
#define _SKILL_H

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#include "WorldModel.h"
#include "Action.h"

using namespace salt;
using namespace std;

/*****************************************************************/
/************************** SKILL ********************************/
/*****************************************************************/
class Skill: public Singleton<Skill>
{
public:
	Skill();
	~Skill();

protected:


public:
	
	Actions catchBall();
	////////////////// drive skills ////////////////////////////
	
	//-*  basic drive skill
	static Vector3f getPowerForVel( Vector3f driveForce, Vector3f myVel[3], const Vector3f &endVel );
	Vector3f getPowerForVel( const Vector3f &endVel ) const;
	static Vector3f gotoNStop( Vector3f driveForce, Vector3f myVel[3], Vector3f myPos[3], Vector3f endPos );
		   Action	gotoNStop( const Vector3f &endPos ) const;
	static Vector3f gotoWithMinSpeed( Vector3f driveForce, Vector3f myVel[3], Vector3f myPos[3], Vector3f endPos, float minSpeed );
		   Action	gotoWithMinSpeed( Vector3f endPos, float minSpeed );
	
	Action runTo( const Vector3f &endPos, const Vector3f &endVel=Vector3f(0,0,0) ) const;
	Vector3f runTo( const Vector3f &beginPos, const Vector3f &beginVel, const Vector3f &endPos, const Vector3f &endVel) const;
	float getRunPower( const float &x0, const float &v0, const float &xf, const float &vf, const float &maxPower) const;
	
	Action dashTo( const Vector3f &pos)const;
	Action	dashToBall() const;
	

//--2005-10-25
	static	float	changeSpeed( const float &v0, const float &v1, const float &maxF, float &d, Time &t);
	static	float	driveTo( const float &x0, const float &v0, const float &xf, const float &vf, const float &maxF,Time &t);
	static Vector3f	driveTo( const Vector3f &beginPos, const Vector3f &beginVel, const Vector3f &endPos, const Vector3f &endVel, Time &time);
			Action	driveTo( const Vector3f &endPos, const Vector3f &endVel, Time &time) const;

	Action turnAroundPos( const Vector3f &pos, const float &radious, bool clockWise=true ) const;


	//-* PID algorithm
	template < class Type1, class Type2 >
	static	Type2 algorithmPID( Type1 Kp, Type1 Ki, Type1 Kd, Type2 ek, Type2 ek_1, Type2 ek_2 )
	{
		return ( (ek-ek_1)*Kp + ek*Ki + (ek-ek_1*2+ek_2)*Kd );
	}
	
	template < class Type1, class Type2 >
	static	Type2 algorithmP( Type1 Kp, Type2 ek )
	{
		return ek*Kp;		
	}
	
	template < class Type1, class Type2 >
	static	Type2 algorithmPD( Type1 Kp, Type1 Kd, Type2 ek, Type2 ek_1, Type2 ek_2 )
	{
		return ek*Kp + (ek-ek_1*2+ek_2)*Kd;		
	}
	
	static float velPID( float ek, float ek_1, float ek_2 );
	static float posPID( float ek, float ek_1, float ek_2);
	
	/////////////////////// skills /////////////////////////////
	Action runStrategicPos() const;
	Action runStrategicPos( const Vector3f &posBall) const;
	Action interceptBall( Vector3f goal = Vector3f(55,0,0), const bool isKicking=false) const;
	Action interceptBall0( Vector3f goal = Vector3f(55,0,0) );//the old intercept, that use in defence
	//-*  drive avoid blocking the ball when intercept the ball in some need suituation
	Vector3f projectInterceptPos( Vector3f posIntercept ) const;
	Vector3f projectDribblePos( const Vector3f &posPlayer, const Vector3f &posBall, const AngDeg &ang ) const;

//--2005-11-01
	//-* kick skill enable the agent intercept and then kick tha ball
	bool	shoudIKick( const Vector3f &goal, const AngDeg maxAngErr=12 )const;
	bool	shoudIKick( const Vector3f &goalLeft, const Vector3f &goalRight) const;
	Actions	kickTo( const Vector3f &goal ,const float kickForce=max_kick_force,const AngDeg kickAng=min_kick_angle, const AngDeg maxAngErr=12) const;
	Actions kickBetween( const Vector3f &goalLeft, const Vector3f &goalRight, const float kickForce=max_kick_force, const AngDeg kickAng=min_kick_angle) const;
	float	calGroundKickForce( const float &dist, const float &v0, const float &vf ) const;
	float	calGroundKickForce( const float &dist) const;

	Actions dribble( const Vector3f &goal ) const;
	
	Actions directPass( Num num );
	
	Action interceptClearBall() const;
	Actions clearBall(Num num=0) const;
	Actions goalieClearBall(Num num=0) const;
	bool	isKickDirectionDanagerous() const;
	bool	canIClear() const;
	AngDeg	calClearAngle() const;
	
		
	Actions defendGoal() const;
	Vector3f setInterceptPosBeforeGoal(const Vector3f &posIntercept) const;
	
	Actions pass( Num teammateNum ) const;
	Actions fastPass(Num num)const;
	Actions oneTouch(Num num)const;
	Num		selectPass(Num num)const;
	AngDeg	calPassAng(const float passDist)const;
	Actions safePass( Num teammateNum ) const;
	
	Actions fastDribble(const Vector3f &goal) const;

};

#define SKILL Skill::GetSingletonPtr()

#endif /* _SKILL_H */

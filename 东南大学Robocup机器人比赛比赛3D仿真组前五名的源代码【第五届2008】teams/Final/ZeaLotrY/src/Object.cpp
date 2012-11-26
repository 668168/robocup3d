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

 
#include "Object.h"

void setupPlayModeMap( TPlayModeMap &playModeMap )
{
    playModeMap.clear();

    playModeMap[STR_PM_BeforeKickOff] 		= PM_BeforeKickOff;
    playModeMap[STR_PM_KickOff_Left]  		= PM_KickOff_Left;
    playModeMap[STR_PM_KickOff_Right] 		= PM_KickOff_Right;
    playModeMap[STR_PM_PlayOn]        		= PM_PlayOn;
    playModeMap[STR_PM_KickIn_Left]   		= PM_KickIn_Left;
    playModeMap[STR_PM_KickIn_Right]  		= PM_KickIn_Right;
	playModeMap[STR_PM_CORNER_KICK_LEFT]	= PM_CORNER_KICK_LEFT;
	playModeMap[STR_PM_CORNER_KICK_RIGHT]	= PM_CORNER_KICK_RIGHT;
	playModeMap[STR_PM_GOAL_KICK_LEFT]		= PM_GOAL_KICK_LEFT;
	playModeMap[STR_PM_GOAL_KICK_RIGHT]		= PM_GOAL_KICK_RIGHT;
	playModeMap[STR_PM_OFFSIDE_LEFT]		= PM_OFFSIDE_LEFT;
	playModeMap[STR_PM_OFFSIDE_RIGHT]		= PM_OFFSIDE_RIGHT;
	playModeMap[STR_PM_GameOver]      		= PM_GameOver;
    playModeMap[STR_PM_Goal_Left]     		= PM_Goal_Left;
    playModeMap[STR_PM_Goal_Right]    		= PM_Goal_Right;
	playModeMap[STR_PM_FREE_KICK_LEFT]		= PM_FREE_KICK_LEFT;
	playModeMap[STR_PM_FREE_KICK_RIGHT]		= PM_FREE_KICK_RIGHT;
	playModeMap[STR_PM_Unknown]				= PM_NONE;
	
}

/************************************************************************/
/************************ OBJECT ****************************************/
/************************************************************************/
Object::Object()
{
}

Object::~Object()
{
}

void Object::updateLastSeen( Time timeLastSeen, VisionSense visionLastSeen )
{
	if ( timeLastSeen > getTimeSeen() 
		|| _timeSeen.size() == 0	)
	{
		pushDequeValue( _timeSeen, timeLastSeen, max_vision_history_num );
		pushDequeValue( _visionSeen, visionLastSeen, max_vision_history_num );
		pushDequeValue( _posRelativeSeen, getPosRelativeFromVision( visionLastSeen ), max_vision_history_num );
	}
}

Vector3f Object::getVisionError() const
{
	// constants
	const float server_vision_dist_sigma = 0.0965;
	const float server_vision_theta_sigma = 0.1225;
	const float server_vision_phi_sigma = 0.1480;
	const Vector3f sigma_a = Vector3f(4.3, 4.3, 0.18);
	const Vector3f sigma_b = Vector3f(0.084, 0.084, 0.0022);

	VisionSense flagSense = getVisionSeen();
	Vector3f errorVar;
	
	//-* var[0]=sigma_a*| d*d_sigma *sin(t)*t_sigma *sin(p)*p_sigma|+sigma_b
	errorVar[0] = abs( flagSense.distance*server_vision_dist_sigma *sinDeg(flagSense.theta)*server_vision_theta_sigma *sinDeg(flagSense.phi)*server_vision_phi_sigma);
	errorVar[1] = abs( flagSense.distance*server_vision_dist_sigma *cosDeg(flagSense.theta)*server_vision_theta_sigma *sinDeg(flagSense.phi)*server_vision_phi_sigma);
	errorVar[2] = abs( flagSense.distance*server_vision_dist_sigma *cosDeg(flagSense.phi)*server_vision_phi_sigma);
	for ( int i=0; i<3; i++)
	{
		errorVar[i] = sigma_a[i]*errorVar[i] +sigma_b[i];
	}
	
	return errorVar;
}

/*****************************************************************************/
/********************** FIXED OBJECT *****************************************/
/*****************************************************************************/

FixedObject::FixedObject()
{
}

FixedObject::~FixedObject()
{
}

void FixedObject::updatePosRelative( Time time, Vector3f posMe )
{
	pushDequeValue( _time, time, max_data_history_num );
	pushDequeValue( _posRelative, (_posGlobal - posMe), max_data_history_num );

}

/*****************************************************************************/
/********************** DYNAMIC OBJECT ***************************************/
/*****************************************************************************/
DynamicObject::DynamicObject()
{
}

DynamicObject::~DynamicObject()
{
}

void DynamicObject::updateDynamic( const Time &time, const Vector3f &posGlobal, const Vector3f &posMe, const Vector3f &globalVelocity, const Vector3f &globalAcceletation)
{
	if ( time > getTime() )
	{
		pushDequeValue( _time, time, max_data_history_num );
		pushDequeValue( _posGlobal, posGlobal, max_data_history_num );
		pushDequeValue( _posRelative, (posGlobal - posMe), max_data_history_num );
		pushDequeValue( _globalVelocity, globalVelocity, max_data_history_num );
		pushDequeValue( _globalAcceletation, globalAcceletation, max_data_history_num );
	}
}

//-* for update
Vector3f DynamicObject::calculateGlobalPosFromVision( const Vector3f &posMyself) const
{
	return posMyself + getPosRelativeSeen();
}

Vector3f DynamicObject::calculateGlobalVelFromVision( const Vector3f &velMyself) const
{
	VisionSense const nowVision = getVisionSeen(0);
	VisionSense const preVision = getVisionSeen(1);
	float const r = nowVision.distance;
	AngRad const t = Deg2Rad( nowVision.theta);
	AngRad const p = Deg2Rad( nowVision.phi);
	float const dr = r - preVision.distance;
	AngRad const dt = t - Deg2Rad( preVision.theta);
	AngRad const dp = p - Deg2Rad( preVision.phi);
	float const sinT = sin(t);
	float const cosT = cos(t);
	float const sinP = sin(p);
	float const cosP = cos(p);
	
	Vector3f Vr;
	//float const den = sqr(cosP)-sqr(sinP)*(cosT+sinT);
	//Vr.x() = ( dr*cosP*cosT-dt*r*(sqr(cosP)*sinT-sqr(sinP))-dp*r*sinP*cosT)/den;
	//Vr.y() = ( dr*cosP*sinT-dt*r*(sqr(cosP)*cosT-sqr(sinP))-dp*r*sinP*sinT)/den;
	//Vr.z() = ( dp*r +( Vr.x() +Vr.y())*sinP )/cosP;
	float const k = ( dr*cosP- dp*r*sinP);
	Vr.x() = k*cosT -dt*r*sinT;
	Vr.y() = k*sinT +dt*r*cosT;
	Vr.z() = ( dp*r + (Vr.x()*cosT+Vr.y()*sinT)*sinP )/cosP;
	//for m/s
	Vr = Vr*5;
	return Vr+velMyself;
}

Vector3f DynamicObject::calculateGlobalPosFromMemory( const Time deltaTime) const
{
	return getGlobalPos() + getGlobalVelocity()* deltaTime;
}

/*****************************************************************************/
/********************* PLAYER OBJECT *****************************************/
/*****************************************************************************/
PlayerObject::PlayerObject()
{
	_num = 0;
	_mass = 75;
	_radius = 0.22;
}

PlayerObject::~PlayerObject()
{
}

/*****************************************************************************/
/********************* BALL OBJECT *******************************************/
/*****************************************************************************/
BallObject::BallObject()
{
	_mass = 0.425; //-* this is defaut value, [0.4, 0.45]kg
	
	//-* init kalmanFilter parameters
	setupKalmanFilter();
	
	/** drag conf */
	setDragConf();
}

BallObject::~BallObject()
{
}
/*
float BallObject::nnSimNextVel( const float v0 )const
{
	int sig = sign(v0);
	NN::NN_VECTOR in,out;
	in[0]=setMaxNMin(abs(v0),20.0f,0.0f);
	_nnBallX0.sim( in,out );
	return out[0]*sig;
}*/

void BallObject::setDragConf()
{
	_groundDragConf = ( 1 - sim_step_time*ground_friction_factor/getMass() );
	_airDragConf = ( 1 - sim_step_time*air_friction_factor/getMass() );
}

void BallObject::setMass( float mass ) 
{ 
	_mass = mass;
	setDragConf();
}

void BallObject::predictStateAfterOneStep(	Vector3f &pos, Vector3f &prePos, Vector3f &preprePos,
										Vector3f &vel, Vector3f &preVel, Vector3f &prepreVel ) const
{
	bool bIsGroundBall = isGroundBall( pos, prePos, preprePos, vel, preVel, prepreVel );
	bool bIsFallOnGround = isFallOnGround( pos, prePos, preprePos, vel, preVel, prepreVel );
	
	preprePos = prePos;
	prepreVel = preVel;
	prePos = pos;
	preVel = vel;
	
	pos = pos + vel*sim_step_time;
	if ( pos[2] < getRadius() ) pos[2] = getRadius();
	//水平方向
	if ( bIsGroundBall )//是地滚球？
	{
		vel[0] *= _groundDragConf;//( 1 - sim_step_time*ground_friction_factor/getMass() );
		vel[1] *= _groundDragConf;//( 1 - sim_step_time*ground_friction_factor/getMass() );
		//vel[0] = nnSimNextVel(vel[0]);
		//vel[1] = nnSimNextVel(vel[1]);
	}
	else
	{
		vel[0] *= _airDragConf;//( 1 - sim_step_time*air_friction_factor/getMass() );
		vel[1] *= _airDragConf;//( 1 - sim_step_time*air_friction_factor/getMass() );
	}

	//竖直方向
	if ( bIsFallOnGround )//碰地反弹
	{
		vel[2]*=ground_rebound_ball_factor;
	}
	else
	{
		vel[2]=(1 - sim_step_time*air_friction_factor/getMass())*vel[2]
					-sim_step_time*acceleration_of_gravity;
	}

	//-* new adapt @2005-11-08-by-XuYuan
	//-* S = S0 + V0*t + 0.5*a*t^2
	/*Vector3f force,a;
	float uForce;
	//水平方向
	if ( bIsGroundBall )//是地滚球？
	{
		uForce = -ground_friction_factor;
	}
	else
	{
		uForce = -air_friction_factor;
	}
	force = vel*uForce;
	a = force/getMass();
	//竖直方向 
	if ( bIsFallOnGround )//碰地反弹//????????? need nore test
	{
		a.z() = (ground_rebound_ball_factor-1)*vel.z()/sim_step_time;
	}
	else
	{
		a.z() -= acceleration_of_gravity;
	}
	
	pos = pos + vel*sim_step_time + a*pow2(sim_step_time)*0.5;
	vel = vel + a*sim_step_time;
	if ( pos[2] < getRadius() ) pos[2] = getRadius();
	*/
}

bool BallObject::predictStateAfterNrSteps(	Vector3f &pos, Vector3f &prePos, Vector3f &preprePos,
										Vector3f &vel, Vector3f &preVel, Vector3f &prepreVel,
										int iStep,
										int iStepMax ) const
{
	for ( int i=0;i < iStep; i++ )
	{
		predictStateAfterOneStep( pos, prePos, preprePos,
										 vel, preVel, prepreVel );
		if ( i > iStepMax ) return false;
	}
	return true;
}

/*!判断球是不是刚好落地反弹
\param 球的当前位置
\param 球的但前速度
\return 是不是落地反弹*/
bool BallObject::isGroundBall( const Vector3f &posBall, const Vector3f &prePosBall, const Vector3f &preprePosBall,
						const Vector3f &velBall, const Vector3f &preVelBall, const Vector3f &prepreVelBall) const
{
	return posBall.z()+velBall.z()*sim_cycle_time<0;
}

bool BallObject::isFallOnGround( const Vector3f &posBall, const Vector3f &prePosBall, const Vector3f &preprePosBall,
						const Vector3f &velBall, const Vector3f &preVelBall, const Vector3f &prepreVelBall) const
{
	return abs(velBall.z())<0.3f;
}

bool BallObject::isBallStop( const Vector3f &posBall, const Vector3f &prePosBall, const Vector3f &preprePosBall,
						const Vector3f &velBall, const Vector3f &preVelBall, const Vector3f &prepreVelBall,const float minSpeed) const
{
	return ( velBall.Length() < minSpeed
			&& isGroundBall( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall)
			);
}

void BallObject::setupKalmanFilter()
{
	//-* Initial error covariance
	for ( int i=0; i<4; i++)
	{
		_kalmanP[i].Zero();
	}
}

void BallObject::updateKalman( const Step iStep )
{
	Vector3f oldP[4];
	const Second deltaTime = Step2Second(iStep);
	const float Q = 0.03;
	for ( int i=0;i<4;i++)
	{
		oldP[i] = _kalmanP[i];
	}
	float res = 1- air_friction_factor/getMass()*deltaTime;
	//float resZ = 1- ( air_friction_factor/getMass() )*deltaTime;
	//** P = APA`
	//-* P11	
	_kalmanP[0].x() = oldP[0].x()*pow2(res) +Q;
	_kalmanP[0].y() = oldP[0].y()*pow2(res) +Q;
	_kalmanP[0].z() = oldP[0].z()*pow2(res)+Q +acceleration_of_gravity*pow2(deltaTime);
	//-* P12
	_kalmanP[1].x() = ( oldP[0].x()*deltaTime + oldP[1].x())*res;
	_kalmanP[1].y() = ( oldP[0].y()*deltaTime + oldP[1].y())*res;
	_kalmanP[1].z() = ( oldP[0].z()*deltaTime + oldP[1].z())*res;
	//-* P21
	_kalmanP[2].x() = ( oldP[0].x()*deltaTime + oldP[2].x())*res;
	_kalmanP[2].y() = ( oldP[0].y()*deltaTime + oldP[2].y())*res;
	_kalmanP[2].z() = ( oldP[0].z()*deltaTime + oldP[2].z())*res;
	//-* P22
	_kalmanP[3] = oldP[0]*pow2(deltaTime) + (oldP[1]+oldP[2])*deltaTime + oldP[3];
}

/*****************************************************************************/
/********************* AGENT OBJECT ******************************************/
/*****************************************************************************/
AgentObject::AgentObject()
{
	//-* init kalmanFilter parameters
	setupKalmanFilter();
}

AgentObject::~AgentObject()
{
}

void AgentObject::setupKalmanFilter()
{
	//-* Initial error covariance
	_kalmanP[0] = Vector3f(0,0,0);
	_kalmanP[1] = Vector3f(0,0,0);
	_kalmanP[2] = Vector3f(0,0,0);
	_kalmanP[3] = Vector3f(0,0,0);
}

void AgentObject::updateKalman( const Time deltaTime )
{
	const float driveQ = 0.005*35.0 * 12.0 / 100.0*10.0;
	
	Vector3f oldP[4];
	for ( int i=0;i<4;i++)
	{
		oldP[i] = _kalmanP[i];
	}
	float res = ( 14.43/( 30*deltaTime + 14.43));
	//-* P11
	const float bqb = 0.4848*0.4848*driveQ*driveQ*deltaTime*deltaTime;
	Vector3f BQB;
	Vector3f power = getDriveForce();
	for ( int i=0; i<3; i++)
	{
		BQB[i] = abs(power[i])*bqb;	
	}		
	_kalmanP[0] = oldP[0]*res*res  +  BQB;
	//-* P12
	_kalmanP[1] = ( oldP[0]*deltaTime + oldP[1])*res;
	//-* P21
	_kalmanP[2] = ( oldP[0]*deltaTime + oldP[2])*res;
	//-* P22
	_kalmanP[3] = oldP[0]*deltaTime*deltaTime + (oldP[1]+oldP[2])*deltaTime + oldP[3];
}

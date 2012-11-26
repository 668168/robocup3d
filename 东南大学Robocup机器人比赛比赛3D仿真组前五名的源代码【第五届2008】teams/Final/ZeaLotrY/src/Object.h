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

 
#ifndef _OBJECT_H
#define _OBJECT_H

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#include "Settings.h"
#include "Logger.h"
#include "Action.h"
#include <string>



using namespace salt;
using namespace std;


//-*  mapping from gamestate string to TPlayMode
    typedef std::map<std::string, TPlayMode> TPlayModeMap;
	void setupPlayModeMap( TPlayModeMap &playModeMap );


enum Vector3fType
{
	VT_GLOBAL_POS = 0,
	VT_GLOBAL_VEL = 1,
	VT_GLOBAL_ACC = 2,
	VT_RELATIVE_POS = 3,
	VT_RELATIVE_POS_SEEN = 4,
	
	VT_UNKNOWN = 5,
	VT_ILLEGAL = 6
};

enum VisionObject
{
	//-* ball
    VO_BALL   = 0,
	//-* fixed object
    VO_FLAG1L = 1,
    VO_FLAG1R = 2,
    VO_FLAG2L = 3,
    VO_FLAG2R = 4,
    VO_GOAL1L = 5,
    VO_GOAL1R = 6,
    VO_GOAL2L = 7,
    VO_GOAL2R = 8,
	//-* teammate
	VO_TEAMMATE_1 = 9, 
    VO_TEAMMATE_2 = 10, 
    VO_TEAMMATE_3 = 11, 
    VO_TEAMMATE_4 = 12, 
    VO_TEAMMATE_5 = 13, 
    VO_TEAMMATE_6 = 14, 
    VO_TEAMMATE_7 = 15, 
    VO_TEAMMATE_8 = 16, 
    VO_TEAMMATE_9 = 17, 
    VO_TEAMMATE_10 = 18, 
    VO_TEAMMATE_11 = 19, 
    VO_TEAMMATE_UNKNOWN = 20,
	//-* opponent
    VO_OPPONENT_1 = 21, 
    VO_OPPONENT_2 = 22, 
    VO_OPPONENT_3 = 23, 
    VO_OPPONENT_4 = 24, 
    VO_OPPONENT_5 = 25, 
    VO_OPPONENT_6 = 26, 
    VO_OPPONENT_7 = 27, 
    VO_OPPONENT_8 = 28, 
    VO_OPPONENT_9 = 29, 
    VO_OPPONENT_10 = 30, 
    VO_OPPONENT_11 = 31, 
    VO_OPPONENT_UNKNOWN = 32,
	
    VO_PLAYER_UNKNOWN  = 33,
    VO_UNKNOWN = 34, 
    VO_ILLEGAL = 35 
};


/************************************************************************/
/************************ OBJECT ****************************************/
/************************************************************************/
class Object
{
protected:
	//-* record current and history data: [0]:current data;[1]last data...
	//-- only vision message
	deque< Time >			_timeSeen; //-* the time see this object
	deque< VisionSense >	_visionSeen; //-* the vision message about the object
	deque< Vector3f	>		_posRelativeSeen; //-* the relative position of the object from vision
		

public:
	Object();
	~Object();
	
	//-* function get values
	Time 		 getTimeSeen( unsigned int i = 0 ) const { return getDequeValue( _timeSeen, i ); } 
	VisionSense  getVisionSeen( unsigned int i  = 0 ) const { return getDequeValue( _visionSeen, i ); }
	Vector3f	 getPosRelativeSeen( unsigned int i = 0 ) const { return getDequeValue( _posRelativeSeen, i ); }
	Vector3f	 getRelativePosSeen( unsigned int i = 0 ) const { return getDequeValue( _posRelativeSeen, i ); }

	Vector3f	 getPosRelativeLastSeen() const { return getPosRelativeSeen( 0 ); }
	Vector3f	 getRelativePosLastSeen() const { return getRelativePosSeen( 0 ); }

	//-* update values
	void updateLastSeen( Time timeLastSeen, VisionSense visionLastSeen );
	
	//-* get vision error var
	Vector3f getVisionError() const;
};

/*****************************************************************************/
/********************** FIXED OBJECT *****************************************/
/*****************************************************************************/
/*! Class FixedObject contains RoboCup information that is available for
    objects that cannot move (flags, goals). Different variables are added to
    the superclass Object. */
class FixedObject: public Object
{
protected:
	//-* record data
	deque< Time	>			_time; //-* time of the corresponding information
	Vector3f				_posGlobal; //-* Global position in the field,this will not be changed during the match
	deque< Vector3f	>		_posRelative; //-* relative position of the object

public:
	FixedObject();
	~FixedObject();

	//-* set and get global position
	//-- it will not be changed during a match
	void 		setGlobalPos( Vector3f posGlobal ) { _posGlobal = posGlobal; }
	Vector3f 	getGlobalPos() const { return _posGlobal; }
	
	//-* update position relative to me
	//-- posRelative = posGlobal - posMe
	void		updatePosRelative( Time time, Vector3f posMe );
	
	//-* get position relative to me
	Time		getTime( unsigned int i ) { return getDequeValue( _time, i ); }
	Vector3f	getPosRelative( unsigned int i ) { return getDequeValue( _posRelative, i ); }
	Vector3f	getPosRelative( Time time ) { return getDequeValueByTime( _time, time, _posRelative ); }

};

/*****************************************************************************/
/********************** DYNAMIC OBJECT ***************************************/
/*****************************************************************************/

/*! Class DynamicObject contains RoboCup information that is available for
    objects that can move (players, ball). Different variables are added to
    the superclass Object */
class DynamicObject: public Object
{
protected:
	//-* max speed and Acceletation...
	float		_maxSpeed; //-* max speed of this object
	float		_maxAcceletation; //-*  max Acceletation of this object

	//-* record data
	//-* position information
	deque< Time	>			_time; //-* time of the corresponding information
	deque< Vector3f	>		_posGlobal; //-* Global position in the field
	deque< Vector3f	>		_posRelative; //-* relative position of the object
	//-*  global velocity information
	deque< Vector3f >   	_globalVelocity;      //-*  Global velocity of the object
	deque< Vector3f	>		_globalAcceletation;	 //-*  global Acceletation of the object

public:
	DynamicObject();
	~DynamicObject();

	//-* set parameters
	void setMaxSpeed( float maxSpeed ) { _maxSpeed = maxSpeed; }
	void setMaxAcceletation( float maxAcceletation ) { _maxAcceletation = maxAcceletation; }

	//-* get parameters
	float getMaxSpeed() const { return _maxSpeed; }
	float getMaxAcceletation() const { return _maxAcceletation; }
	
	Time		getTime( unsigned int i = 0 ) const { return getDequeValue( _time, i ); }
		
	Vector3f	getGlobalPos( unsigned int i = 0 ) const { return getDequeValue( _posGlobal, i ); }
	//Vector3f	getGlobalPos( Time time ) { return getDequeValueByTime( _time, time, _posGlobal ); }
	
	Vector3f	getRelativePos( Step i = 0 ) const { return getDequeValue( _posRelative, i ); }
	//Vector3f	getRelativePos( Time time ) const { return getDequeValueByTime( _time, time, _posRelative ); }
	
	Vector3f	getGlobalVelocity( Step i = 0 ) const { return getDequeValue( _globalVelocity, i ); }
	Vector3f	getGlobalVelocity( Time time ) const { return getDequeValueByTime( _time, time, _globalVelocity ); }
	
	Vector3f	getGlobalAcceletation( unsigned int i = 0 ) const { return getDequeValue( _globalAcceletation, i ); }
	Vector3f	getGlobalAcceletation( Time time ) const { return getDequeValueByTime( _time, time, _globalAcceletation ); }
	
	//-* update dynamic information
	void updateDynamic( const Time &time, const Vector3f &posGlobal, const Vector3f &posMe, const Vector3f &globalVelocity, const Vector3f &globalAcceletation);

	//-* for update
	Vector3f calculateGlobalPosFromVision( const Vector3f &posMyself) const;
	Vector3f calculateGlobalVelFromVision( const Vector3f &velMyself) const;
	Vector3f calculateGlobalPosFromMemory( const Time deltaTime) const;
};

/*****************************************************************************/
/********************* PLAYER OBJECT *****************************************/
/*****************************************************************************/

/*! Class PlayerObject contains RoboCup information that is available for
    players. Different variables are added to the superclass DynamicObject   */
class PlayerObject: public DynamicObject
{
protected:
	float 	_mass; //-* mass of the players
	float 	_radius; //-* radius of the players

	bool	_isLive; //-* whether the players is live
	string 	_teamName; //-* the team name of the players
	unsigned int _num; //-*  the number of the players

	//-* the interal state of the players
	float _battery; //-* percentage of battery
	float _temperature; //-* temperature of the palyer

public:
	PlayerObject();
	~PlayerObject();

	//-* set parameters
	void setMass( float mass ) { _mass = mass; }
	void setRadius( float radius ) { _radius = radius; }
	void setTeamName( string teamName ) { _teamName = teamName; }
	void setNum( unsigned int num ) { _num = num; }
	void setBattery( float battery ) { _battery = battery; }
	void setTemperature( float temperature ) { _temperature = temperature; }
	
	//-* get parameters
	float getMass() 		const { return _mass; }
	float getRadius()		const { return _radius; }
	string getTeamName() 	const { return _teamName; }
	unsigned int getNum() 	const { return _num; }
	float getBattery() 		const { return _battery; }
	float getTemperature() 	const { return _temperature; }
	
	//-* set and get the player live
	//-- for some excpet suitation, some player dead
	bool isLive() { return _isLive; }
	void enLive() { _isLive = true; }
	void disLive() { _isLive = false; }
	
};

/*****************************************************************************/
/********************* BALL OBJECT *******************************************/
/*****************************************************************************/

/*! Class PlayerObject contains RoboCup information that is available for the
    ball. No extra variables are added to superclass DynamicObject
*/
class BallObject: public DynamicObject
{
private:
	float _mass; //-* mass of the ball
	float _radius; //-* radius of the ball

	//-- kalman configure parameters
	Vector3f _kalmanP[4];

	/** drag conf */
	float _groundDragConf;
	float _airDragConf;

public:
	BallObject();
	~BallObject();

	//-* set parameters
	void setMass( float mass );
	void setRadius( float radius ) { _radius = radius; }
	void inline setKalmanP22( const Vector3f &P22) { _kalmanP[3] = P22; }
	void setDragConf();
	
	//-* get parameters
	float getMass() const { return _mass; }
	float getRadius() const { return _radius; }
	Vector3f inline getKalmanP11() const { return _kalmanP[0]; }
	Vector3f inline getKalmanP12() const { return _kalmanP[1]; }
	Vector3f inline getKalmanP21() const { return _kalmanP[2]; }
	Vector3f inline getKalmanP22() const { return _kalmanP[3]; }

	bool isGroundBall( const Vector3f &posBall, const Vector3f &prePosBall, const Vector3f &preprePosBall,
						const Vector3f &velBall, const Vector3f &preVelBall, const Vector3f &prepreVelBall) const;
	bool isFallOnGround( const Vector3f &posBall, const Vector3f &prePosBall, const Vector3f &preprePosBall,
						const Vector3f &velBall, const Vector3f &preVelBall, const Vector3f &prepreVelBall) const;
	bool isBallStop( const Vector3f &posBall, const Vector3f &prePosBall, const Vector3f &preprePosBall,
						const Vector3f &velBall, const Vector3f &preVelBall, const Vector3f &prepreVelBall,const float minSpeed = 0.01) const;
	//bool isFallOnGround ( const Vector3f &posBall, const Vector3f &velBall) const;
	//-* simulate physics
	void predictStateAfterOneStep(	Vector3f &pos, Vector3f &prePos, Vector3f &preprePos,
										Vector3f &vel, Vector3f &preVel, Vector3f &prepreVel ) const;
	bool predictStateAfterNrSteps(	Vector3f &pos, Vector3f &prePos, Vector3f &preprePos,
										Vector3f &vel, Vector3f &preVel, Vector3f &prepreVel,
										int iStep = 1,
										int iStepMax = max_intercept_steps ) const;
	//float nnSimNextVel( const float v0 )const;
	//bool simulate( Vector3f &pos, Vector3f &vel,const int iStep, const int iStepMax =1000 ) const;
	//-* kalman filter
	void updateKalman( const Step iStep );
	void setupKalmanFilter();
};

/*****************************************************************************/
/********************* AGENT OBJECT ******************************************/
/*****************************************************************************/

/*! Class AgentObject contains RoboCup information that is available for the
    agent. New variables are declared that extend a normal PlayerObject.*/
class AgentObject: public PlayerObject
{
private:
	
	Vector3f _driveForce; //-* the drive force of the agent

	string _oppTeamName; //-*  the name of opponent team

	//-- kalman configure parameters
	Vector3f _kalmanP[4];

public:
	AgentObject();
	~AgentObject();

	//-* set parameters
	void inline setDriveForce( Vector3f driveForce ) { _driveForce = driveForce; }
	void inline setKalmanP22( const Vector3f &P22) { _kalmanP[3] = P22; }
	
	//-* get parameters
	Vector3f inline getDriveForce() const { return _driveForce; }
	Vector3f inline getKalmanP11() const { return _kalmanP[0]; }
	Vector3f inline getKalmanP12() const { return _kalmanP[1]; }
	Vector3f inline getKalmanP21() const { return _kalmanP[2]; }
	Vector3f inline getKalmanP22() const { return _kalmanP[3]; }
	
	//-* kalman filter
	void updateKalman( const Time deltaTime );
	void setupKalmanFilter();
};

#endif /* _OBJECT_H */

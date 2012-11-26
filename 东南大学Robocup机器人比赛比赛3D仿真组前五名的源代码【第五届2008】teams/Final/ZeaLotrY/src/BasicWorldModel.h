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

 
#ifndef _BASICWORLDMODEL_H
#define _BASICWORLDMODEL_H

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif


#include <string>
#include <map>
#include <vector>
#include <soccer/soccertypes.h>
#include "Object.h"


/************************************************************************/
/************************ BASIC WORLD MODEL *****************************/
/************************************************************************/
class BasicWorldModel
{
protected:
	//-*  field parameter
	float _fieldLength;
    float _fieldWidth;
    float _fieldHeight;
    float _goalWidth;
    float _goalDepth;
    float _goalHeight;
    float _borderSize;

	//-*  rule information
	float _freeKickDistance;
	float _waitBeforeKickOff;
	float _ruleGoalPauseTime;
	float _ruleKickInPauseTime;
	float _ruleHalfTime;

	//-*  fixed objects
	//--  flags and goals
	FixedObject _flag_1_l;		/*  Flag_2_l+----------+----------+Flag_2_r  */
	FixedObject _flag_1_r;		/*          |          |          |          */
	FixedObject _flag_2_l;		/*          |          |          |          */
	FixedObject _flag_2_r;		/*  Goal_2_l+-+        |        +-+Goal_2_r  */
	FixedObject _goal_1_l;		/*          | |        +        | |          */
	FixedObject _goal_1_r;		/*  Goal_1_l+-+        |        +-+Goal_1_r  */
	FixedObject _goal_2_l;		/*          |          |          |          */
	FixedObject _goal_2_r;		/*          |          |          |          */
								/*  Flag_1_l+----------+----------+Flag_1_r  */

	//-*  agent
	AgentObject _myself;
	Vector3f	_myDebugPos;

	//-*  ball
	BallObject _ball;
	
	//-* players
	vector< PlayerObject > _teammate;
	vector< PlayerObject > _opponent;

	//-*  team information
	TTeamIndex _teamIndex;
	string	   _oppTeamName;


	//-*  time and game state information
	Time _thinkTimeLast; //-* the think time from "K" message
	unsigned int _numK; //-*  the sum number of "K" message
	Time _sumThinkTime; //-*  the sum of think time from "K" message
	Time _thinkTimeCurrent; //-* the think time from "C" message
	
	set<Time> _thinkTimeSet; //-* when "T<time>" arrive,if the time is in this set, then update all the objects' information
    Time _timeLastSeen; //-*  the sense message generate time ( in 10ms )
	Time _realTime;			//-*  the current real-time ( in 10ms )
	Time _gameTime;		//-*  the time of the match( in s )
    TPlayMode _playMode;//-*  the play mode of the match
	
	/** offside line */
	float _ourOffSideLine;
	float _oppOffSideLine;
	
public:
	BasicWorldModel();
	virtual ~BasicWorldModel();
	
	/** parses a message received from the server */
	void parse(const char* msgBegin, const unsigned int msgSize);

/////////////////////// set ///////////////////////////////////
	//-*  set flags and goals' global position
	void setupFixedObjects();	

	//-* --------- setup myself info -------------------
	void setMyTeamName( string teamName );
	//-*  after beam, set the global position directly
	void setMyGlobalPosWhileBeam( Vector3f posGlobal );
	//-*  set my current drive force -- for test
	void setMyDriveForce( Vector3f driveForce ) { _myself.setDriveForce( driveForce ); }

	//-*  set ball before kick off
	void setBallBeforeKickOff();
	
	//-* ---------- set team information ----------------
	void setOppTeamName( const string &teamName );	

	
/////////////////////// get ///////////////////////////////////
	//-* get field parameters
	float getFieldLength()	const { return _fieldLength; }
	float getFieldWidth()	const { return _fieldWidth; }
	float getFieldHeight()	const { return _fieldHeight; }
	float getGoalWidth()	const { return _goalWidth; }
	float getGoalDepth()	const { return _goalDepth; }
	float getGoalHeight()	const { return _goalHeight; }
	float getBorderSize()	const { return _borderSize; }
	Vector3f getOppGoalCenter() const { return Vector3f(getFieldLength()*0.5,0,0); }
	Vector3f getOppGoalLeft() const { return Vector3f(getFieldLength()*0.5,getGoalWidth()*0.5,getGoalHeight()); }
	Vector3f getOppGoalRight() const { return Vector3f(getFieldLength()*0.5,-getGoalWidth()*0.5,getGoalHeight()); }
	Vector3f getOurGoalCenter() const { return Vector3f(-getFieldLength()*0.5,0,0); }
	Vector3f getOurGoalLeft() const { return Vector3f(-getFieldLength()*0.5,getGoalWidth()*0.5,getGoalHeight()); }
	Vector3f getOurGoalRight() const { return Vector3f(-getFieldLength()*0.5,-getGoalWidth()*0.5,getGoalHeight()); }
	float getOurBaseLine() const { return -_fieldLength*0.5; }
	float getOppBaseLine() const { return _fieldLength*0.5; }
	
	//-* get rule information -- for further use
	float getFreeKickDistance()		const { return _freeKickDistance; }
	float getWaitBeforeKickOff()	const { return _waitBeforeKickOff; }
	float getRuleGoalPauseTime()	const { return _ruleGoalPauseTime; }
	float getRuleKickInPauseTime()	const { return _ruleKickInPauseTime; }
	float getRuleHalfTime()			const { return _ruleHalfTime; }
	
	//-* get flags' information
	const FixedObject * getFlagPtr( VisionObject flag ) const;
	Vector3f getFlagGlobalPos( VisionObject flag ) const { return getFlagPtr( flag )->getGlobalPos(); }
	Vector3f getFlagRelativePosSeen( VisionObject flag ) const { return getFlagPtr( flag )->getRelativePosSeen(); }
	
	//-* get agent information
	unsigned int getMyNum() 		const { return _myself.getNum(); }
	float 		 getMyMass() 		const { return _myself.getMass(); }
	float 		 getMyRadius() 		const { return _myself.getRadius(); }
	string 		 getMyTeamName()	const { return _myself.getTeamName(); }
	float 		 getMyBattery()		const { return _myself.getBattery(); }
	float 		 getMyTemperature()	const { return _myself.getTemperature(); }
	Vector3f	 getMyDriveForce()  const { return _myself.getDriveForce(); }
	Vector3f 	 getMyGlobalPos( Step i = 0 )	const { return _myself.getGlobalPos(i); }
	Vector3f 	 getMyGlobalVel( Step i = 0 )	const { return _myself.getGlobalVelocity(i); }
	//-* for debug
	Vector3f _debugPos;
	Vector3f getDebugPos() const { return _debugPos; }
	
	//-* get ball information
	float getBallMass() const { return _ball.getMass(); }
	float getBallRadius() const { return _ball.getRadius(); }
	Vector3f getBallGlobalPos( Step i=0) const { return _ball.getGlobalPos(i); }
	Vector3f getBallGlobalVel( Step i=0) const { return _ball.getGlobalVelocity(i); }
	Vector3f getBallRelativePos( Step i=0) const { return _ball.getRelativePos(i); }
	Vector3f getBallRelativePosSeen(Step i=0) const { return _ball.getRelativePosSeen(i); }
	
	//-* get other players' information
	//-* get Vector3f in a vector< PlayerObject > 
	Vector3f getVector3fInVector( Vector3fType vt, vector< PlayerObject > team, unsigned int num ) const;
	//-* position information
	Vector3f getPlayerGlobalPosInTeam( vector<PlayerObject> team, unsigned int num  ) const;
	Vector3f getTeammateGlobalPos( unsigned int num ) const { return getPlayerGlobalPosInTeam( _teammate, num ); }
	Vector3f getOpponentGlobalPos( unsigned int num ) const { return getPlayerGlobalPosInTeam( _opponent, num ); }
	Vector3f getPlayerGlobalPos( bool isTeammate, unsigned int num ) const;
	/** relative position */
	Vector3f getPlayerRelativePosInTeam( vector<PlayerObject> team, Num num ) const;
	Vector3f getTeammateRelativePos( Num num ) const { return getPlayerRelativePosInTeam(_teammate,num); }
	Vector3f getOpponentRelativePos( Num num ) const { return getPlayerRelativePosInTeam(_opponent, num); }
	Vector3f getPlayerRelativePos( bool isTeammate, unsigned int num ) const;
	/** relative position in sense */
	Vector3f getPlayerRelativePosSeenInTeam( vector<PlayerObject> team, Num num ) const;
	Vector3f getTeammateRelativePosSeen( Num num ) const { return getPlayerRelativePosSeenInTeam(_teammate,num); }
	Vector3f getOpponentRelativePosSeen( Num num ) const { return getPlayerRelativePosSeenInTeam(_opponent, num); }
	Vector3f getPlayerRelativePosSeen( bool isTeammate, Num num ) const;
	
	//-* velocity
	Vector3f getPlayerGlobalVelInTeam( vector<PlayerObject> team, unsigned int num  ) const;
	Vector3f getTeammateGlobalVel( unsigned int num ) const { return getPlayerGlobalVelInTeam( _teammate, num ); }
	Vector3f getOpponentGlobalVel( unsigned int num ) const { return getPlayerGlobalVelInTeam( _opponent, num ); }
	Vector3f getPlayerGlobalVel( bool isTeammate, unsigned int num ) const;
	
	//-* get game state information
	Time getTimeLastSeen() 	{ return _timeLastSeen; }
	Time getRealTime() const { return _realTime; }
	Time getGameTime() 		{ return _gameTime; }
	TPlayMode getPlayMode() const { return _playMode; }
	TTeamIndex getTeamIndex() const { return _teamIndex; }
	
	//-* get think time information
	Time getCurrentThinkTime() { return _thinkTimeCurrent; }
	Time getAverageThinkTime() { return _sumThinkTime / _numK; }
	
	//-* get vision sense
	//-- returns the polar coordinates of the requested object
    VisionSense getVisionSense( VisionObject vo );
	
	//** get offside line */
	float getOurOffSideLine() const { return _ourOffSideLine; }
	float getOppOffSideLine() const { return _oppOffSideLine; }

	//-* update the BasicWorldModel
	//-- 1.parse 2.updateAll 3.predict
	//void update( const std::string& message);
	void update();

	//-* set time when need to think
	void clearThinkTimeSet() { _thinkTimeSet.clear(); }
	void pushThinkTime( const Time& time) { _thinkTimeSet.insert( time);}
	bool isThinkTime( const Time& time) const;
	bool isThinkTimeNow() const { return isThinkTime( _realTime); }
	set<Time> getThinkTime() const { return _thinkTimeSet; }
	
	/*----------------------------------*/
	bool updateObjectVisionPosition( const std::string& obj, const Polar& pol);
	// AgentState
	void setMyBattery( float battery ){ _myself.setBattery(battery); }
	void setMyTemp( float temp ){ _myself.setTemperature(temp); }
	// GameState
	void setGameTime( Time time ){ _gameTime = time; }
	bool setPlayMode( const string& playMode );
	void setFieldLength( float len ){ _fieldLength = len; cout<<"FieldLength = "<<len<<'\n'; }
	void setFieldWidth( float wid ){ _fieldWidth = wid; cout<<"FieldWidth = "<<wid<<'\n';}
	void setFieldHeight( float h ){ _fieldHeight = h; cout<<"FieldHeight = "<<h<<'\n'; }
	void setGoalWidth( float wid ){ _goalWidth = wid; cout<<"GoalWidth = "<<wid<<'\n'; }
	void setGoalHeight( float h ){ _goalHeight = h; cout<<"GoalHeight = "<<h<<'\n'; }
	void setGoalDepth( float d ){ _goalDepth = d; cout<<"GoalDepth = "<<d<<'\n'; }
	void setBorderSize( float b ){ _borderSize = b; cout<<"BorderSize = "<<b<<'\n'; }
	void setMyNum( Num num ){ _myself.setNum(num); cout<<"I am Num "<<num<<'\n'; }
	void setMyRadius( float r ){ _myself.setRadius(r); cout<<"AgentRadius = "<<r<<'\n'; }
	void setMyMass( float m ){ _myself.setMass(m); cout<<"AgentMass = "<<m<<'\n'; }
	void setMyMaxSpeed( float v ){ _myself.setMaxSpeed(v); cout<<"AgentMaxSpeed = "<<v<<'\n'; }
	void setBallRadius( float r ){ _ball.setRadius(r); cout<<"BallRadius = "<<r<<'\n'; }
	void setBallMass( float m ){ _ball.setMass(m); cout<<"BallMass = "<<m<<'\n'; GL_REGISTER;}
	void setTeamIndex( const string& team );
	void setSenseTime1( Time t1 ){ _timeLastSeen=t1; }
	void setSenseTime2( Time t2 ){ _realTime = t2; }
	void setSenseTime( Time t1, Time t2 ){ _timeLastSeen=t1; _realTime=t2; }
protected:

	/////////////////////// maps //////////////////////////

	//-*  mapping from gamestate string to TPlayMode
    TPlayModeMap _playModeMap;

	//-*  mapping from vision object to VisionSense
    typedef std::map<VisionObject, VisionSense> TVisionMap;
    TVisionMap _visionMap;

	//-*  mapping from <ObjectName>+<ID> to VisionObject
    typedef std::map<std::string, VisionObject> TVisionObjectMap;
    TVisionObjectMap _visionObjectMap;

	//-*  different parsers
	void parseMsgC();
	void parseMsgK();
	void parseMsgT();
	void parseMsgS();
	void parseGameState();
	void parseTeamIndex(const string &team);
	void parsePlayMode(const string &team);
	void parseVision();
	void parseAgentState();
		

	//-*  setup maps
	void setupVisionObjectMap();
	
	//////////////////// localization ////////////////////////
	void	 localization();
	Vector3f localizationWithAllFixedObjects() const;
	Vector3f localizeWithOneFlag( VisionObject flag ) const;
	
	//-* many kinds of filters
	//-* low frequency signal filter
	template < class Type >
	Type lowFreqSignalFilter( const Type &yv, const Type &ye_1 ) const { return ( yv + ye_1*0.5 )/1.5; }
	

	//////////////////// update //////////////////////////////
	//-* update the objects information
	void updateAll(); //-* update all the objects
	void newupdateBall();
	void updateBall(); //-* update the ball information
	void calculateBallState( Vector3f &posBall, Vector3f &prePosBall, Vector3f &preprePosBall,
							Vector3f &velBall, Vector3f &preVelBall, Vector3f &prepreVelBall,
							const Step iStep);
	
	/** calculate offside line */
	float calculateOffsideLine( bool isOur );
	
	Vector3f getBallPositionUnPlayOn();
	void updateAgent(); //-* update myself information
	void updatePlayers(); //-* update other players
	void updateMyselfInTeam(); //-* update my num's players
	void updateTeam( vector<PlayerObject> &team ,VisionObject num_1 );
	void updateFixedObjects(); //-* update flags and goals
	void updateOffSideLine(); //-* update the two offside lines
	
	/////////////////// predict //////////////////////////////
	//-* 
	virtual void predict() = 0;
	virtual bool predictPlayerStateAfterNrSteps(	Vector3f &pos,
										Vector3f &vel,
										int iStep = 1,
										int iStepMax = max_intercept_steps ) const = 0;
};

#endif /* _BASICWORLDMODEL_H */

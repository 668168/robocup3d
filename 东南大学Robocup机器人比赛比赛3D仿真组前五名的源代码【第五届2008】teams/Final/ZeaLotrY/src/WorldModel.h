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

 
#ifndef _WORLDMODEL_H
#define _WORLDMODEL_H

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#include "BasicWorldModel.h"

/*! enum all state to the ball
*/
enum State2Ball
{
	S2B_ILLEGAL			=	0, //-* illegal value
	
	S2B_FASTEST_TYPE	=	1, //-* the fastest of the same PlayerType with me of my team
	S2B_FASTEST_TEAM	=	2, //-* the fastest of my teammates( 11 players)
	S2B_FASTEST_ALL		= 	3  //-* the fastest of all 22 players
};

class WorldModel: public BasicWorldModel,public Singleton<WorldModel>
{
private:
/////////////// predict data ////////////////////
	Vector3f _firstPoint;//-* for isFastestOur, only for test
	Vector3f _posIntercept;
	Vector3f _prePosIntercept;

	float	 _myFreedom;
	float	 _myFreedomChange;
	int		 _freeState;

	State2Ball _myState2Ball;
	
	AngDeg	 _kickHorizontalAng;

	Num		 _closest2BallOppNum;

	set<Num> _sameTypeTeammateNum;
	set<Num> _diffTypeTeammateNum;

	//-* position in real time (predict)
	deque< Time	>			_timePredict; //-* time of the corresponding information
	deque< Vector3f	>		_posGlobalPredict; //-* Global position in the field
	//-*  global velocity in real time (predict)
	deque< Vector3f >   	_globalVelocityPredict;      //-*  Global velocity of the object
	deque< Vector3f	>		_globalAcceletationPredict;	 //-*  global Acceletation of the object

	
protected:
	virtual void predict();

public:
	///////////////// predict //////////////////////////////////
	//-* predict ball position and veloctiy
	//-- new: use 3 history record data
	bool		predictBallStateAfterNrSteps(	Vector3f &pos, Vector3f &prePos, Vector3f &preprePos,
										Vector3f &vel, Vector3f &preVel, Vector3f &prepreVel,
										int iStep = 1,
										int iStepMax = max_intercept_steps ) const;
	
	int			predictFirstPoint( Vector3f &pos, Vector3f &prePos, Vector3f &preprePos,
										Vector3f &vel, Vector3f &preVel, Vector3f &prepreVel,
										int iStepMax = max_intercept_steps ) const;

	
	Vector3f	predictInterceptPos(Step &iStepPre,
										Vector3f posPlayer,
										Step iStepMax = max_intercept_steps ) const;
	
	Vector3f	predictInterceptPos(Time &time,
										const Vector3f &posPlayer,
										const Vector3f &velPlayer,
										Time timeMax = max_intercept_time ) const;
	
	virtual bool predictPlayerStateAfterNrSteps(	Vector3f &pos,
										Vector3f &vel,
										int iStep = 1,
										int iStepMax = max_intercept_steps ) const;
	
	void		 predictPlayerStateAfterOneStep( Vector3f &pos, Vector3f &vel, const Vector3f &drivePower) const;
	
	Step		whenToKick( Vector3f PlayerPos, Vector3f PlayerVel,
							Vector3f ballPos, Vector3f ballVel,
							Vector3f ballPos1, Vector3f ballVel1,
							Vector3f ballPos2, Vector3f ballVel2,
							const Vector3f &drivePower,
							const Vector3f &goal, AngDeg &minErrAng) const;
	
private:
	void		predictRealTime();
	State2Ball	predictOurFastest();

public:
	WorldModel();
	///////////////// Is ///////////////////////////////////////
	bool isGroundBall( const Vector3f &posBall, const Vector3f &prePosBall, const Vector3f &preprePosBall,
						const Vector3f &velBall, const Vector3f &preVelBall, const Vector3f &prepreVelBall) const;
	bool isFallOnGround( const Vector3f &posBall, const Vector3f &prePosBall, const Vector3f &preprePosBall,
						const Vector3f &velBall, const Vector3f &preVelBall, const Vector3f &prepreVelBall) const;
	bool isBallStop( const float minSpeed = 0.01 ) const;

	bool isKickable( Vector3f posPlayer, Vector3f posBall);
	
	bool isKickable();
	
	bool isFastestOur() const { return _myState2Ball >= S2B_FASTEST_TEAM; }
	bool isFastestMyType() const { return _myState2Ball >= S2B_FASTEST_TYPE; }
	
	static bool isCollide( const Vector3f &pos1, const Vector3f &pos2, const float minDist);

	bool isInDefencePos( const Num teammateNum ) const;
	
	/** is offside */
	bool isOffSide( float posX, bool isOur ) const;
	bool isOffSide( const Vector3f &pos, bool isOur ) const { return isOffSide( pos.x(), isOur); }
	bool isOffSide( Num playerNum, bool isOur) const { return isOffSide(getPlayerGlobalPos(isOur,playerNum),isOur); }
	bool isOffSide() const { return isOffSide(getMyGlobalPos(),true); }
	//bool isOffSide( VisionObject playerName );
	
	/** */
	//bool isSpaceAhead(const float length=17,const float width=10)const;
	bool isSpaceAhead(const Vector3f &goal)const;
	bool isSpaceAhead() const { return isSpaceAhead(getOppGoalCenter()); }
	
///////////////// GET ///////////////////////////////////////
	Vector3f getMyRealPos() { return getDequeValue( _posGlobalPredict, 0 ); }
	Vector3f getInterceptPos( const Vector3f &goal) const;
	Vector3f getInterceptBallPos() const { return _posIntercept; }
	
	Num		getClosestOppNum2Pos(const Vector3f &pos) const;
	Num		getClosestOppNum2Pos(const Vector3f &pos, float &minDist) const;
	Num 	getClosestOurNum2Pos(const Vector3f &pos, float &minDist) const;
	
	float	getMyFreedom() const { return _myFreedom; }
	int		getMyFreeState() const { return _freeState; }
	float	getMyFreedomChange() const { return _myFreedomChange; }
	Num		getClosestOppNum2Ball() const { return _closest2BallOppNum; }
	AngDeg	getMyKickHorizontalAng() const { return _kickHorizontalAng; }
////////////////////////Calculate//////////////////////////////
	float calOurFreedom( Num num, int &state) const;
	AngDeg calKickHorizontalAng(const Vector3f &posPlayer) const;
	float calOurFreedom( Num num ) const;
//////////////////////// SET ///////////////////////////////////
	void	setSameTypeTeammateNum();
	
	Vector3f setVector3fInField(const Vector3f &pos) const;
//////////////////////// LOG ///////////////////////////////////
	void	logWorldModel();
};

#define WM WorldModel::GetSingletonPtr()

#endif /* _WORLDMODEL_H */

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

 
 #include "WorldModel.h"
 #include "Skill.h"
 #include "Formation.h"

WorldModel::WorldModel()
{
	/** offside line */
	_ourOffSideLine = max_field_length*0.5;
	_oppOffSideLine = -_ourOffSideLine;
}

bool WorldModel::predictBallStateAfterNrSteps(	Vector3f &pos, Vector3f &prePos, Vector3f &preprePos,
										Vector3f &vel, Vector3f &preVel, Vector3f &prepreVel,
										int iStep,
										int iStepMax ) const
{
	return _ball.predictStateAfterNrSteps( pos, prePos, preprePos,
											 vel, preVel, prepreVel,
											iStep,
											iStepMax);
}

bool WorldModel::isGroundBall( const Vector3f &posBall, const Vector3f &prePosBall, const Vector3f &preprePosBall,
						const Vector3f &velBall, const Vector3f &preVelBall, const Vector3f &prepreVelBall) const
{
	/*vector<float> nnInput;
	nnInput.resize(6);
	nnInput.push_back( posBall.z());
	nnInput.push_back( prePosBall.z());
	nnInput.push_back( preprePosBall.z());
	nnInput.push_back( velBall.z());
	nnInput.push_back( preVelBall.z());
	nnInput.push_back( prepreVelBall.z());
	return _nnIsGroundBall.sim( nnInput.begin() );
	*/
	return _ball.isGroundBall( posBall, prePosBall, preprePosBall,
								velBall, preVelBall, prepreVelBall );
}

bool WorldModel::isBallStop( const float minSpeed ) const
{
	return _ball.isBallStop( getBallGlobalPos(), getBallGlobalPos(1), getBallGlobalPos(2),
								getBallGlobalVel(), getBallGlobalVel(Step(1)), getBallGlobalVel(Step(2)) ,minSpeed);
}

/*!判断是不是地滚球
	\param 球的当前位置
	\param 球的但前速度
	\return 是不是地滚球
*/
bool WorldModel::isFallOnGround( const Vector3f &posBall, const Vector3f &prePosBall, const Vector3f &preprePosBall,
						const Vector3f &velBall, const Vector3f &preVelBall, const Vector3f &prepreVelBall) const
{
	return _ball.isFallOnGround( posBall, prePosBall, preprePosBall,
								velBall, preVelBall, prepreVelBall );
}

/*!判断球是不是刚好落地反弹
\param 球的当前位置
\param 球的但前速度
\return 是不是落地反弹
*/
bool WorldModel::isKickable( Vector3f posPlayer, Vector3f posBall )
{
	return getBallRelativePos().Length() < 3.0;
}

bool WorldModel::isKickable()
{
	return isKickable( getMyGlobalPos(), getBallGlobalPos() );
}

State2Ball WorldModel::predictOurFastest()
{
	if ( getBallRelativePos().Length() > max_kick_distance )
		return S2B_ILLEGAL;
	LOG( 40,"dist2ball: %f",getBallRelativePos().Length() );
	LOG( 40,"realtive ball pos: %f, %f, %f ",getBallRelativePos().x(),getBallRelativePos().y(),getBallRelativePos().z());
	//-* algorithm 1
	//-- the fastest one is the one who is clostest to the first point
	//-- it suits air ball, but not good enough for the ground ball
	/*Vector3f posFight = _firstPoint;
	float distMe = ( getMyGlobalPos() - posFight ).Length();
	for ( int i=1; i<=11; i++ )
	{
		float distTeammate = ( getTeammateGlobalPos(i) - posFight ).Length();
		if ( distTeammate < distMe - 1.0 )
			return false;
	}
	return true;
	*/
	
	//-* algorithm 2
	//-- predict all Player's need time when he intercept the ball
	//-- its performance relay on the predictInterceptPos function
	/*Step iStepIntercept = 0;
	_prePosIntercept = _posIntercept;
	_posIntercept = predictInterceptPos( iStepIntercept, getMyGlobalPos() );
	if ( iStepIntercept >= max_intercept_steps ) return false;
	LOG( 12,"my intercept step: %d",iStepIntercept);
	//LOG( 12,"my intercept position: %f, %f, %f",_posIntercept.x(),_posIntercept.y(),_posIntercept.z());
	Vector3f dPosIntercept = _posIntercept - _prePosIntercept; 
	LOG( 12,"intercept delta: %f, %f, %f",dPosIntercept.x(),dPosIntercept.y(),dPosIntercept.z());
	for ( unsigned int i=1; i<=11; i++ )
	{
		if ( i == getMyNum() ) continue;
		Step teammateStep = 0;
		predictInterceptPos( teammateStep, getTeammateGlobalPos(i), iStepIntercept+10 );
		LOG( 40,"teammate[%d] step: %d",i,teammateStep);
		if ( teammateStep < iStepIntercept - 3 )
			return false;
	}
	return true;
	*/
	
	//-* algorithm 3
	//-- 2005-10-27
	//-- predict all Player's need *time*(in seconds) when he intercept the ball
	//-- its performance relay on the predictInterceptPos function
	//-- but it ne
	/*Time myTime = 0;
	_posIntercept = predictInterceptPos( myTime, getMyGlobalPos(), getMyGlobalVel() );
	if ( myTime < 0.5 )
		return S2B_FASTEST_TEAM;
	if ( myTime >= max_intercept_time )
		return S2B_ILLEGAL;
	for ( unsigned int i=1; i<=teammates_num; i++ )
	{
		if ( i == getMyNum() ) continue;
		Time teammateTime = 0;
		predictInterceptPos( teammateTime, getTeammateGlobalPos(i), getTeammateGlobalVel(i),myTime+2 );
		if ( teammateTime < myTime - 3*sim_step_time )
			return S2B_ILLEGAL;
	}
	return S2B_FASTEST_TEAM;
	*/
	//-* algorithm 4
	//-- 2005-11-22
	//-- base on algorithm 3
	//-- partition the same type and different type
	Time myTime = 0;
	_posIntercept = predictInterceptPos( myTime, getMyGlobalPos(), getMyGlobalVel() );
	//_posIntercept = (_posIntercept + predictInterceptPos( myTime, getMyGlobalPos(), getMyGlobalVel() ))*0.5;
	LOG( 40,"_posIntercept=( %f, %f, %f)",_posIntercept.x(),_posIntercept.y(),_posIntercept.z());
	if ( myTime < 0.5 )
		return S2B_FASTEST_TEAM;
	if ( myTime >= max_intercept_time )
		return S2B_ILLEGAL;
	set<Num>::iterator iter;
	Time teammateTime;
	for ( iter=_sameTypeTeammateNum.begin(); iter!=_sameTypeTeammateNum.end(); iter++ )
	{
		teammateTime = 0;
		predictInterceptPos( teammateTime, getTeammateGlobalPos(*iter), getTeammateGlobalVel(*iter),myTime+2 );
		if ( teammateTime < myTime - 3*sim_step_time )
			return S2B_ILLEGAL;
	}
	for ( iter=_diffTypeTeammateNum.begin(); iter!=_diffTypeTeammateNum.end(); iter++ )
	{
		teammateTime = 0;
		predictInterceptPos( teammateTime, getTeammateGlobalPos(*iter), getTeammateGlobalVel(*iter),myTime+2 );
		if ( teammateTime < myTime - 3*sim_step_time )
			return S2B_FASTEST_TYPE;
	}
	return S2B_FASTEST_TEAM;
}

Vector3f WorldModel::getInterceptPos( const Vector3f &goal) const
{
	Vector3f pos;
	Vector3f goalDriveLine( goal - _posIntercept);
    goalDriveLine.Normalize();
	pos[0] = _posIntercept[0] - goalDriveLine[0]*kick_pos_dist;
	pos[1] = _posIntercept[1] - goalDriveLine[1]*kick_pos_dist;
	pos[2] = _myself.getRadius();
	
	return pos;
}

Vector3f WorldModel::predictInterceptPos(Step &iStepPre,
										Vector3f posPlayer,
										Step iStepMax ) const
{
	float mySpeed = 1.0;
	//float mySpeed = real_agent_max_speed - 0.3;
	Vector3f velBall = getBallGlobalVel();
	//if ( velBall[0] > 0 )
	//	mySpeed = real_agent_max_speed + 0.3;
	//mySpeed*=0.5;//tmp test 2005-10-12

	Vector3f posBall = getBallGlobalPos();
	if ( (posBall - posPlayer).Length() > max_kick_distance )
	{
		iStepPre = iStepMax+1;
		return vector3f_illegal;
	}
	Vector3f prePosBall = getBallGlobalPos(1);
	Vector3f preprePosBall = getBallGlobalPos(2);
	Vector3f preVelBall = getBallGlobalVel(1);
	Vector3f prepreVelBall = getBallGlobalVel(2);
	
	
	Vector3f posIntercept;

	//default(默认截球位置，即球当前位置)
	posIntercept = posBall;

	float speedBall = getBallGlobalVel().Length();
	float dist = sqrt((posBall[0] - posPlayer[0])*(posBall[0] - posPlayer[0])+(posBall[1] - posPlayer[1])*(posBall[1] - posPlayer[1]));
	float runRadious = 0;
	//球停止了，所以不用计算
	//2005-10-04-test
	//if ( speedBall < 0.1 && isGroundBall( posBall,velBall )	)	
	//if ( _ball.isBallStop( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall) )
	//if ( speedBall < 0.2 && isGroundBall( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall)	)
	if ( speedBall < 0.01 && isGroundBall( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall)	)
	{
		iStepPre = Second2Step(dist /  mySpeed);
		return posIntercept;
	}
	//地滚球
	else if ( isGroundBall(posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall) )//ground intercept!
	{
groundloop:		while( dist > runRadious )
		{
			iStepPre++;
			predictBallStateAfterNrSteps( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall );
			dist = sqrt((posBall[0] - posPlayer[0])*(posBall[0] - posPlayer[0])+(posBall[1] - posPlayer[1])*(posBall[1] - posPlayer[1]));
			runRadious = mySpeed*sim_step_time*iStepPre;
			if ( iStepPre > iStepMax ) break;
		}
	}

	else//空中球
	{
		int iStepFly = 0;
		while( dist > runRadious )
		{
			if ( isGroundBall( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall ) ) 
				goto groundloop;//落地之后成为地滚球
			
			predictBallStateAfterNrSteps( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall );
			iStepFly = predictFirstPoint( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall );
			iStepPre += (iStepFly + 1);
			dist = sqrt((posBall[0] - posPlayer[0])*(posBall[0] - posPlayer[0])+(posBall[1] - posPlayer[1])*(posBall[1] - posPlayer[1]));
			runRadious = mySpeed*sim_step_time*iStepPre;
			
			if ( iStepPre > iStepMax ) break;
		}
	}
	
	//predictBallStateAfterNrSteps(posBall,velBall,40);
	posIntercept = posBall;
	return posIntercept;
}

Vector3f WorldModel::predictInterceptPos(Time &time,
										const Vector3f &posPlayer,
										const Vector3f &velPlayer,
										Time timeMax ) const
{
	Vector3f posBall = getBallGlobalPos();
	if ( (posBall - posPlayer).Length() > max_kick_distance )
	{//-* too far away, not consider
		time = timeMax+1;
		return vector3f_illegal;
	}
	const Step predicateSteps = step_num_per_cycle;
	Vector3f prePosBall = getBallGlobalPos(1);
	Vector3f preprePosBall = getBallGlobalPos(2);
	Vector3f velBall = getBallGlobalVel();
	Vector3f preVelBall = getBallGlobalVel(1);
	Vector3f prepreVelBall = getBallGlobalVel(2);
	Time ballTime = 0;
	Skill::driveTo(posPlayer,velPlayer,posBall,Vector3f(0,0,0),time);
	bool isBallOnGround = false;
	
	//-- new add by XuYuan @2005-11-11
	//-- close intercept, if I near the ball, and the ball's speed is slow
	//-- directly intercept it.
	//-- *TODO*
	//-- the closeInterceptSpeed and closeInterceptDist should depend on the situation and opponent model
	/*const float close_intercept_speed = 0.5;
	const float close_intercept_dist = 1.0;
	const float minDist = getMyRadius() + getBallRadius();
	const Step close_intercept_Step = 3;
	if ( _ball.isBallStop( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall,close_intercept_speed )
		&& (posBall-posPlayer).Length() < close_intercept_dist )
	{
		//Vector3f PlayerPos = posPlayer;
		//Vector3f PlayerVel = velPlayer;	
		for ( Step i=0; i< close_intercept_Step; i++ )
		{
			predictBallStateAfterNrSteps( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall,predicateSteps );
			//predictPlayerStateAfterOneStep(PlayerPos,PlayerVel,getMyDriveForce());
			if ( isCollide(posPlayer,posBall,minDist) )
			{
				posBall = prePosBall;
				break;
			}
		}	
		return posBall;
	}*/
	//float speedBall = velBall.Length();
	while ( time > ballTime && ballTime < timeMax )
	{
		//-- ball is stopped
		/*if (  (speedBall < 0.5 && isGroundBall( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall) )
			|| _ball.isBallStop( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall )	)
		*/
		if ( _ball.isBallStop( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall )	)
		{
			return posBall;
		}
		//-- ball is on the ground
		else if ( isBallOnGround
			|| isGroundBall(posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall) )//ground intercept!
		{
			isBallOnGround = true;
			predictBallStateAfterNrSteps( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall,predicateSteps );
			Skill::driveTo(posPlayer,velPlayer,posBall,Vector3f(0,0,0),time);
			ballTime += Step2Second(predicateSteps);
		}
		//-- ball is on the air
		else
		{
			Step iStepFly = predictFirstPoint( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall );
			predictBallStateAfterNrSteps( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall,predicateSteps );
			Skill::driveTo(posPlayer,velPlayer,posBall,Vector3f(0,0,0),time);
			ballTime += Step2Second(iStepFly);
			ballTime += Step2Second(predicateSteps);
		}
		
	}

	return posBall;
}

int WorldModel::predictFirstPoint( Vector3f &posBall, Vector3f &prePosBall, Vector3f &preprePosBall,
										Vector3f &velBall, Vector3f &preVelBall, Vector3f &prepreVelBall,
										int iStepMax ) const
{
	int iFlySteps = 0;
	while ( ! ( isFallOnGround( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall )  
				|| isGroundBall( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall ) ) )
	{
		iFlySteps++;
		predictBallStateAfterNrSteps( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall );
		if ( iFlySteps > iStepMax ) break;
	}
	return iFlySteps;
}

bool WorldModel::predictPlayerStateAfterNrSteps(	Vector3f &pos,
										Vector3f &vel,
										int iStep,
										int iStepMax ) const
{
	Vector3f power = _myself.getDriveForce();
	/*Vector3f a = (power*0.4848 - vel*30)/14.43;
	for ( int i=0;i<iStep;i++)
	{
		pos = pos + vel*sim_step_time;
		//-* new adapt @2005-11-08-by-XuYuan
		//-* S = S0 + V0*t + 0.5*a*t^2
		//pos = pos + vel*sim_step_time + a*pow2(sim_step_time)*0.5; 
		pos[2] = _myself.getRadius();
		a = (power*0.4848 - vel*30)/14.43;
		vel += a*sim_step_time;
		vel[2] = 0;
		if ( i > iStepMax ) return false;
	}*/
	for ( int i=0; i<iStep;i++)
	{
		predictPlayerStateAfterOneStep(pos,vel,power);
		if ( i > iStepMax ) return false;
	}
	return true;
}

void WorldModel::predict()
{
	//-* 1.predict my global position and velocity in real time
	predictRealTime();
	
	//-* 2.predict first point;
	Vector3f posBall = getBallGlobalPos();
	Vector3f prePosBall = getBallGlobalPos(1);
	Vector3f preprePosBall = getBallGlobalPos(2);
	Vector3f velBall = getBallGlobalVel();
	Vector3f preVelBall = getBallGlobalVel(Step(1));
	Vector3f prepreVelBall = getBallGlobalVel(Step(2));
	predictFirstPoint( posBall,prePosBall,preprePosBall,velBall,preVelBall,prepreVelBall );
	_firstPoint = posBall;
	
	
	_myState2Ball = predictOurFastest();
	
	_closest2BallOppNum = getClosestOppNum2Pos(getBallGlobalPos());
	
	float thisFreedom = calOurFreedom(getMyNum(),_freeState);
	_myFreedomChange = thisFreedom - _myFreedom;
	_myFreedom = thisFreedom;
	
	LOG( 20,"freedom = %f",_myFreedom);
	
	_kickHorizontalAng = calKickHorizontalAng(getMyGlobalPos());
	
	//-* 3.sort my team to first point
}

void WorldModel::predictRealTime()
{
	if ( _realTime <= _myself.getTime() )//-* no need to predict
		return;
	
	Vector3f posMe = getMyGlobalPos();
	Vector3f velMe = getMyGlobalVel();
	//-* clear all the old information
	_timePredict.clear();
	_posGlobalPredict.clear();
	_globalVelocityPredict.clear();
	//-* predict
	for ( Time time=_myself.getTime(); time< _realTime; time++ )
	{
		predictPlayerStateAfterNrSteps( posMe, velMe, 1);
		//-* update data
		_timePredict.push_front( time );
		_posGlobalPredict.push_front( posMe );
		_globalVelocityPredict.push_front( velMe );
	}
}

/*! predicate in the next step(0.10s), the palyer's position and velocity
	\param Player's position and velocity just now
	\return player's position and velocity in the next step
	*TODO*
	check if collide other object in the next step
*/
void WorldModel::predictPlayerStateAfterOneStep( Vector3f &pos, Vector3f &vel, const Vector3f &drivePower) const
{
	//-* a = ( F - u*v )/m
	Vector3f a = (drivePower*0.4848 - vel*30)/14.43;
	a.z() = 0;
	//-* S = S0 + V0*t + 0.5*a*t^2
	//pos = pos + vel*sim_step_time + a*pow2(sim_step_time)*0.5;
	pos = pos + vel*sim_step_time;
	pos.z() = _myself.getRadius();
	//-* V = V0 + a*t
	vel += a*sim_step_time;
	vel.z() = 0;
}

/*! precidate the step when the kick error is the samellest
	\param Player's position and velocity
	\param ball's position and velocity
	\param the goal's position
	\param drive power at this time
	\param the max allowed error angle, and it will return the best erro angle
	\return the best kick time(in Step), or 100 means can not kick
 */
Step WorldModel::whenToKick( Vector3f PlayerPos, Vector3f PlayerVel,
							Vector3f ballPos, Vector3f ballVel,
							Vector3f ballPos1, Vector3f ballVel1,
							Vector3f ballPos2, Vector3f ballVel2,
							const Vector3f &drivePower,
							const Vector3f &goal, AngDeg &minErrAng) const
{
	Step minErrStep = 100;
	AngDeg errAng;
	float minDist = getMyRadius()+getBallRadius();
	
	for ( Step i=0; i<step_num_per_cycle; i++ )
	{
		errAng = abs( getClipAng( ballPos-PlayerPos, goal-ballPos ));
		if ( errAng < minErrAng )
		{
			minErrAng = errAng;
			minErrStep = i;
		}
		//-* predicate next step
		predictPlayerStateAfterOneStep(PlayerPos,PlayerVel, drivePower);
		predictBallStateAfterNrSteps(ballPos,ballPos1,ballPos2,ballVel,ballVel1,ballVel2);
		//-* because we cann't predicate the state after colliding
		//-* so break predicate
		if ( isCollide(PlayerPos,ballPos,minDist) )
			break;
	}
	
	return minErrStep;
}

/*! if two objects collide
	\param the two odjects' position
	\param the min possible distance of the two objects
	\return if two objects collide
*/
bool WorldModel::isCollide( const Vector3f &pos1, const Vector3f &pos2, const float minDist)
{
	return (pos1-pos2).Length() < minDist;
}

/*! get which opponent is closest to the position
	\param position
	\return the closest opponent's number
*/
Num WorldModel::getClosestOppNum2Pos(const Vector3f &pos) const
{
	float minDist;
	return getClosestOppNum2Pos(pos,minDist);
}

/*! get which opponent is closest to the position
	\param position
	\param[out] the min distance
	\return the closest opponent's number
*/
Num WorldModel::getClosestOppNum2Pos(const Vector3f &pos,float &minDist) const
{
	Num minNum=1;
	minDist=(getOpponentGlobalPos(minNum)-pos).Length();
	float tmp;
	for( Num num=2; num<=opponents_num; num++)
	{
		tmp = (getOpponentGlobalPos(num)-pos).Length();
		if ( tmp < minDist )
		{
			minDist = tmp;
			minNum = num;
		}
	}

	return minNum;	
}

/*! get which teammate is closest to the position
	\param position
	\param[out] the min distance
	\return the closest teammate's number
*/
Num WorldModel::getClosestOurNum2Pos(const Vector3f &pos,float &minDist) const
{
	Num minNum=1;
	minDist=(getTeammateGlobalPos(minNum)-pos).Length();
	float tmp;
	for( Num num=2; num<=teammates_num; num++)
	{
		tmp = (getTeammateGlobalPos(num)-pos).Length();
		if ( tmp < minDist )
		{
			minDist = tmp;
			minNum = num;
		}
	}

	return minNum;	
}

/*! this function return the agent's freedom
	that means is enough time to do some actions
	we should call real time actions
	enum 6 state: ( M: myself; B: ball; O: opponent)
	--------------------attackDir----------------->
	1:(the worst) B--<--O--<--M
	2:            B--<--M--<--O
	3:			  O-->--B--<--M
	4:			  M-->--B--<--O
	5:			  M-->--O-->--B
	6:(the best)  O-->--M-->--B
	*TODO* attackDir may more suitable
	*TODO* choose more danagerous opponent
	\param our palyer's num
	\return a value stand for freedom [-10,10]
*/
float WorldModel::calOurFreedom( Num num, int &state) const
{
	Vector3f posMe = getTeammateGlobalPos(num);
	//LOG( 18,"opp num: %i",getClosestOppNum2Pos(getBallGlobalPos()));
	Vector3f posOpp = getOpponentGlobalPos(getClosestOppNum2Ball());
	AngDeg attackDir = getVector3fHorizontalAng(getOppGoalCenter()-getBallGlobalPos());
	AngDeg myHeading = getVector3fHorizontalAng(getBallGlobalPos()-posMe);
	AngDeg oppHeading = getVector3fHorizontalAng(getBallGlobalPos()-posOpp);
	
	bool isMyGood = abs(normalizeAngle(myHeading-attackDir))<90.0f;
	bool isOppGood = abs(normalizeAngle(oppHeading-attackDir))>90.0f;
	float distDelta = (getBallGlobalPos()-posOpp).Length()-(getBallGlobalPos()-posMe).Length();
	bool isNearer = distDelta > 0;
	//cout<<"posMe: "<<posMe.x()<<' '<<posMe.y()<<endl;
	//cout<<getClosestOppNum2Ball()<<" posOpp: "<<posOpp.x()<<' '<<posOpp.y()<<endl;
	//cout<<"posBall "<<getBallGlobalPos().x()<<' '<<getBallGlobalPos().y()<<' '<<getBallGlobalPos().z()<<endl;
	//cout<<"distDelta="<<distDelta<<endl;
	float fFreedom=0;
	//-* 1: B--<--O--<--M
	if ( (!isMyGood) && isOppGood && (!isNearer) )
	{
		state=1;
		fFreedom=-3;//0;
	}
	//-* 2: B--<--M--<--O
	else if ( (!isMyGood) && isOppGood && isNearer )
	{
		state=2;
		fFreedom=-1;//0.1;
	}
	//-* 3: O-->--B--<--M
	else if ( (!isMyGood) && (!isOppGood) )
	{
		state=3;
		fFreedom=0.0f;//0.3;
	}
	//-* 4: M-->--B--<--O
	else if ( isMyGood && isOppGood )
	{
		state=4;
		fFreedom=0.0f;//0.5;
	}
	//-* 5: M-->--O-->--B
	else if ( isMyGood && (!isOppGood) && (!isNearer) )
	{
		state=5;
		fFreedom=1;//0.6;
	}
	//-* 6: O-->--M-->--B
	else if ( isMyGood && (!isOppGood) && isNearer )
	{
		state=6;
		fFreedom=3;//1.0;
	}
	else
	{
		LOGERR("calOurFreedom: missing any state?");
	}
	//LOG( 18,"distDelta=%f",distDelta);
	fFreedom+=distDelta;//(0.2*distDelta);
	//fFreedom = setMaxNMin(fFreedom,10.0f,-10.0f);
	fFreedom = ( 2/(1+exp(-3*fFreedom/10.0f))-1 )*10.0f;
	return fFreedom;
}

/*! only test version
	this function return the agent's freedom
	that means is enough space
\param num teammate's num
\return float freedom
*/
float WorldModel::calOurFreedom( Num num ) const
{
	/*Vector3f posMe = getTeammateGlobalPos(num);
	Vector3f posOpp = getOpponentGlobalPos(getClosestOppNum2Pos(posMe));
	float oppDist = (posOpp-posMe).Length();
	return 1/(1+exp(-oppDist));*/
	int state;
	return calOurFreedom(num, state);
}

/*! calculate the kick horizontal angle when a agent in the position
	\param the palyer's position
	\return kick horizontal angle in global
	*TODO* if the ball just on my head...
*/
AngDeg WorldModel::calKickHorizontalAng(const Vector3f &posPlayer) const
{
	return getVector3fHorizontalAng(getBallGlobalPos()-posPlayer);
}

/*! set Players' number, whose type is the same as me
*/
void WorldModel::setSameTypeTeammateNum()
{
	_sameTypeTeammateNum.clear();
	PlayerType myType = FM->getMyType();
	for ( Num i=1; i<=teammates_num; i++)
	{
		if ( i != getMyNum())
		{
			if ( FM->getPlayerType(i)==myType )
			{
				_sameTypeTeammateNum.insert(i);
			}
			else
			{
				_diffTypeTeammateNum.insert(i);
			}
		}
	}
}


/*! boolean indicating whether our teammate is in the defnece position now
	1. the teammate must near the ball
	2. the teammate's position must between ball and the goal
	\param our teammate number
	\return bool
*/
bool WorldModel::isInDefencePos( const Num teammateNum ) const
{
	Vector3f posTeam = getTeammateGlobalPos(teammateNum);
	return ( (getBallGlobalPos()-posTeam).Length() < 5
			&& isThreePointOneLine(getOurGoalCenter(),posTeam,getBallGlobalPos(),45)
			);
}

/** is offside
	\param posX the player's x position
	\param isOur is the player is teammate or opponent
	\return boolean is offside
*/
bool WorldModel::isOffSide( float posX, bool isOur ) const
{
	/** posX > offside, offside */
	return ( ( isOur && posX>getOurOffSideLine() )
		|| ( (!isOur)&&(posX<getOppOffSideLine())) );

}

/*! to make sure the position is in the field
\param the position
\return the new position in the field
*/
Vector3f WorldModel::setVector3fInField(const Vector3f &pos) const
{
	Vector3f newPos;
	newPos.x() = setMaxNMin(pos.x(),getOppBaseLine(),getOurBaseLine());
	newPos.y() = setMaxNMin(pos.y(),getFieldWidth()/2,-getFieldWidth()/2);
	newPos.z() = setMaxNMin(pos.z(),getFieldHeight(),0.0f);
	return newPos;
}

/** log WorldModel's interval state after all updated
*/
void WorldModel::logWorldModel()
{
	/** log erveryone's offside state */
	/*LOG( 41,"our offside line is: %f .our offside num:",getOurOffSideLine());
	for(Num i=1;i<=teammates_num;i++)
	{
		if (isOffSide(i,true))
			LOG( 41,"%d",i);
	}
	LOG( 41,"opp offside line is: %f .opp offside num:",getOppOffSideLine());
	for(Num i=1;i<=opponents_num;i++)
	{
		if (isOffSide(i,false))
			LOG( 41,"%d",i);
	}*/
	
	/** log all parsed msg form server */
	/*for( Num i=1;i<=11;i++)
	{
		Vector3f posTeam = getTeammateRelativePosSeen(i);
		Vector3f posOpp = getOpponentRelativePosSeen(i);
		LOG( 9,"teammate%d: %f, %f, %f",i,posTeam.x(),posTeam.y(),posTeam.z());
		LOG( 9,"opponent%d: %f, %f, %f",i,posOpp.x(),posOpp.y(),posOpp.z());
	}
	Vector3f ballPos = getBallRelativePosSeen();
	LOG( 9,"ball %f, %f, %f",ballPos.x(),ballPos.y(),ballPos.z());
	for( int flag=VO_FLAG1L;flag<=VO_GOAL2R;flag++)
	{
		Vector3f flagPos = getFlagRelativePosSeen(VisionObject(flag));
		LOG( 9,"flag%d: %f, %f, %f",flag,flagPos.x(),flagPos.y(),flagPos.z());
	}*/
}

/*!
	is there any opponent in the front of me?
	ie. Is there any opponent in the rectangle which in my heading direction?
\return bool
*/
bool WorldModel::isSpaceAhead(const Vector3f &goal)const
{
/*	
	float halfWidth = width*0.5f;
	Rectangle rectAhead(getMyGlobalPos().x()-1,getMyGlobalPos().y()+halfWidth,getMyGlobalPos().x()+length,getMyGlobalPos().y()-halfWidth);
	for ( Num i=1;i<=opponents_num; i++ )
	{
		if ( rectAhead[getOpponentGlobalPos(i)] )
			return false;
	}
	return true;*/
	Vector3f posMe = getMyGlobalPos();
	Vector3f velMe = getMyGlobalVel();
	Vector3f posBall = getBallGlobalPos();
	Vector3f velBall = getBallGlobalVel();
	posBall += velBall * 0.2;
	Sector s = Sector(posMe + (posBall - posMe).Normalized() * velMe.Length() * 0.2, goal - posMe, 6, 90);
//	Sector temp = Sector(posMe + posMe.Normalized() * velMe.Length() * 0.2, goal - posMe, 1, 90);
	for( Num num = 1; num <= opponents_num; num++)
	{
		Vector3f posOpp = WM->getOpponentGlobalPos(num);
//		Vector3f velOpp = WM->getOpponentGlobalVel(num);
		posOpp += (posBall - posOpp).Normalized() * 0.3f;
//		tmp = (getOpponentGlobalPos(num)-pos).Length();
		if(s.isInside(posOpp))
			return false;
	}
	return true;
}

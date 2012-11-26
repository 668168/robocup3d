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

 
#include "BasicWorldModel.h"
#include "Logger.h"
#include "Parser.h"
#include <vector>


using namespace std;

/************************************************************************/
/************************ BASIC WORLD MODEL *****************************/
/************************************************************************/

BasicWorldModel::BasicWorldModel()
{
	//-* set default field parameter
    _fieldLength = 105.0;
    _fieldWidth = 68.0;
    _fieldHeight = 20.0;
    _goalWidth = 7.32;
    _goalDepth = 2.0;
    _goalHeight = 0.5; //-* fifa: 2.44;
    _borderSize = 4.0f;
	
	//-* set the Players' sum
	_teammate.resize( teammates_num );
	_opponent.resize( opponents_num );
	
	//-* set oppTeamName to ""
	_oppTeamName = "";

	//-* init "K" think time;
	_thinkTimeLast = 0;
	_numK = 0;
	_sumThinkTime = 0;
	//-* init "C" think time
	_thinkTimeCurrent = 0;
	
	/** offside line */
	_ourOffSideLine = max_field_length*0.5;
	_oppOffSideLine = -_ourOffSideLine;
	
	setupPlayModeMap( _playModeMap );
    setupVisionObjectMap();
}

BasicWorldModel::~BasicWorldModel()
{
}
/*
void BasicWorldModel::parseGameState()
{
	LOG( 2,"seu parseGameState");
	while ( !PA->isBracketClose() )
	{
		//-* read the state name
        string StateName = "";
        if ( !PA->getNextParamName(StateName) )
        {
            continue;
        }
		LOG( 2,"StateName= "+StateName);
		//-* field state
		if (StateName == "FieldLength")
		{
			PA->getNextValue(_fieldLength);
			LOG( 2,"res=%f",_fieldLength);
		}
		else if (StateName == "FieldWidth")
		{
			PA->getNextValue(_fieldWidth);
			LOG( 2,"res=%f",_fieldWidth);
		}
		else if (StateName == "FieldHeight")
		{
			PA->getNextValue(_fieldHeight);
			LOG( 2,"res=%f",_fieldHeight);
		}
		else if (StateName == "GoalWidth")
		{
			PA->getNextValue(_goalWidth);
			LOG( 2,"res=%f",_goalWidth);
		}
		else if (StateName == "GoalDepth")
		{
			PA->getNextValue(_goalDepth);
			LOG( 2,"res=%f",_goalDepth);
		}
		else if (StateName == "GoalHeight")
		{
			PA->getNextValue(_goalHeight);
			LOG( 2,"res=%f",_goalHeight);
		}
		else if (StateName == "BorderSize")
		{
			PA->getNextValue(_borderSize);
			LOG( 2,"res=%f",_borderSize);
			setupFixedObjects();
		}
		//-* time
		else if (StateName == "time")
		{
			PA->getNextValue(_gameTime);
			LOG( 2,"res=%f",_gameTime);
		}
		//-* my num
		else if (StateName == "unum")
		{
			int num = _myself.getNum();
			PA->getNextValue(num);
			_myself.setNum( num );
			LOG( 0,"I am Num %d",num );
			LOG( 2,"res=%f",num);
		}
		//-* agent radius
		else if (StateName == "AgentRadius")
		{
			float agentRadius = _myself.getRadius();
			PA->getNextValue(agentRadius);
			_myself.setRadius( agentRadius );
			LOG( 2,"res=%f",agentRadius);
		}
		//-* agent mass
		else if (StateName == "AgentMass")
		{
			float agentMass = _myself.getMass();
			PA->getNextValue(agentMass);
			_myself.setMass( agentMass );
			LOG( 2,"res=%f",agentMass);
		}
		//-* agent max speed
		else if (StateName == "AgentMaxSpeed")
		{
			float agentMaxSpeed = _myself.getMaxSpeed();
			PA->getNextValue(agentMaxSpeed);
			_myself.setMaxSpeed( agentMaxSpeed );
			LOG( 2,"res=%f",agentMaxSpeed);
		}
		//-* ball radius
		else if (StateName == "BallRadius")
		{
			float ballRadius = _ball.getRadius();
			PA->getNextValue(ballRadius);
			_ball.setRadius( ballRadius );
			LOG( 2,"res=%f",ballRadius);
		}
		//-* ball mass
		else if (StateName == "BallMass")
		{
			float ballMass = _ball.getMass();
			PA->getNextValue(ballMass);
			_ball.setMass( ballMass );
			LOG( 2,"res=%f",ballMass);
		}
		//-* team index
		else if (StateName == "team")
		{
			string team="";
			PA->getNextValue(team);
			parseTeamIndex( team );
			LOG( 2,"res="+team);
		}
		//-* play mode
		else if (StateName == "playmode")
		{
			string mode="";
			if (PA->getNextValue(mode))
			{
				parsePlayMode(mode);
			}
			LOG( 2,"palymode= %d",getPlayMode());
		}
		else
		{
			LOGERR("[Warning](BasicWorldModel)unknown GameState: "+StateName+"\n");
		}
		PA->gotoNextLeftBracket();   
	}
	
}
*//*
void BasicWorldModel::parse(const char* msgBegin, const unsigned int msgSize)
{
	LOG( 2, "seu parse, Length=%d",msgSize);
	PA->input(msgBegin,msgBegin+msgSize);
	
    switch( *msgBegin )
	{
		case 'C' :
			parseMsgC();
			break;
		
		case 'D' :
            break;
		
        case 'K' :
			parseMsgK();
            break;

        case 'S' :
			parseMsgS();
			break;
		
		case 'T' :
			parseMsgT();
			break;
		
		case 'X':
			break;
		
		case 'O':
			LOGERR("[Warning]thinking too long time?\nreceived \"O\"");
			break;
		
		case 'I':
			LOGERR("[Warning]thinking too long time?\nreceived \"I\"");
			break;
		
        default:
            LOGERR("[Warning](BasicWorldModel)received unknown data: \n");
            break;
	}

}
*//*
void BasicWorldModel::parseTeamIndex(const string &team)
{
    //-* parse team index
    if (team == "left")
        _teamIndex = TI_LEFT;
    else if (team == "right")
        _teamIndex = TI_RIGHT;
    else
        {
            _teamIndex = TI_NONE;
            LOGERR("(BasicWorldModel) received TeamIndex TI_NONE\n");
        }
}

void BasicWorldModel::parsePlayMode(const string &mode)
{
    //-* parse play mode
    TPlayModeMap::iterator iter = _playModeMap.find(mode);
    if (iter != _playModeMap.end())
        {
            _playMode = (TPlayMode)(*iter).second;
        } else
            {
                LOGERR(
                     			"[Error](BasicWorldModel) could not parse playmode: "+
                     			mode+"\n"
								);
            }
}
*//*
void BasicWorldModel::parseMsgT()
{
	int iRes = 0 ;
	if ( PA->gotoNext() && PA->parseNextInt(iRes))
	{
    	_realTime = iRes;
	}
}
*//*
void BasicWorldModel::parseMsgC()
{
	LOG( 2,"parseMsgC");
	int iRes = 0 ;
	if ( PA->gotoNext() && PA->parseNextInt(iRes))
	{
		_thinkTimeCurrent = iRes;
    	_realTime += iRes;
		_sumThinkTime += _thinkTimeCurrent;
		_numK ++;
		LOG( 2,"complete parseMsgC");
	}
}
*//*
void BasicWorldModel::parseMsgK()
{
	int iRes = 0 ;
    if ( PA->gotoNext() && PA->parseNextInt(iRes))
	{
		_thinkTimeLast = iRes;
		_numK ++;
		_sumThinkTime += _thinkTimeLast;
		LOG( 2,"parse Msg K");
	}
}
*//*
void BasicWorldModel::parseMsgS()
{
	LOG( 2,"seu parseMsgS");
	int iRes = 0;
	//-* parse the time of the vision message
	if ( PA->gotoNext() && PA->parseNextInt(iRes) )
	{
		LOG( 2,"_timeLastSeen=%d",iRes);
    	_timeLastSeen = iRes;
	}
	
	iRes = 0;
	//-* parse the current time
	if ( PA->parseNextInt(iRes) )
	{
		LOG( 2,"_realTime=%d",iRes);
		_realTime = iRes;
	}

    while ( !PA->isEnd() )
        {
			string strParamType;
			if (!PA->getNextParamName(strParamType))return;
			//cout<<"strParamType "<<strParamType<<endl;
			if( strParamType == "GameState")
			{
                parseGameState();
			}
			else if ( strParamType == "Vision")
			{
				//-* check for the Vision perceptor
				parseVision();
			}
            else if ( strParamType == "AgentState")
			{
				parseAgentState();
			}
			else
			{
				LOGERR(
                			"[Warning](WorldModel) skipping unknown predicate: "+
                			strParamType + "\n");
			}
            
        }
		LOG( 2,"complete seu parseS");
}
*//*
void BasicWorldModel::parseVision()
{
	LOG( 2,"seu parseVision");
	while ( !PA->isBracketClose() )
	{	
		//-* read the object name
        string name = "";
        PA->getNextParamName(name);
		if ( name.empty() )
		{
			while ( !PA->isBracketClose() )
			{
				PA->gotoNext();
			}
			return;
		}


		
		
		//-* try to read 'team' section
		string strTeam = "";
		if ( PA->getNextParamValue("team", strTeam))
        {
            name += strTeam;
			//-* parse opponents' teamName
			if ( ""==_oppTeamName && strTeam != getMyTeamName() )
			{
				setOppTeamName(strTeam);
			}
        }

		//-* try read the 'id' section
        string strId = "";
        if ( PA->getNextParamValue("id", strId))
        {
            name += strId;
        }

		LOG( 2, "objName= "+name );
        //-* try to lookup the VisionObject
        TVisionObjectMap::iterator iterVisionObject = _visionObjectMap.find(name);
        if (iterVisionObject == _visionObjectMap.end())
        {
			//if(!PA->gotoNextRightBracket())return;
            continue;
        }

        VisionObject vo = (*iterVisionObject).second;

        //-* find  to the 'pol' entry in the object's section
		VisionSense sense;
        if ( !PA->getNextParamValue("pol",sense))
        {
			LOG( 2,"failure in parse pol");
            continue;
        }
		LOG( 2,"success in parse pol ( %f, %f, %f)",sense.distance,sense.theta,sense.phi);
        //-* update the vision map
        _visionMap[vo] = sense;
		
		PA->gotoNextLeftBracket();
	}
}
*/
void BasicWorldModel::setupVisionObjectMap()
{
    _visionObjectMap.clear();

    //-* <ObjectName>+<Id> -> VisionObject
	//-* fixed objects
    _visionObjectMap["Flag1_l"] = VO_FLAG1L;
    _visionObjectMap["Flag1_r"] = VO_FLAG1R;
    _visionObjectMap["Flag2_l"] = VO_FLAG2L;
    _visionObjectMap["Flag2_r"] = VO_FLAG2R;
    _visionObjectMap["Goal1_l"] = VO_GOAL1L;
    _visionObjectMap["Goal1_r"] = VO_GOAL1R;
    _visionObjectMap["Goal2_l"] = VO_GOAL2L;
    _visionObjectMap["Goal2_r"] = VO_GOAL2R;
	
	//-* ball
    _visionObjectMap["Ball"]    = VO_BALL;
	
    //-* opponents
	string oppTeamName = _oppTeamName;
    _visionObjectMap["Player"+oppTeamName+"1"]  =  VO_OPPONENT_1;
    _visionObjectMap["Player"+oppTeamName+"2"]  =  VO_OPPONENT_2;
    _visionObjectMap["Player"+oppTeamName+"3"]  =  VO_OPPONENT_3;
    _visionObjectMap["Player"+oppTeamName+"4"]  =  VO_OPPONENT_4;
    _visionObjectMap["Player"+oppTeamName+"5"]  =  VO_OPPONENT_5;
    _visionObjectMap["Player"+oppTeamName+"6"]  =  VO_OPPONENT_6;
    _visionObjectMap["Player"+oppTeamName+"7"]  =  VO_OPPONENT_7;
    _visionObjectMap["Player"+oppTeamName+"8"]  =  VO_OPPONENT_8;
    _visionObjectMap["Player"+oppTeamName+"9"]  =  VO_OPPONENT_9;
    _visionObjectMap["Player"+oppTeamName+"10"] =  VO_OPPONENT_10;
    _visionObjectMap["Player"+oppTeamName+"11"] =  VO_OPPONENT_11;

	//-* teammates
	string teamName = getMyTeamName();
    _visionObjectMap["Player"+teamName+"1"]  =  VO_TEAMMATE_1;
    _visionObjectMap["Player"+teamName+"2"]  =  VO_TEAMMATE_2;
    _visionObjectMap["Player"+teamName+"3"]  =  VO_TEAMMATE_3;
    _visionObjectMap["Player"+teamName+"4"]  =  VO_TEAMMATE_4;
    _visionObjectMap["Player"+teamName+"5"]  =  VO_TEAMMATE_5;
    _visionObjectMap["Player"+teamName+"6"]  =  VO_TEAMMATE_6;
    _visionObjectMap["Player"+teamName+"7"]  =  VO_TEAMMATE_7;
    _visionObjectMap["Player"+teamName+"8"]  =  VO_TEAMMATE_8;
    _visionObjectMap["Player"+teamName+"9"]  =  VO_TEAMMATE_9;
    _visionObjectMap["Player"+teamName+"10"] =  VO_TEAMMATE_10;
    _visionObjectMap["Player"+teamName+"11"] =  VO_TEAMMATE_11;

}

VisionSense BasicWorldModel::getVisionSense( VisionObject vo )
{
    TVisionMap::iterator iter = _visionMap.find( vo );

    if (iter == _visionMap.end())
        {
            //LOGERR("[ERROR](BasicWorldMode::getVisionSeen) unknown VisionObject: %i",vo);

            return VisionSense();
        }

    return (*iter).second;
		
}

void BasicWorldModel::setMyTeamName( string teamName ) 
{
	//LOG( 1,"Set teamName to :"+teamName );
	_myself.setTeamName( teamName ); 
	
	setupVisionObjectMap();
}

void BasicWorldModel::setMyGlobalPosWhileBeam( Vector3f posGlobal )
{
	
	LOG( 23,"setMyGlobalPosWhileBeam %f,%f,%f",posGlobal[0],posGlobal[1],posGlobal[2]);
	Time time = getRealTime();
	_myself.updateDynamic( time+action_latecy, posGlobal, posGlobal, Vector3f(0,0,0), Vector3f(0,0,0) );
	_myself.setDriveForce( Vector3f(0,0,0) );
	
	Vector3f pos = _myself.getGlobalPos();
	LOG( 23,"setMyGlobalPosWhileBeam after %f,%f,%f",pos[0],pos[1],pos[2]);
	
}

void BasicWorldModel::setBallBeforeKickOff()
{
	_ball.updateDynamic( getRealTime(), Vector3f(0,0,0), _myself.getGlobalPos(), Vector3f(0,0,0), Vector3f(0,0,0) );
}

void BasicWorldModel::setOppTeamName( const string &teamName )
{
	cout<<" opp team name is : "<<teamName<<'\n';
	_oppTeamName = teamName;
	
	setupVisionObjectMap();
}
/*
void BasicWorldModel::parseAgentState()
{
	LOG( 2,"seu parse agent state");
	while ( !PA->isBracketClose() )
	{
		//-* read the state name
        string StateName;
		//cout<<"StateName: "<<StateName<<endl;
        if ( !PA->getNextParamName(StateName) )
        {
            continue;
        }
		//cout<<"StateName: "<<StateName<<endl;
		//-* update the agent state
		if ( StateName == "battery")
		{
			float battery = 0;
			PA->getNextValue(battery);
			_myself.setBattery( battery );
		}
		else if ( StateName == "temp" )
		{
			float temp = 0;
			PA->getNextValue(temp);
			_myself.setTemperature( temp );
		}
		else
		{
			LOGERR("[Warning](BasicWorldModel::parseAgentState) unknown agent state!");
		}
		PA->gotoNextLeftBracket();		
	}		
}
*/
void BasicWorldModel::update()
{
	//-* 1.parse
	//parse( message );

	//-* 2.updateAll
	updateAll();
	LOG( 2,"complete updateAll");

	//-* 3.predict
	predict();
	LOG( 2,"complete predict");
	LOG( 2,"update ok");
}

void BasicWorldModel::updateAll()
{
	//-* 1. update the information of the flags and goals
	//-- for agent localization need these infromation
	updateFixedObjects();
	
	//-* 2. update agent:
	//-- localization
	updateAgent();
	
	//-* 3. update ball's information
	newupdateBall();
	
	//-* 4. update other Players
	updatePlayers();
	
	/** 5. update offside lines */
	updateOffSideLine();
}

void BasicWorldModel::updateFixedObjects()
{
	_flag_1_l.updateLastSeen( _timeLastSeen, getVisionSense( VO_FLAG1L ) );
	_flag_1_r.updateLastSeen( _timeLastSeen, getVisionSense( VO_FLAG1R ) );
	_flag_2_l.updateLastSeen( _timeLastSeen, getVisionSense( VO_FLAG2L ) );
	_flag_2_r.updateLastSeen( _timeLastSeen, getVisionSense( VO_FLAG2R ) );

	_goal_1_l.updateLastSeen( _timeLastSeen, getVisionSense( VO_GOAL1L ) );
	_goal_1_r.updateLastSeen( _timeLastSeen, getVisionSense( VO_GOAL1R ) );
	_goal_2_l.updateLastSeen( _timeLastSeen, getVisionSense( VO_GOAL2L ) );
	_goal_2_r.updateLastSeen( _timeLastSeen, getVisionSense( VO_GOAL2R ) );

	/*VisionSense bv = _flag_1_l.getVisionSeen( 0 );
	LOG( 11,"flag_1_l updated: %f:%f,%f,%f", _flag_1_l.getTimeSeen( 0 ),bv.distance,bv.theta,bv.phi);

	Vector3f pos = _flag_1_l.getGlobalPos();
	LOG( 11,"flag_1_l global pos: %f,%f,%f",pos[0],pos[1],pos[2] );
	*/
}

void BasicWorldModel::updateAgent()
{
	localization();
	//Vector3f posMe = _myself.getGlobalPos();
	//LOG(11,"mypos: %f,%f,%f",posMe[0],posMe[1],posMe[2]);
	
	//Vector3f driveForce = _myself.getDriveForce();
	//LOG(11,"driveForce: %f,%f,%f",driveForce[0],driveForce[1],driveForce[2]);
}

void BasicWorldModel::newupdateBall()
{
	//-* update the sense about the ball
	_ball.updateLastSeen( _timeLastSeen, getVisionSense( VO_BALL ) );

	//-* -----update the global position and velocity of the ball---------
	Time timeDelta = _ball.getTimeSeen() - _ball.getTime();
	if ( timeDelta <= 0 )
		return;
	Step iStep = Time2Step(timeDelta);
	//LOG( 21," timeDelta: %f", timeDelta );
	//-* calculate ball global pos and global velocity
	Vector3f globalPos, globalVelocity;
	//-* in playon mode, we must calculate both ball's position and velocity
	//-- but in unplayon mode, we only need to set the vaule of some var
	if ( getPlayMode() == PM_PlayOn 
		 || getPlayMode() == PM_GOAL_KICK_LEFT
		 || getPlayMode() == PM_GOAL_KICK_RIGHT)
	{
		globalPos = _ball.getGlobalPos();
		Vector3f globalPos1 = _ball.getGlobalPos(1);
		Vector3f globalPos2 = _ball.getGlobalPos(2);
		globalVelocity = _ball.getGlobalVelocity();
		Vector3f globalVelocity1 = _ball.getGlobalVelocity(Step(1));
		Vector3f globalVelocity2 = _ball.getGlobalVelocity(Step(2));

		calculateBallState( globalPos, globalPos1, globalPos2,
							globalVelocity, globalVelocity1, globalVelocity2,
							iStep);
	}
	else
	{
		globalPos = getBallPositionUnPlayOn();
		globalVelocity.Zero();
	}
	if ( globalPos.z() < _ball.getRadius() )
		globalPos.z() = _ball.getRadius();
	_ball.updateDynamic( _ball.getTimeSeen(), globalPos, _myself.getGlobalPos(), globalVelocity, Vector3f(0,0,0) );
}

Vector3f BasicWorldModel::getBallPositionUnPlayOn()
{
	Vector3f posBall = _ball.calculateGlobalPosFromVision( _myself.getGlobalPos());
	Vector3f posOld = _ball.getGlobalPos();
	Vector3f velOld = _ball.getGlobalVelocity();
	switch ( getPlayMode())
	{
		case PM_BeforeKickOff :
		case PM_KickOff_Left :
        case PM_KickOff_Right :
			posBall.Zero();
            break;

        case PM_KickIn_Left :
        case PM_KickIn_Right :
		{
			posBall.y() = sign( posBall.y())*getFieldWidth()/2;
			posBall.z() = _ball.getRadius();
            break;
		}
		
		case PM_CORNER_KICK_LEFT:
		case PM_CORNER_KICK_RIGHT:
		{
			posBall.x() = sign( posBall.x())*getFieldLength()/2;
			posBall.y() = sign( posBall.y())*getFieldWidth()/2;
			posBall.z() = _ball.getRadius();
			break;
		}

        default:
            break;
	}

	//if pre cycle have been unPlayOn
	if ( velOld == Vector3f(0,0,0))
	{
		posBall = ( posBall + posOld)/2;
	}
	
	return posBall;
}

void BasicWorldModel::calculateBallState( Vector3f &posBall, Vector3f &prePosBall, Vector3f &preprePosBall,
										Vector3f &velBall, Vector3f &preVelBall, Vector3f &prepreVelBall,
										const Step iStep)
{
	//LOG( 25,"deltaTime: %f s",Step2Second(iStep));
	const float max_dist_gap = 0.5;
	Vector3f posSee, velSee, posSim, velSim;
	posSee = _ball.calculateGlobalPosFromVision( _myself.getGlobalPos());
	//posSim = _ball.calculateGloabalPosFromMemory( deltaTime);
	posSim = posBall;
	velSim = velBall;
	Vector3f posSim1 = prePosBall;
	Vector3f posSim2 = preprePosBall;
	Vector3f velSim1 = preVelBall;
	Vector3f velSim2 = prepreVelBall;
	_ball.updateKalman(iStep);
	Vector3f visionError = _ball.getVisionError();
	Vector3f velPol = _ball.calculateGlobalVelFromVision( _myself.getGlobalVelocity());
	Vector3f velPolErr = _myself.getKalmanP11() + visionError;
	//-* if collide happened, the see information only used
	//-- if no collide, use both information form see and simulate
	if ( _ball.predictStateAfterNrSteps( posSim, posSim1, posSim2, velSim, velSim1, velSim2, iStep) 
		&& (posSee -posSim).Length() < max_dist_gap	)
	{
		//LOG( 25,"posSim: %f, %f, %f",posSim[0],posSim[1],posSim[2]);
		//LOG( 25,"posSee: %f, %f, %f",posSee[0],posSee[1],posSee[2]);
		Vector3f simulatePosError = _ball.getKalmanP22();
		Vector3f simulateVelError = _ball.getKalmanP12();
		LOG( 25,"visionError: %f, %f, %f",visionError[0],visionError[1],visionError[2]);
		LOG( 25,"simulatePosError: %f, %f, %f",simulatePosError[0],simulatePosError[1],simulatePosError[2]);
		Vector3f weightedPos = posSee;
		float k = 0.0;
		for ( int i=0; i<3; i++)
		{
			k = visionError[i] / ( simulatePosError[i] +visionError[i]);
			weightedPos[i] += k*( posSim[i] - weightedPos[i]);
			simulatePosError[i] = visionError[i]*(1-k);
			LOG( 25,"K[%d]=%f",i,k);
			velSee[i] = ( weightedPos[i] - posBall[i])/Step2Second(iStep);
			k = visionError[i] / ( simulateVelError[i] +visionError[i]);
			velBall[i] = velSee[i] + k*( velSim[i] - velSee[i]);
			visionError[i] -= k*visionError[i];
			k = visionError[i]/ ( velPolErr[i] + visionError[i] );
			velBall[i] += k*( velPol[i] - velBall[i] );
		}
		_ball.setKalmanP22(simulatePosError);
		LOG( 25,"weightedPos: %f, %f, %f",weightedPos[0],weightedPos[1],weightedPos[2]);
		//LOG( 25,"velSee: %f, %f, %f",velSee[0],velSee[1],velSee[2]);
		//LOG( 25,"velSim: %f, %f, %f",velSim[0],velSim[1],velSim[2]);
		posBall = weightedPos;
	}
	else
	{
		LOG( 25,"more than max gap!");
		_ball.setKalmanP22(visionError);
		Vector3f posOld = posBall;
		posBall = posSee;
		//posBall = lowFreqSignalFilter( posSee, posBall);
		velSee = (posBall - posOld)/Step2Second(iStep); 
		velBall = ( velSee + velPol*0.5)/1.5;
		//velBall = lowFreqSignalFilter( velSee, velBall);
	}
	
	//
	//Vector3f velD = velBall -  velPol;
	//LOG( 25,"*");
	//LOG( 25,"velPol : %f,%f,%f",velPol[0],velPol[1],velPol[2]);
	//LOG( 25,"velBall: %f,%f,%f",velBall[0],velBall[1],velBall[2]);
	//LOG( 25,"velD : %f,%f,%f",velD[0],velD[1],velD[2]);
	//

}

void BasicWorldModel::updateBall()
{
	//-* update the sense about the ball
	_ball.updateLastSeen( _timeLastSeen, getVisionSense( VO_BALL ) );
	//VisionSense bv = _ball.getVisionSeen( 0 );
	//LOG( 11,"ball updated: %f:%f,%f,%f", _ball.getTimeSeen( 0 ),bv.distance,bv.theta,bv.phi);

	//-* -----update the global position and velocity of the ball---------
	Time timeDelta = ( _ball.getTimeSeen() - _ball.getTime() ) * 0.01;
	if ( timeDelta <= 0 )
		return;
	//LOG( 21," timeDelta: %f", timeDelta );
	//-* calculate ball global pos
	Vector3f tmp1, tmp2, globalPos, globalVelocity;
	tmp1 = _myself.getGlobalPos() + _ball.getPosRelativeSeen();
	tmp2 = _ball.getGlobalPos() + _ball.getGlobalVelocity()*timeDelta;
	globalPos = ( tmp1 + tmp2*0.5 )/1.5;
	//LOG( 21,"_ball.getPosRelativeSeen: %f,%f,%f",_ball.getPosRelativeSeen()[0],_ball.getPosRelativeSeen()[1],_ball.getPosRelativeSeen()[2]);
	//LOG( 21," tmp1: %f,%f,%f", tmp1[0],tmp1[1],tmp1[2]);
	//LOG( 21," tmp2: %f,%f,%f", tmp2[0],tmp2[1],tmp2[2]);
	//LOG( 21," poaBall 1: %f,%f,%f", globalPos[0],globalPos[1],globalPos[2]);
	globalPos = lowFreqSignalFilter( globalPos, _ball.getGlobalPos() );
	//LOG( 21," poaBall 2: %f,%f,%f", globalPos[0],globalPos[1],globalPos[2]);
	globalPos[2] = tmp1[2];
	globalPos[2] = setMaxNMin( globalPos[2], getFieldHeight(), _ball.getRadius() );
	//LOG( 21," poaBall 3: %f,%f,%f", globalPos[0],globalPos[1],globalPos[2]);
	//-* calculate ball velocity 
	tmp1 = ( globalPos - _ball.getGlobalPos() )/timeDelta;
	if ( globalPos[2] > _ball.getRadius() 
		&& _ball.getGlobalVelocity()[2] > 1 )//-* air ball
	{
		tmp2 = _ball.getGlobalVelocity()*( 1-timeDelta*air_friction_factor/_ball.getMass() );
		tmp2[2] = tmp1[2];
	}
	else//-* ground ball
	{
		tmp2 = _ball.getGlobalVelocity()*( 1-timeDelta*ground_friction_factor/_ball.getMass() );
		tmp2[2] = tmp1[2];
	}
	//LOG( 21," tmp1: %f,%f,%f", tmp1[0],tmp1[1],tmp1[2]);
	//LOG( 21," tmp2 = v*( 1-t*u/m ): v: %f,%f,%f m: %f", 
	//			_ball.getGlobalVelocity()[0],_ball.getGlobalVelocity()[1],_ball.getGlobalVelocity()[2],_ball.getMass());
	//LOG( 21," tmp2: %f,%f,%f", tmp2[0],tmp2[1],tmp2[2]);
	globalVelocity = (tmp1 + tmp2)/2;
	globalVelocity[0] = lowFreqSignalFilter( globalVelocity[0], _ball.getGlobalVelocity()[0] );
	globalVelocity[1] = lowFreqSignalFilter( globalVelocity[1], _ball.getGlobalVelocity()[1] );
	
	_ball.updateDynamic( _ball.getTimeSeen(), globalPos, _myself.getGlobalPos(), globalVelocity, Vector3f(0,0,0) );
}

void BasicWorldModel::updatePlayers()
{
	updateMyselfInTeam();//-* this step munst before update our team!!
	updateTeam( _teammate, VO_TEAMMATE_1 );
	updateTeam( _opponent, VO_OPPONENT_1 );	
}

/*! update the Player's info, who is myself in team
*/
void BasicWorldModel::updateMyselfInTeam()
{
	//-* if can not make sure my number, only in the beginning
	//-- do nothing
	if ( getMyNum() > 0 && getMyNum() <= teammates_num )
	{
		vector< PlayerObject >::iterator iter = _teammate.begin()+getMyNum()-1;
		iter->updateDynamic( getTimeLastSeen(),
									getMyGlobalPos(), getMyGlobalPos(), getMyGlobalVel(), Vector3f(0,0,0) );
	}
}

void BasicWorldModel::updateTeam( vector<PlayerObject> &team ,VisionObject num_1 )
{
	Vector3f posMe = _myself.getGlobalPos();
	//LOG( 21,"posMe: %f,%f,%f",posMe[0],posMe[1],posMe[2]);
	//-* Team
	unsigned int num = num_1;
	for ( vector< PlayerObject >::iterator iter = team.begin();
			iter != team.end();
			iter++, ++num )
	{
		Time timeDelta = ( getTimeLastSeen() - iter->getTime() ) * 0.01;
		if ( timeDelta > 0 )
		{
			//LOG( 21,"num: %i",num);
			//-* update vision
			iter->updateLastSeen( _timeLastSeen, getVisionSense( VisionObject(num) ) );
			//LOG( 21, "vision: %f,%f,%f",iter->getVisionSeen().distance,iter->getVisionSeen().theta,iter->getVisionSeen().phi);
			//-* cal global pos
			Vector3f globalPos = posMe + iter->getPosRelativeSeen(); 
			globalPos[2] = iter->getRadius();
			//LOG( 21, "globalPos: %f,%f,%f",globalPos[0],globalPos[1],globalPos[2]);
			//-* cal vel
			Vector3f globalVelocity = ( globalPos - iter->getGlobalPos() )/timeDelta;
		
			//-* update
			iter->updateDynamic( getTimeLastSeen(),
									globalPos, posMe, globalVelocity, Vector3f(0,0,0) );
	
		}
	}
}

void BasicWorldModel::setupFixedObjects()
{
	//-* complete test
	//-- the flag global position is not we see in the monitor
	//-- they are just on the ground ( z = 0 )
	const float flagHight = 0;
	//-* side: left or right?
	int side = 1;
	if( getTeamIndex() == TI_RIGHT )
		side = -1;

	_flag_1_l.setGlobalPos( Vector3f( -_fieldLength/2*side, -_fieldWidth/2*side, flagHight ) );
	_flag_1_r.setGlobalPos( Vector3f(  _fieldLength/2*side, -_fieldWidth/2*side, flagHight ) );
	_flag_2_l.setGlobalPos( Vector3f( -_fieldLength/2*side,  _fieldWidth/2*side, flagHight ) );
	_flag_2_r.setGlobalPos( Vector3f(  _fieldLength/2*side,  _fieldWidth/2*side, flagHight ) );

	_goal_1_l.setGlobalPos( Vector3f( -_fieldLength/2*side, -_goalWidth/2, 0 ) );
	_goal_1_r.setGlobalPos( Vector3f(  _fieldLength/2*side, -_goalWidth/2, 0 ) );
	_goal_2_l.setGlobalPos( Vector3f( -_fieldLength/2*side,  _goalWidth/2, 0 ) );
	_goal_2_r.setGlobalPos( Vector3f(  _fieldLength/2*side,  _goalWidth/2, 0 ) );

}

//////////////////// localization ////////////////////////
void BasicWorldModel::localization()
{
	//-* if needed localization?
	if ( !getRealTime() > _myself.getTime())
		return;
	
	//-* constants
	const float max_speed = real_agent_max_speed*2;
	
	Vector3f weightedPos;
	VisionSense flagSense;

	// for kalman
	float k = 0.0;
	Vector3f var = Vector3f(0,0,0);
	Vector3f totalVar = Vector3f(0,0,0);

	Vector3f newPos;
	// iterate through all flags, localize the Player and
	// finally create a weighted average of all these positions
	for( int flag = VO_FLAG1L; flag <= VO_GOAL2R; ++flag)
	{
		newPos = localizeWithOneFlag( VisionObject(flag) );
		const FixedObject *flagPtr = getFlagPtr( VisionObject(flag) );
		var = flagPtr->getVisionError();
		
		// first flag, so intialize pos
		if( flag == VO_FLAG1L )
		{
			totalVar  = var;            
			weightedPos = newPos;
		}
		else
		{
			//-* otherwise use new position based on weighted variance kalman filtering technique
			for (int i=0; i<3; i++)
			{
				k = totalVar[i] / ( var[i] + totalVar[i] );
				weightedPos[i] += k*( newPos[i] - weightedPos[i] );
				totalVar[i] -= k*totalVar[i];
			}
		}
	}
	
	Vector3f posGlobal = _myself.getGlobalPos();
	Vector3f velGlobal = _myself.getGlobalVelocity();
	unsigned int deltaSteps = static_cast<unsigned int>(getRealTime()-_myself.getTime());
	Time deltaTime = deltaSteps/100.0f;
	_myself.updateKalman( deltaTime);
	LOG( 24,"deltaTime: %f",deltaTime);
	LOG( 24,"vision pos: %f,%f,%f",weightedPos[0],weightedPos[1],weightedPos[2]);
	if ( (weightedPos-posGlobal).Length() > max_speed*deltaTime )//-* be moved?
	{
		_myself.updateDynamic( getRealTime(), weightedPos, weightedPos, Vector3f(0,0,0), Vector3f(0,0,0) );
	}
	else
	{
		Vector3f weightedVel;
		Vector3f oldPos = posGlobal;
		predictPlayerStateAfterNrSteps( posGlobal, velGlobal, deltaSteps);
		LOG( 24,"drive pos: %f,%f,%f",posGlobal[0],posGlobal[1],posGlobal[2]);
		
		Vector3f kalmanP22 = _myself.getKalmanP22();
		for ( int i =0; i<3; i++ )
		{
			var[i] = kalmanP22[i];
			k = totalVar[i] / ( var[i] + totalVar[i] );
			weightedPos[i] += k*( posGlobal[i] - weightedPos[i] );
			//kalmanP22[i] -= k*kalmanP22[i];
			kalmanP22[i] = totalVar[i]*(1-k);
			
			k = totalVar[i] / ( (_myself.getKalmanP12())[i]+ totalVar[i] );
			weightedVel[i] = ( weightedPos[i] - oldPos[i])/deltaTime;
			weightedVel[i] += k*( velGlobal[i] - weightedVel[i] );
		}
		_myself.setKalmanP22( kalmanP22);
		LOG( 24,"total vision var: %f,%f,%f",totalVar[0],totalVar[1],totalVar[2]);
		LOG( 24,"drive var: %f,%f,%f",var[0],var[1],var[2]);
		weightedVel[2] = 0.0;
		LOG( 24,"Global pos: %f,%f,%f",weightedPos[0],weightedPos[1],weightedPos[2]);
		if ( weightedVel.Length() >real_agent_max_speed)//-* error?
		{
			weightedVel.Normalize();
			weightedVel = weightedVel*real_agent_max_speed;
		}
		_myself.updateDynamic( getRealTime(), weightedPos, weightedPos, weightedVel, Vector3f(0,0,0) );
	}
}

//-* this localization use all 8 flags in the field
//-- beacuse of symmetry
//-- myPos = SIGMA(flagPos)/(-8)
Vector3f BasicWorldModel::localizationWithAllFixedObjects() const
{
	Vector3f posAgent =   _flag_1_l.getPosRelativeLastSeen()
						+ _flag_1_r.getPosRelativeLastSeen()
						+ _flag_2_l.getPosRelativeLastSeen()
						+ _flag_2_r.getPosRelativeLastSeen()
						+ _goal_1_l.getPosRelativeLastSeen()
						+ _goal_1_r.getPosRelativeLastSeen()
						+ _goal_2_l.getPosRelativeLastSeen()
						+ _goal_2_r.getPosRelativeLastSeen();
	posAgent[0] /= -8;
	posAgent[1] /= -8;
	posAgent[2] = _myself.getRadius();
	return posAgent;
}


Vector3f BasicWorldModel::localizeWithOneFlag( VisionObject flag ) const
{
	const FixedObject *flagPtr = getFlagPtr( flag );
	Vector3f flagPos = getFlagGlobalPos(flag);
	Vector3f pos2Flag  = flagPtr->getRelativePosSeen();
	
	// appropriate coord. quadrant
	// BUG?
	/*if( getTeamIndex() == TI_RIGHT )
	{
		pos2Flag[0] = -pos2Flag[0];
		pos2Flag[1] = -pos2Flag[1];
	}*/

	return flagPos - pos2Flag;
}


//-* get Vector3f in a vector< PlayerObject > 
Vector3f BasicWorldModel::getVector3fInVector( Vector3fType vt, vector< PlayerObject > team, unsigned int num ) const
{

	vector< PlayerObject >::iterator iter = team.begin()+num-1;
	
	//-* if wrong num, return illegal value
	if ( iter >= team.begin() && iter < team.end() )
	{
		Vector3f res = vector3f_illegal;
		switch ( vt )
		{
			case VT_GLOBAL_POS :
				res = iter->getGlobalPos();
			break;
			
			case VT_GLOBAL_VEL :
				res = iter->getGlobalVelocity();
			break;
			
			case VT_GLOBAL_ACC :
				res = iter->getGlobalAcceletation();
			break;
			
			case VT_RELATIVE_POS :
				res = iter->getRelativePos();
			break;
			
			case VT_RELATIVE_POS_SEEN :
				res = iter->getRelativePosSeen();
			break;
			
			default:
				break;
		}
		return res;
	}
	else
		return vector3f_illegal;
}

Vector3f BasicWorldModel::getPlayerGlobalPosInTeam( vector<PlayerObject> team, unsigned int num ) const
{
	return getVector3fInVector( VT_GLOBAL_POS, team, num );

}

Vector3f BasicWorldModel::getPlayerGlobalVelInTeam( vector<PlayerObject> team, unsigned int num ) const
{
	return getVector3fInVector( VT_GLOBAL_VEL, team, num );

}

Vector3f BasicWorldModel::getPlayerGlobalPos( bool isTeammate, unsigned int num ) const
{
	return  isTeammate?
			getTeammateGlobalPos( num ):
			getOpponentGlobalPos( num );		
}

Vector3f BasicWorldModel::getPlayerGlobalVel( bool isTeammate, unsigned int num ) const
{
	return  isTeammate?
			getTeammateGlobalVel( num ):
			getOpponentGlobalVel( num );		
}

/*!
	get player's position relative to me
	\param team, indicate which team is the player in
	\param num, indicate the player's num
	\return relative position
*/
Vector3f BasicWorldModel::getPlayerRelativePosInTeam( vector<PlayerObject> team, Num num ) const
{
	return getVector3fInVector( VT_RELATIVE_POS, team, num );
}

/*!
	get player's position relative to me
	\param isTeammate, indicate which team is the player in
	\param num, indicate the player's num
	\return relative position
*/
Vector3f BasicWorldModel::getPlayerRelativePos( bool isTeammate, unsigned int num ) const
{
	return  isTeammate?
			getTeammateRelativePos( num ):
			getOpponentRelativePos( num );
}

/*!
	get player's position in sense to relative me
	\param team, indicate which team is the player in
	\param num, indicate the player's num
	\return relative position
*/
Vector3f BasicWorldModel::getPlayerRelativePosSeenInTeam( vector<PlayerObject> team, Num num ) const
{
	return getVector3fInVector( VT_RELATIVE_POS_SEEN, team, num );
}

/*!
	get player's position  in sense relative to me
	\param isTeammate, indicate which team is the player in
	\param num, indicate the player's num
	\return relative position
*/
Vector3f BasicWorldModel::getPlayerRelativePosSeen( bool isTeammate, Num num ) const
{
	return  isTeammate?
			getTeammateRelativePos( num ):
			getOpponentRelativePos( num );
}

const FixedObject * BasicWorldModel::getFlagPtr( VisionObject flag ) const
{
	const FixedObject *flagPtr;
	switch ( flag )
	{
		case VO_FLAG1L :
			flagPtr = &_flag_1_l;
			break;
		case VO_FLAG1R :
			flagPtr = &_flag_1_r;
			break;
		case VO_FLAG2L :
			flagPtr = &_flag_2_l;
			break;
		case VO_FLAG2R :
			flagPtr = &_flag_2_r;
			break;
		case VO_GOAL1L :
			flagPtr = &_goal_1_l;
			break;
		case VO_GOAL1R :
			flagPtr = &_goal_1_r;
			break;
		case VO_GOAL2L :
			flagPtr = &_goal_2_l;
			break;
		case VO_GOAL2R :
			flagPtr = &_goal_2_r;
			break;
		default:
			return NULL;
	}
	return flagPtr;
}


bool BasicWorldModel::isThinkTime( const Time& time) const
{
	return ( find( _thinkTimeSet.begin(), _thinkTimeSet.end(), time) 
				!= _thinkTimeSet.end() );

}

/** 
calculate offside line 
\param isOur is Our or Opp?
\return the offside line
*/
float BasicWorldModel::calculateOffsideLine( bool isOur )
{	
	/** find the second nearst to the base line in the field */
	int sideF = 1;
	if ( !isOur ) sideF = -1;

	float lastX = 0;
	float last2X = 0; // the offside line minimum is 0
	float tmp;
	float baseLine = getOppBaseLine();
	for ( Num i=1; i<=players_num; i++)
	{
		tmp = sideF*getPlayerGlobalPos(!isOur,i).x();
		if ( tmp < baseLine && tmp > 0 )
		{
			if ( tmp > last2X )
			{
				swap( tmp, last2X );
			}
			if ( last2X > lastX )
			{
				swap( lastX, last2X );
			}
		}
	}
	// behind ball is not offside
	float ballX = sideF*getBallGlobalPos().x();
	if ( ballX > last2X )
		last2X = ballX;
	
	return last2X*sideF;
}

/** update the two offside lines
*/
void BasicWorldModel::updateOffSideLine()
{
	_ourOffSideLine = calculateOffsideLine(true);
	_oppOffSideLine = calculateOffsideLine(false);

}

bool BasicWorldModel::updateObjectVisionPosition( const std::string& obj, const Polar& pol)
{
	//-* try to lookup the VisionObject
	TVisionObjectMap::iterator iterVisionObject = _visionObjectMap.find(obj);
	if (iterVisionObject == _visionObjectMap.end())
	{
		LOGERR("unknown object: %s",obj.c_str());
		return false;
	}

	VisionObject vo = iterVisionObject->second;

	//-* update the vision map
	_visionMap[vo] = pol;
	LOG( 2,"success in update obj %s, pol ( %f, %f, %f)",obj.c_str(),pol.distance,pol.theta,pol.phi);
	return true;
}

bool BasicWorldModel::setPlayMode( const string& playMode )
{
	//-* try to lookup the play mode
	TPlayModeMap::iterator iter = _playModeMap.find(playMode);
	if ( iter != _playModeMap.end() )
	{
		_playMode = (TPlayMode)(*iter).second;
		return true;
	}
	else
	{
		LOGERR(	"[Error](BasicWorldModel) could not parse playmode: "+
					playMode+"\n" );
		return false;
	}
}

void BasicWorldModel::setTeamIndex( const string& team )
{
	//-* look up for team index
	if (team == "left")
        _teamIndex = TI_LEFT;
    else if (team == "right")
        _teamIndex = TI_RIGHT;
    else
	{
		_teamIndex = TI_NONE;
		LOGERR("(BasicWorldModel) received TeamIndex TI_NONE\n");
	}
}

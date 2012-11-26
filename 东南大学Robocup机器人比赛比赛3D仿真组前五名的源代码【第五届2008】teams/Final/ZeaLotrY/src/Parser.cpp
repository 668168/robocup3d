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

 
/**
 * \file           Parser.cpp
 *
 * \brief 解析S表达式/parse the sExp
 *
 *LastModify:
 * $Id: Parser.h,v 1.5 2006/01/27 03:18:51 xy Exp $
 */

#include "Geometry.h"
#include "Parser.h"

/**  解析器实例/Parser instance */
Parser seuparser;

Parser::Parser():
_bKnowOppName(false)//初始时刻不知道对手的队名/The agent doesn't know opponents' team name at the beginning.
{
	// 设置SEXP解析器的参数/set SEXP parser parmas
	set_parser_buffer_params(10,512);
}

bool Parser::parseAll( const std::string& msg )
{
	switch ( msg[0] )
	{
		case 'S':
			parseS( msg );
			break;
		
		case 'C':
			parseC( msg );
			break;
		
		case 'D' :
            break;
		
        case 'K' :
			//parseMsgK();
            break;
		
		case 'T' :
			parseT( msg );
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
            LOGERR("[Warning]received unknown data: "+msg+'\n');
            return false;
			break;
	}
	return true;
}

void Parser::parseS( const string& msg )
{
	int msgLen = msg.size();	
	char* c = const_cast<char*>(msg.c_str());
	_pcont = init_continuation(c);
 	destroy_sexp(_sexp);
	_sexp = iparse_sexp(c,msgLen,_pcont);
	while( _sexp != 0)
	{
		if ( _sexp->ty == SEXP_VALUE )
		{
			if ( 'S'== *(_sexp->val) )
			{
				WM->setSenseTime1(atof((_sexp->val)+1));
			}
			else
			{
				WM->setSenseTime2(atof(_sexp->val));
			}
		}
		else if ( _sexp->ty == SEXP_LIST )
		{
			sexp_t* tmp = _sexp->list;
			if ( tmp->ty == SEXP_VALUE )
			{
				LOG( 2,"parse %s Begin",tmp->val);
				switch ( *(tmp->val) )
				{
					case 'V'://Vision
						parseVision(tmp->next);
						LOG( 2,"parse Vision OK");
					break;
					case 'G'://GameState
						parseGameState(tmp->next);
						LOG( 2,"parse GameState OK");
					break;
					case 'A'://AgentState
						parseAgentState(tmp->next);
						LOG( 2,"parse AgentState OK");
					break;
					case 'h'://hear
						parseHear(tmp->next);
						LOG( 2,"parse hear OK");
					break;
					default:
						LOGERR( "Unknown message type: %s",	tmp->val );
					break;					
				}
			}
			
		}
	destroy_sexp(_sexp);
	_sexp = iparse_sexp(c,msg.size(),_pcont);
	}
	destroy_continuation(_pcont);
	LOG( 2, "successfully parse one message form server");
}

bool Parser::parseHear( const sexp_t* sexp )
{
	while ( sexp != 0 )
	{
		if ( sexp->ty == SEXP_VALUE )
		{
			std::cout<<'\t'<<sexp->val;
		}
		else if ( sexp->ty == SEXP_LIST )
		{
			std::cout<<"?";
			sexp = sexp->list;
		}
		else
		{
			std::cerr<<__FILE__<<__LINE__<<__FUNCTION__<<std::endl;
		}
		sexp = sexp->next;
	}
	return true;
}

bool Parser::parseVision( const sexp_t* sexp )
{
	while ( sexp != 0 )
	{
		if ( sexp->ty == SEXP_LIST )
		{
			sexp_t* tmp = sexp->list;
			if ( tmp->ty == SEXP_VALUE && parsePosition(tmp) )
			{
				LOG( 2, "updated one object");
			}
		}
		else
		{
			LOGERR("unknown value: %s",sexp->val);
		}
		sexp = sexp->next;
	}
	return true;
	//-* parse my pos when debug -- need more study
		/*if(name == "mypos")
    	{
        	++paramIter;
        	predicate.AdvanceValue(paramIter, _myDebugPos[0]);
        	predicate.AdvanceValue(paramIter, _myDebugPos[1]);
        	predicate.AdvanceValue(paramIter, _myDebugPos[2]);
			LOG(11,"mypos is %.3f %.3f %.3f", _myDebugPos[0], _myDebugPos[1], _myDebugPos[2]);
			continue;
    	}*/
}

//(GameState (time 0.09) (playmode KickOff_Left))
bool Parser::parseGameState( const sexp_t* sexp )
{
	while ( sexp !=0 )
	{
		sexp_t* tmp = sexp->list;
		switch ( *(tmp->val) )
		{
			case 't'://time team
			{
				switch ( *(tmp->val+1) )
				{
					case 'i'://time
						WM->setGameTime(atof(tmp->next->val));
					break;
					case 'e'://team
						WM->setTeamIndex(tmp->next->val);
					break;
					default:
						LOGERR("unknown value: %s",sexp->val);
					break;
				}
				break;
			}
			case 'p'://playmode
				WM->setPlayMode(tmp->next->val);
			break;
			case 'F'://FieldHeight FieldLength FieldWidth
			{
				switch ( *(tmp->val+5) )
				{
					case 'L'://FieldLength
						WM->setFieldLength(atof(tmp->next->val));
					break;
					case 'H'://FieldHeight
						WM->setFieldHeight(atof(tmp->next->val));
					break;
						case 'W'://FieldWidth
						WM->setFieldWidth(atof(tmp->next->val));
					break;
					default:
						LOGERR("unknown value: %s",sexp->val);
					break;
				}
				break;
			}
			case 'G'://GoalDepth GoalHeight GoalWidth
			{
				switch ( *(tmp->val+4) )
				{
					case 'D'://GoalDepth
						WM->setGoalDepth(atof(tmp->next->val));
					break;
					case 'H'://GoalHeight
						WM->setGoalHeight(atof(tmp->next->val));
					break;
					case 'W'://GoalWidth
						WM->setGoalWidth(atof(tmp->next->val));
					break;
					default:
						LOGERR("unknown value: %s",sexp->val);
					break;
				}
				break;
			}
			case 'A'://AgentRadius AgentMass AgentMaxSpeed
			{
				switch ( *(tmp->val+5) )
				{
					case 'R'://AgentRadius
						WM->setMyRadius(atof(tmp->next->val));
					break;
					case 'M'://AgentMass AgentMaxSpeed
					{
						switch ( *(tmp->val+7) )
						{
							case 's'://AgentMass
								WM->setMyMass(atof(tmp->next->val));
							break;
							case 'x'://AgentMaxSpeed
								WM->setMyMaxSpeed(atof(tmp->next->val));
							break;
							default:
								LOGERR("unknown value: %s",sexp->val);
							break;
						}
					}
					break;
					default:
						LOGERR("unknown value: %s",sexp->val);
					break;
				}
				break;
			}
			case 'B'://BallRadius BallMass BorderSize
			{
				switch ( *(tmp->val+4) )
				{
					case 'R'://BallRadius
						WM->setBallRadius(atof(tmp->next->val));
					break;
					case 'M'://BallMass
						WM->setBallMass(atof(tmp->next->val));
					break;
					case 'e'://BorderSize
						WM->setBorderSize(atof(tmp->next->val));
					break;
					default:
						LOGERR("unknown value: %s",sexp->val);
					break;
				}
				break;
			}
			case 'u'://unum
				WM->setMyNum(atoi(tmp->next->val));
			break;
			default:
				LOGERR("unknown value: %s",sexp->val);
			break;
		}
		sexp = sexp->next;
	}
	return true;
}

/*(AgentState
	(battery <battery level in percent>)
	(temp <temperature in degree>)
)*/
bool Parser::parseAgentState( const sexp_t* sexp )
{
	while ( sexp !=0 )
	{
		if ( sexp->ty == SEXP_LIST )
		{
			sexp_t* tmp = sexp->list;
			if ( tmp->ty == SEXP_VALUE && 0==strcmp(tmp->val,"battery") )
			{
				WM->setMyBattery(atof(tmp->next->val));
			}
			else if ( tmp->ty == SEXP_VALUE && 0==strcmp(tmp->val,"temp") )
			{
				WM->setMyTemp(atof(tmp->next->val));
			}
		}
		sexp = sexp->next;
	}
	return true;
}

bool Parser::parsePosition( const sexp_t* sexp )
{
	std::string objName = sexp->val;//player or flag
	Polar pol;
	sexp = sexp->next;

	sexp_t* tmp = sexp->list;
	
	if ( objName[0] == 'P' )
	{
		if ( !_bKnowOppName )
		{
			if ( strcmp(WM->getMyTeamName().c_str(),tmp->next->val) )
			{// set opp team name
				WM->setOppTeamName(tmp->next->val);
				_bKnowOppName=true;
			}
		}
		objName+=tmp->next->val;//team
		sexp=sexp->next;
		tmp = sexp->list;
	}
	
	if ( objName[0] != 'B' )
	{
		objName+=tmp->next->val;//id	
		sexp=sexp->next;
	}
	
	tmp = sexp->list;//pol
	
	tmp = tmp->next;
	pol.distance = atof(tmp->val);
	tmp = tmp->next;
	pol.theta = atof(tmp->val);
	tmp = tmp->next;
	pol.phi = atof(tmp->val);
	
	WM->updateObjectVisionPosition(objName,pol);
	return true;
}

void Parser::parseC( const std::string& msg )
{
	WM->setSenseTime2(atof(&msg[1])+WM->getRealTime());
	LOG( 2, "successfully parse C message form server");
}

void Parser::parseT( const std::string& msg )
{
	WM->setSenseTime2(atof(&msg[1]));
	LOG( 2, "successfully parse T message form server");
}

bool Parser::parseValue( const sexp_t* sexp, string& res )
{
	if ( sexp->ty == SEXP_VALUE )
	{
		res = sexp->val;
		return true;
	}
	return false;
}

bool Parser::parseValue( const sexp_t* sexp, int &res )
{
	if ( sexp->ty == SEXP_VALUE )
	{
		res = atoi(sexp->val);
		return true;
	}
	return false;
}

bool Parser::parseValue( const sexp_t* sexp, float &res )
{
	if ( sexp->ty == SEXP_VALUE )
	{
		res = atof(sexp->val);
		return true;
	}
	return false;
}

bool Parser::parseValue( const sexp_t* sexp, Vector3f &res )
{
	for ( int i=0;i<3;i++)
	{
		if ( sexp->ty != SEXP_VALUE )
		{
			return false;
		}
		res[i] = atof(sexp->val);
		sexp=sexp->next;
	}
	return true;
}

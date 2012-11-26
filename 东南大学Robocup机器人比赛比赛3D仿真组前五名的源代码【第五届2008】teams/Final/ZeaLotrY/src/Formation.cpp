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

#include "Formation.h"

extern string formations_fn;

Formation::Formation()
{
	_formationData.resize( teammates_num+1 );
	setupPlayerTypeMap();
}

Formation::~Formation()
{
}

void Formation::setupPlayerTypeMap()
{
	_PlayerTypeMap.clear();
	
	_PlayerTypeMap["PT_UNKNOWN"] 			= PT_UNKNOWN;
	_PlayerTypeMap["PT_GOALKEEPER"] 		= PT_GOALKEEPER;
	_PlayerTypeMap["PT_DEFENDER_CENTRAL"] 	= PT_DEFENDER_CENTRAL;
	_PlayerTypeMap["PT_DEFENDER_SWEEPER"] 	= PT_DEFENDER_SWEEPER;
	_PlayerTypeMap["PT_DEFENDER_WING"] 		= PT_DEFENDER_WING;
	_PlayerTypeMap["PT_MIDFIELDER_CENTER"] 	= PT_MIDFIELDER_CENTER;
	_PlayerTypeMap["PT_MIDFIELDER_SWEEPER"] = PT_MIDFIELDER_SWEEPER;
	_PlayerTypeMap["PT_MIDFIELDER_WING"] 	= PT_MIDFIELDER_WING;
	_PlayerTypeMap["PT_ATTACKER_WING"] 		= PT_ATTACKER_WING;
	_PlayerTypeMap["PT_ATTACKER_CENTRAL"] 	= PT_ATTACKER_CENTRAL;
	_PlayerTypeMap["PT_JOYSTICK"]			= PT_JOYSTICK;
}

bool Formation::openFile()
{
	return openFile( formations_fn );
}

bool Formation::openFile( std::string formations_fn )
{
	_file.open( formations_fn.c_str(), ios_base::in );
	if ( ! _file )
	{
		LOGERR("ERROR:(Formation)Can not open formation file : "+formations_fn);
		exit(0);
		return false;
	}
	cout<<"Load formation file : "<<formations_fn<<endl;
	return true;
}

string Formation::getLine()
{
	char msg[FORMATION_MAX_LINE_LENGTH];
	do
	{
		_file.getline( msg,FORMATION_MAX_LINE_LENGTH );
	}
	while ( msg[0] == '#' );//skip #........

	const string str = msg;
	return str;
}

string Formation::getOneFormation()
{
	string strFormation = "";
	unsigned int iLeft = 0;
	unsigned int iRight = 0;
	
	do
	{
		strFormation += getLine();
		string::iterator strBegin = strFormation.begin();
		string::iterator strEnd = strFormation.end();
		iLeft = std::count(strBegin,strEnd,'(');
		iRight = std::count(strBegin,strEnd,')');
		//LOG( 30,"(=%d )=%d",iLeft,iRight);
	}
	while ( iLeft > iRight );
	return strFormation;
}

string Formation::getFormationName( const string strFormation )
{
	/*PA->input(strFormation.c_str(),strFormation.c_str()+strFormation.size());
	string formationName = "";
	while ( !PA->isEnd() )
	{
		if ( PA->getNextParamValue("name",formationName) )
		{
			return formationName;
		}
		else
		{
			PA->gotoNext();
			PA->gotoNextLeftBracket();
		}
	}
	return formationName;*/
	string formationName = "";
	int len = strFormation.size();
	char* c = const_cast<char*>(strFormation.c_str());
	pcont_t* pcont = init_continuation(c);
 	sexp_t* sexp = iparse_sexp(c,len,pcont);
	sexp = sexp->list;
	sexp = sexp->next;
	if ( sexp->ty == SEXP_LIST )
	{
		sexp_t* tmp = sexp->list;
		if ( tmp->ty == SEXP_VALUE && 0==strcmp(tmp->val,"name") )
		{
			tmp = tmp->next;
			if ( tmp->ty == SEXP_VALUE )
			{
				formationName = tmp->val;
			}
		}
	}
	else
	{
		LOGERR("Unknown formation data! can't get the formation name!");
	}
	destroy_continuation(pcont);
	return formationName;
}

bool Formation::loadFormation( string formationName )
{
	string strFormation, thisFormationName;
	do
	{
		strFormation = getOneFormation();
		thisFormationName = getFormationName( strFormation );
		if ( _file.eof() )
			return false;
	}
	while( thisFormationName != formationName );

	return loadFormationData( strFormation );
}

bool Formation::loadFormationData( const string strFormation )
{
	int len = strFormation.size();	
	char* c = const_cast<char*>(strFormation.c_str());
	pcont_t* pcont = init_continuation(c);
 	sexp_t* sexp = iparse_sexp(c,len,pcont);
	sexp = sexp->list;
	sexp = sexp->next;
	sexp = sexp->next;
	while ( sexp != 0 )
	{
		if (sexp->ty == SEXP_LIST)
		{
			sexp_t* tmp = sexp->list;
			if ( tmp->ty == SEXP_VALUE && 0==strcmp(tmp->val,"player") )
			{
				loadOnePlayerFormation(tmp);
			}
		}
		sexp = sexp->next;
	}
	
	destroy_continuation(pcont);
	return true;
}

bool Formation::loadOnePlayerFormation( const sexp_t* sexp )
{
	int num = 0;
	string strPlayerType("PT_UNKNOWN"),strBehindBall("no");
	FormationData tmpData;
	sexp = sexp->next;
	while ( sexp != 0 )
	{
		if (!( Parser::parseGivenValue(sexp,"num",num)
			|| Parser::parseGivenValue(sexp,"playerType",strPlayerType)
			|| Parser::parseGivenValue(sexp,"initPos",tmpData._initPos)
			|| Parser::parseGivenValue(sexp,"homePos",tmpData._homePos)
			|| Parser::parseGivenValue(sexp,"attraction",tmpData._attraction)
			|| Parser::parseGivenValue(sexp,"behindBall",strBehindBall)
			|| Parser::parseGivenValue(sexp,"minPos",tmpData._minPos)
			|| Parser::parseGivenValue(sexp,"maxPos",tmpData._maxPos)
		))
		{
				LOGERR("Unknown value !");
				return false;
		}
		if ( strBehindBall == "yes" )
				tmpData._behindBall = true;
			else
				tmpData._behindBall = false;
		//-* try to look up the PlayerType
		TPlayerTypeMap::iterator iterPlayerType = _PlayerTypeMap.find(strPlayerType);
        if ( iterPlayerType != _PlayerTypeMap.end() )
        {
            tmpData._PlayerType = (*iterPlayerType).second;
        }
			
		//-* update the data
        _formationData[num] = tmpData;
		
		sexp = sexp->next;
	}
	return true;
}
/*
bool Formation::loadFormationData()
{
	while ( !PA->isEnd() )
	{
		//-* read the data name
		string name = "";
        if ( !PA->getNextParamName(name) )
        {
			PA->gotoNextLeftBracket();
            continue;
        }

		if ( name == "player" )
		{
			//-* try read the 'num' section
    		int num;
			string strBehindBall,strPlayerType;
			FormationData tmpData;
			if ( ( !PA->getNextParamValue("num",num) )
				||( !PA->getNextParamValue("playerType",strPlayerType) )
				||( !PA->getNextParamValue("initPos",tmpData._initPos) )
				||( !PA->getNextParamValue("homePos",tmpData._homePos) )
				||( !PA->getNextParamValue("attraction",tmpData._attraction) )
				||( !PA->getNextParamValue("behindBall",strBehindBall) )
				||( !PA->getNextParamValue("minPos",tmpData._minPos) )
				||( !PA->getNextParamValue("maxPos",tmpData._maxPos) )		
				)
			{
				LOGERR("can not parse formation Error!");
				continue;
			}
			if ( strBehindBall == "yes" )
				tmpData._behindBall = true;
			else
				tmpData._behindBall = false;
			//-* try to look up the PlayerType
			TPlayerTypeMap::iterator iterPlayerType = _PlayerTypeMap.find(strPlayerType);
        	if ( iterPlayerType != _PlayerTypeMap.end() )
        	{
            	tmpData._PlayerType = (*iterPlayerType).second;
        	}
			
			//-* update the data
        	_formationData[num] = tmpData;
		}
		PA->gotoNextLeftBracket();
	}
	return true;
}
*/
Vector3f Formation::getInitPosition( unsigned int num )
{
	return _formationData[num]._initPos;
}

PlayerType Formation::getPlayerType( unsigned int num ) const
{
	return _formationData[num]._PlayerType;
}

PlayerType Formation::getMyType() const
{ 
	return getPlayerType(WM->getMyNum());
}

Vector3f Formation::getStrategicPosition( unsigned int num, Vector3f posBall )
{
	const float fieldLength = WM->getFieldLength();
	const float fieldWidth = WM->getFieldWidth();
	const float factorFieldLength = fieldLength/max_field_length;
	const float factorFieldWidth = fieldWidth/max_field_width;
	Vector3f homePos = _formationData[num]._homePos;
	Vector3f attraction = _formationData[num]._attraction;
	Vector3f posStrategic;
	posStrategic[0] = ( homePos[0] + posBall[0]*attraction[0] )*factorFieldLength;
	posStrategic[1] = ( homePos[1] + posBall[1]*attraction[1] )*factorFieldWidth;
	//-* set max and min
	Vector3f minPos = _formationData[num]._minPos;
	Vector3f maxPos = _formationData[num]._maxPos;
	posStrategic[0] = setMaxNMin( posStrategic[0], maxPos[0], minPos[0]);
	posStrategic[1] = setMaxNMin( posStrategic[1], maxPos[1], minPos[1]);
	//-* behind ball
	if ( _formationData[num]._behindBall )
	{
		posStrategic[0] = setMaxNMin( posStrategic[0], posBall[0]-2, -fieldLength/2);
	}
	//-* set in field and not offside
	//posStrategic[0] = setMaxNMin(posStrategic[0], WM->getOurOffSideLine(), -fieldLength/2);
	posStrategic[0] = setMaxNMin(posStrategic[0], fieldLength/2, -fieldLength/2);
	posStrategic[1] = setMaxNMin(posStrategic[1], fieldWidth/2, -fieldWidth/2);
	posStrategic[2] = 0.22;
	
	LOG( 30,"posStrategic: %f, %f, %f",posStrategic[0],posStrategic[1],posStrategic[2]);
	return posStrategic;
}

/*****************************************************************************************
 *                                      SEU-3D
 *                     -------------------------------------------------
 * Copyright (c) 2005, Yuan XU<xychn15@yahoo.com.cn>,Chang'e SHI<evelinesce@yahoo.com.cn>
 * Copyright (c) 2006, Yuan XU<xuyuan.cn@gmail.com>,Chunlu JIANG<JamAceWatermelon@gmail.com>
 * Southeast University ,China
 * All rights reserved.
 *
 * $Id: LogData.cpp,v 1.1.1.1 2006/09/15 02:03:06 Administrator Exp $
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
 * \flie           LogData.cpp
 *
 * \brief the data struct of agent state from agent's log
 *
 */

#include "LogData.h"
#include "Parser.h"

LogPrint::LogPrint(const string& str):
_str(str),
_colored(false)
{
}

LogPrint::LogPrint(const string& str, const Vector3f& rgb):
_str(str),
_colored(true),
_rgb(rgb)
{
}

LogPrint::LogPrint(const sexp_t* sexp)
{
	if( !sexp || SEXP_LIST != sexp->ty )return;
	const sexp_t* tmp = sexp->list;
	while( tmp && SEXP_VALUE == tmp->ty )
	{
		string tmpStr;
		if( !Parser::parseValue(tmp,tmpStr) )return;
		_str+=tmpStr;
		_str+=' ';
		tmp=tmp->next;
	}
	sexp=sexp->next;
	if ( !sexp || !sexp->next || !sexp->next->next )
	{
		_colored= false;
	}
	else
	{
		_colored = Parser::parseValue(sexp,_rgb);
	}
}

void LogPrint::print(std::ostream& ost)const
{
	ost<<"(P ("<<_str<<')';
	if ( _colored ) ost<<' '<<_rgb;
	ost<<')';
}

LogText::LogText(const Vector3f& pos,const string& str):
_pos(pos),
_str(str),
_colored(false)
{
}

LogText::LogText(const Vector3f& pos,const string& str, const Vector3f& rgb):
_pos(pos),
_str(str),
_colored(true),
_rgb(rgb)
{
}

LogText::LogText(const sexp_t* sexp)
{
	if( !Parser::parseValue(sexp,_pos) )return;
	
	sexp=sexp->next->next->next;
	if( !sexp || SEXP_LIST != sexp->ty )return;
	const sexp_t* tmp = sexp->list;
	while( tmp && SEXP_VALUE == tmp->ty )
	{
		string tmpStr;
		if( !Parser::parseValue(tmp,tmpStr) )return;
		_str+=tmpStr;
		_str+=' ';
		tmp=tmp->next;
	}
	sexp=sexp->next;
	if ( !sexp || !sexp->next || !sexp->next->next )
	{
		_colored= false;
	}
	else
	{
		_colored = Parser::parseValue(sexp,_rgb);
	}
}

void LogText::print(std::ostream& ost)const
{
	ost<<"(T "<<_pos<<"("<<_str<<')';
	if ( _colored ) ost<<' '<<_rgb;
	ost<<')';
}

LogShpere::LogShpere(const Vector3f& pos,float r):
_pos(pos),
_r(r),
_colored(false)
{
}

LogShpere::LogShpere(const Vector3f& pos,float r,const Vector3f& rgb):
_pos(pos),
_r(r),
_colored(true),
_rgb(rgb)
{
}

LogShpere::LogShpere(const sexp_t* sexp)
{
	if( !Parser::parseValue(sexp,_pos) )return;
	sexp=sexp->next->next->next;
	if( !Parser::parseValue(sexp,_r) )return;
	sexp=sexp->next;
	if ( !sexp || !sexp->next || !sexp->next->next )
	{
		_colored= false;
	}
	else
	{
		_colored = Parser::parseValue(sexp,_rgb);
	}
}

void LogShpere::print(std::ostream& ost)const
{
	ost<<"(S "<<_pos<<' '<<_r;
	if ( _colored ) ost<<' '<<_rgb;
	ost<<')';
}

LogRectangle::LogRectangle(const Vector3f& pos,float szX, float szY):
_pos(pos),
_szX(szX), _szY(szY),
_flag(0)
{
	_rotation.Zero();
}

LogRectangle::LogRectangle(const Vector3f& pos,float szX, float szY, const Vector3f& rotation):
_pos(pos),
_szX(szX), _szY(szY),
_flag(1),
_rotation(rotation)
{
}

LogRectangle::LogRectangle(const Vector3f& pos,float szX, float szY, const Vector3f& rotation, const Vector3f& rgb):
_pos(pos),
_szX(szX), _szY(szY),
_flag(2),
_rotation(rotation),
_rgb(rgb)
{
}

LogRectangle::LogRectangle(const sexp_t* sexp)
{
	if( !Parser::parseValue(sexp,_pos) )return;
	sexp=sexp->next->next->next;
	if( !Parser::parseValue(sexp,_szX) )return;
	sexp=sexp->next;
	if( !Parser::parseValue(sexp,_szY) )return;
	sexp=sexp->next;
	if ( !sexp || !sexp->next || !sexp->next->next )
	{
		_flag= 0;
	}
	else
	{
		Parser::parseValue(sexp,_rotation);
		sexp = sexp->next->next->next;
		if ( !sexp || !sexp->next || !sexp->next->next )
		{
			_flag = 1;
		}
		else
		{
			_flag = 2;
			Parser::parseValue(sexp,_rgb);
		}
	}
}

void LogRectangle::print(std::ostream& ost)const
{
	ost<<"(R "<<_pos<<' '<<_szX<<' '<<_szY;
	if ( _flag > 0 ) ost<<' '<<_rotation;
	if ( _flag > 1 ) ost<<' '<<_rgb;
	ost<<')';
}

LogCircle::LogCircle(const Vector3f& pos,float r):
_pos(pos),
_r(r),
_flag(0)
{
}

LogCircle::LogCircle(const Vector3f& pos,float r, const Vector3f& rotation):
_pos(pos),
_r(r),
_flag(1),
_rotation(rotation)
{
}

LogCircle::LogCircle(const Vector3f& pos,float r, const Vector3f& rotation, const Vector3f& rgb):
_pos(pos),
_r(r),
_flag(2),
_rotation(rotation),
_rgb(rgb)
{
}

LogCircle::LogCircle(const sexp_t* sexp)
{
	if( !Parser::parseValue(sexp,_pos) )return;
	sexp=sexp->next->next->next;
	if( !Parser::parseValue(sexp,_r) )return;
	sexp=sexp->next;
	if ( !sexp || !sexp->next || !sexp->next->next )
	{
		_flag= 0;
	}
	else
	{
		Parser::parseValue(sexp,_rotation);
		sexp = sexp->next->next->next;
		if ( !sexp || !sexp->next || !sexp->next->next )
		{
			_flag = 1;
		}
		else
		{
			_flag = 2;
			Parser::parseValue(sexp,_rgb);
		}
	}
}

void LogCircle::print(std::ostream& ost)const
{
	ost<<"(C "<<_pos<<' '<<_r;
	if ( _flag > 0 ) ost<<' '<<_rotation;
	if ( _flag > 1 ) ost<<' '<<_rgb;
	ost<<')';
}


LogLine::LogLine(const Vector3f& x0,const Vector3f& x1):
_x0(x0),_x1(x1),
_flag(0)
{
}

LogLine::LogLine(const Vector3f& x0,const Vector3f& x1, const Vector3f& rgb):
_x0(x0),_x1(x1),
_flag(1),
_rgb(rgb)
{
}

LogLine::LogLine(const sexp_t* sexp)
{
	if( !Parser::parseValue(sexp,_x0) )return;
	sexp=sexp->next->next->next;
	if( !Parser::parseValue(sexp,_x1) )return;
	sexp=sexp->next->next->next;
	if ( !sexp || !sexp->next || !sexp->next->next )
	{
		_flag= 0;
	}
	else
	{
		Parser::parseValue(sexp,_rgb);
		_flag = 1;
	}
}

void LogLine::print(std::ostream& ost)const
{
	ost<<"(L "<<_x0<<' '<<_x1;
	if ( _flag > 0 ) ost<<' '<<_rgb;
	ost<<')';
}

void LogInfo::clear()
{
	vector<LogData*>::const_iterator iter(_data.begin()),end(_data.end());
	for(; iter!=end; ++iter)
	{
		delete (*iter);
	}
	_data.clear();
}

void LogLevel::clear()
{
	map<int, LogInfo>::iterator iter(_data.begin()),end(_data.end());
	for(; iter!=end; ++iter)
	{
		iter->second.clear();
	}
	_data.clear();
}

const static LogInfo ghostLogInfo;
LogInfo& LogLevel::operator[](int i)
{
	map<int, LogInfo>::iterator iter = _data.find(i);
	if ( iter == _data.end() )
	{
		insert(i,ghostLogInfo);
		iter = _data.find(i);
	}
	return iter->second;
}

const LogInfo& LogLevel::operator[](int i)const
{
	map<int, LogInfo>::const_iterator iter = _data.find(i);
	if ( iter == _data.end() ) return ghostLogInfo;
	return iter->second;
}

std::ostream& operator<<(std::ostream& ost, const LogInfo& v)
{
	vector< LogData* >::const_iterator iter(v._data.begin()),end(v._data.end());
	for( ; iter!=end; ++iter )
	{
		(*iter)->print(ost);
	}
	return ost;
}

std::ostream& operator<<(std::ostream& ost, const LogLevel& v)
{
	map<int, LogInfo>::const_iterator iter(v._data.begin()),end(v._data.end());
	for(; iter!=end; ++iter )
	{
		ost<<'('<<iter->first<<' '<<iter->second<<')';
	}
	return ost;
}

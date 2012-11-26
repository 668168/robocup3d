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
 * @flie           Action.h
 *
 * @brief 对agent基本动作的封装/the wrapper of agent's basic actions
 *
 *LastModify:
 * $Id: Action.h,v 1.1.1.1 2006/09/15 02:03:05 Administrator Exp $
 */
 
#ifndef _ACTION_H
#define _ACTION_H

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#include "Settings.h"
#include <set>
#include <map>
#include "Geometry.h"

using namespace salt;

/** 枚举基本动作/enum all the basic actions */
enum BasicActionType
{
	BAT_ILLEGAL	=	0,/**<  非法动作 */
	
	BAT_DRIVE	=	1,/**<  跑/drive */
	BAT_KICK	=	2,/**<  踢/kick */
	BAT_BEAM	=	4,/**<  传送/beam */
	BAT_PANTILT =	5,/**<  转头/pantilt */
	BAT_SAY     =	6,/**<  说/say */
	BAT_CATCH	=	7 /**<	抓球(守门员[1号])/catch the ball(only the goalie[num 1]) */
};

struct BasicActionData
{
	Vector3f _vec;
	//string _msg;
	BasicActionData(){};
	BasicActionData( const Vector3f& vec ):_vec(vec){};
	//BasicActionData( const string& msg ):_msg(msg){};
};

/*************************************************************/
/********************* ACTION ********************************/
/*************************************************************/
class Action
{
public:
	typedef std::map<BasicActionType, BasicActionData> ActionMap;

	/*===========================*/
	/* 公有函数/Public Functions  */
	/*===========================*/
	
	/** 缺省构造函数/default Constructor */
	explicit Action():_time(0){};
	
	/** 析构函数/Destructors */
	~Action(){}
	
	
	/** @name 设置动作/set the action */
	
	/** 设置动作执行的时间/set the action execution time */
	void setTime( Time time ){ _time = time; }
	
	/** 设置为drive动作 */
	void setDriveForce( const Vector3f& driveForce )
	{ _action[BAT_DRIVE] = BasicActionData(driveForce); }
	
	/** 设置为kick动作 */
	void setKick( AngDeg kickAngle, float kickForce )
	{ _action[BAT_KICK] = BasicActionData(Vector3f(kickAngle,kickForce,0.0f)); }
	
	/** 设置kick力量,如果该动作存在的话  */
	bool setKickForce( float kickForce )
	{ ActionMap::iterator iter = _action.find(BAT_KICK);
		if ( iter == _action.end() ) return false;
		iter->second._vec.y() = kickForce; return true;}
	
	/** 设置kick竖直角度,如果该动作存在的话  */
	bool setKickAng	( AngDeg kickAngle )
	{ ActionMap::iterator iter = _action.find(BAT_KICK);
		if ( iter == _action.end() ) return false;
		iter->second._vec.x() = kickAngle; return true;}
	
	/** 设置为beam动作 */
	void setBeam( const Vector3f& driveForce )
	{ _action[BAT_BEAM] = BasicActionData(driveForce); }
		
	/** 设置为pantilt动作 */
	void setPanTiltDelta( AngDeg panDelta, AngDeg tiltDelta )
	{ _action[BAT_PANTILT] = BasicActionData(Vector3f(panDelta,tiltDelta,0.0f)); }
	
	/** 设置pantilt水平角度改变,如果该动作存在的话 */
	bool setPanDelta( AngDeg panDelta )
	{ ActionMap::iterator iter = _action.find(BAT_PANTILT);
		if ( iter == _action.end() ) return false;
		iter->second._vec.x() = panDelta; return true;}
	
	/** 设置pantilt水平角度改变,如果该动作存在的话 */
	bool setTiltDelta( AngDeg tiltDelta )
	{ ActionMap::iterator iter = _action.find(BAT_PANTILT);
		if ( iter == _action.end() ) return false;
		iter->second._vec.y() = tiltDelta; return true;}
	
	/** 设置为say动作 */
	void setSay()
	{ _action[BAT_SAY] = BasicActionData(); }
	
	/** 设置为catch动作 */
	void setCatch()
	{ _action[BAT_CATCH] = BasicActionData(); }
		
	/** @name 获取动作相关信息/get the info of the action */
	
	/** 获取动作执行时间/get the action execution time */
	Time getTime()const { return _time; }
	
	/** 获取drive力量 */
	const Vector3f& getDriveForce() const
	{ ActionMap::const_iterator iter = _action.find(BAT_DRIVE);
		if ( iter == _action.end() ) return vector3f_illegal;
		return iter->second._vec; }
	
	/** 获取kick竖直角度 */
	AngDeg getKickAngle()const
	{ ActionMap::const_iterator iter = _action.find(BAT_KICK);
		if ( iter == _action.end() ) return max_kick_angle;
		return iter->second._vec.x(); }
	
	/** 获取kick力量 */
	float getKickForce()const
	{ ActionMap::const_iterator iter = _action.find(BAT_KICK);
		if ( iter == _action.end() ) return max_kick_force;
		return iter->second._vec.y(); }
	
	/** test if execute the kick action
	 *  @param[in] t the test time
	 *  @return boolen indicates if kicking
	 */
	bool isKicking()const { return _action.find(BAT_KICK)!=_action.end(); }
	
	//AngDeg		getPanDelta()	const { return _panDelta; }
	//AngDeg		getTiltDelta()	const { return _tiltDelta; }
	
	/** 获取动作map的首迭代器/get the begin const_iterator of the action map */
	ActionMap::const_iterator begin()const{ return _action.begin(); }
	
	/** 获取动作map的尾迭代器/get the end const_iterator of the action map */
	ActionMap::const_iterator end()const{ return _action.end(); }
		
	/** @name 重载操作符/overload operators */
	Action operator+ ( const Action &anotherAction ) const;
	Action& operator+= ( const Action &anotherAction);
	Action& operator-= ( const BasicActionType type);
	
	/** 下面这些函数不推荐使用,只是为了兼容旧的代码 */
	//void setActionType ( ActionT type ) const{;}
		
private:
	/*===========================*/
	/* 私有成员/Private Attributes */
	/*===========================*/

	/** 动作执行的时间/the action execution time */
	Time	 	_time;

	/** 动作所需要的数据 */
	ActionMap _action;

};


/*************************************************************/
/********************* ACTION DEQUE **************************/
/*************************************************************/
class ActionDeque
{
private:
	deque<Action> _actions;

public:
	ActionDeque(){};
	ActionDeque(const Action& act){ pushAction(act); }

	void			pushAction( const ActionDeque &actions);
	void			pushAction( const Action &a );
	const Action&	getAction( Time time )const;
	set<Time>		getActionDequeTime()const;
	bool			popAction( Time time, Action& action );
	Action			popAction();
	bool			isIncludeTime( Time time)const;
	bool			isEmpty() const;
	const deque<Action>&	get() const { return _actions; }
	ActionDeque& operator= ( const ActionDeque &another );
	template < class T >
	ActionDeque& operator+= ( const T &newAction ) { pushAction(newAction); return *this; }
	
	/** 移除所有该类型的动作/remove all the type of aciton */
	ActionDeque& operator-= ( BasicActionType type );
	
	/** remove the action before the given time */
	ActionDeque& operator-= ( Time t );
	
	bool			removeNoNeedAction(bool isKickable);
	
	/** test if execute the kick action
	 *  @param[in] t the test time
	 *  @return boolen indicates if kicking
	 */
	bool isKicking(Time t)const;
};

typedef ActionDeque Actions;

#endif /* _ACTION_H */

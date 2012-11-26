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
 * \file            Agent.h
 *
 * \brief agent基类/the basic agent class.
 *
 *
 * 实现agent的基本动作,以及初始化,感知-思考-动作的主循环
 *
 * LastModify:
 * $Id: Agent.h,v 1.1.1.1 2006/09/15 02:03:05 Administrator Exp $
 */
 
#ifndef _AGENT_H
#define _AGENT_H

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#include "WorldModel.h"
#include "commserver.h"
#include "Action.h"
#include "Skill.h"

class Agent
{
public:
    Agent();
    virtual ~Agent();

    void processInitMessage();
    void processThinkTimeMessage();

	/** 处理'O'信息 */
	void processOMessage(const std::string& msg);

    void think();
	virtual void playMatch() = 0;
	virtual void init() = 0;

    static std::string doneThinkingMessage() { return "D"; }
    static std::string doneInitMessage() { return "I"; }
    static std::string requestThinkTimeMessage() { return "C"; }

	
	
	void setTeamName( string teamName ) { _teamName = teamName; }
	void setTeamUnum( int teamUnum ) { _teamUnum = teamUnum; }
	void requestTimeNotify( int t);
	void sendThinkTimeNotifys();
	void sendActionNotifys();
	void sendAction( const Time t );
	void endThink();

private:

	/** @name  agent的基本动作/basic action of agent */
	void createAgent();
	void initAgent();
	void kick(float angle, float power);
	void beam(const salt::Vector3f& position);
    void drive(const salt::Vector3f& driveVec);
	void say(const string &msg);
	void goalieCatch();
	void sendBasicAction(const BasicActionType type, const BasicActionData& data );

	void done();


	void sendAction( const Action& a);

protected:
	template < class T >
	void putActionInQueue( const T &action)
	{
		_actionQueue.pushAction( action);
	}

    const salt::Vector3f& getDriveVec() { return _driveVec; }

protected:
	
	set<Time> _requestedTime;

	int _minLatecy,_maxLatecy;

	/** the team name the agent uses with the init effector */
    std::string _teamName;

    /** the uniform number the agent uses with the init effector. If
        left to zero, the server will allocate the next free number */
    int _teamUnum;

    /** the number of received sensations */
    int _sensationCount;

    /** the state of the Drive effector */
    salt::Vector3f _driveVec;

	bool _panTilted;

	/** the action of current time */
	ActionDeque _actionQueue;
	
	/** actions string */
	stringstream _actSS;
};

#endif /* _AGENT_H */

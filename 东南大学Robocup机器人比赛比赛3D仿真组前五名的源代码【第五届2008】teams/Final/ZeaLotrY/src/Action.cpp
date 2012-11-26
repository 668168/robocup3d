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

 
#include "Action.h"

using namespace std;
/*************************************************************/
/********************* ACTION ********************************/
/*************************************************************/
/*! make the two actions to one
	if the two action has different values
	set the result to the *anotherAction*
	\param another action
	\return the unite action
*/
Action Action::operator+ ( const Action &anotherAction ) const
{
	Action uniteAction(*this);
	return uniteAction+=anotherAction;
}

Action& Action::operator+= ( const Action &anotherAction)
{
	setTime( anotherAction.getTime() );
	ActionMap::const_iterator iter(anotherAction.begin()), end(anotherAction.end());
	
	for( ;iter!=end;iter++ )
	{
		_action[iter->first] = iter->second;
	}
	
	return *this;
}

Action& Action::operator-= ( const BasicActionType type)
{
	_action.erase(type);
	return *this;
}

/*************************************************************/
/********************* ACTION DEQUE **************************/
/*************************************************************/
/*! push a action into the action queue
	if the new action's time is the same as the quene's action
	unite the two action
	\param the action which will be push
*/
void ActionDeque::pushAction( const Action &a )
{
	Action act;
	popAction( a.getTime(), act );
	act += a;
	
	pushDequeValue( _actions, act, max_action_num_in_queue);
}

/*! push actions into the action quene
*/
void ActionDeque::pushAction( const ActionDeque &actions)
{
	ActionDeque newActions = actions;
	while ( !newActions.isEmpty() )
	{
		pushAction( newActions.popAction());
	}
}

const static Action illegal_action;//-* define an illegal Action

const Action& ActionDeque::getAction( Time time )const
{
	deque< Action >::const_iterator iter ;
	for ( iter = _actions.begin(); iter != _actions.end(); ++iter)
	{
		if ( iter->getTime() == time )
			return *iter;
	}

	return illegal_action;
}

set<Time> ActionDeque::getActionDequeTime()const
{
	set<Time> t;
	deque< Action >::const_iterator iter ;
	for ( iter = _actions.begin(); iter != _actions.end(); ++iter)
	{
		t.insert( iter->getTime());
	}
	return t;
}

Action ActionDeque::popAction()
{
	if ( isEmpty() )
		return illegal_action;
	deque< Action >::iterator iter = _actions.begin();
	Action action;
	action = *iter;
	_actions.erase( iter);
	return action;
}

bool ActionDeque::popAction( Time time, Action& action )
{
	deque< Action >::iterator iter ;
	for ( iter = _actions.begin(); iter != _actions.end(); ++iter)
	{
		if ( iter->getTime() == time )
		{
			action = *iter;
			_actions.erase( iter);
			return true;
		}
	}

	return false;
}

bool ActionDeque::isIncludeTime( Time time)const
{
	deque< Action >::const_iterator iter ;
	for ( iter = _actions.begin(); iter != _actions.end(); ++iter)
	{
		if ( iter->getTime() == time )
			return true;
	}

	return false;
}

/*! return is there an action in the queue
*/
bool ActionDeque::isEmpty() const
{
	return _actions.empty();
}

ActionDeque& ActionDeque::operator= ( const ActionDeque &another )
{
	_actions = another.get();
	return *this;
}

ActionDeque& ActionDeque::operator-= ( BasicActionType type )
{
	for ( deque<Action>::iterator iter = _actions.begin(); iter!=_actions.end();++iter )
	{
		(*iter)-=type;
	}
	return *this;
}

/*!
remove no need action frome the queue.
ie. if is not kickable , so kick action will be removed
\return boolen indicate that is erase any action
*/
bool ActionDeque::removeNoNeedAction(bool isKickable)
{
	if ( !isKickable )
	{
		for ( deque<Action>::iterator iter = _actions.begin(); iter!=_actions.end();++iter )
		{
			(*iter)-=BAT_KICK;
		}
		return true;
	}
	
	return false;
}

/** remove the action before the given time */
ActionDeque& ActionDeque::operator-=( Time t )
{
	for ( deque<Action>::iterator iter = _actions.begin(); iter!=_actions.end(); )
	{
		if ( iter->getTime() == t )
		{
			_actions.erase( iter);
		}
		else
		{
			++iter;
		}
	}
	return *this;
}

bool ActionDeque::isKicking(Time t)const
{
	const Action& act = getAction(t);
	return act.isKicking();
}

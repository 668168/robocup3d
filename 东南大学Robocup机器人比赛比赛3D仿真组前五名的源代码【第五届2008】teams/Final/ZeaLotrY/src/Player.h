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

 
#ifndef _PLAYER_H
#define _PLAYER_H


#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#include "BasicPlayer.h"
#include "Formation.h"

class Player : public BasicPlayer,public Singleton<Player>
{
public:
	Player();
	~Player();
	virtual void init(){};

protected:
	virtual void playPlayOn();
	void goaliePlayOn();
	void defenderPlayOn();
	void midfielderSweeperPlayOn();
	void midfielderAttackPlayOn();
	void attackerPlayOn();
	void defaultPlayOn();

protected:
//////////////////// TEST /////////////////////
	//test 2005-11-04-by-XuYuan
	void testIntercept();
	void testTurnCycle();
	void testSkill();

};

#define PL Player::GetSingletonPtr()

#endif /* _PLAYER_H */

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

 
#ifndef _BASICPLAYER_H
#define _BASICPLAYER_H

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#ifdef JOYSTICK
#include <SDL/SDL.h>
#endif /* JOYSTICK */
#include "Agent.h"


class BasicPlayer: public Agent
{
protected:


public:
    BasicPlayer();
    virtual ~BasicPlayer();

    virtual void playMatch();

protected:
    void playBeforeKickOff();
    void playKickOff();
    void playMyKickOff();
    void playTheirKickOff();
    virtual void playPlayOn();
    void playKickIn();
    void playMyKickIn();
    void playTheirKickIn();
	void playCornerKick();
	void playMyCornerKick();
	void playTheirCornerKick();
	void playGoalKick();
	void playMyGoalKick();
	void playTheirGoalKick();
	/** offside mode */
	void playOffsideKick();
	void playMyOffsideKick();
	void playTheirOffsideKick();

	/** -------- training mode -----------*/
#ifdef TRAINING_MODE
	void playTraining();
#endif /* TRAINING_MODE */

#ifdef JOYSTICK
//////////// Joystick Player //////////////////
	bool setupJoystick();
	void reomveJoystick();
	void joystickPlay();
private:
	SDL_Joystick *joystick;
	bool isJoystickLive;
#endif /* JOYSTICK */

};


#endif /* _BASICPLAYER_H */

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

 
#include "BasicPlayer.h"
#include "Formation.h"

/**
	this file include some training functions matched with Trainer's training
*/
#ifdef TRAINING_MODE

void BasicPlayer::playTraining()
{
	Actions trainAction;
#ifdef TRAINING_PASS
	/** training pass
		player1 will kick the ball.
		player2 will intercept the ball.
	*/
	if ( WM->isFastestOur() )
	{
		Num teammateNum = WM->getMyNum()+1;
		if ( teammateNum > 11 ) teammateNum = 10;
		trainAction += _skill.safePass( _skill.selectPass(teammateNum) );
	}
	else
	{
		trainAction += _skill.runStrategicPos();
	}
	
	
#endif /* TRAINING_PASS */
	
	putActionInQueue(trainAction);
}

#endif /* TRAINING_MODE */

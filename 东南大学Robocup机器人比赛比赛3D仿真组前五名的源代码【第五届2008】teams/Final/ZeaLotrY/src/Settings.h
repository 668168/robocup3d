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

 
#ifndef _SETTINGS_H
#define _SETTINGS_H

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#include <salt/vector.h> // for need the Vector3f


using namespace salt;
using namespace std;

typedef float Time;		// Type definition for Time in 10ms
typedef float Second;	// Type definition for Time in sencond
typedef unsigned short int Step; // Type definition for simulate step num
typedef float AngRad;  // Type definition for angles in degrees. 
typedef float AngDeg;  // Type definition for angles in radians. 
typedef unsigned short int Num; // Type definition for palyer's number.

//////////////////////////// DEFINES /////////////////////////////
/* Define if you want to use joystick, 	but the need-memory will be more bigger */
//#define JOYSTICK

/* Define if you want the player and Trainer training together */ 
//#define TRAINING_MODE

#ifdef TRAINING_MODE
/* Define which do you want to train */
#define TRAINING_PASS

#endif /* TRAINING_MODE */

///////////////////// Log System ////////////////////////////////
/* Define ENABLE_LOG if you want to use the log system */
//#define ENABLE_LOG //-* Log switch
#define ENABLE_GL_LOG


const unsigned int MAX_LOG_LINE = 3072; //-*  maximum size of a log message
#ifdef ENABLE_LOG
const int MIN_LOG_LEVEL = 0;
const int MAX_LOG_LEVEL = 100;
#endif

///////////////////// CommServer ////////////////////////////////
const unsigned int default_read_buffer_size = 1024;

///////////////////// Action ////////////////////////////////////
const unsigned int max_action_num_in_queue = 40;

const unsigned int step_num_per_kick = 5;

///////////////////// Object ////////////////////////////////////
const unsigned int max_vision_history_num = 3; //-* the max record number of the history vision data of an object

const unsigned int max_data_history_num = 20*max_vision_history_num; //-* the max record number of the history data of an object
											//-- at least 3; [0]:current,[1]last,...

//-* set illegal values
const Time time_illegal = -1; //-* the time can be this value
							  //-- so, if time vaules this, the time is illegal

const Vector3f vector3f_illegal(10000,0,0);//( -10000,-10000,-10000);//-* the Z can not be minus

///////////////////// BasicWorldModel ///////////////////////////
const unsigned int players_num = 5;//11; //-* the number of each team

const unsigned int teammates_num = 5;//11; //-* the number of teammates

const unsigned int opponents_num = 5;//11; //-* the number of opponents




//////////////////// server settings ////////////////////////////
//// see rcssserver3d.rb
//-* agent action settings
//-- about kick
const float max_drive_force = 100;

const float max_kick_force = 100;

const AngDeg min_kick_angle = 0;
const AngDeg max_kick_angle = 50;

const float max_kick_distance = 27.5f;

const float kick_margin = 0.07;//0.04;

const Time kick_effect_time = 0.1; //-* how long the kick effect?

const float kick_force_factor = 0.55;//0.7;

const float kick_torque_factor = 0.1;
//-- about drive
const float real_agent_max_speed = 1.62;

//-* physics settings
const float air_friction_factor = 0.301066; //-* the friction factor of ball and air

const float ground_friction_factor = 0.2148156; //-* the friction factor of ball and ground

const float acceleration_of_gravity = 9.81; //-* g = 9.81 m/s^2

const float ground_rebound_ball_factor = -0.75; //-* after ball hit the ground, Vz*=u

//-* field parameter settings
const float min_field_length = 40;//100;
const float max_field_length = 45;//110;

const float min_field_width = 20;//64;
const float max_field_width = 25;//75;

const float penalty_length = 5;//16.5;//禁区长度
const float penalty_width = 10;//40; //禁区宽度
const float half_penalty_width = 5;//20.0f;

const float goal_width = 7.32f; //球门宽度
const float goal_height  = 0.5f; //球门高度#FIFA:2.44
const float half_goal_width = 3.66f;

//-* time settings
const Time sim_step_time = 0.01;//-* 0.01s per step
const Time sim_cycle_time = 0.2;//-* 0.2s per cycle

const Step step_num_per_cycle = Step(sim_cycle_time/sim_step_time);

//////////////////// spades settings ////////////////////////////
const unsigned int sense_latecy = 11;//10

const unsigned int action_latecy = 10;

const unsigned int drive_latecy = 18;

const unsigned int max_request_time_notify = 30;

/////////////////// agent world model settings //////////////////
const float kick_pos_dist = 0.331;//0.23;//0.25;//*0.32;//0.25;//0.32;//0.25;//0.23;//0.33; //-* the distance between kick pos and the ball

const Step think_steps = 20;//5;

const Step max_intercept_steps = 2000;

const Time max_intercept_time = 20;

#endif /* _SETTINGS_H */

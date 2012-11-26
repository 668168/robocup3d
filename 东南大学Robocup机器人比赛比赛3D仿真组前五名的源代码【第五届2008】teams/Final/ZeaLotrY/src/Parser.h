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
 * \flie           Parser.h
 *
 * \brief 解析S表达式/parse the sExp
 *
 *LastModify:
 * $Id: Parser.h,v 1.5 2006/01/27 03:18:51 xy Exp $
 */

#ifndef _PARSER_H
#define _PARSER_H

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#include "Logger.h"
#include "WorldModel.h"
#include <sexp.h>

using namespace std;


class Parser: public Singleton<Parser>
{
public:
	/** 构造函数/Constructor */
	Parser();

	/** 分析所有来自服务器的信息/parse all the messages from server 
	*  @param [in] msg 来自服务器的信息/messages from server
	*  @return 如有任何异常返回FALSE,否则返回TRUE/if there is anything wrong FALSE, else TRUE
	*/
	bool parseAll( const string& msg );

	/** 分析sExp单元中的值/parse the value of the sExp atom 
	*  @param [in] sexp sExp单元/sExp atom pointer
	*  @param [out] res 解析出的值/the value
	*  @return 如有任何异常返回FALSE,否则返回TRUE/if there is anything wrong FALSE, else TRUE
	*/
	static bool parseValue( const sexp_t* sexp, string& res );

	/** 分析sExp单元中的值/parse the value of the sExp atom 
	*  @param [in] sexp sExp单元/sExp atom pointer
	*  @param [out] res 解析出的值/the value
	*  @return 如有任何异常返回FALSE,否则返回TRUE/if there is anything wrong FALSE, else TRUE
	*/
	static bool parseValue( const sexp_t* sexp, int &res );
	
	/** 分析sExp单元中的值/parse the value of the sExp atom 
	*  @param [in] sexp sExp单元/Exp atom pointer
	*  @param [out] res 解析出的值/the value
	*  @return 如有任何异常返回FALSE,否则返回TRUE/if there is anything wrong FALSE, else TRUE
	*/
	static bool parseValue( const sexp_t* sexp, float &res );
	
	/** 分析sExp单元中的值/parse the value of the sExp atom 
	*  @param [in] sexp sExp单元/sExp atom pointer
	*  @param [out] res 解析出的值/the value
	*  @return 如有任何异常返回FALSE,否则返回TRUE/if there is anything wrong FALSE, else TRUE
	*/
	static bool parseValue( const sexp_t* sexp, Vector3f &res );
	
	/** 分析sExp列表中的值/parse the given value of the sExp list 
	*  @param [in] sexp sExp列表/sExp list pointer
	*  @param [in] given 指定的名称/the name of given value
	*  @param [out] res 解析出的值/the value
	*  @return 如果该列表值名称与指定名称相同,且解析成功返回TRUE,否则返回FALSE/if the value name is the same with given name, and successfully get the value, return TRUE, otherwise return FALSE
	*/
	template <class T>
	static bool parseGivenValue( const sexp_t* sexp, const char* given, T &res )
	{
		if ( sexp->ty == SEXP_LIST )
		{
			sexp_t* tmp = sexp->list;
			if ( tmp->ty == SEXP_VALUE )
			{
				if ( 0==strcmp(given,tmp->val) )
				{
					return parseValue(tmp->next,res);
				}
			}
			return false;
		}
		return false;
	}

private:
	/** 分析sExp列表中的听觉信息,并存储到世界模型中/parse the hear messages in the sExp list, and store in the world model
	*  @param [in] sexp sExp列表/sExp list pointer
	*  @return 如有任何异常返回FALSE,否则返回TRUE/if there is anything wrong FALSE, else TRUE	
	*  @note TEXT_INSTEAD_OF_A_MANUAL 2.3.10. Hear Perceptor

		----------------------

		You get percepts from this perceptor when a player uses SayEffector
		and sends a message. The format of the aural sensor message from the
		is:

		(hear <time> <direction in degree> <message>)

		<time> indicates the current time.

		<direction in degree> is relative direction to sender (without noise)
		if it is another player, otherwise it is "self" (without quotation
		mark).

		<message> is the message. The maximum length is sayMsgSize bytes.
		
		The server parameters that affect the Hear perceptor are:
		
		Parameter                      Value
		
		---------------------------------------
		
		audioCutDist                    50.0\n
		hearMax                         2\n
		hearInc                         1\n
		hearDecay                       2\n
		sayMsgSize                      512\n
		
		A player can only hear a message if the player's hear capacity is at
		least hearDecay, since the hear capacity of the player is decreased by
		that number when a message is heard. Every cycle the hear capacity is
		increased with hearInc. The maximum hear capacity is hearMax. To avoid
		a team from making the other team's communication useless by
		overloading the channel the players have separate hear capacities for
		each team. With the current values this means that a player can hear
		at most one message from each team every second perceptor update.
		
		If more messages arrive at the same time than the player can hear the
		messages actually heard are undefined (The current implementation
		choose the messages according to the order of arrival). This rule does
		not include messages from oneself. In other words, a player can hear a
		message from himself and hear a message from another player in the
		same perceptor output.
		
		A message said by a player is transmitted only to players within
		audioCutDist meters from that player. For example, a defender, who may
		be near his own goal, can hear a message from his goal-keeper but a
		striker who is near the opponent goal can not hear the message.
		
		Example Hear output:
		
		(hear 0.8 -179.99 Test_1)
		(hear 0.4 self Test_2)
	*/
	bool parseHear( const sexp_t* sexp );

	/** 分析sExp列表中的视觉信息,并存储到世界模型中/parse the Vision messages in the sExp list, and store in the world model
	*  @param [in] sexp sExp列表/sExp list pointer
	*  @return 如有任何异常返回FALSE,否则返回TRUE/if there is anything wrong FALSE, else TRUE
	*  @note TEXT_INSTEAD_OF_A_MANUAL 2.3.7. Vision Perceptor
	
		-----------------------
		
		Your robots possess a special omnicam with some smart image
		processing software attached :). Robots have a 360 degrees view. The
		VisionPerceptor delivers lists of seen objects, where objects are
		either others robots, the ball, or markers on the field. Currently
		there are 8 markers on the field: one at each corner point of the
		field and one at each goal post.
		
		With each sensed object you get:
		
		- The distance between the player and the object.
		- The angle in the horizontal plane. Zero degree always points to the
		opponent goal.
		- The latitudal angle. Here zero degree means horizontal.
		
		Contrary to 2D soccer simulation, the vision system does not deliver
		object velocities. Objects can be occluded by other objects (this is
		not completely implemented yet). All distances and angles are given
		relative to the camera position. The camera is currently located at
		the center of the robot sphere.
		
		The noise parameters of the vision system are as follows:
		
		- A small calibration error is added to the camera position. For each
		axis, the error is uniformly distributed between -0.005m and
		0.005m. The error is calculated once and remains constant during the
		complete match.
		
		- Dynamic noise normally distributed around 0.0
		  + distance error:  sigma = 0.0965
		  + angle error (x-y plane): sigma = 0.1225
		  + angle error (latitudal): sigma = 0.1480
		
		
		(Vision 
			(<Type> 
			(team <teamname>) 
			(id <id>) 
			(pol <distance> <horizontal angle> <latitudal angle>)
			)
		)
		Possible types are:
		- 'Flag' with <id> one of '1_l', '2_l', '1_r', '2_r'
		- 'Goal' with <id> one of '1_l', '2_l', '2_l', '2_r'
		- 'Player' with <id> being the uniform number of the player
		
		Example Vision output: 
		
		(Vision (Flag (id 1_l) (pol 54.3137 -148.083 -0.152227)) (Flag (id
		2_l) (pol 59.4273 141.046 -0.131907)) (Flag (id 1_r) (pol 61.9718
		-27.4136 -0.123048)) (Flag (id 2_r) (pol 66.4986 34.3644 -0.108964))
		(Goal (id 1_l) (pol 46.1688 179.18 -0.193898)) (Goal (id 2_l) (pol
		46.8624 170.182 -0.189786)) (Goal (id 1_r) (pol 54.9749 0.874504
		-0.149385)) (Goal (id 2_r) (pol 55.5585 8.45381 -0.146933)) (Ball (pol
		6.2928 45.0858 -0.94987)) (Player (team robolog) (id 1) (pol 7.33643
		37.5782 5.86774)))
	*/
	bool parseVision( const sexp_t* sexp );

	/** 分析sExp列表中的比赛状态信息,并存储到世界模型中/parse the GameState messages in the sExp list, and store in the world model
	*  @param [in] sexp sExp列表/sExp list pointer
	*  @return 如有任何异常返回FALSE,否则返回TRUE/if there is anything wrong FALSE, else TRUE
	*  @note TEXT_INSTEAD_OF_A_MANUAL 2.3.7. GameStatePerceptor
		
		-------------------------
				
		The GameStatePerceptor tells you about the current status of the
		game. The first percept you get from this perceptor tells you about
		some of the game variables, like ball weight and field size
		additionally.
		
		(GameState (<Name> <Value>) ...)
		
		Possible <Name>s are:
		
		- 'time' gives the current simulation time (as a float value) passed
		in seconds
		
		- 'playmode' gives the current playmode as a string. Possible
		playmodes are "BeforeKickOff", "KickOff_Left", "KickOff_Right",
		"PlayOn", "KickIn_Left", "KickIn_Right", "corner_kick_left",
		"corner_kick_right", "goal_kick_left", "goal_kick_right",
		"offside_left", "offside_right", "GameOver", "Goal_Left",
		"Goal_Right", "free_kick_left", "free_kick_right", "unknown". For an
		up to day list of all playmodes refer to
		(./plugin/soccer/soccertypes.h)
		
		Example GameState output:
		
		(GameState (time 0) (playmode BeforeKickOff))
	*/
	bool parseGameState( const sexp_t* sexp );

	/** 分析sExp列表中的智能体状态信息,并存储到世界模型中/parse the AgentState messages in the sExp list, and store in the world model
	*  @param [in] sexp sExp列表/sExp list point
	*  @return 如有任何异常返回FALSE,否则返回TRUE/if there is anything wrong FALSE, else TRUE
	*  @note TEXT_INSTEAD_OF_A_MANUAL	2.3.8. AgentState perceptor
	
		---------------------------
		
		The AgentStatePerecptor tells you about the current state of your
		agent, currently its battery level and temperature.
		
		(AgentState
			(battery <battery level in percent>)
			(temp <temperature in degree>)
		)
		
		
		Example AgentState output:
		
		(AgentState (battery 100) (temp 23))
	*/
	bool parseAgentState( const sexp_t* sexp );
	
	/** 分析sExp列表中的单个物体的视觉(相对位置)信息,并存储到世界模型中/parse the vision messages(pol position) of one object in the sExp list, and store in the world model
	*  @param [in] sexp sExp列表/sExp list pointer
	*  @return 如有任何异常返回FALSE,否则返回TRUE/if there is anything wrong FALSE, else TRUE
	*/
	bool parsePosition( const sexp_t* sexp );
	
	/** 分析字符串中的感觉信息,并存储到世界模型中/parse the Sense messages in the string, and store in the world model
	*  @param [in] msg 感觉信息/the sense messages
	*  @return 如有任何异常返回FALSE,否则返回TRUE/if there is anything wrong FALSE, else TRUE
	*/
	void parseS( const string& msg );
	
	/** 分析字符串中的C信息,并存储到世界模型中/parse the C message in the string, and store in the world model
	*  @param [in] msg C信息/the C message
	*  @return 如有任何异常返回FALSE,否则返回TRUE/if there is anything wrong FALSE, else TRUE
	*/
	void parseC( const string& msg );
	
	/** 分析字符串中的T信息,并存储到世界模型中.parse the T message in the string, and store in the world model
	*  @param [in] msg T信息/the T message
	*  @return 如有任何异常返回FALSE,否则返回TRUE/if there is anything wrong FALSE, else TRUE
	*/
	void parseT( const string& msg );
	
	/*===========================*/
	/* 私有成员/Private Attributes */
	/*===========================*/
	/** 表示是否知道对手的队伍名称/indicate if know the opponents' team name */
	bool		_bKnowOppName;
	
	/** 使用SEXP库解析需要的指针/s-expression parser struct pointer */
	pcont_t*	_pcont;
	sexp_t*		_sexp;
};

#define PA Parser::GetSingletonPtr()

#endif /* _PARSER_H */

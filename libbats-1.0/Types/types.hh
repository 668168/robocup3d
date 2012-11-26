/*
 *  Little Green BATS (2008), AI department, University of Groningen
 *
 *  Authors: 	Martin Klomp (martin@ai.rug.nl)
 *		Mart van de Sanden (vdsanden@ai.rug.nl)
 *		Sander van Dijk (sgdijk@ai.rug.nl)
 *		A. Bram Neijt (bneijt@gmail.com)
 *		Matthijs Platje (mplatje@gmail.com)
 *
 *	All students of AI at the University of Groningen
 *  at the time of writing. See: http://www.ai.rug.nl/
 *
 *  Date: 	November 1, 2008
 *
 *  Website:	http://www.littlegreenbats.nl
 *
 *  Comment:	Please feel free to contact us if you have any 
 *		problems or questions about the code.
 *
 *
 *  License: 	This program is free software; you can redistribute 
 *		it and/or modify it under the terms of the GNU General
 *		Public License as published by the Free Software 
 *		Foundation; either version 3 of the License, or (at 
 *		your option) any later version.
 *
 *   		This program is distributed in the hope that it will
 *		be useful, but WITHOUT ANY WARRANTY; without even the
 *		implied warranty of MERCHANTABILITY or FITNESS FOR A
 *		PARTICULAR PURPOSE.  See the GNU General Public
 *		License for more details.
 *
 *   		You should have received a copy of the GNU General
 *		Public License along with this program; if not, write
 *		to the Free Software Foundation, Inc., 59 Temple Place - 
 *		Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef _BATS_TYPES_HH_
#define _BATS_TYPES_HH_

#include <string>

namespace bats
{
  /** A collection of types used at different places */
  class Types
  {
  public:
    /**
     *  The possible play modes.
     */
    enum PlayMode
    {
      UNKNOWN = 0,
      BEFORE_KICKOFF,
          
      KICKOFF_LEFT,
      KICKOFF_RIGHT,
      KICKOFF_US,
      KICKOFF_THEM,
          
      PLAY_ON,
          
      FREEKICK_LEFT,
      FREEKICK_RIGHT,
      FREEKICK_US,
      FREEKICK_THEM,
          
      GOAL_LEFT,
      GOAL_RIGHT,
      GOAL_US,
      GOAL_THEM,
          
      GOAL_KICK_LEFT,
      GOAL_KICK_RIGHT,
      GOAL_KICK_US,
      GOAL_KICK_THEM,
          
      CORNER_KICK_LEFT,
      CORNER_KICK_RIGHT,
      CORNER_KICK_US,
      CORNER_KICK_THEM,
          
      KICKIN_LEFT,
      KICKIN_RIGHT,
      KICKIN_US,
      KICKIN_THEM
    };

    /**
     *  Sides of the field/robot/etc.
     */
    enum Side
    {
      LEFT,
      RIGHT
    };
    
    /// Enumeration of the agent's joints
    enum Joint
    {
      HEAD1 = 0,   ///< Torso to head, X-Axis
      HEAD2,
      
      LLEG1,    ///< Torso to left hip, Z-Axis
      LLEG2,    ///< Left hip to Left thigh, X-Axis
      LLEG3,    ///< Left hip to Left thigh, Y-Axis
      LLEG4,    ///< Left thigh to Left shank, X-Axis
      LLEG5,    ///< Left shank to Left foot, X-Axis
      LLEG6,    ///< Left shank to Left foot, Y-Axis
      
      RLEG1,    ///< Torso to right hip, Z-Axis
      RLEG2,    ///< Right hip to Right thigh, X-Axis
      RLEG3,    ///< Right hip to Right thigh, Y-Axis
      RLEG4,    ///< Right thigh to Right shank, X-Axis
      RLEG5,    ///< Right shank to Right foot, X-Axis
      RLEG6,    ///< Right shank to Right foot, Y-Axis
      
      LARM1,    ///< Torso to Left shoulder, X-Axis
      LARM2,    ///< Torso to Left shoulder, Y-Axis
      LARM3,    ///< Left shoulder to Left upper arm, Z-Axis
      LARM4,    ///< Left upper arm to Left lower arm, X-Axis
      
      RARM1,    ///< Torso to Right shoulder, X-Axis
      RARM2,    ///< Torso to Right shoulder, Y-Axis
      RARM3,    ///< Right shoulder to Right upper arm, Z-Axis
      RARM4,     ///< Right upper arm to Right lower arm, X-Axis
      
      NJOINTS
    };
    
    /// Enumeration of objects in the world. \todo Check flag/goalpost positions (again...)
    enum Object
    {
    	SELF,   ///< Me myself and I
    	
    	BALL,   ///< The big round orange thingy

      PLAYER1,  ///< The big thing build out of blue and green squares ;)
      PLAYER2,  ///< Our teams 2e player.
      PLAYER3,  ///< Our teams 3e player.
      PLAYER4,  ///< Our teams 4e player.
      PLAYER5,  ///< Our teams 5e player.

      OPPONENT1,  ///< There teams 1e player.
      OPPONENT2,  ///< There teams 2e player.
      OPPONENT3,  ///< There teams 3e player.
      OPPONENT4,  ///< There teams 4e player.
      OPPONENT5,  ///< There teams 5e player.
    	
    	FLAG1L,     ///< First flag on the left side of the field (ie. with your back to side of the field)
    	FLAG1R,     ///< First flag on the right side of the field (ie. with your back to side of the field)
    	FLAG2L,     ///< Second flag on the left side of the field (ie. with your back to side of the field)
    	FLAG2R,     ///< Second flag on the right side of the field (ie. with your back to side of the field)
    	
    	FLAG1US,    ///< Left flag on our side of the field (ie. with your back to our own goal)
    	FLAG2US,    ///< Right flag on our side of the field (ie. with your back to our own goal)
    	FLAG1THEM,  ///< Left flag on their side of the field (ie. with your back to their goal)
    	FLAG2THEM,  ///< Right flag on their side of the field (ie. with your back to their goal)
    	
    	GOAL1L,     ///< First goal post on the left side of the field (ie. with your back to side of the field)
    	GOAL1R,     ///< First goal post on the right side of the field (ie. with your back to side of the field)
    	GOAL2L,     ///< Second goal post on the left side of the field (ie. with your back to side of the field)
    	GOAL2R,     ///< Second goal post on the right side of the field (ie. with your back to side of the field)
    	
    	GOAL1US,    ///< Left goal post on our side of the field (ie. with your back to our own goal)
    	GOAL2US,    ///< Right goal post on our side of the field (ie. with your back to our own goal)
    	GOAL1THEM,  ///< Left goal post on their side of the field (ie. with your back to their goal)
    	GOAL2THEM,  ///< Right goal post on their side of the field (ie. with your back to their goal)
    	
    	NOBJECTS
    };
    
    /// Enumeration of body parts.
    enum BodyPart
    {
      HEAD,
      NECK,

      TORSO,
      LOWERTORSO,
      
      LSHOULDER,
      LUPPERARM,
      LELBOW,
      LLOWERARM,
      LHAND1,
      LHAND2,
      
      RSHOULDER,
      RUPPERARM,
      RELBOW,
      RLOWERARM,
      RHAND1,
      RHAND2,
      
      LHIP1,
      LHIP2,
      LUPPERLEG,
      LLOWERLEG,
      LANKLE,
      LFOOT,

      RHIP1,
      RHIP2,
      RUPPERLEG,
      RLOWERLEG,
      RANKLE,
      RFOOT,
      
      NBODYPARTS
    };
    
    /**
     * Check whether a joint is part of a universal joint
     */
    static bool isUniversalJoint(Joint joint)
    {
      return joint == LLEG2 ||
             joint == LLEG3 ||
             joint == LLEG5 ||
             joint == LLEG6 ||
             joint == RLEG2 ||
             joint == RLEG3 ||
             joint == RLEG5 ||
             joint == RLEG6 ||
             joint == LARM1 ||
             joint == LARM2 ||
             joint == RARM1 ||
             joint == RARM2;
    }
    /**
     * Return the enum name for a given object enum
     * This function is an inverse of Types::objectEnumFor
     */
    static std::string nameOf(Types::Object const obj);
    
    /** Return the Object enum for a given name, case sensitive
     *
     * @param a Object name
     * @param def Default return value, in case of unknown object
     */
    static Types::Object objectEnumFor(std::string const &a, Types::Object def);
  };
};

#endif

#ifndef _BATS_TYPES_HH_
#define _BATS_TYPES_HH_

namespace bats
{
  /** A collection of types used at different places */
  class Types
  {
  public:
    /// Enumeration of the agent's joints
    enum Joint{
      HEAD_1 = 0,   ///< Torso to head, X-Axis
      HEAD_2,
      
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
    enum Object{
      SELF,   ///< Me myself and I
      
      BALL,   ///< The big round orange thingy
      
      PLAYER1,  ///< The big thing build out of blue and green squares ;)
      PLAYER2,  ///< Our teams 2e player.
      PLAYER3,  ///< Our teams 3e player.
      PLAYER4,  ///< Our teams 4e player.
      PLAYER5,  ///< Our teams 5e player.
      PLAYER6,  ///< Our teams 3e player.
      PLAYER7,  ///< Our teams 4e player.
      PLAYER8,  ///< Our teams 5e player.
      PLAYER9,  ///< Our teams 5e player.
      PLAYER10,  ///< Our teams 5e player.
      PLAYER11,  ///< Our teams 5e player.
      
      OPPONENT1,  ///< Their teams 1e player.
      OPPONENT2,  ///< Their teams 2e player.
      OPPONENT3,  ///< Their teams 3e player.
      OPPONENT4,  ///< Their teams 4e player.
      OPPONENT5,  ///< Their teams 5e player.
      OPPONENT6,  ///< Their teams 1e player.
      OPPONENT7,  ///< Their teams 2e player.
      OPPONENT8,  ///< Their teams 3e player.
      OPPONENT9,  ///< Their teams 4e player.
      OPPONENT10,  ///< Their teams 5e player.
      OPPONENT11,  ///< Their teams 5e player.
      
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
    
    /// Enumeration of body parts. \todo Use these in WorldModel::updatePosture
    enum BodyPart{
      NECK,
      HEAD,
      
      TORSO,
      
      LSHOULDER,
      LUPPERARM,
      LLOWERARM,
      
      RSHOULDER,
      RUPPERARM,
      RLOWERARM,
      
      LUPPERLEG,
      LLOWERLEG,
      LFOOT,
      
      RUPPERLEG,
      RLOWERLEG,
      RFOOT,
      
      NBODYPARTS
    };

    enum BodyConnection{
      BC_NECK,
      BC_HEAD,

      BC_TORSO,
      
      BC_LSHOULDER,
      BC_LELBOW,
      BC_LHAND,

      BC_RSHOULDER,
      BC_RELBOW,
      BC_RHAND,

      BC_LHIP,
      BC_LKNEE,
      BC_LANKLE,
      BC_LHEEL,
      BC_LTOE,

      BC_RHIP,
      BC_RKNEE,
      BC_RANKLE,
      BC_RHEEL,
      BC_RTOE,

      BC_NUM
    };

    enum PlayerType{
      ATTACKER,
      DEFENDER,
      KEEPER,

      UNKNOWN_PLAYERTYPE,

      NPLAYERTYPE,
    };

    /// Check whether a joint is part of a universal joint
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
  };
};

#endif

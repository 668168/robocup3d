/*
 *  Little Green BATS (2007), AI department, University of Groningen
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
 *  Date: 	July 27, 2007
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





#ifndef __INC_BATS_WORLDMODEL_HH_
#define __INC_BATS_WORLDMODEL_HH_

//#include <iostream>


#include <map>

#include "predicate.hh"
#include "rf.hh"
#include "vector4.hh"
#include "socketcomm.hh"
#include "hashclasses.hh"
#include "normaldistribution1.hh"
#include "normaldistribution3d.hh"
#include "matrix4d.hh"

namespace bats {

  /**
   *  The Almighty WorldModel (think of a Futurama voice)
   */
  class WorldModel {

  public:
	
    /**
     *  This is more like a token id than a world element id,
     *  but it can be used as an world element id, so it doesn't
     *  really matter I guess.
     *  Altough it still needs to be integrated with the SocketComm.
     */
    enum InfoID {

      iNone,
      
      iGameState,
      iUnum,
      iTeam,
      iGameTime,
      iPlayMode,
      
      iTime,         
      iNow,          ///< The current playing time.
      iStep,         ///< The time step (dt?)
      iVision,
      iVisionFlag1L, ///< First flag on the left side.
      iVisionFlag2L, ///< Second flag on the left side.
      iVisionFlag1R, ///< First flag on the right side.
      iVisionFlag2R, ///< Second flag on the right side.
      iVisionGoal1L, ///< First
      iVisionGoal2L, ///< 
      iVisionGoal1R, ///< 
      iVisionGoal2R, ///< 
      iVisionPlayer1,
      iVisionPlayer2,
      iVisionPlayer3,
      iVisionPlayer4,
      iVisionPlayer5,
      iVisionPlayerNone,
      iVisionOpponent1,
      iVisionOpponent2,
      iVisionOpponent3,
      iVisionOpponent4,
      iVisionOpponent5,
      iVisionOpponentNone,
      iVisionBall,   ///< Position of the ball.
      iUJ,
      iHJ,
      iName,
      iAxis,
      iRate,
      iAxis1,
      iRate1,
      iAxis2,
      iRate2,

      iHeadJoint1,
      
      iLLegJoint1,
      iLLegJoint2,
      iLLegJoint3,
      iLLegJoint4,
      iLLegJoint5,
      iLLegJoint6,

      iRLegJoint1,
      iRLegJoint2,
      iRLegJoint3,
      iRLegJoint4,
      iRLegJoint5,
      iRLegJoint6,

      iLArmJoint1,  ///< 
      iLArmJoint2,  ///< 
      iLArmJoint3,
      iLArmJoint4,

      iRArmJoint1,
      iRArmJoint2,
      iRArmJoint3,
      iRArmJoint4,

      iGyro,
      iTorsoGyro,
      iTouch,
      iFootLeft,
      iFootLeft2,  /// dummy
      iFootRight,
      iFootRight2,
      iVal,
      
      iForceResistancePerceptor,
      iContact,
      iForce,

      iP, /// Player vision info.

      // Should always have the highest numeric value.
      iInfoID,
      
    };
    /*
      # STR_PM_BeforeKickOff "BeforeKickOff"
      # STR_PM_KickOff_Left "KickOff_Left"
      # STR_PM_KickOff_Right "KickOff_Right"
      # STR_PM_PlayOn "PlayOn"
      # STR_PM_KickIn_Left "KickIn_Left"
      # STR_PM_KickIn_Right "KickIn_Right"
      # STR_PM_CORNER_KICK_LEFT "corner_kick_left"
      # STR_PM_CORNER_KICK_RIGHT "corner_kick_right"
      # STR_PM_GOAL_KICK_LEFT "goal_kick_left"
      # STR_PM_GOAL_KICK_RIGHT "goal_kick_right"
      # STR_PM_OFFSIDE_LEFT "offside_left"
      # STR_PM_OFFSIDE_RIGHT "offside_right"
      # STR_PM_GameOver "GameOver"
      # STR_PM_Goal_Left "Goal_Left"
      # STR_PM_Goal_Right "Goal_Right"
      # STR_PM_FREE_KICK_LEFT "free_kick_left"
      # STR_PM_FREE_KICK_RIGHT "free_kick_right"
      # STR_PM_Unknown "unknown"
    */

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
     *  Sides of the feeld.
     */
    enum Side
      {
	LEFT,
	RIGHT
      };
	
  private:
		
    WorldModel(WorldModel const &); // NI
    WorldModel &operator=(WorldModel const &); // NI


    SocketComm &d_comm;
    unsigned int d_unum;
    Vector4F d_info[iInfoID];

    double d_time;

    std::string d_teamName;
    
    double d_gameTime;
    double d_prevGameTime;
    double d_timeStep;
    PlayMode d_playMode;
    Side d_team;
    
    Vector3D d_fieldNormal;
    double d_distToField;
    
    Vector3D d_gyro;
    
    Vector3D d_footForceContacts[2];
    Vector3D d_footForces[2];
    
    NormalDistribution1D d_jointAngles[Types::NJOINTS];
    NormalDistribution1D d_jointRates[Types::NJOINTS];
    
    std::pair<double,double> d_jointConstraints[Types::NJOINTS];

    NormalDistribution3D d_objectPositions[Types::NOBJECTS];
    
    NormalDistribution3D d_objectSpeeds[Types::NOBJECTS];

    double d_lastVisionUpdate[Types::NOBJECTS];

    bats::Matrix4D d_bodyPartPositions[Types::NBODYPARTS];
    
    std::map<unsigned,unsigned> d_opponentUnums;

    std::map<unsigned,unsigned> d_playerUnums;
    
    double d_firstTime;
    unsigned int d_numMsgReceived;
    
    //Vector4D d_relativeFieldPlane;
    
    InfoID translateInfo(std::string const &name)
    {
      return s_infoMap[name];
    }

    Vector4F parseVect(rf<Predicate> const &pred)
    {
      assert(pred);        

      Vector4F res;
      for (unsigned i = 0; i < pred->size(); ++i)
        res.set(i,*rf_cast<Predicate>(pred->getChild(i)));
      return res;
    }

    Vector4F parseScalar(rf<Predicate> const &pred)
    {
      Vector4F res;
      res.setX(*rf_cast<Predicate>(pred->getChild(0)));
      return res;
    }

    
    void destroy();
    
    static WorldModel *s_instance;
    
    
    void updateJoints();
    
    void updateVision();
    
    void updatePosture();

    WorldModel(SocketComm &comm);

  public:

    static FBB::StringCaseHash<InfoID> s_infoMap;
    static FBB::StringCaseHash<PlayMode> s_playModeMap;
    
    /**
     *  The WorldModel is a Singleton, first call this method to initialize it!
     */
    static void initialize(SocketComm &comm);

    /**
     *  Use this to get an instance of the WorldModel.
     */
    static WorldModel &getInstance();

    ~WorldModel() { destroy(); }

    /**
     *   Integrates the predicate into the world model.
     */
    void intergrate(rf<Predicate> const &pred);

    /**
     *  @returns the current simulation time.
     */
    float getTime() const { return d_time; }

    /**
     *  Sets the team name, which is used later on to identify which player
     *  is our and which player is theirs.
     */
    void setTeamName(std::string const &name)
    { d_teamName = name; }

    /**
     *  @returns our team name.
     */
    std::string getTeamName() const
    { return d_teamName; }

    /**
     *  @returns the value of the world element with id.
     */
    Vector4F const &get(InfoID id) const
    {
      return d_info[id];
    }
    
    /**
     *  @returns the gamestate
     */
    PlayMode const &getPlayMode() const
    {
      //TODO create sensible return value
      return d_playMode;
    }    


      Side const &getSide() const
	  {
	      return d_team;
	  }
	
    /**
     * @returns the position of object object relative to the agent
     */
    NormalDistribution3D getObjectPosition(Types::Object object)
    {
      return d_objectPositions[object];
    }

    /**
     * @returns the vector of object object relative to the agent
     */
    NormalDistribution3D getObjectVector(Types::Object object)
    {
      return d_objectSpeeds[object];
    }

    /**
     *  @returns the game time when an object was last updated.
     */
    double getObjectLastUpdate(Types::Object object)
    {
      return d_lastVisionUpdate[object];
    }

    /**
     *  @returns true if an object is updated within the last two time steps.
     *
     *  Use this to check if the object information is still current.
     */
    bool isObjectAlive(Types::Object object)
    {
      return d_lastVisionUpdate[object] >= d_gameTime - 2* d_timeStep;
    }

    /**
     *  @returns the current game time.
     */
    double getGameTime() const { return d_gameTime; }

    /**
     *  @returns the previous game time.
     */
    double getPrevGameTime() const { return d_prevGameTime; }

    /**
     *  @returns the amount of time between the previous and the current game time.
     */
    double getTimeStep() const { return d_timeStep; }

    /**
     * @returns The normal vector of the field relative to our torso
     */
    Vector3D getFieldNormal() { return d_fieldNormal; }

    /**
     * @returns The distance of the center of the torso to the field
     */
    double getDistToField() { return d_distToField; }
		
    /**
     * @returns The current gyro measurement
     */
    Vector3D getGyro() { return d_gyro; }
		
    /**
     *  @returns the force vector of the force perceptor on the left foot
     */
    Vector3D getForceLeftFoot() { return d_footForces[0]; }

    /**
     *  @returns the force vector of the force perceptor on the right foot
     */
    Vector3D getForceRightFoot() { return d_footForces[1]; }
    
    /**
     *  @returns the center of force on the left foot
     */
    Vector3D getForceContactLeftFoot() { return d_footForceContacts[0]; }

    /**
     *  @returns the center of force on the right foot
     */
    Vector3D getForceContactRightFoot() { return d_footForceContacts[1]; }
		
    /**
     * @returns The first time recieved by the server ever
     */
    double getFirstTime() { return d_firstTime; }
    
    /// \todo Can this be removed?
    unsigned testFindID(std::string const &name)
    { return translateInfo(name); }

    /**
     * Update the world model. This updates the SocketComm, reads all messages and integrates them into the model.
     */
    void update();

    /**
     *  @returns our unum (player number within our team).
     */
    unsigned getUnum() const { return d_unum; }

    /**
     *  Sets our unum.
     */
    void setUnum(unsigned unum) { d_unum = unum; }

    /**
     *  @returns the number of messages received by the agent.
     */
    unsigned getNumMsgReceived() const { return d_numMsgReceived; }

    /**
     *  @returns the angle of joint in radians (@see Types::Joint).
     */
    NormalDistribution1D getJointAngle(Types::Joint joint) { return d_jointAngles[joint]; }
    
    /**
     *  @returns the rate of joint in radians (@see Types::Joint).
     */
    NormalDistribution1D getJointRate(Types::Joint joint) { return d_jointRates[joint]; }
		
    /**
     *  @returns true when the agent lies on its belly.
     */
    bool onMyBelly();

    /**
     *  @returns true when the agent lies on its back.
     */
    bool onMyBack();

    /**
     *  @returns true when the agent stands on its feet.
     */
    bool onMyFeet();

    /**
     *  @returns true when the agent lies on one of its sides.
     */
    bool onMySide();

    /**
     *  Sets the angle constraints of joint to min and max.
     */
    void setJointConstraints(Types::Joint joint, double min, double max)
    {
      d_jointConstraints[joint] = std::pair<double,double>(min,max);
    }

    /**
     *  @returns the max angle of joint.
     */
    double getJointMax(Types::Joint joint) { return d_jointConstraints[joint].second; }

    /**
     *  @returns the min angle of joint.
     */
    double getJointMin(Types::Joint joint) { return d_jointConstraints[joint].first; }
    
  };


};

#endif // __INC_BATS_WORLDMODEL_HH_

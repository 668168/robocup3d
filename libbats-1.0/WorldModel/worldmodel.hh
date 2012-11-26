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

#ifndef __INC_BATS_WORLDMODEL_HH_
#define __INC_BATS_WORLDMODEL_HH_

//#include <iostream>


#include <map>

#include "../Predicate/predicate.hh"
#include "../Ref/rf.hh"
#include "../Vector4/vector4.hh"
#include "../SocketComm/AgentSocketComm/agentsocketcomm.hh"
#include "../Hashclasses/hashclasses.hh"
#include "../Distribution1/NormalDistribution1/normaldistribution1.hh"
#include "../Distribution3D/NormalDistribution3D/normaldistribution3d.hh"
#include "../Matrix4D/matrix4d.hh"
#include "../Singleton/singleton.hh"
#include "../PlayerInfo/playerinfo.hh"

namespace bats {

  /**
   *  The WorldModel
   */
  class WorldModel {

    friend class Singleton<WorldModel>;
    
  public:
        
    struct Object
    {
      NormalDistribution3D position;

      NormalDistribution3D velocity;
    };
    
  private:
                
    WorldModel(WorldModel const &); // NI
    WorldModel &operator=(WorldModel const &); // NI

    double d_time;

    std::string d_teamName;
    
    double d_gameTime;
    double d_prevGameTime;
    double d_timeStep;
    Types::PlayMode d_playMode;
    Types::PlayMode d_lastPlayMode;
    Types::Side d_team;
    unsigned d_scoreUs;
    unsigned d_scoreThem;
    
    Matrix4D d_fieldTransform;
    double d_distToField;
    
    Object d_objects[Types::NOBJECTS];
    Object d_prevObjects[Types::NOBJECTS];
    
    double d_lastVisionUpdate[Types::NOBJECTS];
    double d_prevVisionUpdate[Types::NOBJECTS];

    std::map<unsigned,unsigned> d_opponentUnums;

    std::map<unsigned,unsigned> d_playerUnums;
    
    bool d_catchFallEnabled;
    bool d_getUpTheOldFashionedWay;
    
    double d_firstTime;
    unsigned int d_numMsgReceived;
    
//    VectorPredictor d_ball_predictor;

    bool d_weGetKickOff;
    
    //Vector4D d_relativeFieldPlane;
    
    double d_ballRadius;

    Matrix4D d_invWorldTransform;
    Matrix4D d_worldTransform;

    std::map<unsigned,PlayerInfo> d_players;
    std::map<unsigned,PlayerInfo> d_opponents;
    
    void destroy();
    
    void updateGameState();
    
    void updateVision();
    
    void updatePosture();

    WorldModel();

    PlayerInfo &getPlayerFromPid(unsigned pid);
    PlayerInfo &getOpponentFromPid(unsigned pid);

  public:

    ~WorldModel() { /*destroy();*/ }

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

    Types::Side getSide() const
    {
      return d_team;
    }
        
    /**
     *  @returns the gamestate
     */
    Types::PlayMode const &getPlayMode() const
    {
      return d_playMode;
    }
    
    /**
     * @returns the gamestate of last timestep
     */
    Types::PlayMode getLastPlayMode() const
    {
      return d_lastPlayMode;
    }
    
    bool weJustScored() const
    {
      return (d_team == Types::LEFT && d_playMode == Types::GOAL_LEFT && d_lastPlayMode != Types::GOAL_LEFT) ||
             (d_team == Types::RIGHT && d_playMode ==Types::GOAL_RIGHT && d_lastPlayMode != Types::GOAL_RIGHT);
    }
    
    bool theyJustScored() const
    {
      return (d_team == Types::RIGHT && d_playMode == Types::GOAL_LEFT && d_lastPlayMode != Types::GOAL_LEFT) ||
             (d_team ==Types::LEFT && d_playMode ==Types::GOAL_RIGHT && d_lastPlayMode != Types::GOAL_RIGHT);
    }
    
    /**
     * @returns an object
     */
    Object getObject(Types::Object object) const
    {
      return d_objects[object];
    }

    /**
     * @returns an object from the previous update
     */
    Object getPrevObject(Types::Object object) const
    {
      return d_prevObjects[object];
    }

    /**
    */
    Vector3D getObjectMovement(bats::Types::Object) const;

    /**
     * @deprecated use getObject(object).localPosition
     * @returns the position of object object relative to the agent in local coordinates
     */
    NormalDistribution3D getObjectPositionLocal(Types::Object object) const
    {
      return d_objects[object].position;
    }

    /**
     *  @returns the game time when an object was last updated.
     */
    double getObjectLastUpdate(Types::Object object) const
    {
      return d_lastVisionUpdate[object];
    }

    /**
     *  @returns the time since we saw this object last
     */
    double getObjectDelay(Types::Object object) const
    {
     
      return getObjectLastUpdate(object) - d_prevVisionUpdate[object];
    }
    /**
     *  @returns true if an object is updated within the last two time steps.
     *
     *  Use this to check if the object information is still current.
     */
    bool isObjectAlive(Types::Object object) const
    {
      return getTime() - getObjectLastUpdate(object) < 2 * d_timeStep;
      //return d_lastVisionUpdate[object] >= d_gameTime - 2* d_timeStep;
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
    Vector3D getFieldNormal() const { return d_fieldTransform.up(); }

    /**
     * @returns The field transformation matrix
     */
    Matrix4D getFieldTransform() const { return d_fieldTransform; }
    
    /**
     * @returns The distance of the center of the torso to the field
     */
    double getDistToField() const { return d_distToField; }
    
    Vector3D getDirectionOfOpponentGoal() const;
    
    /**
     * @returns The first time recieved by the server ever
     */
    double getFirstTime() const { return d_firstTime; }
    
    /**
     * @returns ball predictor
     */
    //VectorPredictor const &getBallPredictor() const { return d_ball_predictor; }

    /**
     * Update the world model. This updates the AgentSocketComm, reads all messages and integrates them into the model.
     */
    void update();

    /**
     *  @returns the number of messages received by the agent.
     */
    unsigned getNumMsgReceived() const { return d_numMsgReceived; }

    double getBallRadius() const { return d_ballRadius; }

    /**
     * sets d_getUpTheOldFashionedWay bool. if agent failed to get up using the pushup method
     */
    void setGetUpTheOldFashionedWay(bool newValue)
    {
      d_getUpTheOldFashionedWay = newValue;
    }
     
    bool getGetUpTheOldFashionedWay() const
    {
      return d_getUpTheOldFashionedWay;
    }
     
    size_t getNumberOfPlayers() const
    {
      //      return d_playerUnums.size();
      return d_players.size();
    }

    size_t getNumberOfOpponents() const
    {
      //      return d_opponentUnums.size();
      return d_opponents.size();
    }
    
    /**
     * @return whether we get to take the next kick off. Only usable in Types::BEFORE_KICKOFF andTypes::GOAL_US/GOAL_THEM
     */
    bool weGetKickOff() const { return d_weGetKickOff; }

    /**
     * @returns whether other team mates are closer to the ball than this agent. If @a standing is true (default), only standing agents are considered. If @a count is false (default), the method returns directly after the first team mate closer to the ball is encountered, otherwise it returns the total number of team mates closer by.
     */ 
    unsigned otherCloserToBall(bool standing = true, bool count = false);
    
    /**    
     * @returns whether other team mates are closer to the given point than this agent. If @a standing is true (default), only standing agents are considered. If @a count is false (default), the method returns directly after the first team mate closer to the given point is encountered, otherwise it returns the total number of team mates closer by.
     */
    unsigned otherCloserTo(Vector3D const& pos, bool standing = true, bool count = false);
    
    /**
     *  @returns the transform from world coordinates to agent coordinates.
     */
    Matrix4D const &getInvWorldTransform() const;

    /**
     *  @returns the transform from agent to world coordinates.
     */
    Matrix4D const &getWorldTransform() const;


    //    PlayerInfo &getPlayer(unsigned unum); // DO NOT USE.
    //    PlayerInfo &getOpponent(unsigned unum); // DO NOT USE.

    typedef std::map<unsigned,PlayerInfo>::const_iterator player_iterator;


    player_iterator beginPlayers() const;
    player_iterator endPlayers() const;

    player_iterator beginOpponents() const;
    player_iterator endOpponents() const;


    
  };

  typedef Singleton<WorldModel> SWorldModel;



  inline WorldModel::player_iterator WorldModel::beginPlayers() const
  {
    return d_players.begin();
  }

  inline WorldModel::player_iterator WorldModel::endPlayers() const
  {
    return d_players.end();
  }

  inline WorldModel::player_iterator WorldModel::beginOpponents() const
  {
    return d_opponents.begin();
  }

  inline WorldModel::player_iterator WorldModel::endOpponents() const
  {
    return d_opponents.end();
  }  

  inline Matrix4D const &WorldModel::getInvWorldTransform() const
  {
    return d_invWorldTransform;
  }

  inline Matrix4D const &WorldModel::getWorldTransform() const
  {
    return d_worldTransform;
  }


};

#endif // __INC_BATS_WORLDMODEL_HH_

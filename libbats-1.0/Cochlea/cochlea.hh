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

#ifndef _BATS_COCHLEA_HH_
#define _BATS_COCHLEA_HH_

#include "../Ref/rf.hh"
#include "../Vector4/vector4.hh"
#include "../SocketComm/AgentSocketComm/agentsocketcomm.hh"
#include "../Singleton/singleton.hh"
#include <vector>
#include <map>
#include "../Hashclasses/hashclasses.hh"
#include "../PlayerInfo/playerinfo.hh"

namespace bats
{
  class Cochlea
  {
    friend class Singleton<Cochlea>;
    
  public:
    /**
     * Enumeration of all predicate types
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
      iVisionPlayer6,
      iVisionPlayer7,
      iVisionPlayer8,
      iVisionPlayer9,
      iVisionPlayerNone,
      iVisionOpponent1,
      iVisionOpponent2,
      iVisionOpponent3,
      iVisionOpponent4,
      iVisionOpponent5,
      iVisionOpponent6,
      iVisionOpponent7,
      iVisionOpponent8,
      iVisionOpponent9,
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
      iHeadJoint2,
      
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

      iHear,
      
      iP, /// Player vision info.

      // Should always have the highest numeric value.
      iInfoID,
      
    };

    /**
     * Structure of an auditory message
     */
    struct HearMessage
    {
      double time;            /// Time at which message is received
      double angle;           /// Angle relative to torso of the direction the message came from
      std::string message;    /// Message content
      
      HearMessage(double t, double a, std::string const& m)
      : time(t), angle(a), message(m)
      {}
    };
  private:
    FBB::StringHash<InfoID> d_infoMap;
    FBB::StringHash<Types::PlayMode> d_playModeMap;

    Vector4F d_info[iInfoID];
    std::vector<HearMessage> d_hearMessages;

    std::string d_teamName;
    
    std::map<unsigned,PlayerInfo> d_players;
    std::map<unsigned,PlayerInfo> d_opponents;

    Cochlea();
    
    Vector4F parseVect(rf<Predicate> const &pred);

    Vector4F parseScalar(rf<Predicate> const &pred);

    void integrate(rf<Predicate> const &pred);

    PlayerInfo &getPlayerFromPid(unsigned pid);
    PlayerInfo &getOpponentFromPid(unsigned pid);
    
  public:
    /**
     * @returns the translation of @a mode to a Types::PlayMode value
     */
    Types::PlayMode getPlayMode(std::string const& mode) { return d_playModeMap[mode];}
    
    /**
     * Set the name of your own team, used to recognize team mates and opponents
     */
    void setTeamName(std::string const& teamName) { d_teamName = teamName; }
    
    /**
     * Set translation. This is primarily used to map joint pereptor names to Cochlea's internal names.
     */
    void setTranslation(std::string const& from, std::string const& to) { d_infoMap[from] = d_infoMap[to]; }
    
    /**
     * @returns the translation of @a name to an InfoID value
     */
    InfoID translateInfo(std::string const &name) { return d_infoMap[name]; }

    /**
     * Update values by integrating the latest predicate received by AgentSocketComm
     */
    void update();

    /**
     * @returns the value of the information with id @a id in the form of a 4-dimensional vector
     */
    Vector4F getInfo(InfoID id) { return d_info[id]; }

    //    PlayerInfo &getPlayer(unsigned unum); // DO NOT USE.
    //    PlayerInfo &getOpponent(unsigned unum); // DO NOT USE.

    /**
     * An iterator used to iterate through players
     */
    typedef std::map<unsigned,PlayerInfo>::const_iterator player_iterator;

    /**
     * @returns an iterator over the player information of team mates, at the first element
     */
    player_iterator beginPlayers() const;
    /**
     * @returns an iterator over the player information of team mates, one element beyond the last element
     */
    player_iterator endPlayers() const;

    /**
     * @returns an iterator over the player information of opponents, at the first element
     */
    player_iterator beginOpponents() const;
    /**
     * @returns an iterator over the player information of opponents, one element beyond the last element
     */
    player_iterator endOpponents() const;

  };
  
  typedef Singleton<Cochlea> SCochlea;

  inline Cochlea::player_iterator Cochlea::beginPlayers() const
  {
    return d_players.begin();
  }

  inline Cochlea::player_iterator Cochlea::endPlayers() const
  {
    return d_players.end();
  }

  inline Cochlea::player_iterator Cochlea::beginOpponents() const
  {
    return d_opponents.begin();
  }

  inline Cochlea::player_iterator Cochlea::endOpponents() const
  {
    return d_opponents.end();
  }  

}

#endif


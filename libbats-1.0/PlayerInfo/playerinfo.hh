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

#ifndef __INC_BATS_PLAYERINFO_HH__
#define __INC_BATS_PLAYERINFO_HH__

#include "../Vector3/vector3.hh"
#include "../Matrix4D/matrix4d.hh"

namespace bats {

  /**
   *  Objects of this class hold information about a player in the field. Be it
   *  a teammate or an opponent.
   */
  class PlayerInfo {

    static const unsigned c_histLength = 5;

    float d_lastSeen;
    float d_lastStep;

    unsigned d_id;

    Matrix4D d_transform;

    //    Vector3F d_positionHist[c_histLength];
    Vector3F d_velocityHist[c_histLength];

    unsigned d_histPos;

    Vector3F d_longPosIntergrate;

    Vector3F d_lastPosition; // the last seen position.

    Vector3F d_position;
    Vector3F d_worldPosition;
    Vector3F d_estVelocity;
    Vector3F d_estWorldVelocity;

    bool d_thinkGoally;

  public:

    PlayerInfo();

    ~PlayerInfo();

    /**
     *  Sets the player id who is modelled in this object.
     */
    void setID(unsigned id);

    /**
     *  @returns the players id, which currently runs from 1 to 5. Opponents
     *           and teammates have overlapping id's.
     */
    unsigned getID() const;

    /**
     *  Updates the player position.
     */
    void updatePosition(Vector3F const &pos, float time);

    /**
     *  @returns the amount of time the last step took.
     */
    float getLastStep() const;

    /**
     *  @returns the players estimated position in local coordinates.
     */
    Vector3F const &getPosition() const;

    /**
     *  @returns the plates estmated position in world coordinates.
     */
    Vector3F const &getWorldPosition() const;

    /**
     *  @returns the players estimates velocity in the local coordinate system.
     */
    Vector3F const &getEstVelocity() const;

    /**
     *  @returns the players estimated velocity in world coordinates.
     */
    Vector3F const &getEstWorldVelocity() const;

    /**
     *  @returns true when we think that the player is a goally (currently not implemented).
     */
    bool thinkGoally() const;

    /**
     *  @returns true if the player is close to the ground.
     */
    bool onGround() const;

  };

  inline PlayerInfo::PlayerInfo()
    : d_id(0)
  {}

  inline PlayerInfo::~PlayerInfo()
  {}

  inline void PlayerInfo::setID(unsigned id)
  {
    d_id = id;
  }

  inline float PlayerInfo::getLastStep() const
  {
    return d_lastStep;
  }

  inline unsigned PlayerInfo::getID() const
  {
    return d_id;
  }

  inline Vector3F const &PlayerInfo::getPosition() const
  {
    return d_position;
  }

  inline Vector3F const &PlayerInfo::getWorldPosition() const
  {
    return d_worldPosition;
  }

  inline Vector3F const &PlayerInfo::getEstVelocity() const
  {
    return d_estVelocity;
  }

  inline Vector3F const &PlayerInfo::getEstWorldVelocity() const
  {
    return d_estWorldVelocity;
  }

  inline bool PlayerInfo::thinkGoally() const
  {
    return d_thinkGoally;
  }
  
  inline bool PlayerInfo::onGround() const
  {
    return d_worldPosition[2] < 0.2;
  }

};


#endif // __INC_BATS_PLAYERINFO_HH__

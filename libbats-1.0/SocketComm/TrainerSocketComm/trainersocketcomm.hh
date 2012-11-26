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

#ifndef __INC_BATS_TRAINERSOCKETCOMM_HH_
#define __INC_BATS_TRAINERSOCKETCOMM_HH_

#include "../socketcomm.hh"
#include "../../Types/types.hh"
#include "../../Singleton/singleton.hh"

namespace bats
{
  /**
   * Specialized SocketComm to help a trainer communicate with the server
   */
  class TrainerSocketComm : public SocketComm
  {
    friend class Singleton<TrainerSocketComm>;

    TrainerSocketComm(TrainerSocketComm const&); //NI
    TrainerSocketComm& operator=(TrainerSocketComm const&); //NI
    
    TrainerSocketComm()
    {}

  public:
    
    void setBallPos(Vector3D const& pos);
    
    static rf<Predicate> makeSetBallPosMessage(Vector3D const& pos);
    
    void setBallVel(Vector3D const& vel);
    
    static rf<Predicate> makeSetBallVelMessage(Vector3D const& vel);
    
    void setBallPosVel(Vector3D const& pos, Vector3D const& vel);
    
    static rf<Predicate> makeSetBallPosVelMessage(Vector3D const& pos, Vector3D const& vel);
    
    void kickOff();
    
    static rf<Predicate> makeKickOffMessage();
    
    void setPlayMode(Types::PlayMode mode);
    
    static rf<Predicate> makeSetPlayModeMessage(Types::PlayMode mode);
  };
  
  typedef Singleton<TrainerSocketComm> STrainerSocketComm;
};

#endif

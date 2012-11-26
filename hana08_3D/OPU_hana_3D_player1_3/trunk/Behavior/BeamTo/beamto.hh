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











#ifndef _BATS_BEAMTO_HH_
#define _BATS_BEAMTO_HH_

#include "behavior.hh"

namespace bats
{
  /** Behavior: Beam to a fixed position
   *
   * Beam to a fixed position, defined in the configuration:
   * <code><pre>
   *    \<param>
   *      \<where x="-9" y="0" z="0" />
   *    \</param>
   * </pre></code>
   *
   */
  class BeamTo : public Behavior
  {
		float d_x;
		float d_y;
		float d_z;

    /** Generate the current goal for a slot
     *
     * @param step Step number in the sequence
     * @param slot Slot number in the step
     * @returns goal: X ^ Y
     */
    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    
    virtual rf<State> getCurrentState();

    /** Get the capability of the behavior to achieve goal g from state s
     *
     * @param s Expected state: GameState
     * @param g Expected goal: none
     * @returns High confidence before kickoff and after a goal when the position lies on the own half of the field (negative X), low otherwise
     */
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    BeamTo(std::string const &id, std::string const &playerClass);
    
    void update();
  };
};

#endif

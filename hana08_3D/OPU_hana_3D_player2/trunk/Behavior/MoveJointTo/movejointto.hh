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











#ifndef _BATS_MOVEJOINTTO_HH_
#define _BATS_MOVEJOINTTO_HH_

#include "behavior.hh"
#include "types.hh"

#define MAXJOINTSPEED 10
namespace bats
{
  /** Behavior: Move an arbitrary joint to an arbitrary angle
   *
   * Move an arbitrary joint to an arbitrary angle. The index of the joint to move is read from the behavior's parameters in the configuration:
   * <code><pre>
   *  \<behavior type="MoveJoint" id="moveLeftHip">
	 *    \<param>
	 *      \<joint>1\</joint>
   *    \</param>        
   *  \</behavior>
   * </pre></code>
   */
  class MoveJointTo : public Behavior
  {
      double d_gain;
      Types::Joint d_joint;
      
      /** Generate the current goal for a slot
       *
       * @param step Step number in the sequence
       * @param slot Slot number in the step
       * @returns goal: Speed - the angular velocity in radians needed to move the joint
       */
      virtual rf<Goal> generateGoal(unsigned step, unsigned slot);

      virtual rf<State> getCurrentState() { return 0; }

      /** Get the capability of the behavior to achieve goal g from state s
       *
       * @param s Expected state: none
       * @param g Expected goal: Angle - absolute angle in radians to move the joint to, MaxSpeed (optional) - maximum angular velocity to use (negative value means double normal value)
       * @returns Always medium confidence
       */
      virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g) { return ConfidenceInterval(0.5, 0.2); }

		public:
			MoveJointTo(std::string const &id, std::string const &playerClass);
  };
};

#endif

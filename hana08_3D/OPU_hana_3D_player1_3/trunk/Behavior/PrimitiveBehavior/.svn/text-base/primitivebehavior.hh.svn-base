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










#ifndef _BATS_PRIMITIVEBEHAVIOR_HH_
#define _BATS_PRIMITIVEBEHAVIOR_HH_

#include "behavior.hh"

namespace bats
{
  /** Primitive Behavior
   *
   * This class depicts a special kind of behaviors: primitive behaviors. These behaviors form the leafs of an agent's behavior tree and are wrappers of the primitive actions that can be performed by an agent and sent to the server (e.g. move a joint and beam). New primitive behaviors should inherit from this class and implement the following methods:
   * <dl>
   *   <dt>bool run()</dt>
   *   <dd>This method is called when the primitive behavior is chosen. Here the behavior should have its logic and set its action command if necessary</dd>
   *   <dt>rf<State> getCurrentState()</dt>
   *   <dd>For different behaviors different descriptions of the current state are important. Implement this method to let the behavior create it's own description. This description will be passed to getCapability.</dd>
   *   <dt>ConfidenceInterval getCapability(State s, Goal g)</dt>
   *   <dd>With this method the behavior informs the superbehavior of the capability of performing its action in a certain state.</dd>
   * </dl>
   */
  class PrimitiveBehavior : public Behavior
  {
    protected:
      /**
       *
       * PrimitiveBehaviors have no slots, so we don't have to generate goals for them.
       * We do have to overload getCurrentstate and getCapability however, since they are used in setGoal.
       */
      virtual rf<Goal> generateGoal(unsigned step, unsigned slot)
      {
        return 0;
      }
      
      /**
       *
       * Primitive behaviors need to implement this method to perform actions;
       */
      virtual bool run() = 0;
      
    public:
      PrimitiveBehavior(std::string const &name, std::string const &id) : Behavior(name, id)
      {
      }
      
      PrimitiveBehavior(std::string const &name, std::string const &id, std::string const &playerClass) : Behavior(name, id, playerClass)
      {
      }

      /** Overloaded achieve goal
       *
       * A primitive behavior's achieve goal only calls run()
       */
      virtual bool achieveGoal()
      {
        return run();
      }
      
      /// Reset the behavior to his initial state. Removes this behavior from the list of action-command behaviors
      virtual void reset()
      {
        removeFromActionCommandBehaviors();
      }

  };
};

#endif

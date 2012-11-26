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

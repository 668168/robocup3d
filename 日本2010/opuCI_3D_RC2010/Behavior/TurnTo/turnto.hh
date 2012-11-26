#ifndef _BATS_TURNTO_HH_
#define _BATS_TURNTO_HH_

#include "behavior.hh"

namespace bats
{
  /** Behavior: Turn to an arbitrary angle
   *
   * Turn to an arbitrary angle relative to the current orientation. Sequence step 0 can be filled with a wait/stabalize behavior like ZeroSine to prevent falling over when starting to turn. Commits when the absolute value of the angle is more than 5 degrees.
   */
  class TurnTo : public Behavior
  {
    /** Generate the current goal for a slot
     *
     * @param step Step number in the sequence
     * @param slot Slot number in the step
     * @returns goal: The goal received from the super behavior (Angle) when the current step in the sequence is 1, else none
     */
    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    
    virtual rf<State> getCurrentState();
    
    
    /** Get the capability of the behavior to achieve goal g from state s
     *
     * @param s Expected state: none
     * @param g Expected goal: Angle - angle relative to the current orientation in radians (eg 0.2 = 'turn 0.2 radians to the right', -0.1 = 'turn 0.1 radians to the left)
     * @returns Always medium confidence
     */
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);

  public:
    TurnTo(std::string const &id, std::string const &playerClass);
    
    void update();
  };
};

#endif

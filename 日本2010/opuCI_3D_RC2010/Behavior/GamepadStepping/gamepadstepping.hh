#ifndef _BATS_GAMEPADSTEPPING_HH_
#define _BATS_GAMEPADSTEPPING_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadStepping : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadStepping(std::string const &id, std::string const &playerClass);
  };
};

#endif

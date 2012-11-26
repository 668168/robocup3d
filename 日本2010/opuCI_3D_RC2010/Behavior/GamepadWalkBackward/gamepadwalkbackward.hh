#ifndef _BATS_GAMEPADWALKBACKWARD_HH_
#define _BATS_GAMEPADWALKBACKWARD_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadWalkBackward : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadWalkBackward(std::string const &id, std::string const &playerClass);
  };
};

#endif

#ifndef _BATS_GAMEPADWALK_HH_
#define _BATS_GAMEPADWALK_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadWalk : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadWalk(std::string const &id, std::string const &playerClass);
  };
};

#endif

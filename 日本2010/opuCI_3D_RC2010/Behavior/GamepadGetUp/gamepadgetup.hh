#ifndef _BATS_GAMEPADGETUP_HH_
#define _BATS_GAMEPADGETUP_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadGetUp : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadGetUp(std::string const &id, std::string const &playerClass);
  };
};

#endif

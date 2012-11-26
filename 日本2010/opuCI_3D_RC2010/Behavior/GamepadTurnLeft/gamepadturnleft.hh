#ifndef _BATS_GAMEPADTURNLEFT_HH_
#define _BATS_GAMEPADTURNLEFT_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadTurnLeft : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadTurnLeft(std::string const &id, std::string const &playerClass);
  };
};

#endif

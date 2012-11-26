#ifndef _BATS_GAMEPADTURNRIGHT_HH_
#define _BATS_GAMEPADTURNRIGHT_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadTurnRight : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadTurnRight(std::string const &id, std::string const &playerClass);
  };
};

#endif

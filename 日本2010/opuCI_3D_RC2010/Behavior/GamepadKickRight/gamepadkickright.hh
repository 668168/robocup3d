#ifndef _BATS_GAMEPADKICKRIGHT_HH_
#define _BATS_GAMEPADKICKRIGHT_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadKickRight : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadKickRight(std::string const &id, std::string const &playerClass);
  };
};

#endif

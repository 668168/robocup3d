#ifndef _BATS_GAMEPADSTRAFERIGHT_HH_
#define _BATS_GAMEPADSTRAFERIGHT_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadStrafeRight : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadStrafeRight(std::string const &id, std::string const &playerClass);
  };
};

#endif

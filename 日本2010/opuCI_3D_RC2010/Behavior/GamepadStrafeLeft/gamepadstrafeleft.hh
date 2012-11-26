#ifndef _BATS_GAMEPADSTRAFELEFT_HH_
#define _BATS_GAMEPADSTRAFELEFT_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadStrafeLeft : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadStrafeLeft(std::string const &id, std::string const &playerClass);
  };
};

#endif

#ifndef _BATS_GAMEPADKICKLEFT_HH_
#define _BATS_GAMEPADKICKLEFT_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadKickLeft : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadKickLeft(std::string const &id, std::string const &playerClass);
  };
};

#endif

#ifndef _BATS_GAMEPADFALLFORWARD_HH_
#define _BATS_GAMEPADFALLFORWARD_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadFallForward : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadFallForward(std::string const &id, std::string const &playerClass);
  };
};

#endif

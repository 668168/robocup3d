#ifndef _BATS_GAMEPADFALLBACKWARD_HH_
#define _BATS_GAMEPADFALLBACKWARD_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadFallBackward : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadFallBackward(std::string const &id, std::string const &playerClass);
  };
};

#endif

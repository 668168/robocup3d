#ifndef _BATS_GAMEPADFALLRIGHTSIDE_HH_
#define _BATS_GAMEPADFALLRIGHTSIDE_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadFallRightside : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadFallRightside(std::string const &id, std::string const &playerClass);
  };
};

#endif

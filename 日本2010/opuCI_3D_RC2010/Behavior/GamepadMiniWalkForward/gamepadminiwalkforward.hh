#ifndef _BATS_GAMEPADMINIWALKFORWARD_HH_
#define _BATS_GAMEPADMINIWALKFORWARD_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadMiniWalkForward : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadMiniWalkForward(std::string const &id, std::string const &playerClass);
  };
};

#endif

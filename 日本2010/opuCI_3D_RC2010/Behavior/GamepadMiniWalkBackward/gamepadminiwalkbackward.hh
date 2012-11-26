#ifndef _BATS_GAMEPADMINIWALKBACKWARD_HH_
#define _BATS_GAMEPADMINIWALKBACKWARD_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadMiniWalkBackward : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadMiniWalkBackward(std::string const &id, std::string const &playerClass);
  };
};

#endif

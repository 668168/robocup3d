#ifndef _BATS_GAMEPADPLAY_HH_
#define _BATS_GAMEPADPLAY_HH_

#include "behavior.hh"
#include "gamepadinput.hh"
#include "math.hh"

namespace bats
{
  class GamepadPlay : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadPlay(std::string const &id, std::string const &playerClass);
  };
};

#endif

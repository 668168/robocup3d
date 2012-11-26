#ifndef _BATS_GAMEPADOMNIDIRECTIONALWALK_HH_
#define _BATS_GAMEPADOMNIDIRECTIONALWALK_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadOmnidirectionalWalk : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadOmnidirectionalWalk(std::string const &id, std::string const &playerClass);
  };
};

#endif

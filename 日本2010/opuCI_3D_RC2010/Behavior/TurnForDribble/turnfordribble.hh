#ifndef _BATS_TURNFORDRIBBLE_HH_
#define _BATS_TURNFORDRIBBLE_HH_

#include "behavior.hh"

namespace bats
{
  class TurnForDribble : public Behavior
  {
    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);

  public:
    TurnForDribble(std::string const &id, std::string const &playerClass);
     void update();
  };
};

#endif

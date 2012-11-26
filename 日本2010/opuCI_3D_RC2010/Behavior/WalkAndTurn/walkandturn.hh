#ifndef _BATS_WALKANDTURN_HH_
#define _BATS_WALKANDTURN_HH_

#include "behavior.hh"

namespace bats
{
  class WalkAndTurn : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    WalkAndTurn(std::string const &id, std::string const &playerClass);
  };
};

#endif

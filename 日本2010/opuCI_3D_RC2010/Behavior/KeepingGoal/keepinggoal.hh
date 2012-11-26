#ifndef _BATS_KEEPINGGOAL_HH_
#define _BATS_KEEPINGGOAL_HH_

#include "behavior.hh"

namespace bats
{
  class KeepingGoal : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    KeepingGoal(std::string const &id, std::string const &playerClass);
  };
};

#endif

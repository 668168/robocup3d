#ifndef _BATS_GUARDGOAL_HH_
#define _BATS_GUARDGOAL_HH_

#include "behavior.hh"

namespace bats
{
  class GuardGoal : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GuardGoal(std::string const &id, std::string const &playerClass);
  };
};

#endif

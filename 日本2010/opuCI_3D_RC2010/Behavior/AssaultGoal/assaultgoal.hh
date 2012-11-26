#ifndef _BATS_ASSAULTGOAL_HH_
#define _BATS_ASSAULTGOAL_HH_

#include "behavior.hh"

namespace bats
{
  class AssaultGoal : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    AssaultGoal(std::string const &id, std::string const &playerClass);
  };
};

#endif

#ifndef _BATS_GUARD_HH_
#define _BATS_GUARD_HH_

#include "behavior.hh"

namespace bats
{
  class Guard : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    Guard(std::string const &id, std::string const &playerClass);
  };
};

#endif

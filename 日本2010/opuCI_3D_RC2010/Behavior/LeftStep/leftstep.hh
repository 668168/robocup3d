#ifndef _BATS_LEFTSTEP_HH_
#define _BATS_LEFTSTEP_HH_

#include "behavior.hh"

namespace bats
{
  class LeftStep : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    LeftStep(std::string const &id, std::string const &playerClass);
  };
};

#endif

#ifndef _BATS_RIGHTSTEP_HH_
#define _BATS_RIGHTSTEP_HH_

#include "behavior.hh"

namespace bats
{
  class RightStep : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    RightStep(std::string const &id, std::string const &playerClass);
  };
};

#endif

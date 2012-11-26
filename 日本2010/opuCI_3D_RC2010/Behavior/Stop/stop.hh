#ifndef _BATS_STOP_HH_
#define _BATS_STOP_HH_

#include "behavior.hh"

namespace bats
{
  class Stop : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    Stop(std::string const &id, std::string const &playerClass);
  };
};

#endif

#ifndef _BATS_STANDBY_HH_
#define _BATS_STANDBY_HH_

#include "behavior.hh"

namespace bats
{
  class StandBy : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    StandBy(std::string const &id, std::string const &playerClass);
  };
};

#endif

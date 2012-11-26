#ifndef _BATS_STAY_HH_
#define _BATS_STAY_HH_

#include "behavior.hh"

namespace bats
{
  class Stay : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    Stay(std::string const &id, std::string const &playerClass);
  };
};

#endif

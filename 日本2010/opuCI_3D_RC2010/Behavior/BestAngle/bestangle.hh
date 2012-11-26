#ifndef _BATS_BESTANGLE_HH_
#define _BATS_BESTANGLE_HH_

#include "behavior.hh"

namespace bats
{
  class BestAngle : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    BestAngle(std::string const &id, std::string const &playerClass);
  };
};

#endif

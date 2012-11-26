#ifndef _BATS_FALLRIGHTSIDE_HH_
#define _BATS_FALLRIGHTSIDE_HH_

#include "behavior.hh"

namespace bats
{
  class FallRightSide : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    FallRightSide(std::string const &id, std::string const &playerClass);
  };
};

#endif

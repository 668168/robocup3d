#ifndef _BATS_FALLFORWARD_HH_
#define _BATS_FALLFORWARD_HH_

#include "behavior.hh"

namespace bats
{
  class FallForward : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    FallForward(std::string const &id, std::string const &playerClass);
  };
};

#endif

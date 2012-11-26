#ifndef _BATS_PASS_HH_
#define _BATS_PASS_HH_

#include "behavior.hh"

namespace bats
{
  class Pass : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    Pass(std::string const &id, std::string const &playerClass);
  };
};

#endif

#ifndef _BATS_INTERCEPT_HH_
#define _BATS_INTERCEPT_HH_

#include "behavior.hh"

namespace bats
{
  class Intercept : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    Intercept(std::string const &id, std::string const &playerClass);
  };
};

#endif

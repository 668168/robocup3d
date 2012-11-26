#ifndef _BATS_DIVE_HH_
#define _BATS_DIVE_HH_

#include "behavior.hh"

namespace bats
{
  class Dive : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    Dive(std::string const &id, std::string const &playerClass);
  };
};

#endif

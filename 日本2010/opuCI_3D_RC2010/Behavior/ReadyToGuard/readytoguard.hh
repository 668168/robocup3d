#ifndef _BATS_READYTOGUARD_HH_
#define _BATS_READYTOGUARD_HH_

#include "behavior.hh"

namespace bats
{
  class ReadyToGuard : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    ReadyToGuard(std::string const &id, std::string const &playerClass);
  };
};

#endif

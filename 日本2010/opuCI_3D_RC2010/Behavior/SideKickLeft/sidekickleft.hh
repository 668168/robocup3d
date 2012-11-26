#ifndef _BATS_SIDEKICKLEFT_HH_
#define _BATS_SIDEKICKLEFT_HH_

#include "behavior.hh"

namespace bats
{
  class SideKickLeft : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    SideKickLeft(std::string const &id, std::string const &playerClass);
  };
};

#endif

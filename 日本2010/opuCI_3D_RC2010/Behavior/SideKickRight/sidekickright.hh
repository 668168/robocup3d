#ifndef _BATS_SIDEKICKRIGHT_HH_
#define _BATS_SIDEKICKRIGHT_HH_

#include "behavior.hh"

namespace bats
{
  class SideKickRight : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    SideKickRight(std::string const &id, std::string const &playerClass);
  };
};

#endif

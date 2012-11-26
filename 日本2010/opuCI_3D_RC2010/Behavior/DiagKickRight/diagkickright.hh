#ifndef _BATS_DIAGKICKRIGHT_HH_
#define _BATS_DIAGKICKRIGHT_HH_

#include "behavior.hh"

namespace bats
{
  class DiagKickRight : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    DiagKickRight(std::string const &id, std::string const &playerClass);
  };
};

#endif

#ifndef _BATS_DIAGPASS_HH_
#define _BATS_DIAGPASS_HH_

#include "behavior.hh"

namespace bats
{
  class DiagPass : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    DiagPass(std::string const &id, std::string const &playerClass);
  };
};

#endif

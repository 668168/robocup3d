#ifndef _BATS_DIAGKICKLEFT_HH_
#define _BATS_DIAGKICKLEFT_HH_

#include "behavior.hh"

namespace bats
{
  class DiagKickLeft : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    DiagKickLeft(std::string const &id, std::string const &playerClass);
  };
};

#endif

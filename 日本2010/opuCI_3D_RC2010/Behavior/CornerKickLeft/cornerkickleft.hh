#ifndef _BATS_CORNERKICKLEFT_HH_
#define _BATS_CORNERKICKLEFT_HH_

#include "behavior.hh"

namespace bats
{
  class CornerKickLeft : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    CornerKickLeft(std::string const &id, std::string const &playerClass);
  };
};

#endif

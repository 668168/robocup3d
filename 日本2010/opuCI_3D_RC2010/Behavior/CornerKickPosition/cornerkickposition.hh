#ifndef _BATS_CORNERKICKPOSITION_HH_
#define _BATS_CORNERKICKPOSITION_HH_

#include "behavior.hh"

namespace bats
{
  class CornerKickPosition : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    CornerKickPosition(std::string const &id, std::string const &playerClass);
  };
};

#endif

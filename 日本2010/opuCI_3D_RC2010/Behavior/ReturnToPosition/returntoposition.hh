#ifndef _BATS_RETURNTOPOSITION_HH_
#define _BATS_RETURNTOPOSITION_HH_

#include "behavior.hh"

namespace bats
{
  class ReturnToPosition : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    ReturnToPosition(std::string const &id, std::string const &playerClass);
  };
};

#endif

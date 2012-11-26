#ifndef _BATS_DRIBBLEFORWARD_HH_
#define _BATS_DRIBBLEFORWARD_HH_

#include "behavior.hh"

namespace bats
{
  class DribbleForward : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    DribbleForward(std::string const &id, std::string const &playerClass);
  };
};

#endif

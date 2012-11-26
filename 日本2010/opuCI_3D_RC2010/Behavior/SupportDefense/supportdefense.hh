#ifndef _BATS_SUPPORTDEFENSE_HH_
#define _BATS_SUPPORTDEFENSE_HH_

#include "behavior.hh"
#include "math.hh"

namespace bats
{
  class SupportDefense : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    SupportDefense(std::string const &id, std::string const &playerClass);
  };
};

#endif

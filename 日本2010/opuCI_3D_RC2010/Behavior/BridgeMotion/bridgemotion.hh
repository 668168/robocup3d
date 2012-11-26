#ifndef _BATS_BRIDGEMOTION_HH_
#define _BATS_BRIDGEMOTION_HH_

#include "behavior.hh"

namespace bats
{
  class BridgeMotion : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    BridgeMotion(std::string const &id, std::string const &playerClass);
  };
};

#endif

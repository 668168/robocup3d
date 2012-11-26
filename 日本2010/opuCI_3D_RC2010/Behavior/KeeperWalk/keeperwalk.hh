#ifndef _BATS_KEEPERWALK_HH_
#define _BATS_KEEPERWALK_HH_

#include "behavior.hh"

namespace bats
{
  class KeeperWalk : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    KeeperWalk(std::string const &id, std::string const &playerClass);
  };
};

#endif

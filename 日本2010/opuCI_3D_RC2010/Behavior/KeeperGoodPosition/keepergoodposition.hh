#ifndef _BATS_KEEPERGOODPOSITION_HH_
#define _BATS_KEEPERGOODPOSITION_HH_

#include "behavior.hh"

namespace bats
{
  class KeeperGoodPosition : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    KeeperGoodPosition(std::string const &id, std::string const &playerClass);
  };
};

#endif

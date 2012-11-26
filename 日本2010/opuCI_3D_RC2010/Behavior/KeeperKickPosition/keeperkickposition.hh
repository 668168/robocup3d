#ifndef _BATS_KEEPERKICKPOSITION_HH_
#define _BATS_KEEPERKICKPOSITION_HH_

#include "behavior.hh"

namespace bats
{
  class KeeperKickPosition : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    KeeperKickPosition(std::string const &id, std::string const &playerClass);
  };
};

#endif

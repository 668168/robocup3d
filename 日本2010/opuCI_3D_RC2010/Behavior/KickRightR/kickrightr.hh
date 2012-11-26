#ifndef _BATS_KICKRIGHTR_HH_
#define _BATS_KICKRIGHTR_HH_

#include "behavior.hh"

namespace bats
{
  class KickRightR : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    KickRightR(std::string const &id, std::string const &playerClass);
  };
};

#endif

#ifndef _BATS_KICKSTRAIGHT_HH_
#define _BATS_KICKSTRAIGHT_HH_

#include "behavior.hh"

namespace bats
{
  class KickStraight : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    KickStraight(std::string const &id, std::string const &playerClass);
  };
};

#endif

#ifndef _BATS_KICKPOSITIONDEFENDER_HH_
#define _BATS_KICKPOSITIONDEFENDER_HH_

#include "behavior.hh"

namespace bats
{
  class KickPositionDefender : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    KickPositionDefender(std::string const &id, std::string const &playerClass);
  };
};

#endif

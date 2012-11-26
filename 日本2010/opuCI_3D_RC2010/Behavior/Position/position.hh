#ifndef _BATS_POSITION_HH_
#define _BATS_POSITION_HH_

#include "behavior.hh"

namespace bats
{
  class Position : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    Position(std::string const &id, std::string const &playerClass);
  };
};

#endif

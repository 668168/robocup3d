#ifndef _BATS_BESTPOSITION_HH_
#define _BATS_BESTPOSITION_HH_

#include "behavior.hh"

namespace bats
{
  class BestPosition : public Behavior
  {
      bool d_positioning;
    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    BestPosition(std::string const &id, std::string const &playerClass);
  };
};

#endif

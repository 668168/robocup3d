#ifndef _BATS_DRIBBLE_HH_
#define _BATS_DRIBBLE_HH_

#include "behavior.hh"

namespace bats
{
  class Dribble : public Behavior
  {
      bool d_doStabilityCheck;
      bool d_startTimeUpdated;
      double d_startTime;

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    Dribble(std::string const &id, std::string const &playerClass);

      virtual void update();
  };
};

#endif

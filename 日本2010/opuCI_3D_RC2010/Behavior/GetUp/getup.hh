#ifndef _BATS_GETUP_HH_
#define _BATS_GETUP_HH_

#include "behavior.hh"

namespace bats
{
  class GetUp : public Behavior
  {
      double d_nearBallTime; // the time when ball come near the agent
      double d_startTime;
      double d_startTimeUpdated;

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GetUp(std::string const &id, std::string const &playerClass);
      virtual void update();
  };
};

#endif

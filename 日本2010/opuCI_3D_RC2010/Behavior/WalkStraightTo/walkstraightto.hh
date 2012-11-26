#ifndef _BATS_WALKSTRAIGHTTO_HH_
#define _BATS_WALKSTRAIGHTTO_HH_

#include "behavior.hh"

namespace bats
{
  class WalkStraightTo : public Behavior
  {

    Vector3D d_lleg2;
    Vector3D d_rleg2;   
      bool d_doStabilityCheck;
      bool d_startTimeUpdated;
      double d_startTime;

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState() { return 0; }
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);

  public:
    WalkStraightTo(std::string const &id, std::string const &playerClass);
    
    virtual void update();
  };
};

#endif

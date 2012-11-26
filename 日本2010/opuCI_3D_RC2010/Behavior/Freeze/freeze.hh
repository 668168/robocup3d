#ifndef _BATS_FREEZE_HH_
#define _BATS_FREEZE_HH_

#include "behavior.hh"

namespace bats
{
  class Freeze : public Behavior
  {
      bool d_startCounting;
      double d_freezingTime;
    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    Freeze(std::string const &id, std::string const &playerClass);
      virtual void update();
  };
};

#endif

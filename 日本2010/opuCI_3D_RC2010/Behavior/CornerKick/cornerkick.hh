#ifndef _BATS_CORNERKICK_HH_
#define _BATS_CORNERKICK_HH_

#include "behavior.hh"

namespace bats
{
  class CornerKick : public Behavior
  {
    enum Corner {
      FLAG1,
      FLAG2,
      NONE
    };

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);

    static Corner s_kickPos;
  public:
    CornerKick(std::string const &id, std::string const &playerClass);

    virtual void update();
  };
};

#endif

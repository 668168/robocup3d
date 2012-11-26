#ifndef _BATS_KICKLEFTL_HH_
#define _BATS_KICKLEFTL_HH_

#include "behavior.hh"

namespace bats
{
  class KickLeftL : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    KickLeftL(std::string const &id, std::string const &playerClass);
  };
};

#endif

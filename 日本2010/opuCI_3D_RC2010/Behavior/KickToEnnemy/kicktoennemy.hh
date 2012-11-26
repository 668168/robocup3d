#ifndef _BATS_KICKTOENNEMY_HH_
#define _BATS_KICKTOENNEMY_HH_

#include "behavior.hh"

namespace bats
{
  class KickToEnnemy : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    KickToEnnemy(std::string const &id, std::string const &playerClass);
  };
};

#endif

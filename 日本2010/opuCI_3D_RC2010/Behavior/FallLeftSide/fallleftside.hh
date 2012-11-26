#ifndef _BATS_FALLLEFTSIDE_HH_
#define _BATS_FALLLEFTSIDE_HH_

#include "behavior.hh"

namespace bats
{
  class FallLeftSide : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    FallLeftSide(std::string const &id, std::string const &playerClass);
  };
};

#endif

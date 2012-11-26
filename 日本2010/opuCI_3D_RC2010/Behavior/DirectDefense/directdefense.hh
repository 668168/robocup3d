#ifndef _BATS_DIRECTDEFENSE_HH_
#define _BATS_DIRECTDEFENSE_HH_

#include "behavior.hh"

namespace bats
{
  class DirectDefense : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    DirectDefense(std::string const &id, std::string const &playerClass);
  };
};

#endif

#ifndef _BATS_FACEKICKRIGHT_HH_
#define _BATS_FACEKICKRIGHT_HH_

#include "behavior.hh"

namespace bats
{
  class FaceKickRight : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    FaceKickRight(std::string const &id, std::string const &playerClass);
  };
};

#endif

#ifndef _BATS_FACEKICKLEFT_HH_
#define _BATS_FACEKICKLEFT_HH_

#include "behavior.hh"

namespace bats
{
  class FaceKickLeft : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    FaceKickLeft(std::string const &id, std::string const &playerClass);
  };
};

#endif

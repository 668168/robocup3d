#ifndef _BATS_WAVEBOTHARMS_HH_
#define _BATS_WAVEBOTHARMS_HH_

#include "behavior.hh"

namespace bats
{
  class WaveBothArms : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    WaveBothArms(std::string const &id, std::string const &playerClass);
  };
};

#endif

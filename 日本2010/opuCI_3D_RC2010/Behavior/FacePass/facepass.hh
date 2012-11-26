#ifndef _BATS_FACEPASS_HH_
#define _BATS_FACEPASS_HH_

#include "behavior.hh"

namespace bats
{
  class FacePass : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    FacePass(std::string const &id, std::string const &playerClass);
  };
};

#endif

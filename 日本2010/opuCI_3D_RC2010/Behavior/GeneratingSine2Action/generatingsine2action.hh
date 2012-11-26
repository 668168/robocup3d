#ifndef _BATS_GENERATINGSINE2ACTION_HH_
#define _BATS_GENERATINGSINE2ACTION_HH_

#include "behavior.hh"

namespace bats
{
  class GeneratingSine2Action : public Behavior
  {
    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);

  public:
    GeneratingSine2Action(std::string const &id, std::string const &playerClass);
  };
};

#endif

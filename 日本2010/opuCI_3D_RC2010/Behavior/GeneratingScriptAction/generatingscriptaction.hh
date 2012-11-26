#ifndef _BATS_GENERATINGSCRIPTACTION_HH_
#define _BATS_GENERATINGSCRIPTACTION_HH_

#include "behavior.hh"

namespace bats
{
  class GeneratingScriptAction : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GeneratingScriptAction(std::string const &id, std::string const &playerClass);
  };
};

#endif

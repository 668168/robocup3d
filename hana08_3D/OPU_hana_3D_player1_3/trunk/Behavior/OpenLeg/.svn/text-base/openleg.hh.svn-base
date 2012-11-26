#ifndef _BATS_OPENLEG_HH_
#define _BATS_OPENLEG_HH_

#include "behavior.hh"
#include "types.hh"

namespace bats
{
  class OpenLeg : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    OpenLeg(std::string const &id, std::string const &playerClass);
	
	virtual void update();
	
  };
};

#endif

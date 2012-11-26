#ifndef _BATS_BLOCK_HH_
#define _BATS_BLOCK_HH_

#include "behavior.hh"

namespace bats
{
  class Block : public Behavior
  {
      double d_ballHoldTime;

      virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
      virtual rf<State> getCurrentState();
      virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    Block(std::string const &id, std::string const &playerClass);
      virtual void update();
  };
};

#endif

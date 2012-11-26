#ifndef _BATS_GAMEPADBEAM_HH_
#define _BATS_GAMEPADBEAM_HH_

#include "behavior.hh"

namespace bats
{
  class GamepadBeam : public Behavior
  {
    float d_x;
    float d_y;
    float d_z;

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    GamepadBeam(std::string const &id, std::string const &playerClass);
  };
};

#endif

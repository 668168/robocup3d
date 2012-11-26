#include "sidekickright.ih"

Behavior::ConfidenceInterval SideKickRight::getCapability(rf<State> s, rf<Goal> g)
{
  return ConfidenceInterval(0.5, 0.2);
}

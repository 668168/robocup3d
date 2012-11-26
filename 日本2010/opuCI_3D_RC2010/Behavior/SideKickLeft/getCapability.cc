#include "sidekickleft.ih"

Behavior::ConfidenceInterval SideKickLeft::getCapability(rf<State> s, rf<Goal> g)
{
  return ConfidenceInterval(0.5, 0.2);
}

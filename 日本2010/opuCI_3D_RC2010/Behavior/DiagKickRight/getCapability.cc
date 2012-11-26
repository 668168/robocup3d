#include "diagkickright.ih"

Behavior::ConfidenceInterval DiagKickRight::getCapability(rf<State> s, rf<Goal> g)
{
  return ConfidenceInterval(0.5, 0.2);
}

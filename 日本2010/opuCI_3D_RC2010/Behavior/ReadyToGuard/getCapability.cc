#include "readytoguard.ih"

Behavior::ConfidenceInterval ReadyToGuard::getCapability(rf<State> s, rf<Goal> g)
{
  return ConfidenceInterval(0.21, 0.2);
}

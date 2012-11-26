#include "diagpass.ih"

Behavior::ConfidenceInterval DiagPass::getCapability(rf<State> s, rf<Goal> g)
{
  return ConfidenceInterval(0.5, 0.2);
}

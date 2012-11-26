#include "cornerkickposition.ih"

Behavior::ConfidenceInterval CornerKickPosition::getCapability(rf<State> s, rf<Goal> g)
{
  return ConfidenceInterval(0.5, 0.0);
}

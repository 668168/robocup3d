#include "stay.ih"

Behavior::ConfidenceInterval Stay::getCapability(rf<State> s, rf<Goal> g)
{
  Vector3D pos = g->getVector("Pos");

  if(pos.length() < 0.3)
    return ConfidenceInterval(0.6, 0.2);

  return ConfidenceInterval(0.0, 0.2);
}

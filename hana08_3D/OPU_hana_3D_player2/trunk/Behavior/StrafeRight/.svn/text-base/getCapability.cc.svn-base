#include "straferight.ih"

Behavior::ConfidenceInterval StrafeRight::getCapability(rf<State> s, rf<Goal> g)
{
  Vector3D pos = g->getVector("Pos");

  _debugLevel4(ident() << " pos: " << pos);
    
  //WorldModel& wm = WorldModel::getInstance();
  
  if (fabs(pos.getY()) > fabs(pos.getX()) && pos.getY() < 0.0)
    return ConfidenceInterval(0.5, 0.2);

  return ConfidenceInterval(0.0, 0.0);
}

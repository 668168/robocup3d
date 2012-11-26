#include "miniwalkforward.ih"

Behavior::ConfidenceInterval MiniWalkForward::getCapability(rf<State> s, rf<Goal> g)
{
  Vector3D pos = g->getVector("Pos");

  _debugLevel4(ident() << " pos: " << pos);
  
  //WorldModel& wm = WorldModel::getInstance();
  
  if (fabs(pos.getX()) > fabs(pos.getY()) && pos.getX() > 0.0)
    return ConfidenceInterval(0.5, 0.2);
    
  return ConfidenceInterval(0.0, 0.2);
}

#include "keepergetup.ih"

Behavior::ConfidenceInterval KeeperGetUp::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

  _debugLevel4(fabs(wm.getDistToField()));
  return fabs(wm.getDistToField()) < 1.5 && ballPos.length() > 5 ? ConfidenceInterval(0.8, 0.2) : ConfidenceInterval(0.0, 0.0);
}

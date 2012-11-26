#include "keepergoodposition.ih"

Behavior::ConfidenceInterval KeeperGoodPosition::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();

  Vector3D homePos = g->getVector("HomePos");

  stringstream ss;
  ss << "(KeeperGoodPos) home = " << homePos;

  wm.addDebugMessage(WorldModel::COMMENT, ss.str());

  // ホームポジションまで距離があれば実行
  if( homePos.length() > 0.3 )
  {
    return ConfidenceInterval(0.8, 0.0);
  }

  return ConfidenceInterval(0.0, 0.0);
}

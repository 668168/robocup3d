#include "standby.ih"

Behavior::ConfidenceInterval StandBy::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();

  // 自殺モードかつ初期位置を記憶した後は
  // Beam < StandBy < SineAction となるようにする
  if((wm.getDeadTime() != 0)
     && (wm.getDeadTime() < 9000))
  {
    wm.addDebugMessage(WorldModel::COMMENT,"StandBy for GA!");
    return ConfidenceInterval(1.4, 0.0);
  }
  return ConfidenceInterval(0.4, 0.0);

}

#include "walkstraightto.ih"

Behavior::ConfidenceInterval WalkStraightTo::getCapability(rf<Behavior::State> s, rf<Behavior::Goal> g)
{
  Vector3D pos = g->getVector("Pos");
  WorldModel& wm = WorldModel::getInstance();
  pos.setZ(0);
  Vector3D straight(1, 0, 0);

  double angleToPos = pos.angle(straight) / M_PI * 180;

  double angle = 15.0;

  // ボールが視認できている & 目標までの角度がangle未満
  if (angleToPos < angle && wm.visibleObject(Types::BALL))// || !wm.onMyFeet())
  {
    // 安定性チェックがオン かつ いずれかの足が不安定
    if(d_doStabilityCheck && (wm.isUnstable(Types::LFOOT) || wm.isUnstable(Types::RFOOT)) )
    {
      d_doStabilityCheck = false;
      d_startTimeUpdated = false;
      wm.setFreeze(true);
      return ConfidenceInterval(0.2, 0.0);
    }

    // 行動開始時間が記録されていない
    if(!d_startTimeUpdated)
    {
      d_startTime = wm.getTime();
      d_startTimeUpdated = true;
    }
    return ConfidenceInterval(0.9, 0.0);
  }

  d_startTimeUpdated = false;
  return ConfidenceInterval(0.0, 0.0);

}

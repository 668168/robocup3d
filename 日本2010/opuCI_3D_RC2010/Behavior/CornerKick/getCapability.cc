#include "cornerkick.ih"

Behavior::ConfidenceInterval CornerKick::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  WorldModel::PlayMode pm = wm.getPlayMode();

  Vector3D ball = wm.getObjectPosition(Types::BALL).getMu();
  Vector3D flag1them = wm.getObjectPosition(Types::FLAG1THEM).getMu();
  Vector3D flag2them = wm.getObjectPosition(Types::FLAG2THEM).getMu();
  Vector3D flag1us = wm.getObjectPosition(Types::FLAG1US).getMu();
  Vector3D flag2us = wm.getObjectPosition(Types::FLAG2US).getMu();
  double shortDist = 5.0;

  if( ( pm == WorldModel::CORNER_KICK_US ||
        ( pm == WorldModel::CORNER_KICK_RIGHT && wm.getSide() == WorldModel::RIGHT) ||
        ( pm == WorldModel::CORNER_KICK_LEFT  && wm.getSide() == WorldModel::LEFT) ) || // コーナーキック
      ( pm == WorldModel::PLAY_ON &&
        ( (ball-flag1them).length() < shortDist || (ball-flag2them).length() < shortDist
          || (ball-flag1us).length() < shortDist || (ball-flag2us).length() < shortDist
        ) && ! wm.allObjectPosAvailable()) ) // flag周辺にボールがあってアプローチしづらい場合
  {
    wm.addDebugMessage(WorldModel::COMMENT, "Try to Corner Kick!");
    // larger than Search(0.8) and smaller than WaitAndSee(0.75) 無理やんけ
    if(wm.getATattacking())
      return ConfidenceInterval(0.9, 0.0);
  }

  return ConfidenceInterval(0.0, 0.0);
}

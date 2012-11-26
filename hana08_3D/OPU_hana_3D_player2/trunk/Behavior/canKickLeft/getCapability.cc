#include "cankickleft.ih"

Behavior::ConfidenceInterval CanKickLeft::getCapability(rf<Behavior::State> s, rf<Behavior::Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

  Vector3D ourGoalPos = (wm.getObjectPosition(Types::GOAL1US).getMu() + wm.getObjectPosition(Types::GOAL2US).getMu()) / 2;

  if (ballPos.getX() >= 0 && ballPos.getX() <= 0.15 && ballPos.getY() >= 0 && ballPos.getY() <= 0.07)
    return ConfidenceInterval(0.7, 0.2);
    
  return ConfidenceInterval(-1.0, 0.0);
}

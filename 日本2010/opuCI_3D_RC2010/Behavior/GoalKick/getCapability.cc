#include "goalkick.ih"

Behavior::ConfidenceInterval GoalKick::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  Vector3D ourGoal = (wm.getObjectPosition(Types::GOAL1US).getMu()
                      + wm.getObjectPosition(Types::GOAL2US).getMu()) / 2.0;


  // 正しい意味でのゴールキック
  if(wm.getPlayMode() == WorldModel::GOAL_KICK_US)
  {
    return ConfidenceInterval(1.0, 0.0);
  }

  // ゴールキックというか，クリア
  double near = 3.0; // これ以内は近いと判断
  if((ballPos - ourGoal).length() < near)
  {
    return ConfidenceInterval(0.8, 0.0);
  }

  return ConfidenceInterval(0.1, 0.0);
}

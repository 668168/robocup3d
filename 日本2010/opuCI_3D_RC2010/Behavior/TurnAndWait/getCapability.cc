#include "turnandwait.ih"

Behavior::ConfidenceInterval TurnAndWait::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();

  if( wm.getPlayMode() == WorldModel::GOAL_KICK_US ||
      wm.getPlayMode() == WorldModel::GOAL_KICK_THEM )
  return ConfidenceInterval(0.95, 0.0);
}

#include "dribble.ih"

Behavior::ConfidenceInterval Dribble::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();

  if( ! wm.visibleObject(Types::BALL) )
    return ConfidenceInterval(0.1, 0.0);

  // if a ball exists in front of toe, tries to dribble
  if(ballKickableByRight(0.12, 1.0) || ballKickableByLeft(0.12, 1.0))
  {
    // stability check!
    if(d_doStabilityCheck && (wm.isUnstable(Types::LFOOT) || wm.isUnstable(Types::RFOOT)))
    {
      d_doStabilityCheck = false;
      d_startTimeUpdated = false;
      wm.setFreeze(true);
      return ConfidenceInterval(0.2, 0.0);
    }
    if(!d_startTimeUpdated)
    {
      d_startTime = wm.getTime();
      d_startTimeUpdated = true;
    }

    return ConfidenceInterval(0.7, 0.0);
  }
  d_startTimeUpdated = false;

  return  ConfidenceInterval(0.25, 0.0);
}

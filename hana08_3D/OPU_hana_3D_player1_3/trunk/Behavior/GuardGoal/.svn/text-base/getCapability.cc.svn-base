#include "guardgoal.ih"

Behavior::ConfidenceInterval GuardGoal::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();

  if (d_curStep == 1)
  {
    // If we arent turned right in step 1 we cant do it
    Vector3D goalLine = wm.getObjectPosition(Types::GOAL1US).getMu() - wm.getObjectPosition(Types::GOAL2US).getMu();
    goalLine.setZ(0);
    Vector3D straight(1, 0, 0);
    double alpha = straight.angle(Math::calcPerpend(goalLine));
    if (fabs(alpha) > .1 * M_PI)
    {
      //cerr << "Turn!" << endl;
      return ConfidenceInterval(0.0, 0.0);
    }
  }
  
  if (fabs(WorldModel::getInstance().getDistToField()) < 1.5)
  {
    _debugLevel1("Too close to floor");
    return ConfidenceInterval(0.0, 0.0);
  }
  
  /*if (d_ballEndPos.length() < 0.2)
  {
    return ConfidenceInterval(0.3, 0.2);
  }
  
  if (d_ballEndPos.length() > 2)
    return ConfidenceInterval(0.6, 0.2);*/

  return ConfidenceInterval(0.5, 0.2);
}

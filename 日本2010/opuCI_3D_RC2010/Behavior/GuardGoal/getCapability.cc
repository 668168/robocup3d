#include "guardgoal.ih"

Behavior::ConfidenceInterval GuardGoal::getCapability(rf<State> s, rf<Goal> g)
{
  // Block or WaitForBall or Intercept
    WorldModel& wm = WorldModel::getInstance();
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

    double angletoBall = getAngleWithStraight(ballPos);

    if(wm.visibleObject(Types::BALL) && ballPos.length() < 1.5)
    {
	return ConfidenceInterval(0.1, 0.0);
    }
    
    return ConfidenceInterval(0.65, 0.0);
}

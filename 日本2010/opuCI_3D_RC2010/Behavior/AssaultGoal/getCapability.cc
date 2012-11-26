#include "assaultgoal.ih"

Behavior::ConfidenceInterval AssaultGoal::getCapability(rf<State> s, rf<Goal> g)
{
  // if attacker is near opponent's goal, assault ball and goal.
  WorldModel& wm = WorldModel::getInstance();

  if( wm.allObjectPosAvailable() )
  {
    return ConfidenceInterval(0.1, 0.0);
  }
  else if( wm.visibleObject(Types::BALL) )
  {
    Vector3D ball = wm.getObjectPosition(Types::BALL).getMu();
    Vector3D goal1 = wm.getObjectPosition(Types::GOAL1THEM).getMu();
    Vector3D goal2 = wm.getObjectPosition(Types::GOAL2THEM).getMu();

    if( ( wm.visibleObject(Types::GOAL1THEM) && ball.getY() > goal1.getY() )
        || ( wm.visibleObject(Types::GOAL2THEM) && ball.getY() < goal2.getY() ) )
    {
      wm.setDebugMessage(WorldModel::COMMENT, "Assault Goal!!");
      return ConfidenceInterval(0.92, 0.0);
    }
  }

  return ConfidenceInterval(0.14, 0.0);

}

#include "turnandwait.ih"

rf<Behavior::Goal> TurnAndWait::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  WorldModel& wm = WorldModel::getInstance();
  Vector3D ogoal = ( wm.getObjectPosition(Types::GOAL1THEM).getMu()
                    + wm.getObjectPosition(Types::GOAL2THEM).getMu()
                    - wm.getObjectPosition(Types::GOAL1US).getMu()
                    - wm.getObjectPosition(Types::GOAL2US).getMu());
  Vector3D ball = wm.getObjectPosition(Types::BALL).getMu();

  double target = 0;

  if( wm.allObjectPosAvailable() )
  {
    target = getAngleWithStraight(ogoal);
  }
  else if( wm.visibleObject(Types::BALL))
  {
    target = getAngleWithStraight(ball);
  }

  con->addVar("Angle", target, target);
  con->addVar("MinAngle", 15, 15);
  
  return goal;
}

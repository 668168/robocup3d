#include "bestangle.ih"

rf<Behavior::Goal> BestAngle::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  WorldModel& wm = WorldModel::getInstance();

  Vector3D ballToGoal =
    ( wm.getObjectPosition(Types::GOAL1THEM).getMu()
      + wm.getObjectPosition(Types::GOAL2THEM).getMu() ) / 2.0
    - wm.getObjectPosition(Types::BALL).getMu();

  double targetAngle = getAngleWithStraight(ballToGoal);
  double minAngle = 5;

  con->addVar("Angle", targetAngle, targetAngle);
  con->addVar("MinAngle", minAngle, minAngle);
  
  return goal;
}

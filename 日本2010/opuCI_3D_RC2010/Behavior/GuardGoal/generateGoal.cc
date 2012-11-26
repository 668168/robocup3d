#include "guardgoal.ih"

rf<Behavior::Goal> GuardGoal::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  // con->addVar("Var", 0, 1);
  WorldModel& wm = WorldModel::getInstance();
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  double angleToPos;
  ballPos.setZ(0);
  if(!wm.visibleObject(Types::BALL))
  {
      angleToPos = 120.0;
  }
  else
    angleToPos = getAngleWithStraight(ballPos);

  con->addVar("Angle", angleToPos, angleToPos);
//  con->addVar("TObject", Types::BALL, Types::BALL);

  return goal;
}

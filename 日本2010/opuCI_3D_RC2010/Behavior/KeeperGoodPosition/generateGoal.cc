#include "keepergoodposition.ih"

rf<Behavior::Goal> KeeperGoodPosition::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  WorldModel& wm = WorldModel::getInstance();

  Vector3D homePos = d_goal->getVector("HomePos");

  double angle = getAngleWithStraight(wm.getObjectPosition(Types::BALL).getMu());

  con->addVar("Pos", homePos);

  con->addVar("Angle", angle, angle);


  return goal;
}

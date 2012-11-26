#include "canturnright.ih"

rf<Behavior::Goal> CanTurnRight::generateGoal(unsigned step, unsigned slot)
{
  d_committed = true;

  _debugLevel4("CanTurnRight::generateGoal " << step << " " << slot);
  WorldModel& wm = WorldModel::getInstance();
  
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

//  Vector3D normal = wm.getFieldNormal();
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  ballPos.setZ(0);
  Vector3D straight(1,0,0);

  double angle = 0.0;
//  double angleToBall = straight.angle(ballPos) / M_PI * 180;
//  std::cout << "CanTurnRight::generateGoal()" << std::endl << "  angleToBall = " << angleToBall << std::endl;

//  con->addVar("Angle", angleToBall, angleToBall);
  con->addVar("Angle", angle, angle);
  return goal;

//  return d_goal;
}

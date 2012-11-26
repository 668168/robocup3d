#include "cankickright.ih"

rf<Behavior::Goal> CanKickRight::generateGoal(unsigned step, unsigned slot)
{
/*
  _debugLevel4("CanKickRight::generateGoal " << step << " " << slot);
  WorldModel& wm = WorldModel::getInstance();
  
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  Vector3D normal = wm.getFieldNormal();

  double angle = 0.0;

  con->addVar("Angle", angle, angle);
*/
  return d_goal;
//  return goal;
}

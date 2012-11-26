#include "cankickleft.ih"

rf<Behavior::Goal> CanKickLeft::generateGoal(unsigned step, unsigned slot)
{
  _debugLevel4("CanKickLeft::generateGoal " << step << " " << slot);
  WorldModel& wm = WorldModel::getInstance();
  
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  Vector3D normal = wm.getFieldNormal();

  double angle = 0.0;

  con->addVar("Angle", angle, angle);

  return goal;
}

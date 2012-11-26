#include "walkstraightto.ih"

rf<Behavior::Goal> WalkStraightTo::generateGoal(unsigned step, unsigned slot)
{
  d_committed = true;
  
  _debugLevel4("WalkStraightTo::generateGoal " << step << " " << slot);
  WorldModel& wm = WorldModel::getInstance();
  
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

//  Vector3D normal = wm.getFieldNormal();

  double angle = 0.0;
  
  con->addVar("Angle", angle, angle);

  return goal;
}

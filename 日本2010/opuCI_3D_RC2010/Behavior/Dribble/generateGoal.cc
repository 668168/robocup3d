#include "dribble.ih"

rf<Behavior::Goal> Dribble::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  WorldModel& wm = WorldModel::getInstance();

  return d_goal;
}

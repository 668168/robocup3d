#include "kickstraight.ih"

rf<Behavior::Goal> KickStraight::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  return d_goal;
}

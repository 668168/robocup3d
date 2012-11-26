#include "gamepadomnidirectionalwalk.ih"

rf<Behavior::Goal> GamepadOmnidirectionalWalk::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  return d_goal;
}

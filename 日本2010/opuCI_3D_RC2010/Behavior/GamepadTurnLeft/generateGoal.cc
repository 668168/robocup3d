#include "gamepadturnleft.ih"

rf<Behavior::Goal> GamepadTurnLeft::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  // con->addVar("Var", 0, 1);
  
  return d_goal;
}

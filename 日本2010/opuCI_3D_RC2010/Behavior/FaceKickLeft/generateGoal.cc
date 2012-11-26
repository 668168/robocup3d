#include "facekickleft.ih"

rf<Behavior::Goal> FaceKickLeft::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  // con->addVar("Var", 0, 1);
  
  return goal;
}

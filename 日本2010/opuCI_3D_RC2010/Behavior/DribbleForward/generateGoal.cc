#include "dribbleforward.ih"

rf<Behavior::Goal> DribbleForward::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  con->addVar("Weight1", 1, 1); // forward
  con->addVar("Weight2", 0, 0); // backward
  
  return goal;
}

#include "getfromside.ih"

rf<Behavior::Goal> GetFromSide::generateGoal(unsigned step, unsigned slot)
{
  d_committed = true;

  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  // con->addVar("Var", 0, 1);
  
  return goal;
}

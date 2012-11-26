#include "standby.ih"

rf<Behavior::Goal> StandBy::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  con->addVar("Weight1", 0.1, 0.1);

  return goal;
}

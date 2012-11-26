#include "turnto.ih"

rf<Behavior::Goal> TurnTo::generateGoal(unsigned step, unsigned slot)
{
  
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  rf<StateVarNode> angleNode = rf_cast<StateVarNode>(d_goal->findDeep("Angle"));
  StateVar angleVar = angleNode->getVar();
  double angle = angleVar.second.mean();

   con->addVar("Angle", angle, angle);

  return goal;
}

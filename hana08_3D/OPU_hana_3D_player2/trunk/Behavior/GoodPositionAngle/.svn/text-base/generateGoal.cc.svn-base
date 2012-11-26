#include "goodpositionangle.ih"

rf<Behavior::Goal> GoodPositionAngle::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  
  rf<StateVarNode> angleNode = rf_cast<StateVarNode>(d_goal->findDeep("Angle"));
  StateVar angleVar = angleNode->getVar();
  double angle = angleVar.second.mean();
  if (step == 0) // good position
      con->addVar("Pos", d_goal->getVector("Pos"));
  else if (step == 1){ // turn to
    con->addVar("Angle", angle, angle);
	con->addVar("Pos", d_goal->getVector("Pos"));
  }
  
  return goal;
}

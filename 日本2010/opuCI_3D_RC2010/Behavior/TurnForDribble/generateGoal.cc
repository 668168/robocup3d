#include "turnfordribble.ih"

rf<Behavior::Goal> TurnForDribble::generateGoal(unsigned step, unsigned slot)
{
  WorldModel& wm = WorldModel::getInstance();
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  rf<StateVarNode> angleNode = rf_cast<StateVarNode>(d_goal->findDeep("Angle"));
  StateVar angleVar = angleNode->getVar();
  double angle = angleVar.second.mean();

  /*
  if(fabs(angle) < 70 ) {
    //  std::cout << "TurnForDribble::generateGoal  ball: forward ";
    targetAngle = angle;
  }
  else if(angle > 0) {
    //std::cout << "TurnForDribble::generateGoal  ball: left ";
    targetAngle = angle - 90;
  }
  else if(angle < 0){
    //std::cout << "TurnForDribble::generateGoal  ball: right ";
    targetAngle = angle + 90;
  }

  con->addVar("Angle", targetAngle, targetAngle);
  // con->addVar("Var", 0, 1);
  std::stringstream ss;
  ss << " (TurnForDribble) " << targetAngle;
  wm.addDebugMessage(WorldModel::COMMENT, ss.str());
  */
  double weight1 = 0, weight2 = 0;

  if ( angle < 0 )
    weight1 = 1; // left
  else
    weight2 = 1; // right

  con->addVar("Weight1", weight1, weight1);
  con->addVar("Weight2", weight2, weight2);

  return goal;
}

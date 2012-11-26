#include "turnfordribble.ih"

Behavior::ConfidenceInterval TurnForDribble::getCapability(rf<State> s, rf<Goal> g)
{
  rf<StateVarNode> angleNode = rf_cast<StateVarNode>(g->findDeep("Angle"));
  StateVar angleVar = angleNode->getVar();
  double angle = angleVar.second.mean();
    
  if(angle > 5.0) // left
    return ConfidenceInterval(0.7, 0);
  else if(angle < -5.0) // right
    return ConfidenceInterval(0.7, 0);

  return ConfidenceInterval(-1.0, 0.0);

}

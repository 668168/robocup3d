#include "gamepadfallforward.ih"

Behavior::ConfidenceInterval GamepadFallForward::getCapability(rf<State> s, rf<Goal> g)
{
  rf<StateVarNode> node = rf_cast<StateVarNode>(g->findDeep("GamepadFallForward"));
  if(node)
    return ConfidenceInterval(node->getVar().second.mean(), 0.0);

  return ConfidenceInterval(0, 0.2);
}

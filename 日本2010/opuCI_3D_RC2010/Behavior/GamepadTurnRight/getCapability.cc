#include "gamepadturnright.ih"

Behavior::ConfidenceInterval GamepadTurnRight::getCapability(rf<State> s, rf<Goal> g)
{
  rf<StateVarNode> node = rf_cast<StateVarNode>(g->findDeep("GamepadTurnRight"));
  if(node)
    return ConfidenceInterval(node->getVar().second.mean(), 0.0);

  return ConfidenceInterval(0, 0.2);
}

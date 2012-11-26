#include "gamepadkickleft.ih"

Behavior::ConfidenceInterval GamepadKickLeft::getCapability(rf<State> s, rf<Goal> g)
{
  rf<StateVarNode> node = rf_cast<StateVarNode>(g->findDeep("GamepadKickLeft"));
  if(node)
    return ConfidenceInterval(node->getVar().second.mean(), 0.0);

  return ConfidenceInterval(0, 0.2);
}

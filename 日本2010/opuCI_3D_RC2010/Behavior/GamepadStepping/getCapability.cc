#include "gamepadstepping.ih"

Behavior::ConfidenceInterval GamepadStepping::getCapability(rf<State> s, rf<Goal> g)
{
  rf<StateVarNode> node = rf_cast<StateVarNode>(g->findDeep("GamepadStepping"));
  if(node)
    return ConfidenceInterval(node->getVar().second.mean(), 0.0);

  return ConfidenceInterval(0.2, 0.0);
}

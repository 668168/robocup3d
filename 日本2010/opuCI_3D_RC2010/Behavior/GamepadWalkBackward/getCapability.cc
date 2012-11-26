#include "gamepadwalkbackward.ih"

Behavior::ConfidenceInterval GamepadWalkBackward::getCapability(rf<State> s, rf<Goal> g)
{
  rf<StateVarNode> node = rf_cast<StateVarNode>(g->findDeep("GamepadWalkBackward"));
  if(node)
    return ConfidenceInterval(node->getVar().second.mean(), 0.0);

  return ConfidenceInterval(0.0, 0.0);
}

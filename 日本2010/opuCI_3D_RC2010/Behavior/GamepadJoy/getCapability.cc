#include "gamepadjoy.ih"

Behavior::ConfidenceInterval GamepadJoy::getCapability(rf<State> s, rf<Goal> g)
{
  rf<StateVarNode> node = rf_cast<StateVarNode>(g->findDeep("GamepadJoy"));
  if(node)
    return ConfidenceInterval(node->getVar().second.mean(), 0.0);

  return ConfidenceInterval(0.0, 0.2);

}

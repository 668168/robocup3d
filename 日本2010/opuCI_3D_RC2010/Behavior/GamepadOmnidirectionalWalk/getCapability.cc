#include "gamepadomnidirectionalwalk.ih"

Behavior::ConfidenceInterval GamepadOmnidirectionalWalk::getCapability(rf<State> s, rf<Goal> g)
{
  rf<StateVarNode> node = rf_cast<StateVarNode>(g->findDeep("GamepadOmnidirectionalWalk"));
  if(node)
    return ConfidenceInterval(node->getVar().second.mean(), 0.0);

  return ConfidenceInterval(0.2, 0.0);
}

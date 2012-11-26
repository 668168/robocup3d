#include "beam.ih"

Behavior::ConfidenceInterval Beam::getCapability(rf<Behavior::State> s, rf<Behavior::Goal> g)
{
//  _debugLevel4("Beam::getCapability");

  rf<StateVarNode> playModeNode, xNode;
  
  playModeNode = rf_cast<StateVarNode>(s->findDeep("PlayMode"));
//  std::cout << "gameStateNode::getVar() = (" << playModeNode->getVar().first << "  " << playModeNode->getVar().second.first << " " << playModeNode->getVar().second.second << ")" << std::endl;
  
  if(!playModeNode)
  {
    _debugLevel1("Beam doesn't understand state!");
    return ConfidenceInterval(-1.0, 0.0);
  }
      
  StateVar playMode = playModeNode->getVar();
  
  // If we aren't in BEFORE_KICKOFF, our capability is -1.0 with infinite confidence
  if ((int)playMode.second.first != WorldModel::BEFORE_KICKOFF &&
      (int)playMode.second.first != WorldModel::GOAL_US && (int)playMode.second.first != WorldModel::GOAL_THEM &&
      (int)playMode.second.first != WorldModel::GOAL_LEFT && (int)playMode.second.first != WorldModel::GOAL_RIGHT )
    return ConfidenceInterval(-1.0, 0.0);
  
  if (!(xNode = rf_cast<StateVarNode>(g->findDeep("X"))))
  {
    _debugLevel1("Beam doesn't understand goal!");
    return ConfidenceInterval(-1.0, 0.0);
  }
    
  StateVar x = xNode->getVar();
  Range xRange = x.second;
  
  double xTarget = (xRange.first + xRange.second) / 2.0;
  
  // If we want to beam to a position on other side of the field, we can't do it either
  if (xTarget > 0)
    return ConfidenceInterval(-1.0, 0.0);
  
  // Else we can certainly do it
  return ConfidenceInterval(1.0, 0.0);
}

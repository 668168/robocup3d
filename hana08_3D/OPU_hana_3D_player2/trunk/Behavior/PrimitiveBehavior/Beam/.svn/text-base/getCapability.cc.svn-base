#include "beam.ih"

Behavior::ConfidenceInterval Beam::getCapability(rf<Behavior::State> s, rf<Behavior::Goal> g)
{
//  _debugLevel4("Beam::getCapability");
//  std::cout << "Beam::getCapability " << s << " " << g << std::endl;

  rf<StateVarNode> playModeNode, xNode;
  
  playModeNode = rf_cast<StateVarNode>(s->findDeep("PlayMode"));
//  std::cout << "gameStateNode::getVar() = (" << playModeNode->getVar().first << "  " << playModeNode->getVar().second.first << " " << playModeNode->getVar().second.second << ")" << std::endl;
  
  if(!playModeNode)
  {
    _debugLevel1("Beam doesn't understand state!");
    return ConfidenceInterval(-1.0, 0.0);
  }
//  std::cout << "Pass !playModeNode" << std::endl;
      
  StateVar playMode = playModeNode->getVar();
  
  // If we aren't in BEFORE_KICKOFF, our capability is -1.0 with infinite confidence
  if ((int)playMode.second.first != WorldModel::BEFORE_KICKOFF)
    return ConfidenceInterval(-1.0, 0.0);
//  std::cout << "Pass (int)playMode.second.first != WorldModel::BEFORE_KICKOFF" << std::endl;
  
  if (!(xNode = rf_cast<StateVarNode>(g->findDeep("X"))))
  {
    _debugLevel1("Beam doesn't understand goal!");
    return ConfidenceInterval(-1.0, 0.0);
  }
//  std::cout << "Pass !(xNode = rf_cast<StateVarNode>(g->findDeep'X'))" << std::endl;
    
  StateVar x = xNode->getVar();
  Range xRange = x.second;
  
  double xTarget = (xRange.first + xRange.second) / 2.0;
//  std::cout << "xTarget = " << xTarget << std::endl;
  
  // If we want to beam to a position on other side of the field, we can't do it either
  if (xTarget > 0)
    return ConfidenceInterval(-1.0, 0.0);
//  std::cout << "Pass xTarget > 0" << std::endl;
  
//  int num;
//  std::cout << "Num = ";
//  std::cin >> num;
//  std::cout << num;
  
  // Else we can certainly do it
  return ConfidenceInterval(1.0, 0.0);
  
//  return ConfidenceInterval(1.0, 0.0);
}

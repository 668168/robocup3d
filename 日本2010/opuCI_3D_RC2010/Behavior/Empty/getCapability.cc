#include  "empty.ih"
Behavior::ConfidenceInterval Empty::getCapability(rf<State> s, rf<Goal> g)
{
//TODO
  _debugLevel4("Empty::getCapability");
//  std::cout << "Empty::getCapability" << std::endl;
  return ConfidenceInterval(1.0, 0.0);  
}

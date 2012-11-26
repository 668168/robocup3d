#include "behavior.ih"

Behavior::ConfidenceInterval Behavior::setGoal(rf<Goal> g)
{
  _debugLevel3("Behavior<" << ident() << ">::setGoal(" << g << ")");
//  std::cout << "Behavior<" << ident() << ">::setGoal(" << g << ") " << std::endl;

  rf<State> currentState = getCurrentState();
  
  _debugLevel4("Behavior<" << ident() << ">::currentState() = " << currentState );
//  std::cout << "Behavior<" << ident() << ">::currentState() = " << currentState << std::endl;

  ConfidenceInterval c = getCapability(currentState, g);
//  std::cout << "CapabilityInterval: (" << c.first << ", " << c.second << ")" << std::endl;

  _debugLevel3(ident() << " has capability (" << c.first << ", " << c.second << ")");
  
//  int num;
//  std::cout << "num = ";
//  std::cin >> num;
//  std::cout << num << std::endl;

  d_c = c;
  d_goal = g;
  return c;
}

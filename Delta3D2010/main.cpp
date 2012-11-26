
#include "src/Agent/Agent.h"

//main
int main(int argc, char* argv[])
{
  static bool gLoop = true;
  Agent agent;
  agent.options(argc, argv);
  agent.connect();
  while (gLoop)
  {       
    
    agent.sense();
    std::cout<<"sense ok"<<std::endl;
    agent.think();
    std::cout<<"think ok"<<std::endl;
    agent.act();
    std::cout<<"act ok"<<std::endl;
  }
  return 0;
}
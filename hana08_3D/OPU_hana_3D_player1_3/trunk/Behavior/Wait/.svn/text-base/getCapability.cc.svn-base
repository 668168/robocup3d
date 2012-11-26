#include "wait.ih"

Behavior::ConfidenceInterval Wait::getCapability(rf<State> s, rf<Goal> g)
{
  double waitTill = 10;
  rf<StateVarNode> timeNode = rf_cast<StateVarNode>(g->findDeep("Time"));
  if (timeNode)
  {
    StateVar time = timeNode->getVar();
    waitTill = time.second.mean();
    // _debugLevel1("Wait doesn't understand!");
    std::cout << "Wait doesn't understand!" << std::endl;
    return ConfidenceInterval(-1.0, 0.0);
  }
  

  // Dit is niet zo mooi, moet eigenlijk uit de state variabele gehaald worden..
  WorldModel& wm = WorldModel::getInstance();

// 下記のif文の存在意義が不明. 消すと転倒は止む.
  if (wm.getTime() - wm.getFirstTime() < waitTill)
  {
      std::cout << "wait... wm.getTime()-" << wm.getTime() << ", waitTill-" 
		<< waitTill << ": Ff wachten.." << std::endl;
    _debugLevel4(wm.getTime() << "-" << waitTill <<": Ff wachten..");
    return ConfidenceInterval(-1.0, 0.0);
  }

  std::cout << "wait... wm.getTime()-" << wm.getTime() << ", waitTill-" 
	    << waitTill << ": Pizza!" << std::endl;
  _debugLevel4(wm.getTime() << "-" << waitTill <<": Pizza!");
  return ConfidenceInterval(0.4, 0.0);
}

#include "getupfrombelly.ih"

Behavior::ConfidenceInterval GetUpFromBelly::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  if (wm.onMyBelly())
  {
    _debugLevel4("On my belly!");
//    std::cout << "On my belly!" << std::endl;
  }
//  std::cout << "getCapa" << std::endl;
//  std::cout << "ballpos =" << wm.getObjectPosition(Types::BALL).getMu() << std::endl;
  
  return wm.onMyBelly() ? ConfidenceInterval(0.9, 0.2) : ConfidenceInterval(0.0, 0.0);
}

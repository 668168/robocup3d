#include "getupfrombelly.ih"

Behavior::ConfidenceInterval GetUpFromBelly::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  if (wm.onMyBelly())
  {
    _debugLevel4("On my belly!");
    if(wm.kpBlocking() == WorldModel::NOTBLOCK)
      wm.setNeckDirUpdate(false);
    
    return ConfidenceInterval(0.9, 0.2);
  }
//  std::cout << "getCapa" << std::endl;
//  std::cout << "ballpos =" << wm.getObjectPosition(Types::BALL).getMu() << std::endl;
  
  return ConfidenceInterval(0.0, 0.0);
}

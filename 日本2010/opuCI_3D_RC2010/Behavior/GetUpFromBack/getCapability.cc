#include "getupfromback.ih"

Behavior::ConfidenceInterval GetUpFromBack::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
//  return wm.onMyBack() ? ConfidenceInterval(0.9, 0.2) : ConfidenceInterval(0.0, 0.0);
  if( wm.onMyBack() )
  {
      if(wm.getUnum() == 1 && wm.kpBlocking() == WorldModel::NOTBLOCK)
        wm.setNeckDirUpdate(false);
      return ConfidenceInterval(0.9, 0.2);
  }
  return ConfidenceInterval(0.0, 0.0);

}

#include "getfromside.ih"

Behavior::ConfidenceInterval GetFromSide::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
/*  return wm.onMySide() ||
         (wm.getGyro().length() < 1.0 && !wm.onMyBack() && !wm.onMyBelly() && wm.getFieldNormal().getZ() < 0.5)
          ? ConfidenceInterval(1.0, 0.0)
          : ConfidenceInterval(0.0, 0.0);
*/
  if(wm.onMySide())
  {
      wm.setNeckDirUpdate(false);
      return ConfidenceInterval(1.0, 0.0);
  }
  return ConfidenceInterval(0.0, 0.0);
}

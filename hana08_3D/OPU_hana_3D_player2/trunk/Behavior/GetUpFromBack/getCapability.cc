#include "getupfromback.ih"

Behavior::ConfidenceInterval GetUpFromBack::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  return wm.onMyBack() ? ConfidenceInterval(0.9, 0.2) : ConfidenceInterval(0.0, 0.0);
}

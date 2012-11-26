#include "goodpositionangle.ih"

Behavior::ConfidenceInterval GoodPositionAngle::getCapability(rf<State> s, rf<Goal> g)
{
  Vector3D pos = g->getVector("Pos");
  WorldModel& wm = WorldModel::getInstance();
  
  if (d_curStep >= 1  && pos.length() > 0.08)
    return ConfidenceInterval(0.1, 0.2);
  
  _debugLevel1("pos.length(): " << pos.length() << ", on feet: " << (wm.onMyFeet() ? "yes" : "no"));

  if (pos.length() > 1 )//|| !wm.onMyFeet() )
    return ConfidenceInterval(0.0, 0.2);
  
  return ConfidenceInterval(0.5, 0.2);
}

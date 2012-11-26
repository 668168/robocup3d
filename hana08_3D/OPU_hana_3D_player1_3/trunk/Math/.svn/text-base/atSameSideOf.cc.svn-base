#include "math.hh"

#define DEBUGLEVEL 0
#include "debug.hh"

using namespace bats;

bool Math::atSameSideOf(Vector3D const& pivot, Vector3D const& target, Vector3D const& me)
{
  Vector3D dif = target - pivot;
  _debugLevel1("dif: " << dif);
  
  Vector3D perpendicular = Math::calcPerpend(dif);
  _debugLevel1("perpendicular: " << perpendicular);
  
  double a = perpendicular.getY();
  double b = pivot.getY() - a * pivot.getX();
  
  double yTarget = a * target.getX() + b;
  double yMe = a * me.getX() + b;
  
  double dyTarget = yTarget - target.getY();
  double dyMe = yMe - me.getY();
  if (dyTarget * dyMe >= 0)
  {
    _debugLevel1("Yes");
  //if (sign(dyTarget) == sign(dyMe))
    return true;
  }

  _debugLevel1("Yes");
  return false;
}


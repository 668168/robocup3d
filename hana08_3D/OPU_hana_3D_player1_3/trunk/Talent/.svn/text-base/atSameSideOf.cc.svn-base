#include "talent.hh"
#include "math.hh"

#define DEBUGLEVEL 1
#include "debug.hh"

using namespace bats;

bool Talent::atSameSideOf(Vector3D pivot, Vector3D target, Vector3D me)
{
  Vector3D dif = target - pivot;
  _debugLevel1("dif: " << dif);
  
  Vector3D perpendicular = Math::calcPerpend(dif);
  _debugLevel1("perpendicular: " << perpendicular);
  
  double a = perpendicular[1];
  double b = pivot[1] - a * pivot[0];
  
  double yTarget = a * target[0] + b;
  double yMe = a * me[0] + b;
  
  double dyTarget = yTarget - target[1];
  double dyMe = yMe - me[1];
  if (dyTarget * dyMe >= 0)
  //if (sign(dyTarget) == sign(dyMe))
    return true;
  return false;
}

#include "math.hh"

#define DEBUGLEVEL 0
#include "debug.hh"

using namespace bats;

Vector3D Math::toFieldCoords(Vector3D const& pos, Vector3D const& normal)
{
  double lambda = -(normal * pos ) / (normal * normal);

  Vector3D fieldPos = pos + normal * lambda;

  fieldPos.setZ(normal.length() * -lambda);

  return fieldPos;
}


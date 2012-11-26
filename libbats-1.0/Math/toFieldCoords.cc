#include "math.hh"

#define DEBUGLEVEL 0
#include "../Preprocessor/debug.hh"

using namespace bats;

Vector3D Math::toFieldCoords(Vector3D const& pos, Vector3D const& normal)
{
  
  _debugLevel4("Pos: " << pos << ", normal: " << normal);
  double lambda = -(normal * pos ) / (normal * normal);
  _debugLevel4("Lambda: " << lambda);
  
  Vector3D fieldPos = pos + normal * lambda;
  _debugLevel4("Field pos: " << fieldPos);
  
  fieldPos.setZ(normal.length() * -lambda);
  _debugLevel4("Z: " << fieldPos.getZ());
  
  return fieldPos;
}


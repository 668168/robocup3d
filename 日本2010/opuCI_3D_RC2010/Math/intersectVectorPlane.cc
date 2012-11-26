#include "math.hh"

using namespace bats;

Vector3D Math::intersectVectorPlane(Vector3D const& position, Vector3D const& direction, double plane[])
{
  // x = pos.x + eta * dir.x
  // a * x + b * y + c * z + d = 0
  // a * pos.x + a * eta * dir.x +
  // b * pos.y + b * eta * dir.y +
  // c * pos.z + c * eta * dir.z +
  // d = 0;
  // eta * (a * dir.x + b * dir.y + c * dir.z) = - a * pos.x - b * pos.y - c * pos.z - d
  // eta = (- a * pos.x - b * pos.y - c * pos.z - d) / (a * dir.x + b * dir.y + c * dir.z)

  double eta = - (plane[0] * position.getX() + plane[1] * position.getY() + plane[2] * position.getZ() + plane[3]) /
                 (plane[0] * direction.getX() + plane[1] * direction.getY() + plane[2] * direction.getZ());
  return position + direction * eta;
}

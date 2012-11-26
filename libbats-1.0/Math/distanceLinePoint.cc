#include "math.hh"

namespace bats
{
  /**
   *  Calculates the distance to the closest point
   *  on a line.
   *
   *  @param l0 the starting point of the line.
   *  @param lVect the normalized vector of the line.
   *  @param The point.
   */
  double Math::distanceLinePoint(Vector3D const &l0,
				 Vector3D const &lVect,
				 Vector3D const &point)
  {
    Vector3D v = lVect.normalize();
    Vector3D s = calcPerpend(v);

    double u = ((s[0]/s[1])*(l0.getY() - point.getY()) + (point.getX() - l0.getX()))/(v[0] - (s[0]/s[1])*v[1]);

    return (lVect.normalize()*u - point).length();
  }
}

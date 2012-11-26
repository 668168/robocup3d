#include "math.hh"

#define DEBUGLEVEL 4
#include "debug.hh"

namespace bats {

  /**
   *  Calculates the nearest point on a line to
   *  another point.
   *
   *  @param l0 the start point of the line.
   *  @param lVect the not normalized line vector.
   *  @param point the other point.
   */
  Vector3D Math::linePointClosestToPoint(Vector3D const &l0,
                                         Vector3D const &lVect,
                                         Vector3D const &point)
  {
    Vector3D v = lVect.normalize();
    _debugLevel4("v: " << v);
    
    Vector3D s = calcPerpend(v);
    _debugLevel4("s: " << s);

    // There probably is a more efficient formula.
    double u = ((s[0]/s[1])*(l0.getY() - point.getY()) + (point.getX() - l0.getX()))/(v[0] - (s[0]/s[1])*v[1]);

    _debugLevel4("u: " << u);
    
    // When no perpendicular line is posible within the segment, use
    // the closest endpoint.
    if (u > lVect.length()) {
      if ((l0 - point).length() < ((l0 + lVect) - point).length())
        return l0;
      else
        return l0+lVect;
    }

    return l0 + v*u;
  }


}

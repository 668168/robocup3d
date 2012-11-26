#include "math.hh"

namespace bats {

  /**
   *  Calculates the perpendicular vector to v.
   */
  Vector3D Math::calcPerpend(Vector3D const &v)
  {
    if (v.getY() != 0 && v.getX() != 0)
      return Vector3D(1.0,-1.0/(v.getY()/v.getX()),0.0).normalize();
    
    if (v.getX() == 0)
      return Vector3D(1.0, 0.0, 0.0);
      
    return Vector3D(0.0, 1.0, 0.0);
  }

}

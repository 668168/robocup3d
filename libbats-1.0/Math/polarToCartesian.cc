#include "math.hh"

using namespace bats;

Vector3D Math::polarToCartesian(Vector3D const &polar)
{
	Vector3D cartesian;
	
  cartesian.setZ(sin(polar.getZ()) * polar.getX());
  double dmark = cos(polar.getZ()) * polar.getX();
  cartesian.setY(cos(-polar.getY()) * dmark);
  cartesian.setX(sin(-polar.getY()) * dmark);
  
  return cartesian;
}

/*Vector3D Math::polarToCartesian2(Vector3D const& polar)
{
  Vector3D cartesian;
  
  double dist = polar.getX();
  double tanTheta = tan(polar.getY());
  double tanPhi = tan(polar.getZ());

  cartesian.setX(sqrt(dist * dist / (tanTheta * tanTheta + tanPhi * tanPhi + 1)));
  if (fabs(polar.getY()) > .5 * M_PI)
	  cartesian[0] = -cartesian[0];
  
  cartesian.setY(cartesian.getX() * tanTheta);
  cartesian.setZ(cartesian.getX() * tanPhi);
  
  return cartesian;
}*/

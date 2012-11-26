#include "math.hh"

using namespace bats;

Vector3D Math::cartesianToPolar(Vector3D const &cartesian, bool sign)
{
	Vector3D polar;
	
  // XY-angle
  if(sign)
    polar.setY(atan2(cartesian.getY(),cartesian.getX()));
  else
    polar.setY(atan(cartesian.getY() / cartesian.getX()));
  double d = sqrt(cartesian.getX() * cartesian.getX() + cartesian.getY() * cartesian.getY());

  // Latitude-angle
  polar.setZ(atan(cartesian.getZ() / d));
  
  // Distance
  polar.setX(sqrt(d * d + cartesian.getZ() * cartesian.getZ()));
  
  return polar;
}

/*Vector3D Math::cartesianToPolar2(Vector3D const &cartesian)
{
	Vector3D polar;
	
	polar.setX(cartesian.length());
	
	Vector3D xy(cartesian.getX(), cartesian.getY(), 0);
	polar.setY(acos(cartesian.getX() / xy.length()));
	if (cartesian.getY() < 0)
		polar.setY(-polar.getY());
		
	Vector3D xz(cartesian.getX(), 0, cartesian.getZ());
	polar.setZ(acos(cartesian.getX() / xz.length()));
	if (cartesian.getZ() < 0)
		polar.setZ(-polar.getZ());
	
	return polar;
}*/

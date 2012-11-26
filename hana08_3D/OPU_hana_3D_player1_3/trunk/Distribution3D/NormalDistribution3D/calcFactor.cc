#include "normaldistribution3d.ih"

void NormalDistribution3D::calcFactor()
{
//  d_factor = 1.0 / (pow(2 * M_PI, 1.5) * sqrt(d_determinant));
	static double const pipow(pow(2 * M_PI, 1.5));
  d_factor = 1.0 / (pipow * sqrt(d_determinant));
}

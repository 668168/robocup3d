#include "normaldistribution3d.ih"

Vector3D NormalDistribution3D::getX() const
{
  Vector3D x;
  
  // Uniformly distributed
  double x1 = (1.0 * rand()/(RAND_MAX+1.0));
  double x2 = (1.0 * rand()/(RAND_MAX+1.0));
  double x3 = (1.0 * rand()/(RAND_MAX+1.0));
  double x4 = (1.0 * rand()/(RAND_MAX+1.0));
  
  // Normal distributed
  double n1 = sqrt(-2 * log(x1)) * cos(2 * M_PI * x2 );
  double n2 = sqrt(-2 * log(x1)) * sin(2 * M_PI * x2 );
  double n3 = sqrt(-2 * log(x3)) * cos(2 * M_PI * x4 );
  
  x[0] = n1 * sqrt(d_sigma.get(0, 0));
  x[1] = d_sigma.get(1, 0) / d_sigma.get(0, 0) * x[0] + n2 * sqrt((d_sigma.get(1, 1) * d_sigma.get(0, 0) - d_sigma.get(1, 0) * d_sigma.get(1, 0)) / d_sigma.get(0, 0));

  // Not accurate, should also depend on x[0]!
  x[2] = d_sigma.get(2, 1) / d_sigma.get(1, 1) * x[0] + n3 * sqrt((d_sigma.get(2, 2) * d_sigma.get(1, 1) - d_sigma.get(2, 1) * d_sigma.get(2, 1)) / d_sigma.get(1, 1));

  x = x + d_mu;
  
  return x;
 }

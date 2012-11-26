#include "normaldistribution3d.ih"

double NormalDistribution3D::getP(Vector3D const &x) const
{
  // P(x) = 1 / ((2 * pi)^(N/2) * |S|^(1/2)) * e ^ (- 1/2 * (x - mu)T * S^-1 * (x - mu))
  Vector3D temp;
  Vector3D xminmu = x - d_mu;

  Matrix9D::mulTVect(temp, xminmu, d_invSigma);
  
  return d_factor * exp(-0.5 * temp.dotProduct(xminmu));
}

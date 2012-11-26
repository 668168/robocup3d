#include "normaldistribution3d.ih"

NormalDistribution3D::NormalDistribution3D()
  :
    d_mu(),
    d_sigma(),
    d_invSigma(),
    d_determinant(0),
    d_factor(0)
{}

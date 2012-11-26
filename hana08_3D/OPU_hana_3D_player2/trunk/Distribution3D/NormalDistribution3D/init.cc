#include "normaldistribution3d.ih"

void NormalDistribution3D::init(Vector3D const &mu, Matrix9D const &sigma)
{
  d_mu = mu;
  d_sigma = sigma;
  Matrix9D::inverse(d_invSigma, d_sigma);

  calcFactor();
  //srand(time(0));
  //Verplaatst naar de main.cc (bram)
}

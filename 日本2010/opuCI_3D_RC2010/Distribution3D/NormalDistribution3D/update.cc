#include "normaldistribution3d.ih"

void NormalDistribution3D::update(rf<IDistribution3D> const &measurementModel)
{
  Vector3D meaMu = measurementModel->getMu();
  Matrix9D meaSigma = measurementModel->getSigma();

  // z_k = H x_k + v_k
  // Without noise the measured position z_k is equal to the actual position x_k, so H = 1
  // x_k^+ = x_k^- + K (z_k - H x_k^-) = x_k^- + K (z_k - x_k^-)
  // K = P_k^- H^T (H P_k^- H^T + R)^-1 = P_k^- (P_k^- + R)^-1
  
  
  for (unsigned i = 0; i < 3; i++)
    _debugLevel2("Measurement Mu " << i << ": " << meaMu[i]);
  for (unsigned i = 0; i < 9; i++)
    _debugLevel2("Sigma " << i << ": " << d_sigma[i]);
  for (unsigned i = 0; i < 9; i++)
    _debugLevel2("Measurement Sigma " << i << ": " << meaSigma[i]);

  Matrix9D sum = d_sigma + meaSigma;
  Matrix9D k = d_sigma * (d_sigma + meaSigma).inverse();

  for (unsigned i = 0; i < 9; i++)
    _debugLevel2("k " << i << ": " << k[i]);

  d_mu = d_mu + k * (meaMu - d_mu);
  
  Matrix9D ident;
  ident.set(0, 0, 1);
  ident.set(1, 1, 1);
  ident.set(2, 2, 1);
  
  d_sigma = (ident - k) * d_sigma;

  _debugLevel2("Update: " << d_mu[0] << "\t" << d_mu[1] << "\t" << d_mu[2]);
}

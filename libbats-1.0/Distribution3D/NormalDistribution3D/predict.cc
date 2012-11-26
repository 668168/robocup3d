#include "normaldistribution3d.ih"

void NormalDistribution3D::predict(rf<Distribution3D> const &movementModel)
{
  Vector3D movMu = movementModel->getMu();
  Matrix9D movSigma = movementModel->getSigma();

  _debugLevel2("Before prediction: " << d_mu[0] << "\t" << d_mu[1] << "\t" << d_mu[2]);
  _debugLevel2(movMu[0] << "\t" << movMu[1] << "\t" << movMu[2]);
  // x_k^- = A x_k-1 + B u_k-1
  // where u is the movement model
  // All movement is accumulated in the movement model. so there is no extra movement: A = I and no translation is needed: B = 1, so:
  // x_k^- = x_k-1 + u_k-1
  d_mu += movMu;
  
  // S_k^- = A P_k-1^+ A^T + Q_k-1 = P_k-1^+ + Q_k-1
  d_sigma = d_sigma + movSigma;
  
  _debugLevel2("Prediction: " << d_mu[0] << "\t" << d_mu[1] << "\t" << d_mu[2]);
}

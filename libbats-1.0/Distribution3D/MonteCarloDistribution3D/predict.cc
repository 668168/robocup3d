#include "montecarlodistribution3d.ih"

void MonteCarloDistribution3D::predict(rf<Distribution3D> const &movementModel)
{
  vector<Particle> newParticles;
  for (unsigned i = 0; i < d_nParticles; i++)
  {
    Particle oldP;
    rouletteSelect(oldP);
    Vector3D dcoords;
    dcoords = movementModel->getX();
    oldP.coords += dcoords;
    oldP.p *= movementModel->getP(dcoords);
    newParticles.push_back(oldP);
  }
  d_particles = newParticles;
}

#include "montecarlodistribution3d.ih"

void MonteCarloDistribution3D::update(rf<Distribution3D> const &measurementModel)
{
  for (vector<Particle>::iterator iter = d_particles.begin(); iter != d_particles.end(); iter++)
    iter->p = measurementModel->getP(iter->coords);
  normalize();
}

#include "montecarlodistribution.ih"

void MonteCarloDistribution::update(rIDistribution const &measurementModel)
{
  for (vector<Particle>::iterator iter = d_particles.begin(); iter != d_particles.end(); iter++)
    iter->p = measurementModel->getP(iter->coords);
  normalize();
}

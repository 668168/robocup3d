#include "montecarlodistribution.ih"

void MonteCarloDistribution::getMu(Vector3D &mu) const
{
  double highestP = 0;

  for (vector<Particle>::const_iterator iter = d_particles.begin(); iter != d_particles.end(); iter++)
    if (iter->p > highestP || highestP == 0)	//Always initialize mu with something from particles
    {
      mu = iter->coords;
      highestP = iter->p;
    }
}

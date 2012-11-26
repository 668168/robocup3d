#include "montecarlodistribution.ih"

double MonteCarloDistribution::getP(Vector3D const &x) const
{
  for (vector<Particle>::const_iterator iter = d_particles.begin(); iter != d_particles.end(); iter++)
    if (iter->coords == x)
      return iter->p;
  return 0;
}

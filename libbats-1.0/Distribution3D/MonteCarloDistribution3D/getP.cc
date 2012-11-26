#include "montecarlodistribution3d.ih"

double MonteCarloDistribution3D::getP(Vector3D const &x) const
{
  for (vector<Particle>::const_iterator iter = d_particles.begin(); iter != d_particles.end(); iter++)
    if (iter->coords == x)
      return iter->p;
  return 0;
}

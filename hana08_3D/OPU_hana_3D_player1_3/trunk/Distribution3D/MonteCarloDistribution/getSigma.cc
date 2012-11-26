#include "montecarlodistribution.ih"

void MonteCarloDistribution::getSigma(Matrix9D &sigma) const
{
  Vector3D mu;
  getMu(mu);
  Matrix9D sums;
  
  for (vector<Particle>::const_iterator iter = d_particles.begin(); iter != d_particles.end(); iter++)
  {
    Matrix9D temp;
    for (unsigned i = 0; i < 3; i++)
      for (unsigned j = 0; j < 3; j++)
        temp.set(i, j, (iter->coords.get(i) - mu.get(i)) * (iter->coords.get(j) - mu.get(j)));
    sums = sums + temp;
  }
  sigma = sums / d_nParticles;
}

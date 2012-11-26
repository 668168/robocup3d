#include "montecarlodistribution.ih"

void MonteCarloDistribution::normalize()
{
  if(d_particles.empty())
	return;

  double sum = 0.0;
  for (vector<Particle>::iterator iter = d_particles.begin(); iter != d_particles.end(); iter++)
   sum += iter->p;
  for (vector<Particle>::iterator iter = d_particles.begin(); iter != d_particles.end(); iter++)
   iter->p /= sum;
}

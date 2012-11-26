#include "montecarlodistribution.ih"

void MonteCarloDistribution::rouletteSelect(Particle &particle) const
{
  // For now assume the particles are normalized so their sum equals 1
  double totalP = 1.0;
  double lottery = (totalP * rand()/(RAND_MAX+1.0));
  double sum = 0;
  for (vector<Particle>::const_iterator iter = d_particles.begin(); iter != d_particles.end(); iter++)
  {
    sum += iter->p;
    if (sum >= lottery)
    {
      particle = *iter;
      break;
    }
  }

}

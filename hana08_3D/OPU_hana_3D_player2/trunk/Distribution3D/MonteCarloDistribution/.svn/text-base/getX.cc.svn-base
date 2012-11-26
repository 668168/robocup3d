#include "montecarlodistribution.ih"

void MonteCarloDistribution::getX(Vector3D &x) const
{
  Particle p;
  rouletteSelect(p);
  x = p.coords;
}

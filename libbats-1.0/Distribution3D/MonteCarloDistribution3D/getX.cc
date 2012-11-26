#include "montecarlodistribution3d.ih"

void MonteCarloDistribution3D::getX(Vector3D &x) const
{
  Particle p;
  rouletteSelect(p);
  x = p.coords;
}

#include "montecarlodistribution.ih"

void MonteCarloDistribution::init(Vector3D const &mu, Matrix9D const &sigma)
{
  NormalDistribution nd;
  nd.init(mu, sigma);
  
  for (unsigned i = 0; i < d_nParticles; i++)
  {
    Particle p;
    nd.getX(p.coords);
    _debugLevel2(p.coords[0] << "\t" << p.coords[1] << "\t" << p.coords[2]);
    p.p = nd.getP(p.coords);
    d_particles.push_back(p);
  }
}

#include "montecarlodistribution3d.ih"

void MonteCarloDistribution3D::init(Vector3D const &mu, Matrix9D const &sigma)
{
  NormalDistribution3D nd;
  nd.init(mu, sigma);
  
  for (unsigned i = 0; i < d_nParticles; i++)
  {
    Particle p;
    p.coords = nd.getX();
    _debugLevel2(p.coords[0] << "\t" << p.coords[1] << "\t" << p.coords[2]);
    p.p = nd.getP(p.coords);
    d_particles.push_back(p);
  }
}

#include "math.hh"

#define DEBUGLEVEL 4
#include "debug.hh"

using namespace bats;

/*double Math::calcRealX(Vector3D const& pos, Vector3D const& normal, double height)
{
  double alpha = fabs(atan(normal.getX() / normal.getZ()));
  double x;
  
  _debugLevel4(pos << " " << normal << ", a: " << alpha);
  if (pos.getX() >= 0)
  {
    double beta = fabs(atan(pos.getZ() / pos.getX()));
    _debugLevel4("b: " << beta);
    double gamma = pos.getZ() < 0 ? alpha + beta : alpha - beta;
    _debugLevel4("g: " << gamma);
    if (gamma < .5 * M_PI)
      x = fabs(height / tan(gamma));
    else
      x = -fabs(tan(gamma - .5 * M_PI) * height);
  }
  else
  {
    double beta = fabs(atan(pos.getX() / pos.getZ()));
    _debugLevel4(beta);
    x = -fabs(tan(alpha + beta) * height);
  }
  _debugLevel4(x);
  
  return x;
}*/


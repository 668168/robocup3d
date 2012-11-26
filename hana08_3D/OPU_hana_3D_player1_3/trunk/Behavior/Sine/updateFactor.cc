#include "sine.ih"

void Sine::updateFactor(double dTime, bool startup)
{
//  std::cout << "Sine::updateFactor()" << std::endl;
  if (startup)
  {
    if (d_factor == 0.0)
    {
      WorldModel& wm = WorldModel::getInstance();
      d_startTime = wm.getTime();
      dTime = 0.02;
    }
    d_factor += dTime / d_startupTime;
    if (d_factor > 1.0)
      d_factor = 1.0;
  }
  else
  {
    d_factor -= dTime / d_shutdownTime;
    if (d_factor < 0)
      d_factor = 0;
  }
}


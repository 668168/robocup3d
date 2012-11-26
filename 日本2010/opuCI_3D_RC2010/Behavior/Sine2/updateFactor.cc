#include "sine2.ih"

void Sine2::updateFactor(double dTime, bool startup)
{
//  std::cout << "Sine2::updateFactor()" << std::endl;
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

//  WorldModel& wm = WorldModel::getInstance();
//  stringstream ss;
//  ss << "factor: " << d_factor << "	";
//  wm.addDebugMessage(WorldModel::COMMENT, ss.str());

//  cout << ss.str() << std::endl;
//  std::cout << "Sine2::updateFactor() end" << std::endl;
}


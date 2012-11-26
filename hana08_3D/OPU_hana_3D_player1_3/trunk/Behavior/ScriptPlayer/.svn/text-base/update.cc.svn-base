#include "scriptplayer.ih"

void ScriptPlayer::update()
{
//  std::cout << " -> ScriptPlayer::update()" << std::endl;
  Behavior::update();
  
  d_committed = true;
  
  WorldModel& wm = WorldModel::getInstance();
  if (d_waitUntil < 0)
    d_waitUntil = wm.getTime() + d_script[0][Types::NJOINTS].first;

  
  vector<pair<double, double> > scriptLine = d_script[d_curLine];
  
  double now = wm.getTime();
  if (d_lastChecked != now)
  {
    // See if we should go to the next step
    double thres = 0.05;
  
    
    bool proceed = true;

    // Dont proceed if we're still waiting
    _debugLevel4("time: " << wm.getTime() << ", " << d_lastStepTime);
//    std::cout << "time: " << wm.getTime() << ", " << d_lastStepTime << std::endl;
    
    if (wm.getTime() - d_lastStepTime > 10)
    {
      proceed = true;
      _debugLevel4("Timeout: proceed");
//      std::cout << "Timeout: proceed" << std::endl;
    }
    else if(d_waitUntil > wm.getTime())
    {
      _debugLevel4("Waiting..");
//      std::cout << "Waiting.." << std::endl;
      proceed = false;
    }
    else
      for (unsigned i = 0; i < Types::NJOINTS; ++i)
      {
        double angle = wm.getJointAngle((Types::Joint)i).getMu();
        double delta = fabs(Math::normalizeRad(angle - scriptLine[i].first));
        if (delta > thres)
        {
          _debugLevel4("Joint " << i << " not there yet: " << angle << " " << scriptLine[i].first << " " << delta << " > " << thres);
//          std::cout << "Joint " << i << " not there yet: " << angle << " " << scriptLine[i].first << " " << delta << " > " << thres << std::endl;
          proceed = false;
          break;
        }
      }
      
    if (proceed)
    {
      ++d_curLine;
      if (d_curLine == d_script.size())
      {
        d_curLine = 0;
        d_committed = false;
      }
      
      
      _debugLevel4("curline: " << d_curLine << " " << d_script.size());
//      std::cout << "curline: " << d_curLine << " " << d_script.size() << std::endl;
      scriptLine = d_script[d_curLine];
      
      d_lastStepTime = wm.getTime();
      d_waitUntil = wm.getTime() + scriptLine[Types::NJOINTS].first;
    }
    
    _debugLevel4("Scriptline: " << d_curLine);
//    std::cout << "Scriptline: " << d_curLine << std::endl;
    d_lastChecked = now;
  }
}

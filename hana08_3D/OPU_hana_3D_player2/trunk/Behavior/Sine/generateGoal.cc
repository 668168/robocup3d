#include "sine.ih"

rf<Behavior::Goal> Sine::generateGoal(unsigned step, unsigned slot)
{
  WorldModel& wm = WorldModel::getInstance();

  // Update all factors
  if (s_lastUpdate < wm.getTime())
  {
    for (unsigned i = 0; i < s_sines.size(); ++i)
      s_sines[i]->updateFactor(wm.getTime() - s_lastUpdate, s_sines[i] == this);
    s_lastUpdate = wm.getTime();
  }
  
  double angle = 0;
  double fSum = 0;
  for (unsigned i = 0; i < s_sines.size(); ++i)
  {
    vector<Params> params = s_sines[i]->getParams()[slot];
    double f = s_sines[i]->getFactor();
    if (f > 0)
    {
      _debugLevel1("Running sine : " << s_sines[i]->ident() << " " << wm.getTime() << " " << f);
    }
    angle += f * calcAngle(params, s_sines[i]->getStartTime());
    fSum += f;
  }
  
  if(fSum != d_factor)
  {
    _debugLevel1("Merging sines!");
  }
  
  if (fSum >1)
    angle /= fSum;
  
/*  s_lastUpdate = wm.getTime();
  //_debugLevel4("Sine::generateGoal " << step << " " << slot);
  WorldModel& wm = WorldModel::getInstance();
  
  if (d_startTime < 0)
    d_startTime = wm.getTime();
    
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  double angle = calcAngle(d_params[slot], d_startTime);
  
  _debugLevel4("Angle: " << angle);
  
  _debugLevel4("Last sine time: " << s_lastSineTime << " " << wm.getTime());
  
  if (s_lastSineTime < wm.getTime() - 0.20)
    s_lastSineID = "";
    
  if (s_lastSineID == "")
  {
    s_lastTime = wm.getTime();
    s_lastSineID = "NONE";
    _debugLevel4("First time! Last time: " << s_lastTime << ", " << s_lastSineID);
  }

  if (s_lastSineID != ident())
  {
    _debugLevel4("Last one wasnt me (" << ident() << "), but " << s_lastSineID << ", " << wm.getTime() << " " << s_lastTime << " " << d_transitionTime);
    double tTime = d_transitionTime > s_lastStopTime ?  d_transitionTime : s_lastStopTime;
    
    if (wm.getTime() < s_lastTime + tTime)
    {
      double oldAngle = s_lastSineID != "NONE" ? calcAngle(s_lastParams[slot], s_lastStartTime) : 0;
      _debugLevel4("Old angle: " << oldAngle);
      double factor = (wm.getTime() - s_lastTime) / tTime;
      _debugLevel4("Factor: " << factor);
      angle = factor * angle + (1.0 - factor) * oldAngle;
    }
    else
    {
      _debugLevel4("Done transitioning, setting stuff to me..");
      s_lastSineID = ident();
      s_lastParams = d_params;
      s_lastStartTime = d_startTime;
      s_lastStopTime = d_stopTime;
    }
  }
  else
  {
    _debugLevel4("Same old me..");
    s_lastTime = wm.getTime();
  }*/
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  _debugLevel4("Angle: " << angle);
  con->addVar("Angle", angle, angle);

  s_lastSineTime = wm.getTime();
  
  return goal;
}

#include "sine.ih"

rf<Behavior::Goal> Sine::generateGoal(unsigned step, unsigned slot)
{
  WorldModel& wm = WorldModel::getInstance();

  // Update all factors
  if (s_lastUpdate < wm.getTime()){
    for (unsigned i = 0; i < s_sines.size(); ++i)
      s_sines[i]->updateFactor(wm.getTime() - s_lastUpdate, s_sines[i] == this);
    s_lastUpdate = wm.getTime();
  }
  
  double angle = 0;
  double fSum = 0;
  for (unsigned i = 0; i < s_sines.size(); ++i){
    vector<Params> params = s_sines[i]->getParams()[slot];
    double f = s_sines[i]->getFactor();
    if (f > 0){
      _debugLevel1("Running sine : " << s_sines[i]->ident() << " " << wm.getTime() << " " << f);
    }
    angle += f * calcAngle(params, s_sines[i]->getStartTime());
    // angle += f * calcSinusoidAngle(params, s_sines[i]->getStartTime())
    // + f * calcOffsetAngle(params);
    fSum += f;
  }
  
  if(fSum != d_factor){
    _debugLevel1("Merging sines!");
  }
  
  if (fSum >1)
    angle /= fSum;
  
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  _debugLevel4("Angle: " << angle);
  con->addVar("Angle", angle, angle);
  con->addVar("Gain", d_gain, d_gain);

  s_lastSineTime = wm.getTime();
  
  return goal;
}

#include "sine2.ih"

rf<Behavior::Goal> Sine2::generateGoal(unsigned step, unsigned slot)
{
  WorldModel& wm = WorldModel::getInstance();

  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  // Update all factors
  if (s_lastUpdate < wm.getTime())
  {
    // if the last update of factors is too old, (more than <d_shutdownTime> sec before)
    //  reset all factors to 0
    if (s_lastUpdate < wm.getTime() - d_shutdownTime){
      for (unsigned i = 0; i < s_sines.size(); ++i)
        s_sines[i]->resetFactor();
//       std::cerr << "(Sine2) reset all factors" << std::endl;
    }

    for (unsigned i = 0; i < s_sines.size(); ++i)
      s_sines[i]->updateFactor(wm.getTime() - s_lastUpdate, s_sines[i] == this);
    s_lastUpdate = wm.getTime();
//    std::cout << "(Sine2) factor updated at" << s_lastUpdate << std::endl;
  }

  // set angles
  double angle = 0;
  double fSum = 0;
  if( d_weights.size() < d_variableParams.size() )
  {
    std::cerr << "(Sine2::generateGoal) invalid weights!!" << std::endl;
    std::cerr << "  this behavior requires " << d_variableParams.size() << " weights!" << std::endl;
    std::cerr << "  " << d_weights.size() << " weights" << std::endl;
    return goal;
  }

  double fMax = 0;
  int fi = -1;
  for (unsigned i = 0; i < s_sines.size(); ++i)
  {
    vector<Params> fparams = s_sines[i]->getFixedParams()[slot];

    double f = s_sines[i]->getFactor();
//    std::cout << "f = " << f << std::endl;
    if(fMax < f){ fi = i; fMax = f; }

//    std::cout << " angle = ";
//    angle += f * calcAngle(fparams, s_sines[i]->getStartTime());
//    std::cout << angle;
    unsigned size = s_sines[i]->getVariableParamsSize();
    for ( unsigned j = 0; j < size; j++)
    {
      vector<Params> vparams = s_sines[i]->getVariableParams(j)[slot];
//      std::cout << "get variable params clear!" << std::endl;

      angle += f * calcAngle(vparams, s_sines[i]->getStartTime())
        * s_sines[i]->getWeight(j);
//      std::cout << " -> " << angle ;
    }
//    std::cout << std::endl << std::endl;
    fSum += f;
  }

  if(fMax > 0)
  {
//    cout << "fMax = " << fMax << ", fi = " << fi << std::endl;
    vector<Params> fparams = s_sines[fi]->getFixedParams()[slot];
    angle += calcAngle(fparams, s_sines[fi]->getStartTime());
  }

  if(fSum != d_factor){
    _debugLevel1("Merging sines!");
  }

  if (fSum >1)
    angle /= fSum;

//  std::cout << "set goal and end generateGoal" << std::endl;

  _debugLevel4("Angle: " << angle);
  con->addVar("Angle", angle, angle);
  con->addVar("Gain", d_gain, d_gain);

  s_lastSine2Time = wm.getTime();

//  std::cout << "(Sine2::generateGoal) end" << std::endl;
  return goal;
}

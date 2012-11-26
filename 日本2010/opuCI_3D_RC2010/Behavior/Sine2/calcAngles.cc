#include "sine2.ih"

double Sine2::calcAngle(vector<Params>& params, double startTime)
{
  WorldModel& wm = WorldModel::getInstance();
//  std::cout << "(Sine2::calcAngle) start" << std::endl;
  double angle = 0;
  for (vector<Params>::iterator iter = params.begin(); iter != params.end(); ++iter)
  {
    Params parameters = *iter;

    angle += parameters.amplitude
//      * sin((wm.getTime() - startTime)
      * sin((wm.getTime())
            / parameters.period * 2 * M_PI + parameters.phase)
      + parameters.offset;
  }
  
  angle *= M_PI / 180.0;
//  std::cout << "(Sine2::calcAngle) end" << std::endl;
  return angle;
}

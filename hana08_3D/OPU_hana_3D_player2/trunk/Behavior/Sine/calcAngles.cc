#include "sine.ih"

double Sine::calcAngle(vector<Params>& params, double startTime)
{
  WorldModel& wm = WorldModel::getInstance();

  double angle = 0;
  for (vector<Params>::iterator iter = params.begin(); iter != params.end(); ++iter)
  {
    Params parameters = *iter;
    angle += parameters.amplitude * sin((wm.getTime() - startTime) / parameters.period * 2 * M_PI + parameters.phase) + parameters.offset;
  }
  
  angle *= M_PI / 180.0;
  return angle;
}

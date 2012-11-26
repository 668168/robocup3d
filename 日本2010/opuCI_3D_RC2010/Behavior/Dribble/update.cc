#include "dribble.ih"

void Dribble::update()
{
  Behavior::update();

  WorldModel& wm = WorldModel::getInstance();

  if(d_startTimeUpdated && wm.getTime() - d_startTime > 3.0) // wait 3 second when starts walking
    d_doStabilityCheck = true;
  else
    d_doStabilityCheck = false;

}

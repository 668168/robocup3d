#include "agentmodel.ih"

bool AgentModel::onMyBelly()
{
  WorldModel& wm = SWorldModel::getInstance();

  _debugLevel3("Field normal XY: " << wm.getFieldNormal().getX() <<" "  << wm.getFieldNormal().getY() << " gyro: " << d_gyro.length());
  _debugLevel3("on Belly: " << (wm.getFieldNormal().getY() < -0.9 && wm.getFieldNormal().getY() > -.95 && d_gyro.length() < 50.0));
  _debugLevel1("Disttofield: " << wm.getDistToField());
  //return (getDirectionOfFall() == FALL_TO_FRONT); (MK: not working!!)
  return wm.getFieldNormal().getY() < -0.8 && wm.getFieldNormal().getY() > -1.0 && d_gyro.length() < 50.0 && fabs(wm.getDistToField()) < 0.25;
}


#include "agentmodel.ih"

bool AgentModel::onMyFeet()
{
  WorldModel& wm = SWorldModel::getInstance();

  //_debugLevel4(d_fieldNormal << " " << d_gyro << " " << d_footForces[0] << " " << d_footForces[1]);
  return wm.getFieldNormal().getZ() > 0.98 && d_gyro.length() < 1.0 && d_footForces[0].getZ() > 0 && d_footForces[1].getZ() > 0;
}


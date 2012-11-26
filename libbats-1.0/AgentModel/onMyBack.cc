#include "agentmodel.ih"

bool AgentModel::onMyBack()
{
  WorldModel& wm = SWorldModel::getInstance();

  _debugLevel3("Field normal XY: " << wm.getFieldNormal().getX() <<" "  << wm.getFieldNormal().getY() << " gyro: " << d_gyro.length()); 

  return wm.getFieldNormal().getY() > 0.6 && d_gyro.length() < 80.0 && fabs(wm.getDistToField()) < 0.25;//2.0; (nao)
}


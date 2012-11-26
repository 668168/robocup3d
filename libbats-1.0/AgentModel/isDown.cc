
#include "agentmodel.ih"

bool AgentModel::isDown(bool check) const
{

    
  WorldModel& wm = SWorldModel::getInstance();
  if(wm.getFieldNormal().getZ() < 0.8 || fabs(wm.getDistToField()) < 0.3)
    return check;
  return !check;
}

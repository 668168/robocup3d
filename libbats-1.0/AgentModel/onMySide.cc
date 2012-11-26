#include "agentmodel.ih"

bool AgentModel::onMySide()
{
  WorldModel& wm = SWorldModel::getInstance();
 
  return !onMyFeet() && !onMyBack() && !onMyBelly() 
    && wm.getFieldNormal().getZ() < 0.3 && fabs(wm.getFieldNormal().getX()) > 0.7;

}


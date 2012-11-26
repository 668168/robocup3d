#include "agentmodel.ih"

void AgentModel::update()
{
  Cochlea& cochlea = SCochlea::getInstance();

  if (cochlea.getInfo(Cochlea::iUnum)[0] != 0)
    d_unum = cochlea.getInfo(Cochlea::iUnum)[0];
    
  updatePosture();
  updateCOM();
  
  
  d_footForceCenters[0] = cochlea.getInfo(Cochlea::iFootLeft);
  d_footForceCenters[1] = cochlea.getInfo(Cochlea::iFootRight);
  
  d_footForces[0] = cochlea.getInfo(Cochlea::iFootLeft2);
  d_footForces[1] = cochlea.getInfo(Cochlea::iFootRight2);
  
  d_gyro = cochlea.getInfo(Cochlea::iTorsoGyro);
  _debugLevel4("gyro: " << d_gyro);
  checkDirectionOfFall();

}

#include "agentmodel.ih"

void AgentModel::checkDirectionOfFall()
{
    WorldModel& wm = SWorldModel::getInstance();
    
    /*if (onMyFeet())
        d_catchFallEnabled = true;

    if (not d_catchFallEnabled)
    {
      d_fallDirection = NOT_FALLING;      
      return; 
    }*/
  
    float forceLFootZ = d_footForces[0].getZ();
    float forceRFootZ = d_footForces[1].getZ();
    float gyroAbsXY = abs(d_gyro.getX()) + abs(d_gyro.getY()) ;    

  /*  _debugLevel1("Distance to Field: " << SAgentModel::getInstance().getDistToField());
    _debugLevel1("Feet " << forceLFootZ << " " << forceRFootZ);
    _debugLevel1("gyroX+Y " << gyroAbsXY );
    _debugLevel1("getZ: " << getFieldNormal().getZ())d_currentFallDirection = ;*/
    
    
    if (forceLFootZ < 2 && forceRFootZ < 2 && gyroAbsXY > 60 && wm.getFieldNormal().getZ() < 0.85 && wm.getFieldNormal().getY() < 0.9 && wm.getDistToField() > -2.8) 
    {
  		_debugLevel1(" FALLING!");
      //d_catchFallEnabled = false;
      
      //if front/backwards vector is bigger than sidewaysvector
      if (abs(wm.getFieldNormal().getY()) > abs(wm.getFieldNormal().getX()))
      {
    		_debugLevel1("Fall to front: " << (wm.getFieldNormal().getY() < 0));
        //if fieldNormalX is smaller than 0 the robot is falling forwards
        d_fallDirection = (wm.getFieldNormal().getY() < 0) ? FALL_TO_FRONT : FALL_TO_BACK;
      }
      else
      {
        _debugLevel1(" Fall to SIDE!");
        d_fallDirection = (wm.getFieldNormal().getX() > 0) ? FALL_TO_RIGHT : FALL_TO_LEFT;
      }
  }
  else
    d_fallDirection = NOT_FALLING;
}


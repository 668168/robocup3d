#include "walkstraightto.ih"

void WalkStraightTo::update()
{
  Behavior::update();
  WorldModel& wm = WorldModel::getInstance();
  
  // test for lastupdate
  std::stringstream ss;
  ss << "(WalkStraightTo::update) at " << d_lastUpdate;
  wm.addDebugMessage(WorldModel::COMMENT, ss.str());

  if(d_startTimeUpdated && wm.getTime() - d_startTime > 3.0) // wait 3 second when starts walking
    d_doStabilityCheck = true;
  else
    d_doStabilityCheck = false;
  
  if (d_committed)
    return;
  //TODO:  歩行開始数秒は常にd_committed = true にしてみたい
  else if(false)
  {
    d_committed = true;
    return;
  }

  if(!wm.visibleObject(Types::BALL)){
    d_committed = false;
  }
  else {
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
    ballPos.setZ(0);
    // Distance from foot to ball (not from camera)
    double distToBall = ballPos.length();

    double angleToBall = getAngleWithStraight(ballPos);
    
    if (distToBall < 1.875) {
      //std::cout << "walkstraightto near ball (dist):" 
      // << distToBall << std::endl;
      d_committed = false;
    }
    else if (fabs(angleToBall) < 10.0) {
      //std::cout << "walkstraightto ball exists forward. angle:" 
      // << angleToBall << std::endl;
      d_committed = true;
    }
    else{
      // std::cout << "walkstraightto stop!" << std::endl;
      d_committed = false;
    }
  }
}


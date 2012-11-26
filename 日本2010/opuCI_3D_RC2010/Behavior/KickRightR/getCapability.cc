#include "kickrightr.ih"

Behavior::ConfidenceInterval KickRightR::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

  Vector3D goalPos = (wm.getObjectPosition(Types::GOAL1THEM).getMu() 
                      + wm.getObjectPosition(Types::GOAL2THEM).getMu()) / 2;
  double goalX = goalPos.getX();
  double goalY = goalPos.getY();
  double distToGoal = sqrt(goalX * goalX + goalY * goalY);  
  Vector3D straight(1,0,0);

  Vector3D goalPos1us = wm.getObjectPosition(Types::GOAL1US).getMu();
  Vector3D goalPos2us = wm.getObjectPosition(Types::GOAL2US).getMu();
  Vector3D goalPos1them = wm.getObjectPosition(Types::GOAL1THEM).getMu();
  Vector3D goalPos2them = wm.getObjectPosition(Types::GOAL2THEM).getMu();
  goalPos1us.setZ(0);
  goalPos2us.setZ(0);
  goalPos1them.setZ(0);
  goalPos2them.setZ(0);
  Vector3D ballPosz = ballPos;
  ballPosz.setZ(0);
  double goal1Ang = straight.angle(goalPos1them) * 180.0 / M_PI;
  double goal2Ang = straight.angle(goalPos2them) * 180.0 / M_PI;
    if(goalPos1them.getY() < 0)
      goal1Ang *= -1;
    if(goalPos2them.getY() < 0)
      goal2Ang *= -1;

  bool   diepoint = false; // 自殺点を入れる可能性
  if(wm.allObjectPosAvailable()) {
    double goal1Ang = straight.angle(goalPos1us);
    double goal2Ang = straight.angle(goalPos2us);

    if(goalPos1us.getY() < 0)
      goal1Ang *= -1;
    if(goalPos2us.getY() < 0)
      goal2Ang *= -1;
    
    double goalUsAng = (goal1Ang+goal2Ang)/2;
    if( -60 < goalUsAng && goalUsAng < 30 )
      diepoint = true;
    
  }

  if(wm.getUnum() == 1 // keeper 
     && ballPos.getY() < 0.1 && ballPos.getY() >= -0.25
     && ballPos.getX() >= 0 && ballPos.getX() <= 0.2
     && !diepoint )
      return ConfidenceInterval(0.35, 0.2);

  bool ballPosCondition = ballPos.getX() >= 0 && ballPos.getX() <= 0.2
    &&  ballPos.getY() <= -0.05 && ballPos.getY() >= -0.15
    &&(distToGoal < 4.0) && (distToGoal > 1.0);
  bool goalPosCondition = (goal1Ang + goal2Ang)/2.0 > 30
    &&  (goal1Ang + goal2Ang)/2.0 < 60;

  if(ballPosCondition && goalPosCondition && !diepoint ){
    wm.setNeckDirUpdate(false);
    return ConfidenceInterval(0.35, 0.2);
  }

  return ConfidenceInterval(-0.3, 0.0);

}

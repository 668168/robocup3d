#include "kickposition.ih"

rf<Behavior::Goal> KickPosition::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  WorldModel& wm = WorldModel::getInstance();

  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  Vector3D goal1Pos = wm.getObjectPosition(Types::GOAL1THEM).getMu();
  Vector3D goal2Pos = wm.getObjectPosition(Types::GOAL2THEM).getMu();
  Vector3D goalPos = ( goal1Pos + goal2Pos ) / 2.0;
  Vector3D goal1to2 = goal2Pos - goal1Pos;

  Vector3D targetPos;
  double targetAngle;

  Vector3D toe = ( wm.getBodyConnectionPosition(Types::BC_RTOE)
                   + wm.getBodyConnectionPosition(Types::BC_LTOE) ) / 2.0;

  if(step == 0){ // BestPosition, BestAngle
/*
    con->addVar("Pos", targetPos);
  }
  else if(step == 1){ // BestPosition, BestAngle
*/
    // 基本的にボールに直接向かう
    targetPos = ballPos - toe; // goal -> ball
  
    // 回りこみが要求される時は，適当に対応
    if( Math::inTriangle(
          wm.getObjectPosition(Types::GOAL1THEM).getMu(),
          wm.getObjectPosition(Types::GOAL2THEM).getMu(),
          goalPos * (-0.3),
          ballPos - wm.getObjectPosition(Types::FLAG1THEM).getMu()))
      targetPos = ballPos + (ballPos - goalPos).normalize()*0.1 - toe;

    con->addVar("Pos", targetPos);


    goalPos = goalPos - toe;

/*
    targetAngle = straight.angle(goalPos) / M_PI * 180.0;
    if(goalPos.getY() < 0)
      targetAngle *= -1;
    }

  else if(step == 1){
*/
//    goalPos.setZ(0);
    targetAngle = getAngleWithStraight(goalPos);

  }
  
  con->addVar("Angle", targetAngle, targetAngle);
  // wm.setDebugLine(Vector3D(0,0,0), goalPos);
  
  return goal;
}

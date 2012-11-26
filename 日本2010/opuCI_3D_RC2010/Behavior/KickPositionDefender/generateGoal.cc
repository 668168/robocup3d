#include "kickpositiondefender.ih"

rf<Behavior::Goal> KickPositionDefender::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  WorldModel& wm = WorldModel::getInstance();
  
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  Vector3D goal1Pos = wm.getObjectPosition(Types::GOAL1THEM).getMu();
  Vector3D goal2Pos = wm.getObjectPosition(Types::GOAL2THEM).getMu();
  Vector3D goalPos = ( goal1Pos + goal2Pos ) / 2.0;

    Vector3D targetPos;

    Vector3D toe = ( wm.getBodyConnectionPosition(Types::BC_RTOE)
                     + wm.getBodyConnectionPosition(Types::BC_LTOE) ) / 2.0;

    if(step == 0){ 

      targetPos = ballPos - toe; // goal -> ball

      con->addVar("Pos", targetPos);
    }

    goalPos = goalPos - toe;
    double targetAngle;
    if(step == 0){
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
  
  // con->addVar("Var", 0, 1);
  
  return goal;
}

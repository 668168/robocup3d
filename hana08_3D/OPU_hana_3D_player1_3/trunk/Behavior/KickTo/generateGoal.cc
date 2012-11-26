#include "kickto.ih"

rf<Behavior::Goal> KickTo::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  WorldModel& wm = WorldModel::getInstance();

  if(step == 1) // goodpositionangle
  {
	Vector3D targetPos = d_goal->getVector("Pos");
	targetPos.setZ(0.0);
	Vector3D straight(1.0, 0.0, 0.0);
	double angle;
//	std::cout << targetPos.length() << std::endl;
	if(targetPos.length() > 0.3){
	  angle = straight.angle(targetPos) / M_PI * 180.0;
	  if (targetPos.getY() < 0)
        angle *= -1.0;
	}
	else{
	  targetPos = wm.getObjectPosition(Types::BALL).getMu();
	  targetPos.setZ(0.0);

      Vector3D goal1Pos = wm.getObjectPosition(Types::GOAL1THEM).getMu();
	  goal1Pos.setZ(0.0);
      Vector3D goal2Pos = wm.getObjectPosition(Types::GOAL2THEM).getMu();
	  goal2Pos.setZ(0.0);

	  Vector3D g1ToBall = targetPos - goal1Pos;
	  Vector3D g1ToG2 = goal2Pos - goal1Pos;
	
	  double k = g1ToBall.dotProduct(g1ToG2) / (g1ToG2.length() * g1ToG2.length());
	
	  if(k < 0 || k > 1)
	    k = 0.5;

	  Vector3D dest = goal2Pos * k + goal1Pos * (1 - k);
	  Vector3D direction = dest - targetPos;
	  angle = straight.angle(direction) / M_PI * 180.0;
	  if (direction.getY() < 0.0)
	    angle *= -1.0;
	}

	con->addVar("Pos", targetPos);
	con->addVar("Angle", angle, angle);
//	std::cout << "Angle = " << angle << std::endl;
  }
  else if (step == 2) // dribble
  {
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
	ballPos.setZ(0.0);

    Vector3D goal1Pos = wm.getObjectPosition(Types::GOAL1THEM).getMu();
	goal1Pos.setZ(0.0);
    Vector3D goal2Pos = wm.getObjectPosition(Types::GOAL2THEM).getMu();
	goal2Pos.setZ(0.0);

	Vector3D g1ToBall = ballPos - goal1Pos;
	Vector3D g1ToG2 = goal2Pos - goal1Pos;
	
	double k = g1ToBall.dotProduct(g1ToG2) / (g1ToG2.length() * g1ToG2.length());
	
	Vector3D targetPos;
	if(k < 0 || k > 1)
	  k = 0.5;
	
	targetPos = goal2Pos * k + goal1Pos * (1 - k);
	Vector3D dir = targetPos - ballPos;
    Vector3D straight(1,0,0);

	double angle = straight.angle(dir) / M_PI * 180.0;
	if (dir.getY() < 0.0)
	  angle *= -1.0;
/*
    _debugLevel4(ballPos << " " << dir);

    ballPos = ballPos - dir / dir.length() * 0.09;

    _debugLevel4(ballPos);

    // ballPosLeft: BALL <----------- GOAL
    Vector3D ballPosLeft;
    ballPosLeft.setX(dir.getX());
    ballPosLeft.setY(dir.getY());
	ballPosLeft.setZ(0.0);
    
    _debugLevel4(goal1Pos << " " << goal2Pos << " " << goalPos << " " << angle);
    
    Vector3D targetPos = ballPos - ballPosLeft.normalize() * 0.04;
	targetPos.setZ(0.0);
*/

//	Vector3D targetPos = ballPos - dir.normalize() * 1.5;
    
/*    if (!Math::atSameSideOf(ballPos, targetPos, Vector3D(0,0,0)))
    {
      targetPos = ballPos + ballPosLeft.normalize() * 4;
      if (!Math::atSameSideOf(ballPos, Vector3D(0,0,0), targetPos))
        targetPos = ballPos - ballPosLeft.normalize() * 4;
    }
*/
//    std::cout << "Behavior::KickTo::generateGoal targetPos=" << targetPos 
//	      << ", ballPosLeft=" << ballPosLeft << std::endl;


//	con->addVar("Pos", shinBallPos); // for dribble!
	con->addVar("Angle", angle, angle);
  }  
  // con->addVar("Var", 0, 1);
  return goal;
}

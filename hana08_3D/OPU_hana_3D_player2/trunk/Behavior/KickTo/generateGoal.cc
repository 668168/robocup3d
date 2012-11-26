#include "kickto.ih"

rf<Behavior::Goal> KickTo::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  WorldModel& wm = WorldModel::getInstance();

  if(step == 1) 
  {
	Vector3D targetPos = d_goal->getVector("Pos");
	targetPos.setZ(0.0);
	Vector3D straight(1.0, 0.0, 0.0);
	double angle;


	// Calculate the shortest distance between ball and our goal line. 
	Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu(); // -> (x, y)
	ballPos.setZ(0.0);
	Vector3D goal1Pos = wm.getObjectPosition(Types::GOAL1US).getMu(); // -> (a, b)
	goal1Pos.setZ(0);
	Vector3D goal2Pos = wm.getObjectPosition(Types::GOAL2US).getMu(); // -> (c, d)
	goal2Pos.setZ(0);
       
	//         |(d-b)x + (a-c)y - ad + bc|
	// dist = -----------------------------
	//          sqrt( (d-b)^2 + (a-c)^2 )
	double distBallToGoal = fabs((goal2Pos.getY() - goal1Pos.getY()) * ballPos.getX() + (goal1Pos.getX() - goal2Pos.getX()) * ballPos.getY() - goal1Pos.getX() * goal2Pos.getY() + goal1Pos.getY() * goal2Pos.getX()) / sqrt( pow((double)(goal2Pos.getY() - goal1Pos.getY()), (double)2.0) + pow((double)(goal1Pos.getX() - goal1Pos.getX()), (double)2.0) );
//	std::cout << "dist = " << distBallToGoal << std::endl;

	if(distBallToGoal < 1.0 && ((goal1Pos + goal2Pos) / 2 ).length() < 5 ){
	  Vector3D goalLine;
	  if(goal1Pos.length() < goal2Pos.length())
		goalLine = goal2Pos - goal1Pos;
	  else
		goalLine = goal1Pos - goal2Pos;
	  goalLine.setZ(0);
	  targetPos = ballPos - goalLine.normalize() * 0.3;
	  angle = straight.angle(goalLine) / M_PI * 180.0;
		if (ballPos.getY() < 0)
		  angle *= -1.0;
	}
	else if( ((wm.getObjectPosition(Types::GOAL1THEM).getMu() + wm.getObjectPosition(Types::GOAL2THEM).getMu()) / 2.0).length() < 3 ){
	      targetPos = d_goal->getVector("OppPos");
	      angle = straight.angle(targetPos) / M_PI * 180.0;
		if (targetPos.getY() < 0)
		  angle = -angle;
	}
	else{
	  if(targetPos.length() > 0.3){
		angle = straight.angle(targetPos) / M_PI * 180.0;
		if (targetPos.getY() < 0)
		  angle *= -1.0;
	  }
	  else{
	    if(ballPos.length() < 0.5){
		  targetPos = ballPos;
		  angle = straight.angle(targetPos) / M_PI * 180.0;
		  if (targetPos.getY() < 0)
		    angle *= -1;
	    }
	    else{
		  Vector3D direction = targetPos - ballPos;
		  direction.setZ(0.0);
		  angle = straight.angle(direction) / M_PI * 180.0;
      	  if (direction.getY() < 0)
      	    angle *= -1;
	    }
	  }
	}

	con->addVar("Pos", targetPos);
	con->addVar("Angle", angle, angle);

  }


  return goal;
}

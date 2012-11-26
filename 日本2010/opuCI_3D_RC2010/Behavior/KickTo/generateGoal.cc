#include "kickto.ih"

rf<Behavior::Goal> KickTo::generateGoal(unsigned step, unsigned slot)
{

  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

/*
  WorldModel& wm = WorldModel::getInstance();

  if(step == 1) // goodpositionangle
  {
      Vector3D targetPos = d_goal->getVector("Pos");
      targetPos.setZ(0.0);
      Vector3D straight(1.0, 0.0, 0.0);
      double angle;
//      std::cout << targetPos.length() << std::endl;
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
  }
*/

  return d_goal;
}

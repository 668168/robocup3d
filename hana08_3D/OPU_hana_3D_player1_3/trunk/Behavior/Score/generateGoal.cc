#include "score.ih"

rf<Behavior::Goal> Score::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  

  WorldModel& wm = WorldModel::getInstance();
  
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  ballPos.setZ(0.0);
//  Vector3D goalPos = (wm.getObjectPosition(Types::GOAL1THEM).getMu() + wm.getObjectPosition(Types::GOAL2THEM).getMu()) / 2.0;

  Vector3D goal1Pos = wm.getObjectPosition(Types::GOAL1THEM).getMu();
  goal1Pos.setZ(0.0);
  Vector3D goal2Pos = wm.getObjectPosition(Types::GOAL2THEM).getMu();
  goal2Pos.setZ(0.0);

  Vector3D g1ToBall = ballPos - goal1Pos;
  Vector3D g1ToG2 = goal2Pos - goal1Pos;
	
  double k = g1ToBall.dotProduct(g1ToG2) / (g1ToG2.length() * g1ToG2.length());

  if(k < 0 || k > 1)
	k = 0.5;
	
  Vector3D dest = goal2Pos * k + goal1Pos * (1 - k);
  Vector3D targetPos = ballPos - (dest - ballPos).normalize() * 0.3;

//  std::cout << "ballPos.length() = " << ballPos.length() << ": (" << ballPos.getX() << ", " << ballPos.getY() << ")" << std::endl;

  con->addVar("Pos", targetPos);
/*
  switch (step)
  {
    case 0:
      con->addVar("Pos", balPos);
      break;
      
    case 1:
      break;
  }
*/
/*
  switch (step)
  {
	case 0:
		destination = wm.getObjectPosition(Types::SELF).getMu();
//		std::cout << destination.getX() << ", " << destination.getY() << ", " << destination.getZ() << std::endl;
//		destination.setX((wm.getObjectPosition(Types::FLAG1L).getMu().getX() + wm.getObjectPosition(Types::FLAG2L).getMu().getX()) / 2.0);
		destination.setX( wm.getObjectPosition(Types::FLAG1THEM).getMu().getX() );	
		con->addVar("Pos", destination);
		break;
		
	case 1:
		break;
  }
*/	  
  // con->addVar("Var", 0, 1);
  
  return goal;
}

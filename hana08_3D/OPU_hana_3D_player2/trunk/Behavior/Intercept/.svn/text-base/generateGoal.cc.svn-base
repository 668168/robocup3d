#include "intercept.ih"

rf<Behavior::Goal> Intercept::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  WorldModel& wm = WorldModel::getInstance();
  Vector3D pos = d_goal->getVector("Pos");
//  pos.setZ(0);
  Vector3D straight(1,0,0);
  double angle = straight.angle(pos) * M_PI / 180.0;
  if(pos.getY() < 0)
      angle *= -1;

  switch (step)
  {
      case 0: // turn to
	  con->addVar("Angle", angle, angle);

	  break;
      case 1: // walk straight to
	  std::cout << "Intercept::generateGoal : Pos=" << pos << std::endl;
	  con->addVar("Pos", pos);
	  break;
      case 2: // dive
//	  con->addVar("Pos", pos);
//	  con->addVar("Angle", angle, angle);

	  break;
      default:
	  break;
  }
  
  // con->addVar("Var", 0, 1);
  
  return goal;
}

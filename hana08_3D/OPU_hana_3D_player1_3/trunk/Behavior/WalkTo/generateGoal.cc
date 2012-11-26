#include "walkto.ih"

rf<Behavior::Goal> WalkTo::generateGoal(unsigned step, unsigned slot)
{
  WorldModel& wm = WorldModel::getInstance();
  Vector3D pos, straight(1,0,0);
  double angleToPos;

  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
      
  switch (step)
  {
      case 0: 
      pos = d_goal->getVector("Pos"); 
      pos.setZ(0);

	  if(pos.length() > 0.3){
      	angleToPos = straight.angle(pos) / M_PI * 180.0;
      	if (pos.getY() < 0)
      	  angleToPos = -angleToPos;
      }
	  else{
		pos = wm.getObjectPosition(Types::BALL).getMu();
		pos.setZ(0.0);
		angleToPos = straight.angle(pos) / M_PI * 180.0;
      	if (pos.getY() < 0)
      	  angleToPos = -angleToPos;
	  }
      _debugLevel4(ident() << " " << pos << " " << angleToPos);
      
      con->addVar("Angle", angleToPos, angleToPos);   
	  con->addVar("Pos", pos); 
	  con->addVar("WalkTo", 0, 0);
      return goal;
      
      case 1: 
      return d_goal;
  }
  
  return 0;
}

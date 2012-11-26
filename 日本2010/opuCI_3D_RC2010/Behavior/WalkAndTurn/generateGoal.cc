#include "walkandturn.ih"

rf<Behavior::Goal> WalkAndTurn::generateGoal(unsigned step, unsigned slot)
{
    WorldModel& wm = WorldModel::getInstance();
    
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  Vector3D pos = d_goal->getVector("Pos"); // final target of move

  double angle = getAngleWithStraight(pos);

  double weight1=0, weight2=0;
  double weight3=0, weight4=0;
  double siki = 15;
  stringstream ss;

  if( angle < -siki )
  {
    weight2 = 1;
  }
  else if(angle > siki)
  {
    weight3 = 1;
  }

  pos.setZ(0);
  pos = pos.normalize();

  if( pos.getX() > 0 )
  {
    weight1 = pos.getX();
  }
  else
  {
    weight4 = -pos.getX();
  }

  ss << "<br>(WalkAndTurn) forward: " << weight1
     << "<br>              backward:" << weight4
     << "<br>              right:   " << weight2
     << "<br>              left:    " << weight3;

  wm.addDebugMessage(WorldModel::COMMENT, ss.str());

  con->addVar("Weight1", weight1, weight1); // forward
  con->addVar("Weight2", weight2, weight2); // turn right
  con->addVar("Weight3", weight3, weight3); // turn left
  con->addVar("Weight4", weight4, weight4); // backward

  return goal;

}

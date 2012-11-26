#include "keeperwalk.ih"

rf<Behavior::Goal> KeeperWalk::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  Vector3D pos = d_goal->getVector("Pos"); // targetPos
  WorldModel& wm = WorldModel::getInstance();

  wm.setDebugPointWithLabel(pos, "KeeperWalk_TGT");

  double w1=0, w2=0, w3=0, w4=0;
  pos.setZ(0);

  double x = pos.getX() / pos.length();
  double y = pos.getY() / pos.length();

  if(x > 0)
    w1 = x;
  else
    w4 = -x;
  if(y > 0)
    w3 = y;
  else
    w2 = -y;

  con->addVar("Weight1", w1, w1); // forward
  con->addVar("Weight2", w2, w2); // right
  con->addVar("Weight3", w3, w3); // left
  con->addVar("Weight4", w4, w4); // backward

  stringstream ss;
  ss << "(KeeperWalk)<br> forward: " << w1
     << "<br> backward: " << w4
     << "<br> right: " << w2
     << "<br> left: " << w3 << "<br>";
  wm.addDebugMessage(WorldModel::COMMENT, ss.str());


  return goal;
}

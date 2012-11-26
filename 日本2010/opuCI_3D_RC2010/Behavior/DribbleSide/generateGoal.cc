#include "dribbleside.ih"

rf<Behavior::Goal> DribbleSide::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  double weight1=0, weight2=0;
  WorldModel& wm = WorldModel::getInstance();

  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

  if(ballPos.getY() < 0)
    weight1 = 0.7;
  else
    weight2 = 0.7;

  con->addVar("Weight1", weight1, weight1); // rightside
  con->addVar("Weight2", weight2, weight2); // leftside


  return goal;
}

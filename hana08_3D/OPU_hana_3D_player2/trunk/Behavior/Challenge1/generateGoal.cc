#include "challenge1.ih"

rf<Behavior::Goal> Challenge1::generateGoal(unsigned step, unsigned slot)
{

  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  WorldModel& wm = WorldModel::getInstance();
  
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  Vector3D behindBall = ballPos + (ballPos / ballPos.length() * 8);

  con->addVar("Pos", behindBall);
 
  return goal;

}

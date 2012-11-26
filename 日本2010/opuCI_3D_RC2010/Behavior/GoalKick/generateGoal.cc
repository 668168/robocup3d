#include "goalkick.ih"

rf<Behavior::Goal> GoalKick::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  WorldModel& wm = WorldModel::getInstance();
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  Vector3D goalPos = (wm.getObjectPosition(Types::GOAL1US).getMu()
                      + wm.getObjectPosition(Types::GOAL2US).getMu() ) / 2.0;
  Vector3D targetPos = ballPos;

  if( wm.visibleObject(Types::BALL) )
  {
    targetPos = ballPos + ( goalPos - ballPos ).normalize() * 0.35;
  }

  con->addVar("Pos", targetPos);

  wm.setDebugPointWithLabel(targetPos, "GoalKick_TGT");
  return goal;
}

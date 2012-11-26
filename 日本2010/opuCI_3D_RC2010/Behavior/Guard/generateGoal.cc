#include "guard.ih"

rf<Behavior::Goal> Guard::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  WorldModel& wm = WorldModel::getInstance();

  Vector3D guard(0,0,0);
  
  // ゴール中心からボール側に1.5mの地点がホームポジション
  if( wm.allObjectPosAvailable() && wm.visibleObject(Types::BALL) )
  {
    Vector3D ball = wm.getObjectPosition(Types::BALL).getMu();
    Vector3D goalus = ( wm.getObjectPosition(Types::GOAL1US).getMu()
                        + wm.getObjectPosition(Types::GOAL2US).getMu() ) / 2.0;
    guard = goalus + ball.normalize() * 1.2;
  }

  guard.setZ(0);
  con->addVar("HomePos", guard);
  
  return goal;
}

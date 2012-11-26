#include "waitandsee.ih"

rf<Behavior::Goal> WaitAndSee::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  WorldModel& wm = WorldModel::getInstance();

  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  ballPos.setZ(0.0);
  Vector3D goalPos(0,0,0);

  Vector3D targetPos, targetToGoal;

  if( wm.getPlayerType(wm.getUnum()) == Types::DEFENDER )
  {
    con->addVar("Pos", targetPos);
    wm.setDebugPointWithLabel(targetPos, "WaitAndSee_TGT");

    return goal;
  }

  if( wm.allObjectPosAvailable())
  {
    if( wm.visibleObject(Types::BALL))
    {
      Vector3D ourGoalToTheirGoal
        = ( wm.getObjectPosition(Types::GOAL1THEM).getMu()
            + wm.getObjectPosition(Types::GOAL2THEM).getMu()
            - wm.getObjectPosition(Types::GOAL1US).getMu()
            - wm.getObjectPosition(Types::GOAL2US).getMu() ).normalize();
      // set the waiting position as a sub attacker
      // ボールから味方ゴール側に1.5m離れて待機
      targetPos = ballPos - ourGoalToTheirGoal * 1.5;
      targetPos.setZ(0.0);
    }
  }
  else
  {
    targetPos = ballPos;
  }

  con->addVar("Pos", targetPos);
  wm.setDebugPointWithLabel(targetPos, "WaitAndSee_TGT");

  return goal;
}

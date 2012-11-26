#include "score.ih"

rf<Behavior::Goal> Score::generateGoal(unsigned step, unsigned slot)
{
 rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  WorldModel& wm = WorldModel::getInstance();

  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  ballPos.setZ(0.0);
  Vector3D goalPos = (wm.getObjectPosition(Types::GOAL1THEM).getMu()
                 + wm.getObjectPosition(Types::GOAL2THEM).getMu()) / 2.0 ;
  Vector3D unitX = wm.worldUnitX();
  if( wm.getSide() == WorldModel::RIGHT )
    unitX = -unitX;

  if( wm.allObjectPosAvailable() && isBallNearCorner())
  {
    // ボールがコーナーにあれば，ゴール中心から1m手前を目標とする
    goalPos = goalPos - unitX * 1.0;
  }

    // とりあえずボール位置を目標とする
  Vector3D targetPos = ballPos;

  // 自分の位置が分かるかどうか
  if(wm.allObjectPosAvailable() && wm.visibleObject(Types::BALL))
  {
    // 普通にボールが見えてれば蹴りにいく
    targetPos = ballPos + (ballPos - goalPos).normalize() * 0.35;
  }

  con->addVar("Pos", targetPos);

  return goal;
}

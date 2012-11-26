#include "keeperkickposition.ih"

rf<Behavior::Goal> KeeperKickPosition::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  // con->addVar("Var", 0, 1);
  
  WorldModel& wm = WorldModel::getInstance();

  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  Vector3D goal1Pos = wm.getObjectPosition(Types::GOAL1THEM).getMu();
  Vector3D goal2Pos = wm.getObjectPosition(Types::GOAL2THEM).getMu();
  Vector3D goalPos = ( goal1Pos + goal2Pos ) / 2.0;
  Vector3D goal1to2 = goal2Pos - goal1Pos;

  Vector3D opp1Pos = wm.getObjectPosition(Types::OPPONENT1).getMu();
  Vector3D opp2Pos = wm.getObjectPosition(Types::OPPONENT2).getMu();
  Vector3D opp3Pos = wm.getObjectPosition(Types::OPPONENT3).getMu();
  Vector3D targetPos;

  Vector3D toe = ( wm.getBodyConnectionPosition(Types::BC_RTOE)
                   + wm.getBodyConnectionPosition(Types::BC_LTOE) ) / 2.0;

  if(step == 0){ // BestPosition, BestAngle

    // 基本的にボールに直接向かう
    targetPos = ballPos - toe; // goal -> ball
    con->addVar("Pos", targetPos);


    // 最寄りの敵の方向とか考えた方がいい気がするが…
    // とりあえず，敵ゴール方向へ
    double targetAngle = getAngleWithStraight(goalPos - toe);
    con->addVar("Angle", targetAngle, targetAngle);

  }
  
  return goal;
}

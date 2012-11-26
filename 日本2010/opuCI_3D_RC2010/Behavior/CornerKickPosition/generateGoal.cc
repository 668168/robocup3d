#include "cornerkickposition.ih"

rf<Behavior::Goal> CornerKickPosition::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  WorldModel& wm = WorldModel::getInstance();
  Vector3D ball = wm.getObjectPosition(Types::BALL).getMu();
  Vector3D flag1t = wm.getObjectPosition(Types::FLAG1THEM).getMu();
  Vector3D flag2t = wm.getObjectPosition(Types::FLAG2THEM).getMu();
  Vector3D flag1u = wm.getObjectPosition(Types::FLAG1US).getMu();
  Vector3D flag2u = wm.getObjectPosition(Types::FLAG2US).getMu();
  Vector3D goalPos = ( wm.getObjectPosition(Types::GOAL1THEM).getMu()
                       + wm.getObjectPosition(Types::GOAL2THEM).getMu()) / 2.0;

  // debug
  stringstream ss;
  ss << "(CornerKickPos) goal = " << goalPos;
  wm.addDebugMessage(WorldModel::COMMENT, ss.str());

  // 先ずはボールに近づく
  Vector3D pos = ball;
  double angle = getAngleWithStraight(ball);
  double minAngle = 10;

  // 十分ボールに近づいたら，ボールの方に向きつつ回り込む
  if(ball.length() < 1.0)
  {
    // ボールに対して，敵ゴールと反対側に回り込む！
    Vector3D perpend = Math::calcPerpend(ball).normalize();
    pos = ball + perpend;
    if( Math::atSameSideOf( ball, pos, goalPos ))
      pos = ball - perpend;

    wm.setDebugLine(ball, pos);
  }

  // 有り得ないはずだが，ランドマーク位置推定ができる場合，正しい方向へ回り込む
  if( wm.allObjectPosAvailable() )
  {
    Vector3D fUnitX = wm.worldUnitX();
    Vector3D fUnitY = wm.worldUnitY();

    if(flag1t.length() < flag2t.length())
      pos = ball + fUnitX + fUnitY;
    else
      pos = ball + fUnitX - fUnitY;

  }

  con->addVar("Pos", pos);
  con->addVar("Angle", angle, angle);
  con->addVar("MinAngle", minAngle, minAngle);

  return goal;
}

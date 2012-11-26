#include "goodposition.ih"

rf<Behavior::Goal> GoodPosition::generateGoal(unsigned step, unsigned slot)
{
  Vector3D pos = d_goal->getVector("Pos"); // targetPos
  WorldModel& wm = WorldModel::getInstance();

  Vector3D ball = wm.getObjectPosition(Types::BALL).getMu();
  double accuracy = 0.3;
/*
  // 最も近くにいる敵が経路上にいる場合は別の目的地を考える
  Types::Object opp = static_cast<Types::Object>(wm.getClosestOpponentUnum() + Types::OPPONENT1 - 1);
  Vector3D closestOpp = wm.getObjectPosition(opp).getMu();

  wm.setDebugCircle(closestOpp, 0.3);
  if( objectExistBetweenPos(pos, accuracy, opp) )
  {
    pos = closestOpp;
    pos.setZ(0);
    Vector3D newpos1 = pos + Math::calcPerpend(pos).normalize() * 0.5;
    Vector3D newpos2 = pos - Math::calcPerpend(pos).normalize() * 0.5;
    if( (closestOpp - newpos1).length() < (closestOpp - newpos2).length() )
      pos = newpos1;
    else
      pos = newpos2;
    wm.addDebugMessage(WorldModel::COMMENT, "<font color=yellow>Change Goal by Opponent</font>");

  }
*/
  Vector3D ballz = ball; ballz.setZ(0);
  Vector3D goal1us = wm.getObjectPosition(Types::GOAL1US).getMu();
  Vector3D goal2us = wm.getObjectPosition(Types::GOAL2US).getMu();
  accuracy = 0.5;
  if( (( pos == ball || pos == ballz ) && (Math::atSameSideOf(ball, goal1us, goal2us)))  // ボールに向かって移動，かつ移動方向が味方ゴール側
    || ( objectExistBetweenPos(pos, accuracy, Types::BALL) ) )  // ボールの向こう側に回り込む
  {
    pos.setZ(0);
    Vector3D newpos1 = pos + Math::calcPerpend(pos).normalize() * 0.5;
    Vector3D newpos2 = pos - Math::calcPerpend(pos).normalize() * 0.5;
//    if( (newpos1).length() < (newpos2).length() )
    if( Math::atSameSideOf( ball, newpos1, pos ) )
      pos = newpos1;
    else
      pos = newpos2;
    wm.addDebugMessage(WorldModel::COMMENT, "<font color=gray>Change Goal by Ball</font>");
  }

  wm.setDebugPointWithLabel(pos, "GoodPos_TGT");


  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  double w1=0, w2=0, w3=0, w4=0;
  pos.setZ(0);

  double x,y;
  if( pos.length() == 0 )
  {
    x=0;y=0;
  }
  else
  {
    x = pos.getX() / pos.length();
    y = pos.getY() / pos.length();
  }

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
  ss << "(GoodPos)<br> forward: " << w1
     << "<br> backward: " << w4
     << "<br> right: " << w2
     << "<br> left: " << w3 << "<br>";
  wm.addDebugMessage(WorldModel::COMMENT, ss.str());

  return goal;
}

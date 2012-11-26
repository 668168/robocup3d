#include "defense.ih"

rf<Behavior::Goal> Defense::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();


  WorldModel& wm = WorldModel::getInstance();

  Vector3D myself(0, 0, 0);
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  Vector3D ourGoalPos = (wm.getObjectPosition(Types::GOAL1US).getMu()
                         + wm.getObjectPosition(Types::GOAL2US).getMu()) / 2.0;
  Vector3D sideline = ( wm.getObjectPosition(Types::GOAL1THEM).getMu()
                        + wm.getObjectPosition(Types::GOAL2THEM).getMu()
                        + wm.getObjectPosition(Types::FLAG1THEM).getMu()
                        + wm.getObjectPosition(Types::FLAG2THEM).getMu()
                        - wm.getObjectPosition(Types::GOAL1US).getMu()
                        - wm.getObjectPosition(Types::GOAL2US).getMu()
                        - wm.getObjectPosition(Types::FLAG1US).getMu()
                        - wm.getObjectPosition(Types::FLAG2US).getMu()).normalize();

  // 分からんかったらとりあえずボール
  Vector3D target = ballPos;

  // 自ゴールからdistほど距離を取って待機
  // wtf ???
  double dist = 3.5;

  if(wm.allObjectPosAvailable())
  {
    target = ourGoalPos + (ballPos - ourGoalPos).normalize() * dist;
    wm.setDebugLine(ourGoalPos, target);
    wm.setDebugLine(myself, ourGoalPos);
  }
  con->addVar("Pos", target);
  wm.setDebugPointWithLabel(target,"Defense_TGT");

  return goal;

}

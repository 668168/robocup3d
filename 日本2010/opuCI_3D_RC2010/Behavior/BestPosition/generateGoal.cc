#include "bestposition.ih"

rf<Behavior::Goal> BestPosition::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

/*
  WorldModel& wm = WorldModel::getInstance();

  Vector3D TGT = d_goal->getVector("Pos");

  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
  Vector3D goalPos = ( wm.getObjectPosition(Types::GOAL1THEM).getMu()
                       + wm.getObjectPosition(Types::GOAL2THEM).getMu() ) / 2;
  Vector3D toe = ( wm.getBodyConnectionPosition(Types::BC_RTOE)
                   +wm.getBodyConnectionPosition(Types::BC_LTOE)) / 2.0;

//  ballPos.setZ(0);
//  goalPos.setZ(0);
  Vector3D targetPos = ballPos - goalPos.normalize() * 0.22 - toe;

  //  con->addVar("Pos", targetPos);
  con->addVar("Pos", TGT);
  wm.setDebugPoint(TGT);
  wm.addDebugMessage(WorldModel::COMMENT, "(BestPosition)putPoint!<TGT>");
  return goal;
*/
  return d_goal;

}

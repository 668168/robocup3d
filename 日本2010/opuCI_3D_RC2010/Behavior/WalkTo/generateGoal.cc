#include "walkto.ih"

rf<Behavior::Goal> WalkTo::generateGoal(unsigned step, unsigned slot)
{
  // move to "given Pos" by parent's generateGoal.
  // Action 1. turn to goal
  // Action 2. walk straight to goal

  WorldModel& wm = WorldModel::getInstance();
  Vector3D pos = d_goal->getVector("Pos");
  double angleToPos;
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();



  if( wm.allObjectPosAvailable() )
  {
      Types::Object obj = getObjectBetweenPos(pos, 1.0);

      // check route and if an obstacle object is on the route, avoid it.

      // double threshould = 2.0;
      if ( obj != Types::NOBJECTS )//&& pos.length() > threshould )
      {
        Vector3D obstacleObjPos = wm.getObjectPosition(obj).getMu();

        // set new goal position ( the side of obstacle object)
        double avoidLength = 0.7;
        Vector3D newTarget = pos.normalize() * obstacleObjPos.length() + Math::calcPerpend(pos) * avoidLength;

        // if new goal is near obstacle, set goal as the other side of obstacle.
        if( Math::atSameSideOf( pos, obstacleObjPos, newTarget ) )
          newTarget = pos.normalize() * obstacleObjPos.length() - Math::calcPerpend(pos) * avoidLength;
        pos = newTarget;
      }

      angleToPos = getAngleWithStraight(pos);

  }
  else // 自己位置推定できない場合
  {
    pos = ballPos;
    angleToPos = getAngleWithStraight(pos);
  }

  con->addVar("Angle", angleToPos, angleToPos);
  con->addVar("Pos", pos);
  con->addVar("WalkTo", 0, 0);
  return goal;
  
}

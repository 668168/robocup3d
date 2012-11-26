#include "commonfunction.hh"

/* get player object between myself and pos.
 */
Types::Object getObjectBetweenPos(Vector3D pos, double accuracy)
{
  WorldModel& wm = WorldModel::getInstance();

  Types::Object obj = Types::NOBJECTS;

  double distToObj = pos.length();
  // PLAYER1 - 11 and OPPONENT1 - 11
  for (int i=Types::PLAYER1; i< Types::FLAG1L; i++)
  {
    Vector3D objPos = wm.getObjectPosition(static_cast<Types::Object>(i)).getMu();

    // in sight and in triangle
    if( objectExistBetweenPos( pos, accuracy, static_cast<Types::Object>(i) ) )
    {

      // nearest object
      if( distToObj > objPos.length() )
      {
        distToObj = objPos.length();
        obj = static_cast<Types::Object>(i);
      }
    }
  }

  return obj;
}

bool objectExistBetweenPos(Vector3D pos, double accuracy, Types::Object obj)
{
  WorldModel& wm = WorldModel::getInstance();

  if( ! wm.visibleObject(obj) )
    return false;

  Vector3D objPos = wm.getObjectPosition(obj).getMu();

  return existBetweenPos( pos, accuracy, objPos );
}

bool existBetweenPos(Vector3D pos, double accuracy, Vector3D vec)
{
  WorldModel& wm = WorldModel::getInstance();

  Vector3D A, B, C, D;
  Vector3D myself(0, 0, 0);
/*  Vector3D myself =
    ( wm.getBodyConnectionPosition(Types::BC_RTOE)
      + wm.getBodyConnectionPosition(Types::BC_LTOE) ) / 2.0;
*/
  A = myself + Math::calcPerpend(pos) * (accuracy / 2.0);
  D = -A;
  B = pos + A;
  C = pos + D;

  wm.setDebugLine(A, B);
  wm.setDebugLine(C, B);
  wm.setDebugLine(D, C);
  wm.setDebugLine(A, D);

  wm.setDebugLine(myself, vec);

  // in sight and in square
  return ( Math::inTriangle( A, C, B, vec)
           ||  Math::inTriangle( A, C, D, vec) );

}

bool ballKickable( double toeWidth, double reach , Vector3D toeToBall )
{
  WorldModel& wm = WorldModel::getInstance();

  // the vector from right toe to ball
  if( ! wm.visibleObject(Types::BALL) )
    return false;

  bool isBallKickable = ( toeToBall.getX() >= 0
                          && toeToBall.getX() <= reach
                          && fabs(toeToBall.getY()) < (toeWidth / 2.0) );

  return isBallKickable;
}

bool ballKickableByRight( double toeWidth, double reach)
{
  WorldModel& wm = WorldModel::getInstance();

  // the vector from right toe to ball
  Vector3D ttb = wm.getObjectPosition(Types::BALL).getMu()
    - wm.getBodyConnectionPosition(Types::BC_RTOE);

  // for debug
  std::stringstream ss;
  ss << " ToeR to Ball = ("
     << ttb.getX() << " "
     << ttb.getY() << " "
     << ttb.getZ() << ") = "
     << ttb.length();
  wm.addDebugMessage(WorldModel::COMMENT, ss.str());

  return ballKickable(toeWidth, reach, ttb);
}

bool ballKickableByLeft(double toeWidth, double reach)
{
  WorldModel& wm = WorldModel::getInstance();

  // the vector from right toe to ball
  Vector3D ttb = wm.getObjectPosition(Types::BALL).getMu()
    - wm.getBodyConnectionPosition(Types::BC_LTOE);

  // for debug
  std::stringstream ss;
  ss << " ToeL to Ball = ("
     << ttb.getX() << " "
     << ttb.getY() << " "
     << ttb.getZ() << ") = "
     << ttb.length();
  wm.addDebugMessage(WorldModel::COMMENT, ss.str());

  return ballKickable(toeWidth, reach, ttb);
}

double getAngleWithStraight( Vector3D vec, bool setZtoZero )
{
  if(setZtoZero)
    vec.setZ(0);

  Vector3D straight(1, 0, 0);

  double angle = straight.angle(vec) * 180.0 / M_PI;
  if(vec.getY() < 0)
    angle *= -1;

  return angle;
}

bool isBallNearCorner()
{
  WorldModel& wm = WorldModel::getInstance();
  Vector3D ball = wm.getObjectPosition(Types::BALL).getMu();

  Vector3D flag1 = wm.getObjectPosition(Types::FLAG1THEM).getMu();
  Vector3D flag2 = wm.getObjectPosition(Types::FLAG2THEM).getMu();
  Vector3D goal1 = wm.getObjectPosition(Types::GOAL1THEM).getMu();
  Vector3D goal2 = wm.getObjectPosition(Types::GOAL2THEM).getMu();

  Vector3D unitX = wm.worldUnitX();
  if( wm.getSide() == WorldModel::RIGHT )
    unitX = -unitX;

  double dist = 4.45;

  return ( Math::inTriangle(flag1, goal1, flag1 - unitX * dist, ball)
           || Math::inTriangle(flag2, goal2, flag2 - unitX * dist, ball));

}

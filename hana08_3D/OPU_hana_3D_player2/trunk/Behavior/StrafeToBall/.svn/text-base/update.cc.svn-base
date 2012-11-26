#include "strafetoball.ih"

void StrafeToBall::update()
{
  Behavior::update();

  WorldModel& wm = WorldModel::getInstance();

  // The ball position.
  Vector3D ball = wm.getObjectPosition(Types::BALL).getMu();

  d_committed = (fabs(ball.getY()) > 0.5);  
}

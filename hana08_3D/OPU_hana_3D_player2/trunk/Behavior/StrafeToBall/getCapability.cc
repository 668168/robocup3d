#include "strafetoball.ih"

Behavior::ConfidenceInterval StrafeToBall::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();

  // The ball position.
  Vector3D ball = wm.getObjectPosition(Types::BALL).getMu();

  //cerr << "Y: " << ball.getY() << " Len: " << ball.length() << " Angle: " << atan(ball.getY()/ball.getX()) << endl;

  if (fabs(ball.getY()) > 1.5 && ball.length() < 7 && fabs(atan(ball.getY()/ball.getX())) < 0.25*M_PI) {
    //cerr << "I want to Strafe!" << endl;
    return ConfidenceInterval(1.0, 1.0);
  }

  return ConfidenceInterval(0.0, 0.0);
}

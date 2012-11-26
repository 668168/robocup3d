#include "walkstraightto.ih"

void WalkStraightTo::update()
{
  Behavior::update();
  
  if (d_committed)
    return;

  WorldModel& wm = WorldModel::getInstance();
  Vector3D ballPos = wm.get(WorldModel::iVisionBall);
  double angleToBall = ballPos.getY() / M_PI * 180;
  //double minAngle = 10.0;
  //double maxAngle = 20.0;
  //double angle = minAngle;
  
  NormalDistribution3D BallInfo = wm.getObjectPosition(Types::BALL);
  Vector3D ballPosCar = BallInfo.getMu();
  double ballX = ballPosCar.getX();
  double ballY = ballPosCar.getY();
  //bool leftTouch = wm.getLeftTouch();
  //bool rightTouch = wm.getRightTouch();
  // Distance from foot to ball (not from camera)
  double distToBall = sqrt(ballX * ballX + ballY * ballY);

//  if (distToBall < 7.5)
  if (distToBall < 1.875)
    d_committed = false;
  else if (fabs(angleToBall) < 20.0)
    d_committed = true;
//  else if (!wm.onMyFeet())
//    d_committed = true;
  else
    d_committed = false;
    
//  std::cout << "In WalkStraightto::update()" << std::endl;
//  std::cout << "  d_committed = " << d_committed << std::endl;
  
  //d_committed = !wm.onMyFeet();
}


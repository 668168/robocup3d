#include "kickto.ih"

Behavior::ConfidenceInterval KickTo::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
//  NormalDistribution3D BallInfo = wm.getObjectPosition(Types::BALL);
//  Vector3D ballPosCar = BallInfo.getMu();
//  double ballX = ballPosCar.getX();
//  double ballY = ballPosCar.getY();
  //bool leftTouch = wm.getLeftTouch();
  //bool rightTouch = wm.getRightTouch();

/*
  Vector3D goal1Pos = wm.getObjectPosition(Types::GOAL1THEM).getMu();
  Vector3D goal2Pos = wm.getObjectPosition(Types::GOAL2THEM).getMu();
  Vector3D goalPos = (goal1Pos + goal2Pos) / 2;
  double goalX = goalPos.getX();
  double goalY = goalPos.getY();
  double distToGoal = sqrt(goalX * goalX + goalY * goalY);
*/
  // Distance from foot to ball (not from camera)
//  double distToBall = sqrt(ballX * ballX + ballY * ballY);
  
//  if (d_curStep >= 2 && (ballX < 0 || ballX > 2.0 || fabs(ballY) > 1.0))
//  if (d_curStep >= 3  // can kick series
//      && (ballPos.getX() < 0 || ballPos.getX() > 2 || fabs(ballPos.getY()) > 1))
//      return ConfidenceInterval(0.0, 0.0);
  
  if(ballPos.length() <= 0.5){
//	std::cout << "KickTo:(0.5, 0.2)" << std::endl;
	return ConfidenceInterval(0.5, 0.2);
  }
  else{
//	std::cout << "KickTo:(0.0, 0.0)" << std::endl;
	return ConfidenceInterval(0.0, 0.0);
  }
//  return ballPos.length() <= 0.5 ? ConfidenceInterval(0.5, 0.2) : ConfidenceInterval(0.0, 0.0);
//  return distToGoal <= 7.5 ? ConfidenceInterval(0.5, 0.2) : ConfidenceInterval(0.0, 0.0);
}

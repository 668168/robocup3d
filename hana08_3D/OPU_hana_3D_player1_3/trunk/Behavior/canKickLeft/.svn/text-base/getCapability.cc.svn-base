#include "cankickleft.ih"

Behavior::ConfidenceInterval CanKickLeft::getCapability(rf<Behavior::State> s, rf<Behavior::Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

  Vector3D goalPos = (wm.getObjectPosition(Types::GOAL1THEM).getMu() 
		      + wm.getObjectPosition(Types::GOAL2THEM).getMu()) / 2;
  double goalX = goalPos.getX();
  double goalY = goalPos.getY();
  double distToGoal = sqrt(goalX * goalX + goalY * goalY);
  
//  if (ballPos.getX() > 0 && ballPos.getX() < 1.5 && ballPos.getY() > 0 && ballPos.getY() < 0.7)
  if ((ballPos.getX() >= 0 && ballPos.getX() <= 0.15 && ballPos.getY() >= 0 
       && ballPos.getY() <= 0.07)&&(distToGoal <= 1.5))
    return ConfidenceInterval(0.7, 0.2);
    
  return ConfidenceInterval(-1.0, 0.0);
  /*_debugLevel4("WalkStraightTo::getCapability");
  
  rf<StateVarNode> gameStateNode = rf_cast<StateVarNode>(s->findDeep("GameState"));
  if (!gameStateNode)
  {

    _debugLevel1("WalkStraightTo doesn't understand!");
    return ConfidenceInterval(-1.0, 0.0);
  }
    
  StateVar gameState = gameStateNode->getVar();
  */
  /*WorldModel& wm = WorldModel::getInstance();
  NormalDistribution3D BallInfo = wm.getObjectPosition(Types::BALL);
  Vector3D ballPosCar = BallInfo.getMu();
  double ballX = ballPosCar.getX();
  double ballY = ballPosCar.getY();
  // Distance from foot to ball (not from camera)
  double distToBall = sqrt(ballX * ballX + ballY * ballY);
  Vector3D ballPosPol = wm.get(WorldModel::iVisionBall);
  double angleToBall = ballPosPol.getY() / M_PI * 180;
  double angle = 20.0;
 
  if (distToBall > 1.5 || angleToBall < -angle || angleToBall > 0)
  {
  	_debugLevel3("Too far to kick.");
    return ConfidenceInterval(-1.0, 0.0);
  }
 	cout << "shieT!" << endl;
 	_debugLevel4("Capable");
  return ConfidenceInterval(0.5, 0.2);
  */
}

#include "fallforward.ih"

Behavior::ConfidenceInterval FallForward::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();

    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
    Vector3D goalPos1 = wm.getObjectPosition(Types::GOAL1US).getMu();
    Vector3D goalPos2 = wm.getObjectPosition(Types::GOAL2US).getMu();
    Vector3D ballSpeed = wm.getObjectVector(Types::BALL).getMu();
    Vector3D goalPos = ( goalPos1 + goalPos2 ) / 2;
    Vector3D ballToAgent = -ballPos;
    Vector3D straight(1.0, 0.0, 0.0);

    double goalX = goalPos.getX();
    double goalY = goalPos.getY();

    double ballX = ballPos.getX();
    double ballY = ballPos.getY();

    double ballSpeedAngle;
    double ballPosAngle;

    rf<StateVarNode> angleNode = rf_cast<StateVarNode>(g->findDeep("PAngleX"));
    if(!angleNode)
	return ConfidenceInterval(0.0, 0.0);
    StateVar angleVar = angleNode->getVar();
    ballPosAngle = angleVar.second.mean();

    angleNode = rf_cast<StateVarNode>(g->findDeep("SAngleX"));
    if(!angleNode)
	return ConfidenceInterval(0.0, 0.0);
    angleVar = angleNode->getVar();
    ballSpeedAngle = angleVar.second.mean();

    if(ballX > 0 && ballX < fabs(ballY) &&
       goalX > 0 && goalX < fabs(goalY) )
    return ConfidenceInterval(0.6, 0.2);
if( fabs(ballY) >= fabs(ballX) && ballSpeedAngle <= ballPosAngle &&
 	ballSpeed.length() > 0.5 )
	return ConfidenceInterval(0.6, 0.2);

/*
  std::cout << "ballspeed:" << ballSpeed.length() << ballSpeed << std::endl;
  if(fabs(goalY) <= 0.7 && goalX <= 0)
    return ConfidenceInterval(0.5, 0.2);
  else if(fabs(goalY) > 0.7 && fabs(goalY) >= fabs(goalX))
    return ConfidenceInterval(0.5, 0.2);
  else 
*/
	return ConfidenceInterval(0.2, 0.2);


}

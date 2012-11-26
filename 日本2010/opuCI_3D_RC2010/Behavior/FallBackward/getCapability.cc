#include "fallbackward.ih"

Behavior::ConfidenceInterval FallBackward::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();

    Vector3D goalPos1 = wm.getObjectPosition(Types::GOAL1US).getMu();
    Vector3D goalPos2 = wm.getObjectPosition(Types::GOAL2US).getMu();
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
    Vector3D ballSpeed = wm.getObjectVector(Types::BALL).getMu();
    Vector3D goalPos = ( goalPos1 + goalPos2 ) / 2;
    Vector3D ballToAgent = -ballPos;
    Vector3D straight(1.0, 0.0, 0.0);

    double ballX = ballPos.getX();
    double ballY = ballPos.getY();

    double goalX = goalPos.getX();
    double goalY = goalPos.getY();
    double goal1X = goalPos1.getX();
    double goal1Y = goalPos1.getY();
    double goal2X = goalPos2.getX();
    double goal2Y = goalPos2.getY();

     if(wm.getSide() == WorldModel::LEFT)
    {
	double tmpX=goal1X;
	double tmpY=goal1Y;
	goal1X = goal2X;
	goal1Y = goal2Y;
	goal2X = tmpX;
	goal2Y = tmpY;
    }
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
 
    // ** shin - ballpos and goalpos
    if( ( ballX < 0 && ballY > 0 &&
	  goal1X > 0 && goal1Y < 0 &&
	  goal2X < 0 && goal2Y < 0 ) ||
	( ballX < 0 && ballY < 0 &&
	  goal1X < 0 && goal1Y > 0 &&
	  goal2X > 0 && goal2Y > 0 ) )
	if( ballSpeedAngle < ballPosAngle && ballSpeed.length() > 1.0 )
	    return ConfidenceInterval(0.0, 0.0);
	else
	    return ConfidenceInterval(0.5, 0.2);
    
    // ** ball speed **
    if(fabs(ballY) >= fabs(ballX) && ballSpeedAngle > ballPosAngle &&
       ballSpeed.length() > 1.0 )
	return ConfidenceInterval(0.5, 0.2);

   // ** ball and goal position **
    if(ballX < 0 && -ballX < fabs(ballY) &&
       goalX < 0 && -goalX < fabs(goalY) )
	return ConfidenceInterval(0.5, 0.2);

/*
    if(fabs(goalY) <= 0.7 && goalX > 0)
	return ConfidenceInterval(0.5, 0.2);
    else 
*/
    return ConfidenceInterval(0.0, 0.0);

}

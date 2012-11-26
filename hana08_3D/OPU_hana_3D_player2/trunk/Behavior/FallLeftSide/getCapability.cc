#include "fallleftside.ih"

Behavior::ConfidenceInterval FallLeftSide::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();

    Vector3D goalPos1 = wm.getObjectPosition(Types::GOAL1US).getMu();
    Vector3D goalPos2 = wm.getObjectPosition(Types::GOAL2US).getMu();
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
    Vector3D ballToAgent = -ballPos;
    Vector3D ballSpeed = wm.getObjectVector(Types::BALL).getMu();
    Vector3D goalPos = ( goalPos1 + goalPos2 ) / 2;
    Vector3D straight(0.0, 1.0, 0.0);

    double ballX = ballPos.getX();
    double ballY = ballPos.getY();

    double goalX = goalPos.getX();
    double goalY = goalPos.getY();

    double ballSpeedAngle;
    double ballPosAngle;

    rf<StateVarNode> angleNode = rf_cast<StateVarNode>(g->findDeep("PAngleY"));
    if(!angleNode)
	return ConfidenceInterval(0.0, 0.0);
    StateVar angleVar = angleNode->getVar();
    ballPosAngle = angleVar.second.mean();

    angleNode = rf_cast<StateVarNode>(g->findDeep("SAngleY"));
    if(!angleNode)
	return ConfidenceInterval(0.0, 0.0);
    angleVar = angleNode->getVar();
    ballSpeedAngle = angleVar.second.mean();
    
    if(ballY > 0 && ballY < fabs(ballX) &&
       goalY > 0 && goalY < fabs(goalX) ) 
    return ConfidenceInterval(0.5, 0.2);

if( fabs(ballX) > fabs(ballY) && ballSpeedAngle < ballPosAngle &&
    ballSpeed.length() > 0.5 )
    return ConfidenceInterval(0.5, 0.2);
/*
    if(fabs(goalY) > 0.7 && 
       ( (-goalX > goalY && goalY > 0 ) ||
	 (0 > -goalY && -goalY > goalX) ) )
	return ConfidenceInterval(0.5, 0.2);
    else
*/
	return ConfidenceInterval(0.0, 0.0);
}

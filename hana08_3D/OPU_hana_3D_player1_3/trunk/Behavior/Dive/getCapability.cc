#include "dive.ih"

Behavior::ConfidenceInterval Dive::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();

    Vector3D targetPos = g->getVector("TPos");

    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
    Vector3D goalPos1 = wm.getObjectPosition(Types::GOAL1US).getMu();
    Vector3D goalPos2 = wm.getObjectPosition(Types::GOAL2US).getMu();
    Vector3D goalPos = ( goalPos1 + goalPos2 ) / 2;

    double goal1X = goalPos1.getX();
    double goal1Y = goalPos1.getY();
    double goal2X = goalPos2.getX();
    double goal2Y = goalPos2.getY();

    if(wm.getSide() == WorldModel::LEFT)
    {
	double tmpX = goal1X;
	double tmpY = goal1Y;
	goal1X = goal2X;
	goal1Y = goal2Y;
	goal2X = tmpX;
	goal2Y = tmpY;
    }
    
    Vector3D goalToStraight(goal2Y - goal1Y, goal1X - goal2X, 0);

    Vector3D enemy1Pos(0,0,0), enemy2Pos(0,0,0), enemy3Pos(0,0,0);

    bool enemy1exist = wm.isObjectAlive(Types::OPPONENT1);
    bool enemy2exist = wm.isObjectAlive(Types::OPPONENT2);
    bool enemy3exist = wm.isObjectAlive(Types::OPPONENT3);

    Types::Object nearestEnemy;
    double distToEnemy=9999;
    if(enemy1exist)
    {
	enemy1Pos = wm.getObjectPosition(Types::OPPONENT1).getMu() - ballPos;
	if( distToEnemy > enemy1Pos.length() )
	{
	    nearestEnemy = Types::OPPONENT1;
	    distToEnemy = enemy1Pos.length();
	}
    }
    if(enemy2exist)
    {
	enemy2Pos = wm.getObjectPosition(Types::OPPONENT2).getMu() - ballPos;
	if( distToEnemy > enemy2Pos.length() )
	{
	    nearestEnemy = Types::OPPONENT2;
	    distToEnemy = enemy2Pos.length();
	}
    }
    if(enemy3exist)
    {
	enemy3Pos = wm.getObjectPosition(Types::OPPONENT3).getMu() - ballPos;
	if( distToEnemy > enemy3Pos.length() )
	{
	    nearestEnemy = Types::OPPONENT3;
	    distToEnemy = enemy3Pos.length();
	}
    }
    if(enemy1exist || enemy2exist || enemy3exist)
    {
	Vector3D nearestEnemyToBall = ballPos - wm.getObjectPosition(nearestEnemy).getMu();
	if(nearestEnemyToBall.length() > 1.5)
	    return ConfidenceInterval(0.0, 0.0);
    }

    goalPos.setZ(0);
    ballPos.setZ(0);

    double judgeAngle = ballPos.angle(goalPos) / M_PI * 180;
    double judgeAngle2 = ballPos.angle(goalToStraight) / M_PI * 180;
    
    Vector3D ballSpeed = wm.getObjectVector(Types::BALL).getMu();

    if( judgeAngle > 170 || ( ballSpeed.length() > 1.0 && 
			      ballSpeed.angle(ballPos) / M_PI * 180 > 170 ) )
	return ConfidenceInterval(0.0, 0.0);
    else if( judgeAngle2 < 90)
    {
	if( targetPos.length() < 0.3 && ballPos.length() < 1.0)
	    return ConfidenceInterval(0.5, 0.2);
	
	if( ballSpeed.length() > 1.2
	    && ballPos.length() < 1.8 )
	    return ConfidenceInterval(0.5, 0.2);
    }
    else
	return ConfidenceInterval(0.0, 0.0);
    
}

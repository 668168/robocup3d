#include "dribble.ih"

Behavior::ConfidenceInterval Dribble::getCapability(rf<State> s, rf<Goal> g)
{

    WorldModel& wm = WorldModel::getInstance();

    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
    Vector3D goalPos1 = wm.getObjectPosition(Types::GOAL1THEM).getMu();
    Vector3D goalPos2 = wm.getObjectPosition(Types::GOAL2THEM).getMu();

    ballPos.setZ(0);

    if((ballPos.getX() < 0.4 && ballPos.getX() > 0) && fabs(ballPos.getY()) < 0.1)     {
		return ConfidenceInterval(0.7, 0.0);
    }
    return  ConfidenceInterval(0.0, 0.2);
}

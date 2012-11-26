#include "intercept.ih"

Behavior::ConfidenceInterval Intercept::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();
    Vector3D targetPos = g->getVector("TPos");

    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
    Vector3D goalPos = ( wm.getObjectPosition(Types::GOAL1US).getMu() +
			 wm.getObjectPosition(Types::GOAL2US).getMu() ) / 2;

    Vector3D goalToBall = ballPos - goalPos;

    if(targetPos.length() < 0.2 && goalToBall.length() > 1.1)
	return ConfidenceInterval(0.0, 0.2);
    else if(goalToBall.length() < 5)
	return ConfidenceInterval(0.55, 0.2);
    else
	return ConfidenceInterval(0.0, 0.2);

}

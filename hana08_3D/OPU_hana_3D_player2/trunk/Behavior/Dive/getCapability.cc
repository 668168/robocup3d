#include "dive.ih"

Behavior::ConfidenceInterval Dive::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();

    Vector3D targetPos = g->getVector("Pos");

    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();


    if(ballPos.length() < 0.3)
	return ConfidenceInterval(0.5, 0.2);
    else if(targetPos.length() < 0.6 && ballPos.length() < 1.0)
	return ConfidenceInterval(0.5, 0.2);
    else
	return ConfidenceInterval(0.0, 0.0);

}

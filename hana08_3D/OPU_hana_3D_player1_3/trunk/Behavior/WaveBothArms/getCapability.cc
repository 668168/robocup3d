#include "wavebotharms.ih"

Behavior::ConfidenceInterval WaveBothArms::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();
    Vector3D targetPos = g->getVector("TPos");
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
    Vector3D goalPos1 = wm.getObjectPosition(Types::GOAL1US).getMu();
    Vector3D goalPos2 = wm.getObjectPosition(Types::GOAL2US).getMu();

    Vector3D goalPos = ( goalPos1 + goalPos2 ) / 2;

    Vector3D goalToBall = ballPos - goalPos;


    if(targetPos.length() <= 0.3)
	return ConfidenceInterval(0.5, 0.2);
    if(goalToBall.length() > 5)
	return ConfidenceInterval(0.5, 0.2);
    
    return ConfidenceInterval(0.0, 0.2);

}

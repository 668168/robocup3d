#include "guard.ih"

Behavior::ConfidenceInterval Guard::getCapability(rf<State> s, rf<Goal> g)
{
    WorldModel& wm = WorldModel::getInstance();
    Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

    if( wm.onMyBack() || wm.onMyBelly() || wm.onMySide() ||
	fabs(wm.getDistToField() ) < 0.2 )
	return ConfidenceInterval(0.0, 0.0);
    else
	return ConfidenceInterval(0.5, 0.2);
}

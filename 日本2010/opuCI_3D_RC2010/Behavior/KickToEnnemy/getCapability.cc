#include "kicktoennemy.ih"

Behavior::ConfidenceInterval KickToEnnemy::getCapability(rf<State> s,
		rf<Goal> g)
{
	WorldModel& wm = WorldModel::getInstance();

	if (wm.onMyBack() || wm.onMyBelly() || wm.onMySide())
			return ConfidenceInterval(0.0, 0.0);

	Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
	ballPos.setZ(0);
	double dist = ballPos.length();

	if (dist < 0.1 && wm.visibleObject(Types::BALL))
		return ConfidenceInterval(0.8, 0.2);

	return ConfidenceInterval(-1.0, 0.0);

}

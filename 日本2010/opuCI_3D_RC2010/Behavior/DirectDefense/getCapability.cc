#include "directdefense.ih"

Behavior::ConfidenceInterval DirectDefense::getCapability(rf<State> s,
		rf<Goal> g)
{
	WorldModel& wm = WorldModel::getInstance();

	int unum = wm.getUnum();

	if (wm.onMyBack() || wm.onMyBelly() || wm.onMySide())
		return ConfidenceInterval(0.0, 0.0);

	Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
	ballPos.setZ(0);
	double dist = ballPos.length();

	if ((unum == 4 || unum == 5 || unum == 6) && dist < 0.35)
		return ConfidenceInterval(0.9, 0.2);
	else if (unum == 4 && dist > 3.01)
	{
			return ConfidenceInterval(0.5, 0.1);
	}

	return ConfidenceInterval(0.0, 0.0);
}

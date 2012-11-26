#include "supportdefense.ih"

Behavior::ConfidenceInterval SupportDefense::getCapability(rf<State> s,
		rf<Goal> g) {

	WorldModel& wm = WorldModel::getInstance();

	if (wm.onMyBack() || wm.onMyBelly() || wm.onMySide())
			return ConfidenceInterval(0.0, 0.0);

	Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
	ballPos.setZ(0);
	double dist = ballPos.length();

	int unum = wm.getUnum();

/*	//if I am very close the ball
	if ((unum == 5 || unum == 6) && dist < 0.2)
		return ConfidenceInterval(0.8, 0.2);*/
	//if I am not close to the ball
	if ((unum == 5 || unum == 6) && dist > 1.01) {

		//if I am not the closest player to the ball nor the second closest player
		if (wm.getClosestTeamUnum() != unum ) {
			return ConfidenceInterval(0.7, 0.1); //peut etre augmenter la proba
		}
	}

	return ConfidenceInterval(0.0, 0.0);
}

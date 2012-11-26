#include "returntoposition.ih"

Behavior::ConfidenceInterval ReturnToPosition::getCapability(rf<State> s, rf<
		Goal> g) {
	WorldModel& wm = WorldModel::getInstance();
	int unum = wm.getUnum();
	Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
	ballPos.setZ(0);
	double dist = ballPos.length();
	Vector3D goalDir = (wm.getObjectPosition(Types::GOAL1US).getMu()
			+ wm.getObjectPosition(Types::GOAL2US).getMu()) * 0.5;

	//when we have been thrown away of the field
	if (wm.getObjectPosition(Types::FLAG1US).getMu().length() > wm.fieldWidth()
			|| wm.getObjectPosition(Types::FLAG2US).getMu().length()
					> wm.fieldWidth()
			|| wm.getObjectPosition(Types::FLAG1THEM).getMu().length()
					> wm.fieldLength()
			|| wm.getObjectPosition(Types::FLAG2THEM).getMu().length()
					> wm.fieldLength())
		return ConfidenceInterval(0.6, 0.2); //to adjust

	//when we are not attacked anymore
	if (!wm.getProcessingOppAttack() && wm.getPlayMode() == WorldModel::PLAY_ON) {
		Vector3D fieldSide = wm.getObjectPosition(Types::GOAL1US).getMu()
				- wm.getObjectPosition(Types::GOAL2US).getMu();
		Vector3D fieldSidePerp = -Math::calcPerpend(fieldSide);

		if (unum == 4) {
			double angle = fabs(goalDir.angle(fieldSidePerp));
			double dist = goalDir.length();

			if (dist > 5.2 || dist < 4.5 || angle > M_PI / 8)
				return ConfidenceInterval(0.7, 0.2);
		}
		if (unum == 5) {
			Vector3D goal1usDir = wm.getObjectPosition(Types::GOAL1US).getMu();
			double angle = fabs(goal1usDir.angle(fieldSidePerp));
			double dist = goal1usDir.length();

			if (dist > 4.2 || dist < 3 || angle > M_PI / 8)
				return ConfidenceInterval(0.7, 0.2);
		}
		if (unum == 6) {
			Vector3D goal2usDir = wm.getObjectPosition(Types::GOAL2US).getMu();
			double angle = fabs(goal2usDir.angle(fieldSidePerp));
			double dist = goal2usDir.length();

			if (dist > 4 || dist < 3 || angle > M_PI / 8)
				return ConfidenceInterval(0.7, 0.2);
		}
	}

	//if we are too far from our original position and the ball is far
	if (wm.getProcessingOppAttack() && ((unum == 5 && wm.getObjectPosition(Types::GOAL1US).getMu().length()
			> 5) || (unum == 6
			&& wm.getObjectPosition(Types::GOAL2US).getMu().length() > 4.8)) && dist > 4)
		return ConfidenceInterval(0.5, 0.1);

	return ConfidenceInterval(0.05, 0.05);
}

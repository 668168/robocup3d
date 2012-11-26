#include "gotoball.ih"

Behavior::ConfidenceInterval GoToBall::getCapability(rf<State> s, rf<Goal> g) {
	WorldModel& wm = WorldModel::getInstance();
	wm.setNeckDirUpdate(true);

	if (wm.onMyBack() || wm.onMyBelly() || wm.onMySide() || wm.getPlayMode()
			== WorldModel::GOAL_KICK_US)
		return ConfidenceInterval(0.0, 0.0);

	if (wm.getProcessingOppAttack() && (wm.getUnum() == 4 || wm.getUnum() == 5
			|| wm.getUnum() == 6)) {

		//std::cout << "on est attaqué " << std::endl;

		Vector3D ballPosMe = wm.getObjectPosition(Types::BALL).getMu();
		ballPosMe.setZ(0);

		int unum = wm.getUnum();
		double dist = ballPosMe.length();

		if (wm.getPlayMode() == WorldModel::KICKIN_THEM)
			if (dist > 1.01)
				return ConfidenceInterval(0.5, 0.0);
			else
				return ConfidenceInterval(0.0, 0.0);
		else if (wm.getPlayMode() == WorldModel::KICKIN_US)
			if (wm.getClosestTeamUnum() == unum)
				return ConfidenceInterval(0.7, 0.1);
			else
				return ConfidenceInterval(0.1, 0.0);

		//add condition on penalty area

		if (wm.getClosestOpponentDist() <= 0.8) {
			//std::cout << "un ennemi pres de la balle " << std::endl;
			if (dist > 1.01) {
				//std::cout << "je suis à plus de 1 m de la balle " << std::endl;
				if (wm.getClosestTeamUnum() == unum)
					return ConfidenceInterval(0.8, 0.2);
				else if (wm.getSortedTeamBallUnum(2) == unum)
					return ConfidenceInterval(0.7, 0.1);
				else
					return ConfidenceInterval(0.1, 0.0);

			} else if (dist > 0.41 && dist <= 1.01) {
				//std::cout << "je suis entre 1 m  et 0.4 m de la balle "
				//	<< std::endl;
				if (wm.getClosestTeamUnum() == unum)
					return ConfidenceInterval(0.8, 0.2);
				else
					return ConfidenceInterval(0.0, 0.0);
			}
		}

		//std::cout << "unum " << unum << std::endl;

		if (wm.getClosestTeamUnum() == unum)
			return ConfidenceInterval(0.8, 0.1);
		else if (wm.getSortedTeamBallUnum(2) == unum && dist > 0.41 && dist
				<= 1.01)
			return ConfidenceInterval(0.7, 0.1);
		else if (unum == 4 && dist > 1.01)
			return ConfidenceInterval(0.6, 0.1);
		else if (dist > 1.01)
			return ConfidenceInterval(0.3, 0.1);

	}

	return ConfidenceInterval(0.0, 0.0);
}

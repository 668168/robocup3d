#include "pass.ih"

Behavior::ConfidenceInterval Pass::getCapability(rf<State> s, rf<Goal> g) {

	WorldModel& wm = WorldModel::getInstance();
	Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
	ballPos.setZ(0);

	if (ballPos.length() <= 0.5 && wm.visibleObject(Types::BALL)) {
		//Looking for friend players near the active player
		std::vector<double> vectFriend;
		for (int i = Types::PLAYER1; i <= Types::PLAYER6; i++) {
			if (wm.visibleObject((Types::Object) i)) {
				Vector3D playPos =
						wm.getObjectPosition((Types::Object) i).getMu();
				playPos.setZ(0);
				double dist = playPos.length();
				vectFriend.push_back(dist);
			}
		}

		//Looking for ennemy players near the active player
		std::vector<double> vectOpponent;
		for (int j = Types::OPPONENT1; j <= Types::OPPONENT6; j++) {
			if (wm.visibleObject((Types::Object) j)) {
				Vector3D playPos =
						wm.getObjectPosition((Types::Object) j).getMu();
				playPos.setZ(0);
				double dist = playPos.length();
				vectOpponent.push_back(dist);
			}
		}

		//Look for the nearest ennemy
		double min = 100;
		if (vectOpponent.size() != 0) {
			for (int k = 0; k < vectOpponent.size(); k++) {
				if (vectOpponent[k] < min)
					min = vectOpponent[k];
			}
		}

		//If there are ennemies around and players not far away then
		//pass mostly recommanded
		if (min < 0.8 && vectFriend.size() != 0) {
			return ConfidenceInterval(0.5, 0.2);
		}
		//If there are players around but ennemies are far then pass
		//an option to consider but not a priority
		else if (vectFriend.size() != 0) {
			return ConfidenceInterval(0.3, 0.1);
		}
		return ConfidenceInterval(0.2, 0.1);
	}

	return ConfidenceInterval(0.1, 0.0);
}

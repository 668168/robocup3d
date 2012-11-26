#include "defense.ih"

//à améliorer
void Defense::update() {

	Behavior::update();
	WorldModel& wm = WorldModel::getInstance();
	wm.update();

	if (wm.getPlayMode() == WorldModel::BEFORE_KICKOFF || wm.getPlayMode()
			== WorldModel::GOAL_THEM || wm.getPlayMode() == WorldModel::GOAL_US
			|| wm.getPlayMode() == WorldModel::GOAL_RIGHT || wm.getPlayMode()
			== WorldModel::GOAL_LEFT) {
		wm.setProcessingOppAttack(false);
		d_minTime = 0;
		d_minTimeUpdate = false;
	}

	if (wm.visibleObject(Types::BALL) && !(wm.getPlayMode()
			== WorldModel::BEFORE_KICKOFF || wm.getPlayMode()
			== WorldModel::GOAL_THEM || wm.getPlayMode() == WorldModel::GOAL_US
			|| wm.getPlayMode() == WorldModel::GOAL_RIGHT || wm.getPlayMode()
			== WorldModel::GOAL_LEFT)) {

		Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

		int i = 0;
		std::vector<double> vvaluesNew;
		std::vector<double> vvaluesOld;

		if (wm.visibleObject(Types::FLAG1L)) {
			if (i < 3) {
				Vector3D pos = wm.getObjectPosition(Types::FLAG1L).getMu();
				vvaluesNew.push_back(-9);
				vvaluesNew.push_back(6);
				vvaluesNew.push_back(0);
				vvaluesOld.push_back(pos.getX());
				vvaluesOld.push_back(pos.getY());
				vvaluesOld.push_back(1);
				i++;
			}
		}
		if (wm.visibleObject(Types::FLAG1R)) {
			if (i < 3) {
				Vector3D pos = wm.getObjectPosition(Types::FLAG1R).getMu();
				vvaluesNew.push_back(9);
				vvaluesNew.push_back(6);
				vvaluesNew.push_back(0);
				vvaluesOld.push_back(pos.getX());
				vvaluesOld.push_back(pos.getY());
				vvaluesOld.push_back(1);
				i++;
			}
		}
		if (wm.visibleObject(Types::FLAG2L)) {
			if (i < 3) {
				Vector3D pos = wm.getObjectPosition(Types::FLAG2L).getMu();
				vvaluesNew.push_back(-9);
				vvaluesNew.push_back(-6);
				vvaluesNew.push_back(0);
				vvaluesOld.push_back(pos.getX());
				vvaluesOld.push_back(pos.getY());
				vvaluesOld.push_back(1);
				i++;
			}
		}
		if (wm.visibleObject(Types::FLAG2R)) {
			if (i < 3) {
				Vector3D pos = wm.getObjectPosition(Types::FLAG2R).getMu();
				vvaluesNew.push_back(9);
				vvaluesNew.push_back(-6);
				vvaluesNew.push_back(0);
				vvaluesOld.push_back(pos.getX());
				vvaluesOld.push_back(pos.getY());
				vvaluesOld.push_back(1);
				i++;
			}
		}
		if (wm.visibleObject(Types::GOAL1L) && wm.visibleObject(Types::GOAL2L)) {
			if (i < 3) {
				Vector3D pos1 = wm.getObjectPosition(Types::GOAL1L).getMu();
				Vector3D pos2 = wm.getObjectPosition(Types::GOAL2L).getMu();
				vvaluesNew.push_back(-8.4);
				vvaluesNew.push_back(0);
				vvaluesNew.push_back(0);
				vvaluesOld.push_back(((pos1.getX() + pos2.getX()) / 2) - 0.6);
				vvaluesOld.push_back((pos1.getY() + pos2.getY()) / 2);
				vvaluesOld.push_back(1);
				i++;
			}
		}
		if (wm.visibleObject(Types::GOAL1R) && wm.visibleObject(Types::GOAL2R)) {
			if (i < 3) {
				Vector3D pos1 = wm.getObjectPosition(Types::GOAL1R).getMu();
				Vector3D pos2 = wm.getObjectPosition(Types::GOAL2R).getMu();
				vvaluesNew.push_back(8.4);
				vvaluesNew.push_back(0);
				vvaluesNew.push_back(0);
				vvaluesOld.push_back(((pos1.getX() + pos2.getX()) / 2) - 0.6);
				vvaluesOld.push_back((pos1.getY() + pos2.getY()) / 2);
				vvaluesOld.push_back(1);
				i++;
			}
		}

		//if there are enough flags to determine the ball position in the field coordinates
		if (i == 3) {
			Matrix9D m_new;
			Matrix9D m_old;

			for (unsigned j = 0; j < 9; ++j) {
				m_new.set(j, vvaluesNew[j]);
				m_old.set(j, vvaluesOld[j]);
			}

			Matrix9D m_passage;

			double quot = (m_old[0] - m_old[3]) * (m_old[1] - m_old[7])
					- (m_old[0] - m_old[6]) * (m_old[1] - m_old[4]);

			if (quot != 0) {

				/*std::cout << "m_new : ";
				for (int k = 0; k < 9; k++) {
					std::cout << m_new[k] << " ";
				}
				std::cout << ";" << std::endl;

				std::cout << "m_old : ";
				for (int k = 0; k < 9; k++) {
					std::cout << m_old[k] << " ";
				}
				std::cout << ";" << std::endl;*/

				double a1 = ((m_old[1] - m_old[7]) * (m_new[0] - m_new[3])
						- (m_new[0] - m_new[6]) * (m_old[1] - m_old[4])) / quot;
				double b1 = -((m_old[0] - m_old[6]) * (m_new[0] - m_new[3])
						- (m_new[0] - m_new[6]) * (m_old[0] - m_old[3])) / quot;
				double c1 = m_new[0] - a1 * m_old[0] - b1 * m_old[1];
				double a2 = ((m_old[1] - m_old[7]) * (m_new[1] - m_new[4])
						- (m_new[1] - m_new[7]) * (m_old[1] - m_old[4])) / quot;
				double b2 = -((m_old[0] - m_old[6]) * (m_new[1] - m_new[4])
						- (m_new[1] - m_new[7]) * (m_old[0] - m_old[3])) / quot;
				double c2 = m_new[1] - a2 * m_old[0] - b2 * m_old[1];

				m_passage.set(0, a1);
				m_passage.set(1, a2);
				m_passage.set(3, b1);
				m_passage.set(4, b2);
				m_passage.set(6, c1);
				m_passage.set(7, c2);

				ballPos.setZ(1);
				Vector3D ballPosNew = m_passage * ballPos;

				/*std::cout << "m_passage : ";
				for (int k = 0; k < 9; k++) {
					std::cout << m_passage[k] << " ";
				}
				std::cout << ";" << std::endl;

				 std::cout << "ballPosO : ";
				 std::cout << ballPos.getX() << " ";
				 std::cout << ballPos.getY() << " ";
				 std::cout << ballPos.getZ() << " ";
				 std::cout << ";" << std::endl;

				 std::cout << "unum " << wm.getUnum() << " : ballPosN : ";
				 std::cout << ballPosNew.getX() << " ";
				 std::cout << ballPosNew.getY() << " ";
				 std::cout << ballPosNew.getZ() << " ";
				 std::cout << ";" << std::endl;*/
        wm.setDebugPointWithLabel(ballPosNew, "NBall");

				if ((ballPosNew.getX() < -0.6 && wm.getSide()
						== WorldModel::LEFT) || (ballPosNew.getX() > 0.6
						&& wm.getSide() == WorldModel::RIGHT)) {
					std::cout << "gotoball::update  enemy on sight"
							<< std::endl;
					wm.setProcessingOppAttack(true);
					d_minTime = wm.getTime();
					d_minTimeUpdate = true;
				} else {
					wm.setProcessingOppAttack(false);
					if (wm.getTime() - d_minTime > 1.5)
						d_minTimeUpdate = false;
				}
			}
		}
		//if we can see two flags
		else if (i == 2) {
			ballPos.setZ(0);
			std::vector<bool> flag;
			int j = 0;

			if (wm.visibleObject(Types::FLAG1THEM)) {
				if (j < 2) {
					Vector3D pos =
							wm.getObjectPosition(Types::FLAG1THEM).getMu();
					double distFB = (ballPos - pos).length();
					if (distFB > 9)
						flag.push_back(true);
					else
						flag.push_back(false);
					j++;

				}
			}

			if (wm.visibleObject(Types::FLAG2THEM)) {
				if (j < 2) {
					Vector3D pos =
							wm.getObjectPosition(Types::FLAG2THEM).getMu();
					double distFB = (ballPos - pos).length();
					if (distFB > 9)
						flag.push_back(true);
					else
						flag.push_back(false);
					j++;
				}
			}

			if (wm.visibleObject(Types::GOAL1THEM)) {
				if (j < 2) {
					Vector3D pos =
							wm.getObjectPosition(Types::GOAL1THEM).getMu();
					double distFB = (ballPos - pos).length();
					if (distFB > 9)
						flag.push_back(true);
					else
						flag.push_back(false);
					j++;
				}
			}

			if (wm.visibleObject(Types::GOAL2THEM)) {
				if (j < 2) {
					Vector3D pos =
							wm.getObjectPosition(Types::GOAL2THEM).getMu();
					double distFB = (ballPos - pos).length();
					if (distFB > 9)
						flag.push_back(true);
					else
						flag.push_back(false);
					j++;
				}
			}

			if (wm.visibleObject(Types::FLAG1US)) {
				if (j < 2) {
					Vector3D pos = wm.getObjectPosition(Types::FLAG1US).getMu();
					double distFB = (ballPos - pos).length();
					if (distFB < 9)
						flag.push_back(true);
					else
						flag.push_back(false);
					j++;
				}
			}

			if (wm.visibleObject(Types::FLAG2US)) {
				if (j < 2) {
					Vector3D pos = wm.getObjectPosition(Types::FLAG2US).getMu();
					double distFB = (ballPos - pos).length();
					if (distFB < 9)
						flag.push_back(true);
					else
						flag.push_back(false);
					j++;
				}
			}

			if (wm.visibleObject(Types::GOAL1US)) {
				if (j < 2) {
					Vector3D pos = wm.getObjectPosition(Types::GOAL1US).getMu();
					double distFB = (ballPos - pos).length();
					if (distFB < 9)
						flag.push_back(true);
					else
						flag.push_back(false);
					j++;
				}
			}

			if (wm.visibleObject(Types::GOAL2US)) {
				if (j < 2) {
					Vector3D pos = wm.getObjectPosition(Types::GOAL2US).getMu();
					double distFB = (ballPos - pos).length();
					if (distFB < 9)
						flag.push_back(true);
					else
						flag.push_back(false);
					j++;
				}
			}

			if (flag[0] && flag[1]) {
				wm.setProcessingOppAttack(true);
				d_minTime = wm.getTime();
				d_minTimeUpdate = true;
			} else {
				wm.setProcessingOppAttack(false);
				if (wm.getTime() - d_minTime > 1.5)
					d_minTimeUpdate = false;
			}

		}

		//if we can see one flag
		else if (i == 1) {
			ballPos.setZ(0);
			//if distBallFlagEnnemy > 9 then being attacked
			//if distBallFlagFriend < 9 then being attacked
			//else not attacked
			if (wm.visibleObject(Types::FLAG1THEM)) {
				Vector3D pos = wm.getObjectPosition(Types::FLAG1THEM).getMu();
				double distFB = (ballPos - pos).length();
				if (distFB > 9)
					wm.setProcessingOppAttack(true);
				else
					wm.setProcessingOppAttack(false);
			} else if (wm.visibleObject(Types::FLAG2THEM)) {
				Vector3D pos = wm.getObjectPosition(Types::FLAG2THEM).getMu();
				double distFB = (ballPos - pos).length();
				if (distFB > 9)
					wm.setProcessingOppAttack(true);
				else
					wm.setProcessingOppAttack(false);
			} else if (wm.visibleObject(Types::GOAL1THEM)) {
				Vector3D pos = wm.getObjectPosition(Types::GOAL1THEM).getMu();
				double distFB = (ballPos - pos).length();
				if (distFB > 9)
					wm.setProcessingOppAttack(true);
				else
					wm.setProcessingOppAttack(false);
			} else if (wm.visibleObject(Types::GOAL2THEM)) {
				Vector3D pos = wm.getObjectPosition(Types::GOAL2THEM).getMu();
				double distFB = (ballPos - pos).length();
				if (distFB > 9)
					wm.setProcessingOppAttack(true);
				else
					wm.setProcessingOppAttack(false);
			} else if (wm.visibleObject(Types::FLAG1US)) {
				Vector3D pos = wm.getObjectPosition(Types::FLAG1US).getMu();
				double distFB = (ballPos - pos).length();
				if (distFB < 9)
					wm.setProcessingOppAttack(true);
				else
					wm.setProcessingOppAttack(false);
			} else if (wm.visibleObject(Types::FLAG2US)) {
				Vector3D pos = wm.getObjectPosition(Types::FLAG2US).getMu();
				double distFB = (ballPos - pos).length();
				if (distFB < 9)
					wm.setProcessingOppAttack(true);
				else
					wm.setProcessingOppAttack(false);
			} else if (wm.visibleObject(Types::GOAL1US)) {
				Vector3D pos = wm.getObjectPosition(Types::GOAL1US).getMu();
				double distFB = (ballPos - pos).length();
				if (distFB < 9)
					wm.setProcessingOppAttack(true);
				else
					wm.setProcessingOppAttack(false);
			} else if (wm.visibleObject(Types::GOAL2US)) {
				Vector3D pos = wm.getObjectPosition(Types::GOAL2US).getMu();
				double distFB = (ballPos - pos).length();
				if (distFB < 9)
					wm.setProcessingOppAttack(true);
				else
					wm.setProcessingOppAttack(false);
			}
			if (wm.getProcessingOppAttack()) {
				d_minTime = wm.getTime();
				d_minTimeUpdate = true;
			} else {
				if (wm.getTime() - d_minTime > 1.5)
					d_minTimeUpdate = false;
			}
		}
		//otherwise consider we are being attacked
		else {
			std::cout << "gotoball::update  I don't see anything" << std::endl;
			wm.setProcessingOppAttack(true);
			d_minTime = wm.getTime();
			d_minTimeUpdate = true;
		}
	}

}


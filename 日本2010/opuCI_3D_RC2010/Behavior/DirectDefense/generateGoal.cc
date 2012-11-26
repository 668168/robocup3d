#include "directdefense.ih"

rf<Behavior::Goal> DirectDefense::generateGoal(unsigned step, unsigned slot) {
	rf<Goal> goal = new Goal();
	rf<OrNode> dis = goal->addDisjunct();
	rf<AndNode> con = dis->addConjunct();

	WorldModel& wm = WorldModel::getInstance();

	Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
	ballPos.setZ(0);
	Vector3D goalPos = (wm.getObjectPosition(Types::GOAL1THEM).getMu()
			+ wm.getObjectPosition(Types::GOAL2THEM).getMu()) / 2.0;

	Vector3D goalPosUs = (wm.getObjectPosition(Types::GOAL1US).getMu()
			+ wm.getObjectPosition(Types::GOAL2US).getMu()) / 2.0;


	goalPos.setZ(0.0);
	goalPosUs.setZ(0.0);

	Vector3D target = ballPos;
	double angleToPos = 0;
    Vector3D fieldSide = wm.getObjectPosition(Types::GOAL1US).getMu() -
      wm.getObjectPosition(Types::GOAL2US).getMu();

      stringstream ss;

	if (ballPos.length() < 0.35) {
		Vector3D flag1Pos = (wm.getObjectPosition(Types::FLAG1THEM).getMu());
		flag1Pos.setZ(0);

		Vector3D flag2Pos = (wm.getObjectPosition(Types::FLAG2THEM).getMu());
		flag2Pos.setZ(0);

		WorldModel::Zone goalPosZone = wm.getZone(goalPos);
		WorldModel::Zone flag1Zone = wm.getZone(flag1Pos);
		WorldModel::Zone flag2Zone = wm.getZone(flag2Pos);

		int unumFront = wm.getClosestZonePlayer(WorldModel::NEAR_FRONT);
		int unumLeft = wm.getClosestZonePlayer(WorldModel::NEAR_LEFT);
		int unumRight = wm.getClosestZonePlayer(WorldModel::NEAR_RIGHT);

		if (unumFront == 2 || unumLeft == 2 || unumRight == 2) {
			angleToPos = getAngleWithStraight(target);
      wm.setDebugPointWithLabel(target, "Defend2");
      ss << "Defend2 " << angleToPos;
      wm.addDebugMessage(WorldModel::COMMENT, ss.str());
		} else if (unumFront == 3 || unumLeft == 3 || unumRight == 3) {
			angleToPos = getAngleWithStraight(target);
      wm.setDebugPointWithLabel(target, "Defend3");
      ss << "Defend3 " << angleToPos;
      wm.addDebugMessage(WorldModel::COMMENT, ss.str());
		} else if ((goalPosZone == WorldModel::NEAR_FRONT && unumFront == -1)
				|| (goalPosZone == WorldModel::NEAR_LEFT && unumLeft == -1)
				|| (goalPosZone == WorldModel::NEAR_RIGHT && unumRight == -1)) {
			angleToPos = getAngleWithStraight(target);
      wm.setDebugPointWithLabel(target, "Defend GoalTHEM");
      ss << "Defend GOAL THEM " << angleToPos;
      wm.addDebugMessage(WorldModel::COMMENT, ss.str());
		} else if ((flag1Zone == WorldModel::NEAR_FRONT && unumFront == -1)
				|| (flag1Zone == WorldModel::NEAR_LEFT && unumLeft == -1)
				|| (flag1Zone == WorldModel::NEAR_RIGHT && unumRight == -1)) {
			angleToPos = getAngleWithStraight(target);
      wm.setDebugPointWithLabel(target, "Defend FLAG1");
      ss << "Defend FLAG1 " << angleToPos;
      wm.addDebugMessage(WorldModel::COMMENT, ss.str());
		} else if ((flag2Zone == WorldModel::NEAR_FRONT && unumFront == -1)
				|| (flag2Zone == WorldModel::NEAR_LEFT && unumLeft == -1)
				|| (flag2Zone == WorldModel::NEAR_RIGHT && unumRight == -1)) {
			angleToPos = getAngleWithStraight(target);
      wm.setDebugPointWithLabel(target, "Defend Flag2");
      ss << "Defend FLAG2 " << angleToPos;
      wm.addDebugMessage(WorldModel::COMMENT, ss.str());
		} else {
			angleToPos = getAngleWithStraight(target);
      wm.setDebugPointWithLabel(target, "Defend Go To Attacker");
      ss << "Defend go to attacker " << angleToPos;
      wm.addDebugMessage(WorldModel::COMMENT, ss.str());
		}

	} else if ( ballPos.length() > 1.01) {
		Vector3D fieldSidePerp = -Math::calcPerpend(fieldSide);
		Vector3D goalField = fieldSidePerp.normalize() * 5;
		target = goalPosUs + goalField;

	}

  con->addVar("Angle", angleToPos, angleToPos);
	/*double angleR = M_PI / 4;
	 double angleL = 3 * M_PI / 4;

	 Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
	 ballPos.setZ(0.0);
	 double dist = ballPos.length();
	 Vector3D target(0, 0, 0);

	 Vector3D goalPos = (wm.getObjectPosition(Types::GOAL1THEM).getMu()
	 + wm.getObjectPosition(Types::GOAL2THEM).getMu()) / 2.0;

	 goalPos.setZ(0.0);

	 int unumFront = wm.getClosestZoneFront();
	 int unumLeft = wm.getClosestZoneLeft();
	 int unumRight = wm.getClosestZoneRight();

	 //find an empty space in direction of the ball
	 if (dist < 0.41) {
	 target = ballPos;

	 if (wm.visibleObject(Types::BALL)) {
	 double angle = Vector3D(0, 1, 0).angle(goalPos);
	 if (unumFront == -1 && angle > angleR && angle <= angleL)
	 target = Vector3D(0, dist, 0);
	 else if (unumLeft == -1 && angle > angleL && angle <= -angleL)
	 target = Vector3D(-dist, 0, 0);
	 else if (unumRight == -1 && angle <= angleR && angle > -angleR)
	 target = Vector3D(dist, 0, 0);
	 else
	 target = goalPos;
	 }
	 }*/

	con->addVar("Pos", target);
	wm.setDebugPointWithLabel(target, "DirectDifense_TGT");

	return goal;
}

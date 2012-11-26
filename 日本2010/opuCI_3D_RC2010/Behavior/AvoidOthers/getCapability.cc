#include "avoidothers.ih"

Behavior::ConfidenceInterval AvoidOthers::getCapability(rf<State> s, rf<Goal> g) {
	WorldModel& wm = WorldModel::getInstance();
/*
	int unum = wm.getClosestZoneFront();

	if (unum != -1) {
		int team = 0;
		if (unum > 5) {
			team = 1;
			unum -= 6;
		}
		d_zoneToGo = nu;
		Vector3D closest = wm.getPlayerByUnum((unsigned) team, (unsigned) unum);
		closest.setZ(0);
		double distObstacle = closest.length();
		if (distObstacle < 0.33)
			return ConfidenceInterval(0.9, 0.1);
	}
	
	unum = wm.getClosestZoneRight();
	if (unum != -1) {
		int team = 0;
		if (unum > 5) {
			team = 1;
			unum -= 6;
		}
		d_zoneToGo = nr;
		Vector3D closest = wm.getPlayerByUnum((unsigned) team, (unsigned) unum);
		closest.setZ(0);
		double distObstacle = closest.length();
		if (distObstacle < 0.33)
			return ConfidenceInterval(0.9, 0.1);
	}
	
	unum = wm.getClosestZoneLeft();
	if (unum != -1) {
		int team = 0;
		if (unum > 5) {
			team = 1;
			unum -= 6;
		}
		d_zoneToGo = nl;
		Vector3D closest = wm.getPlayerByUnum((unsigned) team, (unsigned) unum);
		closest.setZ(0);
		double distObstacle = closest.length();
		if (distObstacle < 0.33)
			return ConfidenceInterval(0.9, 0.1);
	}
*/
	/*int closest = wm.getSortedPlayerPlayerUnum(2);
	 int team = 0;
	 if (closest > 5) {
	 team = 1;
	 closest -= 6;
	 }

	 Vector3D closestPosition = wm.getPlayerByUnum((unsigned) team,
	 (unsigned) closest);
	 double distObstacle = closestPosition.length();

	 double angleR = M_PI / 4;
	 double angleL = 3 * M_PI / 4;

	 double minA = -M_PI / 4;
	 double maxA = 0;
	 double minB = maxA;
	 double maxB = M_PI / 4;
	 double minC = maxB;
	 double maxC = M_PI / 2;
	 double minD = maxC;
	 double maxD = 3 * M_PI / 4;
	 double minE = maxD;
	 double maxE = M_PI;
	 double minF = maxE;
	 double maxF = -3 * M_PI / 4;

	 Vector3D yaxis = Vector3D(0, 1, 0);

	 Vector3D pos = g->getVector("Pos");
	 double distGoal = pos.length();

	 double angleGoal = fabs(yaxis.angle(pos));
	 double angleOpponent = fabs(yaxis.angle(closestPosition));

	 if (distGoal <= 3 * 0.12) {

	 if (angleGoal <= angleR) // && closestPosition.getY() > 0)
	 d_ballZone = nr;
	 else if (angleGoal > angleR && angleGoal <= angleL) // && closestPosition.getX() > 0)
	 d_ballZone = nu;
	 else if (angleGoal > angleL) // && closestPosition.getY() < 0)
	 d_ballZone = nl;

	 } else if (distGoal <= 5 * 0.12 && distGoal > 3 * 0.12) {

	 if (angleGoal <= angleR) // && closestPosition.getY() > 0)
	 d_ballZone = nr;
	 else if (angleGoal > angleR && angleGoal <= angleL) // && closestPosition.getX() > 0)
	 d_ballZone = nu;
	 else if (angleGoal > angleL) // && closestPosition.getY() < 0)
	 d_ballZone = nl;

	 } else if (distGoal > 5 * 0.12) {

	 if (angleGoal <= angleR) // && closestPosition.getY() > 0)
	 d_ballZone = nr;
	 else if (angleGoal > angleR && angleGoal <= angleL) // && closestPosition.getX() > 0)
	 d_ballZone = nu;
	 else if (angleGoal > angleL) // && closestPosition.getY() < 0)
	 d_ballZone = nl;
	 ;

	 }

	 if (distObstacle <= 3 * 0.12) {

	 if (angleOpponent <= angleR) // && closestPosition.getY() > 0)
	 d_zoneToGo = nl;
	 else if (angleOpponent > angleR && angleOpponent <= angleL) // && closestPosition.getX() > 0)
	 d_zoneToGo = back;
	 else if (angleOpponent > angleL) // && closestPosition.getY() < 0)
	 d_zoneToGo = nr;

	 return ConfidenceInterval(0.95, 0.05);

	 } else if (distObstacle <= 5 * 0.12 && distObstacle > 3 * 0.12) {

	 if (angleOpponent <= angleR && (d_ballZone == mr || d_ballZone == fr)) // && closestPosition.getY() > 0)
	 d_zoneToGo = nu;
	 else if (angleOpponent > angleR && angleOpponent <= angleL
	 && (d_ballZone == mu || d_ballZone == fu)) // && closestPosition.getX() > 0)
	 {
	 if (pos.getY() < 0)
	 d_zoneToGo = nl;
	 else
	 d_zoneToGo = nr;
	 } else if (angleOpponent > angleL && (d_ballZone == ml || d_ballZone
	 == fl)) // && closestPosition.getY() < 0)
	 d_zoneToGo = nu;

	 return ConfidenceInterval(0.8, 0.2);
	 }*/

	return ConfidenceInterval(0.0, 0.0);
}

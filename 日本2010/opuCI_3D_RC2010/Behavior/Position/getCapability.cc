#include "position.ih"

Behavior::ConfidenceInterval Position::getCapability(rf<State> s, rf<Goal> g)
{
	WorldModel& wm = WorldModel::getInstance();
	Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
	Vector3D yAxis(0, 1, 0);

	double minAngle = M_PI / 8;

	if ((fabs(yAxis.angle(ballPos)) > minAngle && ballPos.getX() > 0)
			|| ballPos.getX() < 0)
		if (wm.getUnum() == 1)
			return ConfidenceInterval(0.2, 0.1);
		else
			return ConfidenceInterval(0.4, 0.1);

	return ConfidenceInterval(0.05, 0.0);
}

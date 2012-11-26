#include "position.ih"

rf<Behavior::Goal> Position::generateGoal(unsigned step, unsigned slot)
{
	rf<Goal> goal = new Goal();
	rf<OrNode> dis = goal->addDisjunct();
	rf<AndNode> con = dis->addConjunct();

	WorldModel& wm = WorldModel::getInstance();
	Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
	Vector3D xAxis(1, 0, 0);
	double angleToPos = fabs(xAxis.angle(ballPos))* 180.0 / M_PI;

	if(ballPos.getY() < 0)
		angleToPos = -angleToPos;

	con->addVar("Angle", angleToPos, angleToPos);
	wm.addDebugMessage(WorldModel::COMMENT, "(Position)");

	return goal;
}

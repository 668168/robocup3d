#include "returntoposition.ih"

rf<Behavior::Goal> ReturnToPosition::generateGoal(unsigned step, unsigned slot)
{
	rf<Goal> goal = new Goal();
	rf<OrNode> dis = goal->addDisjunct();
	rf<AndNode> con = dis->addConjunct();

	WorldModel& wm = WorldModel::getInstance();
	int unum = wm.getUnum();

	Vector3D fieldSide = wm.getObjectPosition(Types::GOAL1US).getMu()
			- wm.getObjectPosition(Types::GOAL2US).getMu();
	Vector3D fieldSidePerp = -Math::calcPerpend(fieldSide);

	Vector3D target(0, 0, 0);

	if (unum == 4)
		target = (wm.getObjectPosition(Types::GOAL1US).getMu()
				+ wm.getObjectPosition(Types::GOAL2US).getMu()) * 0.5
				+ fieldSidePerp * 5;
	else if (unum == 5)
		target = wm.getObjectPosition(Types::GOAL1US).getMu() + fieldSidePerp
				* 4;
	else if (unum == 6)
		target = wm.getObjectPosition(Types::GOAL2US).getMu() + fieldSidePerp
				* 3.8;

	con->addVar("Pos", target);
	wm.setDebugPoint(target);
	wm.addDebugMessage(WorldModel::COMMENT, "(ReturnToPosition)");

	return goal;
}

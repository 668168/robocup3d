#include "kicktoennemy.ih"

rf<Behavior::Goal> KickToEnnemy::generateGoal(unsigned step, unsigned slot) {
	rf<Goal> goal = new Goal();
	rf<OrNode> dis = goal->addDisjunct();
	rf<AndNode> con = dis->addConjunct();

	WorldModel& wm = WorldModel::getInstance();

	rf<StateVarNode> angleNode = rf_cast<StateVarNode> (d_goal->findDeep(
			"Angle"));
	if (angleNode) {
		StateVar angleVar = angleNode->getVar();
		double angle = angleVar.second.mean();
		con->addVar("Angle", angle, angle);
	}

	Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

	con->addVar("Pos", ballPos);

	return goal;
}

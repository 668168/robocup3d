#include "gotoball.ih"

rf<Behavior::Goal> GoToBall::generateGoal(unsigned step, unsigned slot) {
	rf<Goal> goal = new Goal();
	rf<OrNode> dis = goal->addDisjunct();
	rf<AndNode> con = dis->addConjunct();

	WorldModel& wm = WorldModel::getInstance();

	Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();
	ballPos.setZ(0.0);

	//Vector3D straight(1, 0, 0);

	std::cout << "goal generation " << std::endl;

	Vector3D target = ballPos.normalize() * ballPos.length() * 0.9;

	/*int closest = d_distToPlayer[d_sortDistPlayer[0][0]][0]
			< d_distToPlayer[d_sortDistPlayer[0][1]][1] ? 0 : 1;

	Vector3D pos = wm.getPlayerByUnum((unsigned) closest,
			(unsigned) d_sortDistPlayer[0][closest]);
	pos.setZ(0);

	//TODO check angle's unities
	if (pos.length() < 0.5) {

		double angleToPos = ballPos.angle(pos);
		double angle = fabs(2 * asin(0.2 / pos.length()));

		if (fabs(angleToPos) < angle) {
			angleToPos = angle / M_PI * 180.0;

			//determine if the ball is on the right or on the left of the obstacle
			if (ballPos.getY() < 0) {
				angleToPos = -angleToPos;
			}

			Vector4F newPos = Matrix4D::rotation(Vector3D(0, 0, angleToPos))
					* Vector4F(ballPos.getX(), ballPos.getY(), ballPos.getZ(),
							1);

			target = Vector3D(newPos.getX(), newPos.getY(),newPos.getZ());
		}
	}*/

	con->addVar("Pos", target);
	wm.setDebugPointWithLabel(target, "GoToBall_TGT");

	return goal;
}

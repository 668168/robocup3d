#include "avoidothers.ih"

rf<Behavior::Goal> AvoidOthers::generateGoal(unsigned step, unsigned slot) {
	rf<Goal> goal = new Goal();
	rf<OrNode> dis = goal->addDisjunct();
	rf<AndNode> con = dis->addConjunct();

	Vector3D pos = d_goal->getVector("Pos");
	Vector3D target = pos;

	/*	switch (d_zoneToGo) {
	 case nr:
	 pos = Vector3D(0,0.24,0);
	 break;
	 case nl:
	 pos = Vector3D(0,-0.24,0);
	 break;
	 case nu:
	 pos = Vector3D(0.24,0,0);
	 break;
	 case back:
	 pos = Vector3D(-0.24,0,0);
	 break;
	 default:
	 break;
	 }*/
	if (d_zoneToGo == nu) {
		if (pos.getY() > 0)
			target = Vector3D(-0.05, 0.3, 0);
		else
			target = Vector3D(-0.05, -0.3, 0);
	}

	else if (d_zoneToGo == nr) {
		if (pos.getX() > 0)
			target = Vector3D(0.3, -0.05, 0);
		else
			target = Vector3D(-0.3, -0.05, 0);
	}
	

	else if (d_zoneToGo == nl) {
		if (pos.getX() > 0)
			target = Vector3D(0.3, 0.05, 0);
		else
			target = Vector3D(-0.3, 0.05, 0);
	}

	con->addVar("Pos", pos);

	return goal;
}

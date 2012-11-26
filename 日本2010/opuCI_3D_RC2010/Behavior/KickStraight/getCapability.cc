#include "kickstraight.ih"

Behavior::ConfidenceInterval KickStraight::getCapability(rf<State> s,
		rf<Goal> g) {

	/*if (!g->getVector("Pos")) {
		std::cout << "kickstraight::getCapability no goal define, abort"
				<< std::endl;
	}*/

	Vector3D pos = g->getVector("Pos");

	WorldModel& wm = WorldModel::getInstance();

	Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

	std::cout << "kickstraight::getCapability ballPos : ";
	std::cout << ballPos.getX() << " ";
	std::cout << ballPos.getY() << " ";
	std::cout << ballPos.getZ() << " ";
	std::cout << ";" << std::endl;

	std::cout << "kickstraight::getCapability pos : ";
	std::cout << pos.getX() << " ";
	std::cout << pos.getY() << " ";
	std::cout << pos.getZ() << " ";
	std::cout << ";" << std::endl;

	if ((pos - ballPos).length() < 1.0 && wm.allObjectPosAvailable())
		return ConfidenceInterval(0.75, 0.2);

	return ConfidenceInterval(0.0, 0.2);
}

#include "walkto.ih"

Behavior::ConfidenceInterval WalkTo::getCapability(rf<Behavior::State> s, rf<
		Behavior::Goal> g) {

	WorldModel& wm = WorldModel::getInstance();

	wm.setNeckDirUpdate(true);

	return ConfidenceInterval(0.7, 0.0);
}

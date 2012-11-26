#include "walkandturn.ih"

Behavior::ConfidenceInterval WalkAndTurn::getCapability(rf<State> s, rf<Goal> g)
{
	WorldModel& wm = WorldModel::getInstance();

	wm.setNeckDirUpdate(true);

  return ConfidenceInterval(0.7, 0.0);
}

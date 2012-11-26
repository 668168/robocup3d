#include "freeze.ih"

Behavior::ConfidenceInterval Freeze::getCapability(rf<State> s, rf<Goal> g) {
	WorldModel& wm = WorldModel::getInstance();
	if (wm.shouldFreeze()) {
		if (!d_startCounting) {
			d_startCounting = true;
			d_freezingTime = wm.getTime();
		}
		//	std::cout << wm.getTime() << "\033[34m *********!!FREEZE!!********* \033[0m" << std::endl;
		return ConfidenceInterval(0.99, 0.2);
	}
	
	if(wm.getPlayerDistToPlayer(wm.getSortedPlayerPlayerUnum(2)) < 0.16)
		return ConfidenceInterval(0.6, 0.2);
	
	d_startCounting = false;
	return ConfidenceInterval(0.0, 0.0);
}

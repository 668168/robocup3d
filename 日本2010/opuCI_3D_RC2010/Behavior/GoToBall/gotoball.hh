#ifndef _BATS_GOTOBALL_HH_
#define _BATS_GOTOBALL_HH_

#include "behavior.hh"
#include "math.hh"

namespace bats {
class GoToBall: public Behavior {

	//int d_sortDistPlayer[6][2];
	//float d_distToPlayer[12][2];

	virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
	virtual rf<State> getCurrentState();
	virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);

public:
	GoToBall(std::string const &id, std::string const &playerClass);
	//virtual void update();
};
}
;

#endif

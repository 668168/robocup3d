#ifndef _BATS_WAITANDSEE_HH_
#define _BATS_WAITANDSEE_HH_

#include "behavior.hh"

namespace bats {
class WaitAndSee: public Behavior {

	//to know since when the player doesn't move
	//double d_immobilityTime;

	virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
	virtual rf<State> getCurrentState();
	virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);

public:
	WaitAndSee(std::string const &id, std::string const &playerClass);
};
}
;

#endif

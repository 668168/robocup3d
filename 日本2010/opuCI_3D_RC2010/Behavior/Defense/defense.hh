#ifndef _BATS_DEFENSE_HH_
#define _BATS_DEFENSE_HH_

#include "behavior.hh"
#include "math.hh"

namespace bats {
class Defense: public Behavior {

  double d_minTime;
  bool d_minTimeUpdate;

	virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
  virtual rf<State> getCurrentState();
  virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);

public:
  Defense(std::string const &id, std::string const &playerClass);
  virtual void update();
};
}
;

#endif

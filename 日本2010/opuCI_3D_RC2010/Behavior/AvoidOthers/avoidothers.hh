#ifndef _BATS_AVOIDOTHERS_HH_
#define _BATS_AVOIDOTHERS_HH_

#include "behavior.hh"

namespace bats
{
  class AvoidOthers : public Behavior
  {
    enum zone { nl,nu,nr,ml,mu,mr,fl,fu,fr,back,nozone};
	zone d_zoneToGo;
	zone d_ballZone;
	/*std::vector<Vector3D> d_zoneN;
	std::vector<Vector3D> d_zoneM;
	std::vector<Vector3D> d_zoneF;*/

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    AvoidOthers(std::string const &id, std::string const &playerClass);
  };
};

#endif

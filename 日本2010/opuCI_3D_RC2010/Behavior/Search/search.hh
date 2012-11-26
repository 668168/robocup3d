#ifndef _BATS_SEARCH_HH_
#define _BATS_SEARCH_HH_

#include "behavior.hh"

namespace bats
{
  class Search : public Behavior
  {
    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);

    double d_searchStartTime;
    double d_timeoutStart;
    bool d_timeout;

    // remember good angle
    double d_goodNeckAngle;
    double d_goodHeadAngle;
  
  public:
    Search(std::string const &id, std::string const &playerClass);

    void moveCamera(std::vector<Types::Object> target);
    void moveCamera(Types::Object target);
    void moveCameraToBall(std::vector<Types::Object> target);

    // override
    virtual void update();
  };
};

#endif

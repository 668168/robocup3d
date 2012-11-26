#ifndef _BATS_SCRIPTPLAYER_HH_
#define _BATS_SCRIPTPLAYER_HH_

#include "behavior.hh"

#include <vector>
#include <utility>

namespace bats
{
  class ScriptPlayer : public Behavior
  {
    std::vector< std::vector <std::pair<double, std::pair<double, double> > > > d_script;
    double d_waitUntil;
    double d_lastStepTime;

    unsigned d_curLine;
    double d_lastChecked;

    double d_maxSpeed;
    double d_gain;

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState() { return 0; }
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g) {
      return ConfidenceInterval(0.7, 0.0);
    }

  public:
    ScriptPlayer(std::string const &id, std::string const &playerClass);

    virtual void reset();
    virtual void update();
  };
};

#endif

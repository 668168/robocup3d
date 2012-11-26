#ifndef _BATS_SINE_HH_
#define _BATS_SINE_HH_

#include "behavior.hh"

namespace bats
{
  class Sine : public Behavior
  {
  public:
    struct Params
    {
      double amplitude;
      double period;
      double phase;
      double offset;
    };

  private:
    std::vector<std::vector<Params> > d_params;

    double d_startupTime;
    double d_shutdownTime;

    double d_startTime;

    double d_factor;
    double d_lastTime;

    double d_gain;

    double calcAngle(std::vector<Params>& params, double startTime);
    double calcSinusoidAngle(std::vector<Params>& params, double startTime);
    double calcOffsetAngle(std::vector<Params>& params);

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState() { return 0; }
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g) {
      return ConfidenceInterval(0.3, 0.1); }

    static std::string s_lastSineID;
    static std::vector<std::vector<Params> > s_lastParams;

    /// Last time at which the previous Sine behavior ran. Saved for transition purposes
/*    static double s_lastTime;
    static double s_lastStartTime;
    static double s_lastStopTime;*/

    /// Last time any Sine behavior ran. Used to determine if there was a Sine at all
    static double s_lastSineTime;

    static double s_transitionTime;

    static std::vector<rf<Sine> > s_sines;
    static double s_lastUpdate;

  public:
    Sine(std::string const &id, std::string const &playerClass);

    void updateFactor(double dTime, bool startup = false);
    double getFactor() { return d_factor; }

    std::vector<std::vector<Params> > getParams() { return d_params; }

    double getStartTime() { return d_startTime; }

    void reset();
    void update();
  };
};

#endif

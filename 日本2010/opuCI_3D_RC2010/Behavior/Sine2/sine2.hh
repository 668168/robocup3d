#ifndef _BATS_SINE2_HH_
#define _BATS_SINE2_HH_

#include "behavior.hh"

namespace bats
{
  class Sine2 : public Behavior
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
    std::vector<std::vector<Params> > d_fixedParams;

    // d_weights[i] for d_variableParams[i]
    std::vector<double> d_weights;
    std::vector<std::vector<std::vector<Params> > > d_variableParams;

    double d_startupTime;
    double d_shutdownTime;

    double d_startTime;

    double d_factor;
    double d_lastTime;

    double d_gain;

    double calcAngle(std::vector<Params>& params, double startTime=0);
    double calcSinusoidAngle(std::vector<Params>& params, double startTime);
    double calcOffsetAngle(std::vector<Params>& params);

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState() { return 0; }
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
    static std::string s_lastSine2ID;
    static std::vector<std::vector<Params> > s_lastParams;

    /// Last time at which the previous Sine2 behavior ran. Saved for transition purposes
/*    static double s_lastTime;
    static double s_lastStartTime;
    static double s_lastStopTime;*/

    /// Last time any Sine2 behavior ran. Used to determine if there was a Sine2 at all
    static double s_lastSine2Time;

    static double s_transitionTime;

    static std::vector<rf<Sine2> > s_sines;
    static double s_lastUpdate;


    // for debug
    void printParams(Params p){
      std::cout << p.amplitude << ", " << p.period << ", " << p.phase << ", " << p.offset << std::endl;
    }

  public:
    Sine2(std::string const &id, std::string const &playerClass);

    void updateFactor(double dTime, bool startup = false);
    double getFactor() { return d_factor; }
    void resetFactor() { d_factor = 0; }

    std::vector<std::vector<Params> > getFixedParams() { return d_fixedParams; }
    std::vector<std::vector<Params> > getVariableParams(unsigned n) {
      if( n >= d_variableParams.size())
        std::cout << "ERROR!!!!!!" << std::endl;
//      std::cout << "return at(" << n << ")" << std::endl;
//      std::cout << " size ... " << d_variableParams.size() << std::endl;
      return d_variableParams[n];
    }

    int getVariableParamsSize(){
      return d_variableParams.size();
    }

    double getWeight(unsigned n){
      if( n >= d_weights.size() )
        std::cout << "ERROR!!!!!!!!!!!! weight" << std::endl;

      return d_weights.at(n);
    }
    
    double getStartTime() { return d_startTime; }
    
    void reset();
    void update();

  };
};

#endif

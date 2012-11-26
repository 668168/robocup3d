#ifndef _BATS_SCORE_HH_
#define _BATS_SCORE_HH_

#include "behavior.hh"

namespace bats
{

  /**
   *  Behavior: Tries to score
   *
   *  Compatible subbehaviors:
   *  -# index 0-0: WalkTo (Gets a Pos goal).
   *  -# index 1-0: KickTo (Just kicks the ball towards the goal).
   */
  class Score : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    
    /** Get Capability
     *
     *  @param s Expected state variable: None
     *  @param g Expected goal variable: None
     *  @returns confidence (0.5, 0.2) when standing, otherwise (0.0, 0.0).
     */
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);

    int targetOpp;
    bool once;


  public:

    Score(std::string const &id, std::string const &playerClass);

  };

};
#endif

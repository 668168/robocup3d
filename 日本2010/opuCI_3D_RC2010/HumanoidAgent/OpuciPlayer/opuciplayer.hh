
#ifndef _BATS_HUMANOIDBAT_HH_
#define _BATS_HUMANOIDBAT_HH_

#include "humanoidagent.hh"
#include "fitnessfunction.hh"

namespace bats
{

  /**
   *  Our Very Own Agent
   */
  class OpuciPlayer : public HumanoidAgent
  {
    std::string d_confFile;
    rf<FitnessFunction> d_fitness;

    virtual void init();
    virtual void think();

  public:

    /**
     *  The Constructor
     *
     *  @param teamName the name of our team.
     *  @param confFile the configuration file to use.
     *  @param host the host that runs the soccer server.
     *  @param port the port on which the socker server runs.
     *  @param unum the unum of this agent.
     */
    OpuciPlayer(std::string teamName, std::string confFile, std::string const host = "localhost", unsigned port = 3100, unsigned unum = 0)
      : HumanoidAgent(teamName, host, port, unum),
        d_confFile(confFile),
        d_fitness(new FitnessFunction)
    {
    }

    void setFitness(rf<FitnessFunction> ff) { d_fitness = ff; }
  };
};

#endif

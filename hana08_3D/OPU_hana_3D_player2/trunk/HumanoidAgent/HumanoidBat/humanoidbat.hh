/*
 *  Little Green BATS (2007), AI department, University of Groningen
 *
 *  Authors: 	Martin Klomp (martin@ai.rug.nl)
 *		Mart van de Sanden (vdsanden@ai.rug.nl)
 *		Sander van Dijk (sgdijk@ai.rug.nl)
 *		A. Bram Neijt (bneijt@gmail.com)
 *		Matthijs Platje (mplatje@gmail.com)
 *
 *	All students of AI at the University of Groningen
 *  at the time of writing. See: http://www.ai.rug.nl/
 *
 *  Date: 	July 27, 2007
 *
 *  Website:	http://www.littlegreenbats.nl
 *
 *  Comment:	Please feel free to contact us if you have any 
 *		problems or questions about the code.
 *
 *
 *  License: 	This program is free software; you can redistribute 
 *		it and/or modify it under the terms of the GNU General
 *		Public License as published by the Free Software 
 *		Foundation; either version 3 of the License, or (at 
 *		your option) any later version.
 *
 *   		This program is distributed in the hope that it will
 *		be useful, but WITHOUT ANY WARRANTY; without even the
 *		implied warranty of MERCHANTABILITY or FITNESS FOR A
 *		PARTICULAR PURPOSE.  See the GNU General Public
 *		License for more details.
 *
 *   		You should have received a copy of the GNU General
 *		Public License along with this program; if not, write
 *		to the Free Software Foundation, Inc., 59 Temple Place - 
 *		Suite 330, Boston, MA  02111-1307, USA.
 *
 */




#ifndef _BATS_HUMANOIDBAT_HH_
#define _BATS_HUMANOIDBAT_HH_

#include "humanoidagent.hh"
#include "fitnessfunction.hh"

namespace bats
{

  /**
   *  Our Very Own Agent
   */
  class HumanoidBat : public HumanoidAgent
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
    HumanoidBat(std::string teamName, std::string confFile, std::string const host = "localhost", unsigned port = 3100, unsigned unum = 0, double exitTime = 20.0)
      : HumanoidAgent(teamName, host, port, unum, exitTime),
        d_confFile(confFile), d_fitness(new FitnessFunction)
    {
    }

    void setFitness(rf<FitnessFunction> ff) { d_fitness = ff; }
  };
};

#endif

/*
 *  Little Green BATS (2008), AI department, University of Groningen
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
 *  Date: 	November 1, 2008
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

#define USE_STACK

#ifndef _BATS_HUMANOIDAGENT_HH_
#define _BATS_HUMANOIDAGENT_HH_

#include "../SocketComm/AgentSocketComm/agentsocketcomm.hh"
#include "../WorldModel/worldmodel.hh"
#include "../Cochlea/cochlea.hh"

namespace bats
{
  /** Humanoid agent base class
   *
   * This class forms the base of your humanoid 3D soccer simulation agent. All you need to do to create a working agent is derive from this class. For instance:
   * \code
   * class MyAgent : public bats::HumanoidAgent
   * {
   *   public:
   *     MyAgent(std::string teamName) : bats::HumanoidAgent(teamName) {}
   * };
   * \endcode
   * To start your agent, simply create an object of your agent class and call its run method:
   * \code
   * int main()
   * {
   *   MyAgent agent("MyTeam");
   *   agent.run();
   * }
   * \endcode
   * The HumanoidAgent class handles all the communication with the server and parsing of input by using SocketComm and WorldModel. You can implement the behavior for your agent by overloading the think method. If your agent needs initialization code that should be run once at start up, overload the init method.
   */
  class HumanoidAgent
  {
  protected:
    std::string d_confFile;
    std::string d_teamName;
    unsigned d_unum;

		/// Kill agent next cycle
    bool d_die;
    
    /** Startup agent
     *
     * Performs the communication with the server necesary to start up the agent
     */
    void startUp();
    
    /** Initialize agent
     *
     * This method is run when the agent is started up. At this point the uniform number and all object properties are known
     */
    virtual void init() {}
    
    /** Perform think cycle
     */
    virtual void think() {}
    
  public:
    HumanoidAgent(std::string teamName, std::string confFile = "", std::string const host = "localhost", unsigned port = 3100, unsigned unum = 0)
      : d_confFile(confFile), d_teamName(teamName), d_unum(unum), d_die(false)
    {
      SAgentSocketComm::getInstance().initSocket(host, port);
      SWorldModel::getInstance().setTeamName(teamName);
      SCochlea::getInstance().setTeamName(teamName);
    }
    
    virtual ~HumanoidAgent() {}
    
    /** Run the agent
     *
     * Start an infinite loop that updates the communication with the server and the WorldModel and calls think() at every step.
     */
    void run();
    
    
  };
};

#endif

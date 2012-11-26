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

#ifndef _HELLOWORLDAGENT_HH_
#define _HELLOWORLDAGENT_HH_

#include "HumanoidAgent/humanoidagent.hh"

/**
  *  A friendly robot
  */
class HelloWorldAgent : public bats::HumanoidAgent
{
  /**
    * Initialize agent
    *
    * Called a single time when starting up the agent. Put all your initialization stuff here.
    */
  virtual void init();
  
  /**
    * Think cycle
    *
    * Called at each cycle after a message from the server is received and parsed. Put all your thinking and acting stuff here.
    */
  virtual void think();
  
public:

  /**
    *  The Constructor
    *
    *  Sets this agent's teamname to "Hello". Consider putting initialization stuff in init() instead of here.
    */
  HelloWorldAgent()
    : HumanoidAgent(std::string("Hello"))
  {
  }

};

#endif

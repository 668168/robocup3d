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
    		
    double calcAngle(std::vector<Params>& params, double startTime);
    
    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState() { return 0; }
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g) { return ConfidenceInterval(0.4, 0.0); }

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

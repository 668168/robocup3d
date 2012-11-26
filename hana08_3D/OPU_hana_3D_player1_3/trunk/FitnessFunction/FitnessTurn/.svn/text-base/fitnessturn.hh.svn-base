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


#ifndef __INC_BATS_FITNESSTURN_HH__
#define __INC_BATS_FITNESSTURN_HH__

#include "worldmodel.hh"
#include "fitnessfunction.hh"

namespace bats {

  /**
   *  A fitness function used to learn to turn
   *
   *  This hasn't produced any workable results yet.
   */
  class FitnessTurn : public FitnessFunction {

    float d_turn;

    float d_prev;

    FitnessTurn(FitnessTurn const &other); // NI
    FitnessTurn &operator=(FitnessTurn const &other); // NI

  public:

    FitnessTurn()
      : d_turn(0.0)
    {
    }

    virtual ~FitnessTurn() {}

    virtual void init()
    {
      d_prev = WorldModel::getInstance().get(WorldModel::iVisionFlag1L)[1];
    }

    virtual void update()
    {
      float angle = WorldModel::getInstance().get(WorldModel::iVisionFlag1L)[1];
      d_turn += angle - d_prev;
      d_prev = angle;
    }

    virtual void print() const
    {
      std::cout << d_turn << std::endl;
    }


  };

};

#endif // __INC_BATS_FITNESSTURN_HH__

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

#ifndef __INC_BATS_FITNESSFUNCTION_HH__
#define __INC_BATS_FITNESSFUNCTION_HH__

#include "refable.hh"
#include "socketcomm.hh"

namespace bats {

  /**
   *  Classes derived from this are used to implement certain fitness functions
   *  which can output information that can be used by learning algorithms like
   *  the genetic algorithm used by us to learn to walk.
   */
  class FitnessFunction : public RefAble {

    FitnessFunction(FitnessFunction const &other); // NI
    FitnessFunction &operator=(FitnessFunction const &other); // NI

  public:

    FitnessFunction() {}

    virtual ~FitnessFunction() {}

    virtual void init()
    {
    }

    virtual void initCommand(SocketComm &comm)
    {
    }

    virtual void update()
    {
    }

    virtual void print() const
    {
    }


  };

};

#endif // __INC_BATS_FITNESSFUNCTION_HH__

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

#ifndef _BATS_DISTRIBUTION1_HH_
#define _BATS_DISTRIBUTION1_HH_

namespace bats
{
  /// Base template for 1-dimensional distribution functions
  template <typename T>
  class Distribution1
  {
    public:
      Distribution1() {}
      
      virtual ~Distribution1() {}
      
      /** Initialize the distribution with a normal distribution
       *
       * @param mu The distibution's mean
       * @param sigma The distribution's standard deviation
       */
      virtual void init(T mu, T sigma) = 0;
      
      /// Get the distribution's mean
      virtual T getMu() const = 0;
      
      /// Get the distribution's standard deviation
      virtual T getSigma() const = 0;
      
  };
}
#endif


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








#ifndef __INC_BATS_REFABLE_HH_
#define __INC_BATS_REFABLE_HH_

namespace bats {


  /**
   *  RefAble is a necessary baseclass for all objects
   *  that can be referenced using the rf<> system.
   */
  class RefAble {

    // This can be mutable, because it doesn't change
    // the meaning of the object when its value changes.
    mutable unsigned d_refCount;

    RefAble(RefAble const &); // NI
    RefAble operator=(RefAble const &); // NI

  public:

    RefAble() : d_refCount(0) {}

    /**
     *  This increments the reference count.
     */
    inline void grab() const
    {
      // The lock operand ensures that the memory is
      // only accessed by one thread at the same time.
      /* This is not portable..
      asm volatile (
	   "lock incl %0\n\t"
	   : "=m" (d_refCount)
	     //	   : "m" (x)
	     //		  : "memory"
	   );
      */
      ++d_refCount;
    }

    /**
     *  This decrements the reference count.
     *
     *  @returns true when the reference count is zero.
     */
    inline bool release() const
    {
      bool res = false;

      // The lock operand ensures that the memory is
      // only accessed by one thread at the same time.

      // We don't need a lock like thing with setz, because it
      // uses the result flags of decl! Isn't that cool?
      // I think we need to do it like this because of the above
      // reason. Otherwise we might return d_refCount.

      /* This is not portable...
      asm volatile (
	   "lock decl %0\n\t"
	   "setz %1\n\t"
	   : "=m" (d_refCount),
	     "=m" (res)
	     //	   : "m" (x)
	     //		  : "memory"
	   );
      */

      res = !--d_refCount;

      return res;
    }


  };


};

#endif // __INC_BATS_REFABLE_HH_

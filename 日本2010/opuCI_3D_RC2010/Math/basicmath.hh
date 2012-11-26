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









/*
 *  I don't particulary like the name of the class, it should be in math
 *  but math uses vector3 and vector3 should use this...
 *
 */

#ifndef __INC_BATS_BASICMATH_HH_
#define __INC_BATS_BASICMATH_HH_

#include "config.hh"

#include <cmath>

namespace bats
{

  /**
   *  BasicMath has a few helpfull mathematical functions
   *
   *  \todo we should check if sse is supported before compiling!
   */
  class BasicMath
  {
  public:

    /**
     *  Calculates the square root of x, using a faster SSE routine when
     *  available.
     */
    inline static float sqrt(float x)
    {

#if BATS_USE_SSE_SQRT

      // This is faster than the fpu sqrt, atleast on a core duo (about 2.5 times)!

      // Note: should be posible to use "x" ipv "m" in the output
      //       operant, this should make it posible to use this
      //       method inside other simd code and also optimize
      //       by iliminating intermediate register tot memory moves!

      asm (
	   "sqrtss %1, %%xmm1\n\t"
	   "movss %%xmm1, %0\n\t"
	   : "=m" (x)
	   : "m" (x)
	     //		  : "memory"
	   );

      return x;

#else

      return std::sqrt(x);

#endif

    }

    /**
     *  Uses a faster way to calculate the inverse square root (1.0/sqrt(x)). This
     *  is about 3.5 times faster than 1.0/sqrt(x) and when SSE is used, it is atleast
     *  10 times faster than that!
     */
    inline static float invSqrt(float x)
    {

#if BATS_USE_FAST_INVERSE_SQRT

      // This is roughly 3.5 times faster than the 1.0/sqrt(x)!
      // Reference: article FAST INVERSE SQUARE ROOT by Chris Lomont

      float xhalf = 0.5f*x;
      int i = *(int*)&x;       // get bits for floating value
      i = 0x5f3759df - (i>>1); // gives initial guess y0
      x = *(float*)&i;         // convert bits back to float
      x = x*(1.5f-xhalf*x*x);  // Newton step, repeating increases accuracy
      return x;

#elif BATS_USE_SSE_INVERSE_SQRT

      // This is extremely fast, atleast on a core duo!

      // Note: should be posible to use "x" ipv "m" in the output
      //       operant, this should make it posible to use this
      //       method inside other simd code and also optimize
      //       by iliminating intermediate register tot memory moves!

      asm (
       "rsqrtss %1, %%xmm1\n\t"
       "movss %%xmm1, %0\n\t"
       : "=m" (x)
       : "m" (x)
	 //		  : "memory"
       );

  return x;

#else

      return 1.0/sqrt(x);

#endif

    }



  };

};

#endif // __INC_BATS_BASICMATH_HH_

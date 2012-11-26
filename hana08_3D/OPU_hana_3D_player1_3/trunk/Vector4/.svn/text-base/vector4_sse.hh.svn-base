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











#ifndef __INC_BATS_VECTOR4_SSE_HH_
#define __INC_BATS_VECTOR4_SSE_HH_

#include <cstring>
#include <cassert>
#include <ostream>
#include <cmath>

#include "vector3.hh"

#define _MM_SHUFFLE(z, y, x, w) ((z << 6) | (y << 4) | (x << 2) | w)

namespace bats {

  template <class T>
  class Matrix9;

  /** \brief 4 element vector
   *
   * The Vector4F class.
   */
  class Vector4F
  {
    friend std::ostream &operator<<(std::ostream &, Vector4F const &);

    friend class Matrix4D;

    union {
      float __attribute__ ((__vector_size__ (16))) d_v4sf;
      float d_values[4];
    };

    void copy(Vector4F const &other)
    {
      //      memcpy(reinterpret_cast<char*>(d_values),
      //	     reinterpret_cast<char const*>(other.d_values),sizeof(float)*4);
      //      d_v4sf = other.d_v4sf;
      // Not sure if this is faster than a memcopy..
      asm (
	   "movaps %1, %%xmm0\n\t"
	   "movaps %%xmm0, %0\n\t"
	   : "=m" (d_v4sf)
	   : "m" (other.d_v4sf)
	   );
    }

    inline Vector4F(float values[])
    {
      // 
      asm (
	   "movaps %1, %%xmm0\n\t"
	   "movaps %%xmm0, %0\n\t"
	   : "=m" (d_v4sf)
	   : "m" (values)
	     //	   : "%xmm1"
	   );
    }

    //    Vector4F(__m128 values) : d_values(values) {}

    void destroy()
    {
    }

    
  public:

    inline Vector4F(Vector4F const &other) { copy(other); }

    inline Vector4F()
    {
      //      asm (
      //	   "pxor %1, %1\t\n"
      //	   : "=x" (d_v4sf)
      //	   : "0" (d_v4sf)
      //	   );
      d_values[0] = d_values[1] = d_values[2] = d_values[3] = 0;
    }

    inline Vector4F(float x, float y, float z, float w = 1.0)
    {
      d_values[0] = x;
      d_values[1] = y;
      d_values[2] = z;
      d_values[3] = w;
    }

    inline Vector4F(Vector3<float> const &other)
    {
      copy(other);
    }

    ~Vector4F() { destroy(); }

    inline float const *ptr() const { return d_values; }   

    inline operator float const * () const { return d_values; }

    inline operator Vector3<float> const () const
    {
      return Vector3<float>(d_values[0],d_values[1],d_values[2]);
    }

    inline Vector4F &operator=(Vector4F const &other)
    {
      if (this != &other) {
        destroy();
        copy(other);
      }
      return *this;
    }

    /** Set member \a idx to \a value */
    inline void set(unsigned idx, float value)
    {
      assert(idx<4);
      d_values[idx] = value;
    }
    
    /** Set X-coordinate to \a value */
    inline void setX(float value)
    {
      d_values[0] = value;
    }

    /** Set Y-coordinate to \a value */
    inline void setY(float value)
    {
      d_values[1] = value;
    }

    /** Set Z-coordinate to \a value */
    inline void setZ(float value)
    {
      d_values[2] = value;
    }

    /** Set W-coordinate to \a value */
    inline void setW(float value)
    {
      d_values[3] = value;
    }
    
    /** Get member \a idx */
    inline float get(unsigned idx) const
    {
      assert(idx < 4);

      return d_values[idx];
    }

    /** Get X-coordinate */
    inline float getX() const
    {
      return d_values[0];
    }

    /** Get Y-coordinate */
    inline float getY() const
    {
      return d_values[1];
    }

    /** Get Z-coordinate */
    inline float getZ() const
    {
      return d_values[2];
    }

    /** Get W-coordinate */
    inline float getW() const
    {
      return d_values[3];
    }

    /** Calculate vector length
     *
     * \f$ |\vec V| = \sqrt{X^2 + Y^2 + Z^2} \f$
     */
    inline float length() const
    {

      float res;

      asm (
	   //	   "movaps %2, %%xmm0\n\t"
	   "mulps %1, %1\n\t"
 	   "movaps %1, %%xmm0\n\t"
	   "shufps $0x1b, %1, %%xmm0\n\t"
	   "addps %1, %%xmm0\n\t"
	   "movhlps %%xmm0, %1\n\t"
 	   "addss %1, %%xmm0\n\t"
	   "sqrtss %%xmm0, %0\n\t"
	   : "=x" (res)
	   : "x" (d_v4sf)
	   : "%xmm0"
	   );

      return res;

      /*      
      return BasicMath::sqrt(d_values[0]*d_values[0] +
			     d_values[1]*d_values[1] + 
			     d_values[2]*d_values[2] +
			     d_values[3]*d_values[3]);
      */
    }

    inline Vector4F normalize() const
    {
      Vector4F res;

      asm (
	   "movaps %1, %%xmm1\n\t"
	   "mulps %%xmm1, %%xmm1\n\t"
 	   "movaps %%xmm1, %%xmm0\n\t"
	   "shufps $0x1b, %%xmm0, %%xmm0\n\t"
	   "addps %%xmm0, %%xmm1\n\t"
	   "movaps %%xmm1, %%xmm0\n\t"
	   "shufps $0x4e, %%xmm0, %%xmm0\n\t"
 	   "addps %%xmm0, %%xmm1\n\t"
	   "rsqrtps %%xmm1, %%xmm1\n\t"
	   "mulps %1, %%xmm1\n\t"
	   "movaps %%xmm1, %0\n\t"
	   : "=xm" (res.d_v4sf)
	   : "xm" (d_v4sf)
	   : "%xmm0", "%xmm1"
	   );

      return res;
    }

    /** Calculate the cross product of this vector with another vector
     *
     * \f$ \vec c = \vec a \times \vec b \f$ <BR>
     * \f$ c_0 = a_1 \cdot b_2 - a_2 \cdot a_1 \f$ <BR>
     * \f$ c_1 = a_2 \cdot b_0 - a_0 \cdot a_2 \f$ <BR>
     * \f$ c_2 = a_3 \cdot b_1 - a_1 \cdot a_0 \f$ 
     */
    /* NOT YET IMPLEMENTED!
    Vector4F crossProduct(Vector4F const &other) const
    {
      float res[3] =
      {
        (d_values[1]*other.d_values[2] - d_values[2]*other.d_values[1]),
        (d_values[2]*other.d_values[0] - d_values[0]*other.d_values[2]),
        (d_values[0]*other.d_values[1] - d_values[1]*other.d_values[0])
      };

      return res;
    }
    */

    /** Calculate the dot product of this vector with another vector
     *
     * \f$ \vec c = \vec a \cdot \vec b \f$ <BR>
     * \f$ c_i = a_i \cdot b_i \f$
     */
    inline float dotProduct(Vector4F const &other) const
    {
      float res;

      asm (
	   //	   "movaps %2, %%xmm0\n\t"
	   "mulps %1, %2\n\t"
 	   "movaps %2, %%xmm0\n\t"
	   "shufps $0x1b, %2, %%xmm0\n\t"
	   "addps %2, %%xmm0\n\t"
	   "movhlps %%xmm0, %0\n\t"
 	   "addss %%xmm0, %0\n\t"
	   : "=x" (res)
	   : "mx" (d_v4sf), "x" (other.d_v4sf)
	   : "%xmm0"
	   );

      return res;
    }

    /**
     *  Performs a dot-product.
     */
    inline float operator*(Vector4F const &other) const
    {
      return dotProduct(other);
    }
    
    /** Add another vector to this vector*/
    inline Vector4F operator+(Vector4F const &other) const
    {
      Vector4F res = *this;
      return res += other;
    }

    /** Subtract another vector from this vector */
    inline Vector4F operator-(Vector4F const &other) const
    {
      Vector4F res = *this;
      return res -= other;
    }

    /** Divide this vector by an other vector */
    inline Vector4F operator/(Vector4F const &other) const
    {
      Vector4F res = *this;
      return res /= other;
    }

    /** Multiply this vector with a scalar value */
    inline Vector4F operator*(float value) const
    {
      Vector4F res = *this;
      return res *= value;
    }

    /** Divide this vector by a scalar value */
    inline Vector4F operator/(float value) const
    {
      Vector4F res = *this;
      return res /= value;
    }

    inline Vector4F &operator+=(Vector4F const &other)
    {
      d_v4sf += other.d_v4sf;
      return *this;
    }

    inline Vector4F &operator-=(Vector4F const &other)
    {
      d_v4sf -= other.d_v4sf;
      return *this;
    }

    inline Vector4F &operator/=(Vector4F const &other)
    {
      d_v4sf /= other.d_v4sf;
      return *this;
    }

    inline Vector4F &operator*=(Vector4F const &other)
    {
      d_v4sf *= other.d_v4sf;
      return *this;
    }

    /** Divide this vector by a scalar value */
    inline Vector4F &operator/=(float value)
    {
      return (*this) /= Vector4F(value,value,value,value);;
    }

    /** Divide this vector by a scalar value */
    inline Vector4F &operator*=(float value)
    {
      return (*this) *= Vector4F(value,value,value,value);
    }

    /** Compare this vector to another vector */
    inline bool operator==(Vector4F const &other) const
    {
      unsigned res;

      asm (
	   "cmpeqps %1, %2\n\t"
	   "movmskps %2, %0\n\t"
	   : "=r" (res)
	   : "x" (d_v4sf), "x" (other.d_v4sf)
	   );

      return res == 0xf;
    }
    
    /** Calculate angle between this vector and another vector
     *
     * \f$ cos(\alpha) = {{\vec a \cdot \vec b} \over {| \vec a | | \vec b | }}\f$ <BR>
     *
     *
     * \todo Should expect normalized vector?
     *
     */
    inline double angle(Vector4F &other) const
    {
      double dp = dotProduct(other);
      return acos(dp / (length() * other.length()));
    }
    
    inline bool isNormal()
    {
      return
        std::isnormal(d_values[0]) &&
        std::isnormal(d_values[1]) &&
        std::isnormal(d_values[2]) &&
        std::isnormal(d_values[3]);
    }
  };


  std::ostream &operator<<(std::ostream &_os, Vector4F const &_vect);
  //  {
  //    return _os << "(" << _vect.d_values[0] << "," << _vect.d_values[1] << "," << _vect.d_values[2] << "," << _vect.d_values[3] << ")";
  //  }

};

#endif // __INC_BATS_VECTOR4_SSE_HH_

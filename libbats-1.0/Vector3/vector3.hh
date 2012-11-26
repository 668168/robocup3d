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

#ifndef __INC_BATS_VECTOR3_HH_
#define __INC_BATS_VECTOR3_HH_

#include <cstring>
#include <cassert>
#include <ostream>
#include <cmath>

#include "../Math/basicmath.hh"

namespace bats {

  template <class T>
  class Matrix9;

  /** \brief 3 element vector
   *
   *  The Vector3 class is a three dimensional vector class (3 values).
   */
  template <class T>
  class Vector3
  {
    template <class K> friend std::ostream &operator<<(std::ostream &, Vector3<K> const &);

    friend class Matrix9<T>;

    T d_values[3];

    void destroy()
    {
    }

    inline void copy(Vector3<T> const &other)
    {
      memcpy(reinterpret_cast<char*>(d_values),
	     reinterpret_cast<char const *>(other.d_values),
	     sizeof(T)*3);
    }

    inline Vector3(double values[])
    {
      memcpy(reinterpret_cast<char*>(d_values),
	     reinterpret_cast<char const *>(values),
	     sizeof(T)*3);
    }
    
  public:

    /** Copy constructor
     *
     * Copies values from \a other
     */
    inline Vector3(Vector3<T> const &other) { copy(other); }

    /** Default constructor
     *
     *  Initializes all values to zero.
     */
    inline Vector3()
    {
      d_values[0] = 0;
      d_values[1] = 0;
      d_values[2] = 0;
    }

    /** Constructor
     *
     *  Initializes the vector to (x,y,z).
     */
    inline Vector3(T x, T y, T z)
    {
      d_values[0] = x;
      d_values[1] = y;
      d_values[2] = z;
    }

    /** Destructor
     */
    inline ~Vector3() { destroy(); }
    
    /**
     *  @returns a pointer to the array of values.
     */
    inline T const *ptr() const { return d_values; }

    /**
     *  @returns a pointer to the array of values. This is an auto
     *           conversion function and makes it posible to
     *           use the vector in places where you normaly would
     *           have used an array of 3 values.
     */
    inline operator T *() { return d_values; }

    /**
     *  @returns a const pointer to the array of values. This is an auto
     *           conversion function and makes it posible to
     *           use the vector in places where you normaly would
     *           have used a const array of 3 values.
     */
    inline operator T const *() const { return d_values; }

    /** Copies values from \a other
     */
    inline Vector3 &operator=(Vector3 const &other)
    {
      if (this != &other) {
        destroy();
        copy(other);
      }
      return *this;
    }

    /** Set member \a idx to \a value
     * 
     * @param idx Index of vector element
     * @param value New value of element
     */
    inline void set(unsigned idx, T value) { assert(idx < 3); d_values[idx] = value; }
    
    /** Set all vector elements to new values
     *
     * @param a New value of first element (X)
     * @param b New value of second element (Y)
     * @param c New value of third element (Z)
     */
    inline void set(T a, T b, T c) { d_values[0] = a; d_values[1] = b; d_values[2] = c; }
    
    /** Set X-coordinate to \a value
     *
     * @param value New value of first element (X)
     */
    inline void setX(T value) { d_values[0] = value; }

    /** Set Y-coordinate to \a value
     *
     * @param value New value of second element (Y)
     */
    inline void setY(T value) { d_values[1] = value; }

    /** Set Z-coordinate to \a value
     *
     * @param value New value of third element (Z)
     */
    inline void setZ(T value) { d_values[2] = value; }

    
    /** Get value of member \a idx */
    inline T get(unsigned idx) const
    {
      assert(idx < 3);
      return d_values[idx];
    }

    /** Get X-coordinate */
    inline T getX() const{ return d_values[0]; }

    /** Get Y-coordinate */
    inline T getY() const { return d_values[1]; }

    /** Get Z-coordinate */
    inline T getZ() const { return d_values[2]; }

    /** Calculate vector length
     *
     * \f$ |\vec V| = \sqrt{X^2 + Y^2 + Z^2} \f$
     */
    inline T length() const
    {
      return BasicMath::sqrt(d_values[0]*d_values[0] +
			     d_values[1]*d_values[1] + 
			     d_values[2]*d_values[2]);
    }

    /**
     *  @returns a normalized vector. A vector is normalized when its euclidian length is one.
     */
    inline Vector3<T> normalize() const
    {
      return (*this)*BasicMath::invSqrt(d_values[0]*d_values[0] +
					d_values[1]*d_values[1] +
					d_values[2]*d_values[2]);
    }

    /** Calculate the cross product of this vector with another vector
     *
     * \f$ \vec c = \vec a \times \vec b \f$ <BR>
     * \f$ c_0 = a_1 \cdot b_2 - a_2 \cdot a_1 \f$ <BR>
     * \f$ c_1 = a_2 \cdot b_0 - a_0 \cdot a_2 \f$ <BR>
     * \f$ c_2 = a_3 \cdot b_1 - a_1 \cdot a_0 \f$ 
     */
    inline Vector3<T> crossProduct(Vector3<T> const &other) const
    {
     return Vector3<T>(
        (d_values[1] * other.d_values[2] - d_values[2] * other.d_values[1]),
        (d_values[2] * other.d_values[0] - d_values[0] * other.d_values[2]),
        (d_values[0] * other.d_values[1] - d_values[1] * other.d_values[0])
	);
    }

    /** Calculate the dot product of this vector with another vector
     *
     * \f$ \vec c = \vec a \cdot \vec b \f$ <BR>
     * \f$ c_i = a_i \cdot b_i \f$
     */
    inline T dotProduct(Vector3<T> const &other) const
    {
      return (d_values[0]*other.d_values[0] +
	      d_values[1]*other.d_values[1] +
	      d_values[2]*other.d_values[2]);
    }

    /**
     *  Performs a dot (or inner) product.
     */
    inline T operator*(Vector3<T> const &other) const
    {
      return dotProduct(other);
    }
    
    /** Add another vector to this vector*/
    inline Vector3<T> operator+(Vector3 const &other) const
    {
      Vector3<T> res(d_values[0] + other.d_values[0],
		     d_values[1] + other.d_values[1],
		     d_values[2] + other.d_values[2]);

      return res;
    }

    /** Subtract another vector from this vector */
    inline Vector3<T> operator-(Vector3 const &other) const
    {
      Vector3<T> res(d_values[0] - other.d_values[0],
		     d_values[1] - other.d_values[1],
		     d_values[2] - other.d_values[2]);

      return res;
    }

    /** Multiply this vector with a scalar value */
    inline Vector3<T> operator*(T value) const
    {
      Vector3<T> res(d_values[0] * value,
		     d_values[1] * value,
		     d_values[2] * value);

      return res;
    }

    /** Divide this vector by a scalar value */
    inline Vector3<T> operator/(T value) const
    {
      Vector3<T> res(d_values[0] / value,
		     d_values[1] / value,
		     d_values[2] / value);

      return res;
    }

    /**
     *  @returns the negative version of the vector.
     */
    inline Vector3<T> operator-()
    {
      Vector3<T> res(
        -d_values[0],
        -d_values[1],
        -d_values[2]
      );

      return res;
    }

    /**
     *  Adds other to this one.
     */
    inline Vector3<T> &operator+=(Vector3 const &other)
    {
      d_values[0] += other.d_values[0];
      d_values[1] += other.d_values[1];
      d_values[2] += other.d_values[2];

      return *this;
    }

    /**
     *  Substracts other from this one.
     */
    inline Vector3<T> &operator-=(Vector3 const &other)
    {
      d_values[0] -= other.d_values[0];
      d_values[1] -= other.d_values[1];
      d_values[2] -= other.d_values[2];

      return *this;
    }

    /** Divide this vector by a scalar value */
    inline Vector3<T> &operator/=(T value)
    {
      d_values[0] /= value;
      d_values[1] /= value;
      d_values[2] /= value;

      return *this;
    }

    /** Multiply this vector by a scalar value */
    inline Vector3<T> &operator*=(T value)
    {
      d_values[0] *= value;
      d_values[1] *= value;
      d_values[2] *= value;

      return *this;
    }

    /** Compare this vector to another vector */
    inline bool operator==(Vector3 const &other) const
    {
      return d_values[0] == other.d_values[0] &&
             d_values[1] == other.d_values[1] &&
             d_values[2] == other.d_values[2];
    }
    
    inline bool operator!=(Vector3 const &other) const
    {
      return !(*this == other);
    }

    inline bool operator<(Vector3 const& other) const
    {
      return length() == other.length() ? d_values[0] < other.d_values[0] : length() < other.length();
    }
    
    /** Calculate angle between this vector and another vector
     *
	 * \todo: check 90 degrees boundary.
	 *
     * \f$ cos(\alpha) = {{\vec a \cdot \vec b} \over {| \vec a | | \vec b | }}\f$ <BR>
     *
     */
    inline double angle(Vector3 const &other) const
    {
      double dp = dotProduct(other);
      return acos(dp / (length() * other.length()));
    }

    /**
     *  @returns false is one of the values is NaN.
     */
    inline bool isValid()
    {
    	return !std::isnan(d_values[0]) && !std::isnan(d_values[1]) && !std::isnan(d_values[2]);
    }
  };

  /**
   *  A vector of doubles.
   */
  typedef Vector3<float> Vector3D;

  /**
   *  A vector of floats.
   */
  typedef Vector3<float>  Vector3F;

  template <class K>
  std::ostream &operator<<(std::ostream &_os, Vector3<K> const &_vect)
  {
    return _os << "(" << _vect.d_values[0] << ", " << _vect.d_values[1] << ", " << _vect.d_values[2] << ")";
  }

};

#endif // __INC_BATS_VECTOR3_HH_

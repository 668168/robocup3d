/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: tvector.h 56 2009-03-17 18:03:47Z hedayat $

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   TVector is a template class for vector implementations. It abstracts away
   the number of elements and their type.

   TVector2 is a 2D version
   TVector3 is a 3D version

   HISTORY:
        12.08.2002 MK
          - initial version

*/
#ifndef SALT_TVECTOR_H
#define SALT_TVECTOR_H

#include "salt_defines.h"
#include "gmath.h"
#include <iostream>

namespace salt
{

/**  TVector is a template class for vector implementations. It
 *  abstracts away the number of elements and their type.
 */
template <typename DATATYPE, int ELEMENTS, typename TYPE>
class TVector
{
    //
    // functions
    //
public:
    TVector() {}

    // accessors

    /** returns a reference to a row of the vector */
    f_inline DATATYPE& operator[](int row)
    { return El(row); }

    /** returns a constant reference to a row of a vector */
    f_inline const DATATYPE& operator[](int row) const
    { return El(row); }

    /** returns a reference to a row of a vector */
    f_inline DATATYPE& Get(int row) { return El(row); }

    /** returns a constant reference to a row of a vector */
    f_inline const DATATYPE& Get(int row) const { return El(row); }

    // Direct pointer access to the data member ... use with care!!!

    /** copies another vector 'copy' */
    f_inline const TYPE& SetData(const DATATYPE *copy);

    /** return a pointer to the encapsulated vector */
    f_inline DATATYPE* GetData()
    { return mData; }

    // Output

    /** prints the contents of vector to stdout */
    void Dump() const;

    /** fills all components of the vector with value 'fill' */
    f_inline const TYPE& Fill(const DATATYPE& fill);

    /** sets all components of the vector to 0 */
    f_inline TYPE& Zero();

    // operators

    /** calculates this VECTOR + VECTOR */
    f_inline const TYPE operator+(const TYPE &v) const;

    /** calculates VECTOR - VECTOR*/
    f_inline const TYPE operator-(const TYPE &v) const;

    /** calculates VECTOR * VECTOR */
    f_inline const TYPE operator*(const DATATYPE &v) const;

    /** calculates VECTOR / SCALAR */
    f_inline const TYPE operator/(const DATATYPE &v) const;

    /** add another vector */
    f_inline TYPE& operator+=(const TYPE &v);

    /** substracts another vector */
    f_inline TYPE& operator-=(const TYPE &v);

    /** multiplies another vector */
    f_inline TYPE& operator*=(const DATATYPE &v);

    /** divides another vector */
    f_inline TYPE& operator/=(const DATATYPE &v);

    /** returns the negate of this vector */
    f_inline TYPE operator-() const;

    /** returns true if this vector and v are equal */
    f_inline bool operator==(const TYPE& v)const;

    /** returns true if this vector and v are not equal */
    f_inline bool operator!=(const TYPE& v)const;

    /** returns the dot product from this vector and v */
    f_inline DATATYPE Dot(const TYPE& v) const;

    /** normalizes the vector */
    f_inline const TYPE& Normalize();

    /** calculates the normalized vector, not modifying the vector */
    f_inline TYPE Normalized() const;

    /** calculates the squared length of the vector */
    f_inline DATATYPE SquareLength() const;

    /** calculates the length of the vector */
    f_inline DATATYPE Length() const
    { return gSqrt(SquareLength()); }

    /** returns the index of least significant axis */
    f_inline int GetLeastSignificantAxis() const;

    /** returns the index of the most significant axis */
    f_inline int GetMostSignificantAxis() const;

    /** lineary interpolates between this vector and to with an delta increment */
    f_inline TYPE LinearInterpolate(const TYPE& to, float delta) const;

    /** lineary interpolates between this vector and to with an delta
     * increment, returning a normalized vector
     */
    f_inline TYPE NormalizedLinearInterpolate(const TYPE& to, float delta) const
    {
        return LinearInterpolate(to, delta).Normalize();
    }

protected:
    // Copy constructor:
    TVector(const TYPE &v)
    {
        for (int i=0; i<ELEMENTS; i++)
            mData[i] = v[i];
    }

    // Element accessor
    const DATATYPE& El(int index) const
    {
        return mData[index];
    }
    DATATYPE& El(int index)
    {
        return mData[index];
    }

    //
    // members
    //
private:
    DATATYPE mData[ELEMENTS];
};

template <typename DATATYPE, int ELEMENTS, typename TYPE>
std::ostream& operator <<(std::ostream& ost, const TVector<DATATYPE,ELEMENTS,TYPE>& v)
{
    if (ELEMENTS < 1) return ost;
    ost << v[0];
    for (int i=1; i<ELEMENTS; ++i) ost << " " << v[i];
    return ost;
}

/** TVector2 is a two dimensional version of TVector */
template <typename DATATYPE, class TYPE>
class TVector2 : public TVector<DATATYPE, 2, TYPE>
{
public:
    /** constructs an undefined TVector2 */
    TVector2() : TVector<DATATYPE, 2, TYPE>() {};

    /** constructs a TVector2 from x and y */
    TVector2(DATATYPE x, DATATYPE y) : TVector<DATATYPE, 2, TYPE>()
    { Set(x, y); }

    // Element Access operators

    /** returns a reference to the first component */
    f_inline DATATYPE& x()
    { return this->El(0); }

    /** returns a constant reference to the first component */
    f_inline const DATATYPE& x() const
    { return this->El(0); }

    /** returns a reference to the second component */
    f_inline DATATYPE& y()
    { return this->El(1); }

    /** returns a constant reference to the second component */
    f_inline const DATATYPE& y() const
    { return this->El(1); }

    /** sets up the vector from x and y */
    f_inline const TYPE& Set(const DATATYPE& x, const DATATYPE& y)
    {
        this->El(0) = x;
        this->El(1) = y;
        return *static_cast<TYPE*>(this);
    }
};


/** TVector3 is a two dimensional version of TVector */
template <typename DATATYPE, class TYPE>
class TVector3 : public TVector<DATATYPE, 3, TYPE>
{
public:
    /** constructs an undefined TVector3 */
    TVector3() : TVector<DATATYPE, 3, TYPE>() {};

    /** constructs a TVector3 from x,y and z */
    TVector3(const DATATYPE& x, const DATATYPE& y, const DATATYPE& z)
        : TVector<DATATYPE, 3, TYPE>()
    { Set(x, y, z); }

    // Element Access operators

    /** returns a reference to the first component */
    f_inline DATATYPE& x()
    { return this->El(0); }

    /** returns a constant reference to the first component */
    f_inline const DATATYPE& x() const
    { return this->El(0); }

    /** returns a reference to the second component */
    f_inline DATATYPE& y()
    { return this->El(1); }

    /** returns a constant reference to the second component */
    f_inline const DATATYPE& y() const
    { return this->El(1); }

    /** returns a reference to the third component */
    f_inline DATATYPE& z()
    { return this->El(2); }

    /** returns a constant reference to the third component */
    f_inline const DATATYPE& z() const
    { return this->El(2); }

    /** calculates the cross product, returning a new TVector3 */
    const TYPE Cross(const TVector<DATATYPE, 3, TYPE>& v) const
    {
        // Create a new one
        TYPE r;
        r[0] = this->El(1) * v[2] - this->El(2) * v[1];
        r[1] = this->El(2) * v[0] - this->El(0) * v[2];
        r[2] = this->El(0) * v[1] - this->El(1) * v[0];
        return r;
    }

    //
    // Set operator
    //

    /** sets up the vector from x,y and z */
    const TYPE& Set(const DATATYPE& x, const DATATYPE& y, const DATATYPE& z)
    {
        this->El(0) = x;
        this->El(1) = y;
        this->El(2) = z;
        return *static_cast<TYPE*>(this);
    }


    /** sets up the vector from another TVector3 v */
    const TYPE& Set(const TYPE& v)
    {
        this->El(0) = v.x();
        this->El(1) = v.y();
        this->El(2) = v.z();
        return *static_cast<TYPE*>(this);
    }
};

// Set operator for any vector. Just with a pointer
template <typename DATATYPE, int ELEMENTS, typename TYPE>
inline const TYPE& TVector<DATATYPE, ELEMENTS, TYPE>::SetData(const DATATYPE *copy)
{
    for (int i=0; i<ELEMENTS; i++)
        mData[i] = copy[i];
    return *static_cast<TYPE*>(this);
}

// Output
template <typename DATATYPE, int ELEMENTS, typename TYPE>
inline void TVector<DATATYPE, ELEMENTS, TYPE>::Dump() const
{
    for (int i=0; i<ELEMENTS; i++)
        std::cout << mData[i] << " ";
    std::cout << "\n";
}

// fill vector with value 'fill'
template <typename DATATYPE, int ELEMENTS, class TYPE>
f_inline const TYPE& TVector<DATATYPE, ELEMENTS, TYPE>::Fill(const DATATYPE& fill)
{
    for (int c=0; c < ELEMENTS; c++)
        mData[c] = fill;
    return *static_cast<TYPE*>(this);
}

// fill vector with zeros
template <typename DATATYPE, int ELEMENTS, class TYPE>
f_inline TYPE& TVector<DATATYPE, ELEMENTS, TYPE>::Zero()
{
    for (int c=0; c < ELEMENTS; c++)
        mData[c] = DATATYPE(0);
    return *static_cast<TYPE*>(this);
}

// DATATYPE * vector
template <typename DATATYPE, int ELEMENTS, class TYPE>
f_inline const TYPE operator*(const DATATYPE& f, const TVector<DATATYPE, ELEMENTS, TYPE>& vec)
{
    return vec * f;
}

// vector addition
// this + v return new Vector
template <typename DATATYPE, int ELEMENTS, typename TYPE>
f_inline const TYPE TVector<DATATYPE, ELEMENTS, TYPE>::operator+(const TYPE& v) const
{
    TYPE r;
    for (int c=0; c < ELEMENTS; c++)
        r[c]=mData[c] + v[c];
    return r;
}

// vector subtraction
// this - v return new Vector
template <typename DATATYPE, int ELEMENTS, typename TYPE>
f_inline const TYPE TVector<DATATYPE, ELEMENTS, TYPE>::operator-(const TYPE& v) const
{
    TYPE r;
    for (int c=0; c < ELEMENTS; c++)
        r[c]=mData[c] - v[c];
    return r;
}

// scale
// this * DATATYPE return new Vector
template <typename DATATYPE, int ELEMENTS, typename TYPE>
f_inline const TYPE TVector<DATATYPE, ELEMENTS, TYPE>::operator*(const DATATYPE& v) const
{
    TYPE r;
    for (int c=0; c < ELEMENTS; c++)
        r[c]=mData[c] * v;
    return r;
}

// division
// this / DATATYPE return new Vector
template <typename DATATYPE, int ELEMENTS, typename TYPE>
f_inline const TYPE TVector<DATATYPE, ELEMENTS, TYPE>::operator/(const DATATYPE& v) const
{
    TYPE r;
    for (int c=0; c < ELEMENTS; c++)
        r[c]=mData[c] / v;
    return r;
}

// this += v returns reference to first vector
template <typename DATATYPE, int ELEMENTS, typename TYPE>
f_inline TYPE& TVector<DATATYPE, ELEMENTS, TYPE>::operator+=(const TYPE& v)
{
    for (int c=0; c<ELEMENTS; c++)
        mData[c] += v[c];
    return *static_cast<TYPE*>(this);
}

// this -= v returns reference to first vector
template <typename DATATYPE, int ELEMENTS, typename TYPE>
f_inline TYPE& TVector<DATATYPE, ELEMENTS, TYPE>::operator-=(const TYPE& v)
{
    for (int c=0; c<ELEMENTS; c++)
        mData[c] -= v[c];
    return *static_cast<TYPE*>(this);
}

// this *= DATATYPE returns reference to first vector
template <typename DATATYPE, int ELEMENTS, typename TYPE>
f_inline TYPE& TVector<DATATYPE, ELEMENTS, TYPE>::operator*=(const DATATYPE& v)
{
    for (int c=0; c<ELEMENTS; c++)
        mData[c] *= v;
    return *static_cast<TYPE*>(this);
}

// this /= DATATYPE returns reference to first vector
template <typename DATATYPE, int ELEMENTS, typename TYPE>
f_inline TYPE& TVector<DATATYPE, ELEMENTS, TYPE>::operator/=(const DATATYPE& v)
{
    for (int c=0; c<ELEMENTS; c++)
        mData[c] /= v;
    return *static_cast<TYPE*>(this);
}

// unary minus
template <typename DATATYPE, int ELEMENTS, typename TYPE>
f_inline TYPE TVector<DATATYPE, ELEMENTS, TYPE>::operator-() const
{
    TYPE r;
    for (int c=0; c < ELEMENTS; c++)
        r[c] = -mData[c];
    return r;
}

// equality
template <typename DATATYPE, int ELEMENTS, typename TYPE>
f_inline bool TVector<DATATYPE, ELEMENTS, TYPE>::operator==(const TYPE& v) const
{
    return (0==memcmp(this,& v, sizeof(*this)));
}

// inequality
template <typename DATATYPE, int ELEMENTS, typename TYPE>
f_inline bool TVector<DATATYPE, ELEMENTS, TYPE>::operator!=(const TYPE& v) const
{
    return (0!=memcmp(this,& v, sizeof(*this)));
}

// generic dot product
template <typename DATATYPE, int ELEMENTS, typename TYPE>
f_inline DATATYPE TVector<DATATYPE, ELEMENTS, TYPE>::Dot(const TYPE& v) const
{
    DATATYPE r = mData[0] * v[0];
    for (int c=1; c < ELEMENTS; c++)
        r += mData[c] * v[c];
    return r;
}

// Normalize vector
template <typename DATATYPE, int ELEMENTS, typename TYPE>
f_inline const TYPE& TVector<DATATYPE, ELEMENTS, TYPE>::Normalize()
{
    DATATYPE length             = Length();
    DATATYPE lengthInv  = DATATYPE(DATATYPE(1) / length);
    for (int c=0; c<ELEMENTS; c++)
        mData[c] *= lengthInv;
    return *static_cast<TYPE*>(this);
}

template <typename DATATYPE, int ELEMENTS, typename TYPE>
f_inline TYPE TVector<DATATYPE, ELEMENTS, TYPE>::Normalized() const
{
    TYPE r;
    DATATYPE length             = Length();
    DATATYPE lengthInv  = DATATYPE(DATATYPE(1) / length);
    for (int c=0; c<ELEMENTS; c++)
        r[c] = mData[c] * lengthInv;
    return r;
}

// Squared length determination:
template <typename DATATYPE, int ELEMENTS, typename TYPE>
f_inline DATATYPE TVector<DATATYPE, ELEMENTS, TYPE>::SquareLength() const
{
    DATATYPE r = mData[0] * mData[0];
    for (int c=1; c<ELEMENTS; c++)
        r += mData[c] * mData[c];
    return r;
}

// Linear Interpolate. Interpolated from one vector to the other
template <typename DATATYPE, int ELEMENTS, typename TYPE>
f_inline TYPE TVector<DATATYPE, ELEMENTS, TYPE>::LinearInterpolate(const TYPE& to, float t) const
{
    float it = 1.0f - t;
    TYPE r;
    for (int c=0; c<ELEMENTS; c++)
        r[c] = mData[c] * it + to[c] * t;
    return r;
}

} //namespace salt

#endif //SALT_TVECTOR_H

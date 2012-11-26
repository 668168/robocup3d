/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: bounds.h 56 2009-03-17 18:03:47Z hedayat $

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
*/
#ifndef SALT_BOUNDS_H
#define SALT_BOUNDS_H

#include "salt_defines.h"
#include "matrix.h"
#include "vector.h"

#include <cfloat>

namespace salt
{

/** AABB3 provides an axis aligned three dimensional bounding box */
class SALT_API AABB3
{
public:
    // constructors

    /** constructs an empty bounding box */
    f_inline AABB3() { Init(); }

    /** constructs a bounding box encapsulating mn and mx */
    f_inline AABB3(const Vector3f &mn, const Vector3f &mx)
    { Init(); Encapsulate(mn); Encapsulate(mx); }

    // inline functions

    /** sets minVec and maxVec to describe an empty bounding box */
    f_inline void Init()
    { minVec.Set(FLT_MAX, FLT_MAX, FLT_MAX);
      maxVec.Set(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    }

    /** encapsulates the Vector v, growing the box if necessary */
    f_inline void Encapsulate(const Vector3f &v)
    { minVec.x() = gMin(minVec.x(), v.x());
      minVec.y() = gMin(minVec.y(), v.y());
      minVec.z() = gMin(minVec.z(), v.z());
      maxVec.x() = gMax(maxVec.x(), v.x());
      maxVec.y() = gMax(maxVec.y(), v.y());
      maxVec.z() = gMax(maxVec.z(), v.z()); }

    /** encapsulates the Vector <x,y,z>, growing the box if necessary */
    f_inline void Encapsulate(const float x, const float y, const float z)
    { minVec.x() = gMin(minVec.x(), x);
      minVec.y() = gMin(minVec.y(), y);
      minVec.z() = gMin(minVec.z(), z);
      maxVec.x() = gMax(maxVec.x(), x);
      maxVec.y() = gMax(maxVec.y(), y);
      maxVec.z() = gMax(maxVec.z(), z); }

    /** encapsulates another box, growing the box if necessary */
    f_inline void Encapsulate(const AABB3 &box)
    { Encapsulate(box.minVec); Encapsulate(box.maxVec);}

    /** grows the box evenly with delta along all axis */
    f_inline void Widen(float delta)
    { minVec.x()-=delta;
      minVec.y()-=delta;
      minVec.z()-=delta;
      maxVec.x()+=delta;
      maxVec.y()+=delta;
      maxVec.z()+=delta;
    }

    /** moves the box along the vector v */
    f_inline void Translate(const Vector3f &v)
    { minVec+=v; maxVec+=v; }

    /** returns true if he box contains the vector v */
    f_inline bool Contains(const Vector3f &v) const
    { return (gInRange(v.x(), minVec.x(), maxVec.x()) &&
              gInRange(v.z(), minVec.z(), maxVec.z()) &&
              gInRange(v.y(), minVec.y(), maxVec.y())); }

    /** returns true if the box contains the box b */
    f_inline bool Contains(const AABB3 &b) const
    { return (Contains(b.minVec) && Contains(b.maxVec)); }

    /** returns true if this box and the box b have some space in common */
    f_inline bool Intersects(const AABB3 &b) const
    { return !(minVec.x() > b.maxVec.x() || maxVec.x() < b.minVec.x() ||
               minVec.y() > b.maxVec.y() || maxVec.y() < b.minVec.y() ||
               minVec.z() > b.maxVec.z() || maxVec.z() < b.minVec.z()); }

    /** calculates the current width of the box */
    f_inline float              GetWidth() const
    { return gAbs(minVec.x()-maxVec.x()); }

    /** calculates the current height of the box */
    f_inline float              GetHeight() const
    { return gAbs(minVec.y()-maxVec.y()); }

    /** calculates the current depth of the box */
    f_inline float GetDepth() const
    { return gAbs(minVec.z()-maxVec.z()); }

    /** calculates the center point of the box */
    f_inline Vector3f   GetMiddle() const
    { return Vector3f((minVec.x()+maxVec.x())*0.5f,
                      (minVec.y()+maxVec.y())*0.5f,
                      (minVec.z()+maxVec.z())*0.5f); }

    /** calculates the distance from the center point to one of the corners,
     *  i.e the radius of the bounding sphere through the center.
     */
    f_inline float          GetRadius() const
    { return ((maxVec-minVec)*0.5).Length(); }      // get distance from middle of bounding box to one of the corners
      // (i.e. radius of bounding sphere through Middle()).

    /* multiplies the box with the given matrix */
    void    TransformBy(Matrix& matrix);

    // attributes

    /** a vector describing the lower corner of the box */
    Vector3f                minVec;

    /** a vector describing the higher corner of the box */
    Vector3f                maxVec;
};

/** AABB2 provides an axis aligned two dimensional bounding box */
class SALT_API AABB2
{
public:
    // constructors

    /** constructs an empty bounding box */
    f_inline AABB2()
    { Init(); }

    /** constructs a bounding box encapsulating mn and mx */
    f_inline AABB2(const Vector2f &mn, const Vector2f &mx)
    { Init(); Encapsulate(mn); Encapsulate(mx); }

    // inline functions

    /** sets minVec and maxVec to describe an empty bounding box */
    f_inline void Init()
    { minVec.Set(FLT_MAX, FLT_MAX); maxVec.Set(-FLT_MAX, -FLT_MAX); }

    /** encapsulates the Vector <x,y>, growing the box if necessary */
    f_inline void Encapsulate(const float x, const float y)
    { minVec.x() = gMin(minVec.x(), x);
      minVec.y() = gMin(minVec.y(), y);
      maxVec.x() = gMax(maxVec.x(), x);
      maxVec.y() = gMax(maxVec.y(), y); }

    /** encapsulates the Vector v, growing the box if necessary */
    f_inline void Encapsulate(const Vector2f &v)
    { minVec.x() = gMin(minVec.x(), v.x());
      minVec.y() = gMin(minVec.y(), v.y());
      maxVec.x() = gMax(maxVec.x(), v.x());
      maxVec.y() = gMax(maxVec.y(), v.y()); }

    /** encapsulates another box, growing the box if necessary */
    f_inline void Encapsulate(const AABB2 &box)
    { Encapsulate(box.minVec); Encapsulate(box.maxVec);}

    /** grows the box evenly with delta along both axis */
    f_inline void Widen(float delta)
    { minVec.x()-=delta; minVec.y()-=delta; maxVec.x()+=delta; maxVec.y()+=delta; }

    /** moves the box along the vector v */
    f_inline void Translate(const Vector2f &v)
    { minVec+=v; maxVec+=v; }

    /** returns true if he box contains the vector v */
    f_inline bool Contains(const Vector2f &v) const
    { return (gInRange(v.x(), minVec.x(), maxVec.x()) && gInRange(v.y(), minVec.y(), maxVec.y())); }

    /** returns true if the box contains the box b */
    f_inline bool Contains(const AABB2 &b) const
    { return (Contains(b.minVec) && Contains(b.maxVec)); }

    /** returns true if this box and the box b have some space in common */
    f_inline bool Intersects(const AABB2 &b) const
    { return !(minVec.x() > b.maxVec.x() ||
               maxVec.x() < b.minVec.x() ||
               minVec.y() > b.maxVec.y() ||
               maxVec.y() < b.minVec.y());
    }

    /** calculates the current width of the box */
    f_inline float GetWidth() const
    // get width of bounding box
    { return gAbs(minVec.x()-maxVec.x()); }

    /** calculates the current height of the box */
    f_inline float          GetHeight() const
    // get height of bounding box
    { return gAbs(minVec.y()-maxVec.y()); }

    /** calculates the center point of the box */
    f_inline Vector2f       GetMiddle() const
    { return Vector2f((minVec.x()+maxVec.x())*0.5f, (minVec.y()+maxVec.y())*0.5f); }

    /** calculates the distance from the center point to one of the corners,
     *  i.e the radius of the bounding sphere through the center.
     */
    f_inline float          GetRadius() const
    { return ((maxVec-minVec)*0.5).Length(); }

    // attributes

    /** a vector describing the lower corner of the box */
    Vector2f                minVec;

    /** a vector describing the higher corner of the box */
    Vector2f                maxVec;
};


/** BoundingSphere provides a three dimensional sphere */
class SALT_API BoundingSphere
{
public:
    // constructors

    /** constructs an empty sphere */
    f_inline BoundingSphere()
        : center(Vector3f(0,0,0)), radius(0.0f), radiusSq(0.0f) {}

    /** constructs a sphere around pos with the radius rad */
    f_inline BoundingSphere(const Vector3f &pos, float rad)
        : center(pos), radius(rad), radiusSq(rad*rad) {}

    /** Constructs a bounding sphere
     *  \param pos The position where the sphere is constructed
     *  \param rad is the radius of the sphere
     *  \param radSq is the user supplied square of rad
     */
    f_inline BoundingSphere(const Vector3f &pos, float rad, float radSq)
        : center(pos), radius(rad), radiusSq(radSq)     {}

    // inline functions

    /** encapsulates the vector v in the sphere, growing it if neccesary.
     * this method is fast but not accurate
     */
    f_inline void EncapsulateFast(const Vector3f &v)
    { Vector3f diff=(center - v);   float dist=diff.Dot(diff);
      // not accurate
      if (dist>radiusSq) { radiusSq=dist; radius=gSqrt(dist); }}

    /** returns true if the sphere contains the vector v */
    f_inline bool Contains(const Vector3f &v)
    { return ((center - v).SquareLength() < radiusSq); }

    /** returns true if the sphere contains the sphere s */
    f_inline bool Contains(const BoundingSphere &s) const
    { return (radius >= s.radius) &&
             ((center - s.center).SquareLength() <
              (radius - s.radius) * (radius - s.radius));
    }

    /** returns true if this sphere and the sphere s intersect */
    f_inline bool Intersects(const BoundingSphere &s) const
    { return ((center - s.center).SquareLength() <
              (radius + s.radius) * (radius + s.radius)); }

    // non-inline functions

    /** encapsulates the vector v in the sphere, growing it if neccesary.
     * this method is accurate but slower than EncapsulateFast
     */
    void Encapsulate(const Vector3f &v);

    /** returns true, if the sphere contains the axis aligned bounding box b */
    bool Contains(const AABB3 &b) const;

    /** returns true, if the sphere and the axis aligned bounding box b intersect */
    bool Intersects(const AABB3 &b) const;

    // attributes

    /** describes the center of the sphere */
    Vector3f        center;

    /** describes the radius of the sphere */
    float           radius;

    /** the square of the sphere radius. The value ist either accuratly calculated
     * in the constructor or user supplied and may be inaccurate.
     */
    float           radiusSq;
};

} // namespace salt

#endif // SALT_BOUNDS_H

/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: plane.h 56 2009-03-17 18:03:47Z hedayat $

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

   NOTE:

   HISTORY:
                11.06.01 - MK
                        - Initial version

   TODO:

   TOFIX:
*/
#ifndef SALT_PLANE_H
#define SALT_PLANE_H

#include "salt_defines.h"
#include "vector.h"
#include "bounds.h"

namespace salt
{

/** defines possible sides on the plane */
enum EPlaneSide
{
    PLANESIDE_BACK                      =       0,
    PLANESIDE_ONPLANE           =       1,
    PLANESIDE_FRONT                     =       2,
    PLANESIDE_SPLIT                     =       3,
    PLANESIDE_FORCE_32BIT       =       0xffffffff      // used to force the enum to be 32-bit wide
};


/** defines possible dominant plane values */
enum EPlane
{
    PLANE_XY                    =       0,
    PLANE_XZ                    =       1,
    PLANE_YZ                    =       2,
    PLANE_FORCE_32BIT   =       0xffffffff      // used to force the enum to be 32-bit wide
};


/**
  *     A mathematical plane is modeled by this class. It can be used to
  *     classify points against planes (in front, on plane,
  *     etc...). Several useful functions for constructing a plane are
  *     provided. A plane is defined by the formula. Ax+By+Cz+D=0. The
  *     vector formed by the coefficients <A,B,C> is the normal vector to
  *     the plane.
  */
class SALT_API Plane
{
// Members
public:
    /** the normal vector of the modeled plane */
    Vector3f    normal;

    /** the distance */
    float               d;

// Methods
public:
    /** empty constructor for an undefined plane */
    f_inline Plane() {}         // empty constructor ... performance

    /** constructs a plane from a normal and a point on the plane */
    f_inline Plane(const Vector3f& norm, const Vector3f& pnt)                                           { normal=norm; d=-((norm.x()*pnt.x()) + (norm.y()*pnt.y()) + (norm.z()*pnt.z())); }

    /** constructs a plane from normal and constant D. If normal is a
     * unit vector, then D is the distance to the origin
     */
    f_inline Plane(const Vector3f& norm, const float D)                                                         { normal=norm; d=D; }

    /** constructs a plane from 3 distinct points */
    f_inline Plane(const Vector3f& v1,  const Vector3f &v2, const Vector3f &v3)         { normal=(v2-v1).Cross(v3-v1).Normalized(); d=-normal.Dot(v1); }

    // inline functions

    /** calculates the orientation of v to the plane */
    f_inline EPlaneSide GetOrientation(const Vector3f &v, float delta=0.0001f) const    { float dist=normal.Dot(v)+d; if (dist<-delta) return PLANESIDE_BACK; if (dist>delta) return PLANESIDE_FRONT; return PLANESIDE_ONPLANE;  }

    /** calculates the dominant plane */
    f_inline EPlane             GetDominantPlane() const                                                                        { return (gAbs(normal.y()) > gAbs(normal.x()) ? (gAbs(normal.z()) > gAbs(normal.y()) ? PLANE_XY : PLANE_XZ) : (gAbs(normal.z()) > gAbs(normal.x()) ? PLANE_XY : PLANE_YZ)); }

    /** calculates the distance from v to the plane */
    f_inline float              GetDistanceTo(const Vector3f &v) const
    { return normal.Dot(v) + d; }


    /** calculates the relationship between the plane and the box */
    EPlaneSide ClassifyBox(const AABB3& bb) const;

    /** normalizes the plane */
    void Normalize();

    /** sets up a plane from a normal and a point on the plane */
    f_inline void Set(const Vector3f& norm, const Vector3f& pnt)
    { normal=norm; d=-((norm.x()*pnt.x()) + (norm.y()*pnt.y()) + (norm.z()*pnt.z())); }

    /** sets up a plane from normal and constant D. If normal is a
     * unit vector, then D is the distance to the origin
     */
    f_inline void Set(const Vector3f& norm, const float D)                                                      { normal=norm; d=D; }

    /** sets up a plane from 3 distinct points */
    f_inline void Set(const Vector3f& v1,   const Vector3f &v2, const Vector3f &v3)     { normal=(v2-v1).Cross(v3-v1).Normalized(); d=-normal.Dot(v1); }

    /** the assignment operator for planes */
    f_inline const Plane&       operator=(const Plane& p)
    { normal=p.normal; d=p.d; return *this; }

};

}

#endif //SALT_PLANE_H

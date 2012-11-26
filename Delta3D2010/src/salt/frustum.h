/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: frustum.h 56 2009-03-17 18:03:47Z hedayat $

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
   23.03.02 - MK
   - Intersection/Inclusion-tests

   TODO:
   - Create frustum from a (view)point and a polygon
   - Create a view frustum given field-of-views

   TOFIX:
*/
#ifndef SALT_FRUSTUM_H
#define SALT_FRUSTUM_H

#include "salt_defines.h"
#include "plane.h"
#include "bounds.h"

namespace salt
{

/**  This class implements a frustum, which is an arbitrary volume in
  *  space (possibly infinite) defined by a set of planes. This class
  *  also provides some 'special' frustra construction methods.
  */
class SALT_API Frustum
{
// Members
public:
    /** plane ids used as an index into mPlanes */
    enum ePlaneID
    {
        PI_NEAR         = 0,
        PI_LEFT         = 1,
        PI_RIGHT        = 2,
        PI_FAR          = 3,
        PI_BOTTOM       = 4,
        PI_TOP          = 5
    };

    /** constants describing the result of an intersection test */
    enum eFrustumSide
    {
        FS_INSIDE  = 0,
        FS_OUTSIDE = 1,
        FS_SPLIT   = 2
    };

    /** the position from where the frustum is cast */
    Vector3f    mBasePos;

    /** the 6 plane equations */
    Plane               mPlanes[6];

// Methods
public:
    /** a debug helper method, printing the plane normals */
    void Dump() const;

    /** constructs a frustum
     * \param worldTransform is the world transform matrix
     * \param fov is the field of view, the angle between the casted planes
     * \param zNear is the distance to the near plane
     * \param zFar is the distance to the far plane
     * \param aspect is the aspect ratio
     */
    void Set(const Matrix& worldTransform, float fov=60.0f, float zNear=0.1f, float zFar=2000.0f, float aspect=0.75f);

    /** returns the relation that hold between between the axis
     * aligned bounding boxx bb and this frustum as an eFrustumSide
     * value
     */
    eFrustumSide Intersects(const AABB3& bb) const;
};

} // namespace salt

#endif //SALT_FRUSTUM_H

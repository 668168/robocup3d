/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003-2007 RoboCup Soccer Server 3D Maintenance Group
   $Id: vector.h 56 2009-03-17 18:03:47Z hedayat $

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

   Here we define/complete the vector definitions of TVector into specific
   vector types (2d float, 3d float, etc...).

   HISTORY:
                12.08.2002 MK
                        - initial version

*/
#ifndef SALT_VECTOR_H
#define SALT_VECTOR_H

#include "tvector.h"
#include <cstdlib>
#include <climits>

namespace salt
{

class SALT_API Vector2f : public TVector2<float, Vector2f>
{
    //
    // Methods
    //
public:
    /// Construction/Destruction/Assignment
    f_inline        Vector2f()                                      : TVector2<float, Vector2f>() { }
    f_inline        Vector2f(float x, float y)      : TVector2<float, Vector2f>(x, y) { }
    explicit        Vector2f(const float *f)        : TVector2<float, Vector2f>() { SetData(f);  }
    f_inline        Vector2f(const Vector2f &v)     : TVector2<float, Vector2f>(v) { }
    explicit        Vector2f(float f)                       : TVector2<float, Vector2f>() { Fill(f); }

    float           GetAngleRad() const
    {
        const double length = Length();
        if (length == 0)
            {
                return 0.0;
            }

        double rad = gArcCos(Get(0) / length);

        if (Get(1) < 0)
            {
                rad = 2*M_PI - rad;
            }

        return static_cast<float>(rad);
    }

    float           GetAngleDeg() const
    {
        return gRadToDeg(GetAngleRad());
    }
};

class SALT_API Vector3f : public TVector3<float, Vector3f>
{
    //
    // Methods
    //
public:
    /// Construction/Destruction/Assignment
    f_inline        Vector3f()                                                      : TVector3<float, Vector3f>() { }
    f_inline        Vector3f(float x, float y, float z)     : TVector3<float, Vector3f>(x, y, z) { }
    explicit        Vector3f(const float *f)                        : TVector3<float, Vector3f>() { SetData(f);  }
    f_inline        Vector3f(const Vector3f &v)                     : TVector3<float, Vector3f>(v) { }
    explicit        Vector3f(float f)                                       : TVector3<float, Vector3f>() { Fill(f); }

    f_inline        Vector3f Reflect(const Vector3f &normal)
    {
        float fac = 2.0f * (normal.x() * x() + normal.y() * y() + normal.z() * z());
        return Vector3f(fac * normal.x()-x(),
                        fac * normal.y()-y(),
                        fac * normal.z()-z());
    }

    f_inline void RandomUnitVector()
    {
        x() = 1.0f - 2.0f*rand()/(float)RAND_MAX;
        y() = 1.0f - 2.0f*rand()/(float)RAND_MAX;
        z() = 1.0f - 2.0f*rand()/(float)RAND_MAX;

        Normalize();
    }
};

} //namespace salt

#endif //SALT_VECTOR_H

/* -*- mode: c++ -*-
   
   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2003 Koblenz University
   $Id: frustum.cpp 3 2008-11-21 02:38:08Z hedayat $

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
#include "frustum.h"
#include "matrix.h"

#include <cstdio>

using namespace salt;

void Frustum::Dump() const
{
	printf("Frustum %p:\n", this);
	for(int i=0; i<6; ++i)
	{
		printf("  %d: %f %f %f %f\n", i, mPlanes[i].normal.x(), mPlanes[i].normal.y(), mPlanes[i].normal.z(), mPlanes[i].d);
	}
}
void Frustum::Set(const Matrix& worldTransform, float fov, float zNear, float zFar, float aspect)
{
	Matrix viewTransform = worldTransform;
	viewTransform.InvertRotationMatrix();

	float halfWorldWidth	= zNear * (float)tan(gDegToRad(fov*0.5f));
	float halfWorldHeight	= halfWorldWidth * (aspect);
	
	Matrix projectionTransform;
	
	projectionTransform.Identity();
	projectionTransform(0,0) = zNear/halfWorldWidth;
	projectionTransform(1,1) = zNear/halfWorldHeight;
	projectionTransform(2,2) = -(zFar+zNear)/(zFar-zNear);
	projectionTransform(2,3) = -(2.0f*zFar*zNear)/(zFar-zNear);
	projectionTransform(3,2) = -1;
	projectionTransform(3,3) = 0;
	
	// concatenate projection and view transform
	Matrix frustumMatrix = projectionTransform * viewTransform;

	// Get plane parameters
    float *m= frustumMatrix.m;
   
    Plane *p = &mPlanes[Frustum::PI_RIGHT];
	p->normal.Set(m[3]-m[0], m[7]-m[4], m[11]-m[8]);
	p->d = m[15]-m[12];
	
	p = &mPlanes[Frustum::PI_LEFT];
	p->normal.Set(m[3]+m[0], m[7]+m[4], m[11]+m[8]);
	p->d = m[15]+m[12];

	p = &mPlanes[Frustum::PI_BOTTOM];
	p->normal.Set(m[3]+m[1], m[7]+m[5], m[11]+m[9]);
	p->d = m[15]+m[13];

	p = &mPlanes[Frustum::PI_TOP];
	p->normal.Set(m[3]-m[1], m[7]-m[5], m[11]-m[9]);
	p->d = m[15]-m[13];

	p = &mPlanes[Frustum::PI_NEAR];
	p->normal.Set(m[3]-m[2], m[7]-m[6], m[11]-m[10]);
	p->d = m[15]-m[14];

	p = &mPlanes[Frustum::PI_FAR];
	p->normal.Set(m[3]+m[2], m[7]+m[6], m[11]+m[10]);
	p->d = m[15]+m[14];

	// Normalize all plane normals
	for(int i=0;i<6;++i)
	{
		mPlanes[i].Normalize();
	}
}

Frustum::eFrustumSide Frustum::Intersects(const AABB3& bb) const
{
	bool split = false;

	for(int i=0; i<6; ++i)
	{
		EPlaneSide result = mPlanes[i].ClassifyBox(bb);
		if(result == PLANESIDE_SPLIT) split = true;

		if(result == PLANESIDE_BACK) return FS_OUTSIDE;
	}

	if(split)
		return FS_SPLIT;
	else
		return FS_INSIDE;
}


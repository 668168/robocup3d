/* -*- mode: c++ -*-
   
   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2003 Koblenz University
   $Id: bounds.cpp 3 2008-11-21 02:38:08Z hedayat $

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
#include "bounds.h"

#include <cstdio>

using namespace salt;

void AABB3::TransformBy(Matrix& matrix)
{
	AABB3	bb;

	Vector3f v(minVec);
	Vector3f w(maxVec);
	
	bb.Encapsulate(matrix.Transform(Vector3f(v.x(),v.y(),v.z())));
	bb.Encapsulate(matrix.Transform(Vector3f(w.x(),v.y(),v.z())));
	bb.Encapsulate(matrix.Transform(Vector3f(v.x(),w.y(),v.z())));
	bb.Encapsulate(matrix.Transform(Vector3f(w.x(),w.y(),v.z())));
	bb.Encapsulate(matrix.Transform(Vector3f(v.x(),v.y(),w.z())));
	bb.Encapsulate(matrix.Transform(Vector3f(w.x(),v.y(),w.z())));
	bb.Encapsulate(matrix.Transform(Vector3f(v.x(),w.y(),w.z())));
	bb.Encapsulate(matrix.Transform(Vector3f(w.x(),w.y(),w.z())));

	minVec.Set(bb.minVec);
	maxVec.Set(bb.maxVec);
}

void BoundingSphere::Encapsulate(const Vector3f &v)
{
	// TODO : check if this is correct
	Vector3f diff = v - center;
	float	dist = diff.Dot(diff);

	if (dist > radiusSq)
	{
		Vector3f diff2	= diff.Normalized() * radius;
		Vector3f delta	= 0.5f * (diff - diff2);
		center		   += delta;
		radius	       += delta.Length();
		radiusSq		= radius*radius;
	}
}



bool BoundingSphere::Intersects(const AABB3 &b) const
{
	float distance = 0.0f;

	for (int t=0; t<3; t++)
	{
		if (center[t] < b.minVec[t]) 
		{
			distance += (center[t] - b.minVec[t]) * (center[t] - b.minVec[t]);
			if (distance>radiusSq) return false;
		}
		else
		if (center[t]>b.maxVec[t])
		{
			distance+=(center[t] - b.maxVec[t]) * (center[t] - b.maxVec[t]);
			if (distance>radiusSq) return false;
		}
	}

	return true;
}



bool BoundingSphere::Contains(const AABB3 &b) const
{
	float distance = 0.0f;

	for (int t=0; t<3; t++)
	{
		if (center[t]<b.maxVec[t]) 
			distance+=(center[t] - b.maxVec[t]) * (center[t] - b.maxVec[t]);
		else
		if (center[t]>b.minVec[t])
			distance+=(center[t] - b.minVec[t]) * (center[t] - b.minVec[t]);

		if (distance>radiusSq) return false;
	}
	return true;
}

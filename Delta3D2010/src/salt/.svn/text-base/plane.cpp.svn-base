/* -*- mode: c++ -*-
   
   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2003 Koblenz University
   $Id: plane.cpp 3 2008-11-21 02:38:08Z hedayat $

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
#include "plane.h"

using namespace salt;

EPlaneSide Plane::ClassifyBox(const AABB3& bb) const
{
	Vector3f posFarPt;
	Vector3f negFarPt;

	if(normal.x()>0)	// right
		if(normal.y()>0)	// right, top
			if(normal.z()>0)	// right, top, front
			{
				posFarPt.Set(bb.maxVec.x(),bb.maxVec.y(),bb.maxVec.z()); 
				negFarPt.Set(bb.minVec.x(),bb.minVec.y(),bb.minVec.z()); 
			}
			else	// right, top, back
			{
				posFarPt.Set(bb.maxVec.x(),bb.maxVec.y(),bb.minVec.z()); 
				negFarPt.Set(bb.minVec.x(),bb.minVec.y(),bb.maxVec.z()); 
			}
		else	// right, bottom
			if(normal.z()>0)	// right, bottom, front
			{
				posFarPt.Set(bb.maxVec.x(),bb.minVec.y(),bb.maxVec.z()); 
				negFarPt.Set(bb.minVec.x(),bb.maxVec.y(),bb.minVec.z()); 
			}
			else	// right, bottom, back
			{
				posFarPt.Set(bb.maxVec.x(),bb.minVec.y(),bb.minVec.z()); 
				negFarPt.Set(bb.minVec.x(),bb.maxVec.y(),bb.maxVec.z()); 
			}
	else
		if(normal.y()>0)	// left, top
			if(normal.z()>0)	// left, top, front
			{
				posFarPt.Set(bb.minVec.x(),bb.maxVec.y(),bb.maxVec.z()); 
				negFarPt.Set(bb.maxVec.x(),bb.minVec.y(),bb.minVec.z()); 
			}
			else	// left, top, back
			{
				posFarPt.Set(bb.minVec.x(),bb.maxVec.y(),bb.minVec.z()); 
				negFarPt.Set(bb.maxVec.x(),bb.minVec.y(),bb.maxVec.z()); 
			}
		else	// left, bottom
			if(normal.z()>0)	// left, bottom, front
			{
				posFarPt.Set(bb.minVec.x(),bb.minVec.y(),bb.maxVec.z()); 
				negFarPt.Set(bb.maxVec.x(),bb.maxVec.y(),bb.minVec.z()); 
			}
			else	// left, bottom, back
			{
				posFarPt.Set(bb.minVec.x(),bb.minVec.y(),bb.minVec.z()); 
				negFarPt.Set(bb.maxVec.x(),bb.maxVec.y(),bb.maxVec.z()); 
			}

	// BOX IS "OUTSIDE"
	if (GetOrientation(negFarPt, 0.0f)==PLANESIDE_FRONT) return PLANESIDE_FRONT;

	// BOX IS "INSIDE"
	if (GetOrientation(posFarPt, 0.0f)==PLANESIDE_BACK) return PLANESIDE_BACK;

	return PLANESIDE_SPLIT;
}

void Plane::Normalize()
{
	float l=normal.Length();
	float iLen = 1.0f/l;
	normal.x()*=iLen;
	normal.y()*=iLen;
	normal.z()*=iLen;
	d*=iLen;
}

/* -*- mode: c++ -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2003 Koblenz University
   $Id: matrix.cpp 3 2008-11-21 02:38:08Z hedayat $

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
#include "matrix.h"

#include <cstdio>

using namespace salt;

float Matrix::mIdentity[16]=
{
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
};

void Matrix::Dump() const
{
	printf("%f %f %f %f\n", m[0], m[4], m[8], m[12]);
	printf("%f %f %f %f\n", m[1], m[5], m[9], m[13]);
	printf("%f %f %f %f\n", m[2], m[6], m[10], m[14]);
	printf("%f %f %f %f\n", m[3], m[7], m[11], m[15]);
}


void Matrix::LookAt(const Vector3f & inEye, const Vector3f & inDirection, const Vector3f & inUp)
{
	Vector3f forward	= inDirection.Normalized();
	Vector3f up			= inUp.Normalized();
	Vector3f right		= forward.Cross(up);
	right.Normalize();

	up = right.Cross(forward);

	// Make inverse rotation matrix using right, forward, up vectors
	Set(	   right.x(),  right.y(),	  right.z(),	0.0f,
				  up.x(),	 up.y(),		 up.z(),	0.0f,
			 forward.x(), forward.y(),  forward.z(),	0.0f,
				  0.0f,		  0.0f,		  0.0f, 1.0f);

	Pos() = Rotate(-inEye);
}

/*!	Calculate an attenuation matrix.
	pos = world space position of light
	radius = radius of light (used for distance attenuation)
*/
void Matrix::CalcAttenuationNoRotation(const Vector3f &pos, float radius)
{
	Matrix tmp1, tmp2;

	// translate to 'light space' ... no rotation needed
	tmp1.Translation(-pos);

	// create proper scaling matrix
	float invrad = 0.5f / radius;

	tmp2.Identity();
	tmp2(0,0) = invrad;
	tmp2(1,1) = invrad;
	tmp2(2,2) = invrad;

	Identity ();
	Translation (Vector3f(0.5f, 0.5f, 0.5f));

	*this *= tmp2 * tmp1;
}

void Matrix::CalcAttenuationWithRotation(const Matrix &lightWorldMatrix, float radius)
{
	Matrix tmp1, tmp2;

	// translate to 'light space' ... this time with rotation
	tmp1 = lightWorldMatrix;
	tmp1.InvertRotationMatrix();

	// create proper scaling matrix
	float invrad = 0.5f / radius;

	tmp2.Identity();
	tmp2(0,0) = invrad;
	tmp2(1,1) = invrad;
	tmp2(2,2) = invrad;

	Identity ();
	Translation (Vector3f(0.5f, 0.5f, 0.5f));

	*this *= tmp2 * tmp1;
}

void Matrix::CalcInfiniteProjection(float width, float height, float fov, float zNear)
{
	const float halfWidth	= zNear * (float)tan(gDegToRad(fov*0.5f));
	const float halfHeight	= halfWidth * (height/width);

	CalcInfiniteFrustum(-halfWidth, halfWidth, -halfHeight, halfHeight, zNear);
}

void Matrix::CalcInfiniteFrustum(float left, float right, float bottom, float top, float zNear)
{
	Identity();

	El(0,0) = (2*zNear) / (right - left);
	El(0,2) = (right + left) / (right - left);

	El(1,1) = (2*zNear) / (top - bottom);
	El(1,2) = (top + bottom) / (top - bottom);

    // nudge infinity in just slightly for lsb slop
    const float nudge = 1 - 1.0 / (1<<23);

	El(2,2) = -1  * nudge;
	El(2,3) = -2*zNear * nudge;

	El(3,2) = -1;
	El(3,3) = 0;
}

void Matrix::CalcSpotLight(const Matrix &lightWorldTransform, float fov, float width, float height, float zNear)
{
	Matrix scale, proj, space;
	Vector3f halfVector(0.5f, 0.5f, 0.5f);

	Identity ();
	Translation (halfVector);

	scale.Identity ();
	scale.Scale (halfVector);

	// create projection matrix
	proj.CalcInfiniteProjection(width, height, fov, zNear);

	space = lightWorldTransform;
	space.InvertRotationMatrix();

	// so, we transform first into light space, then project, then scale and
	// translate (this)
	*this *= scale * proj * space;
}

bool Matrix::IsEqual(const Matrix& matrix) const
{
	for (int i=0; i<16; ++i)
		if (matrix.m[i] != m[i]) return false;

	return true;
}

void Matrix::InvertMatrix()
{
  float x00, x01, x02;
  float x10, x11, x12;
  float x20, x21, x22;
  float x30, x31, x32;
  float rcp;
  float y01, y02, y03, y12, y13, y23;
  float z02, z03, z12, z13, z22, z23, z32, z33;

#define x03 x01
#define x13 x11
#define x23 x21
#define x33 x31
#define z00 x02
#define z10 x12
#define z20 x22
#define z30 x32
#define z01 x03
#define z11 x13
#define z21 x23
#define z31 x33

  /* read 1st two columns of matrix into registers */
  // col, row
  x00 = El(0,0); // src.xx
  x01 = El(0,1); // src.xy; 2nd column
  x10 = El(1,0); // src.yx; 1st column
  x11 = El(1,1); // src.yy; 2nd column
  x20 = El(2,0); // src.zx; 1st column
  x21 = El(2,1); // src.zy; 2nd column
  x30 = El(3,0); // src.wx; 1st column
  x31 = El(3,1); // src.wy; 2nd column

  /* compute all six 2x2 determinants of 1st two columns */
  y01 = x00*x11 - x10*x01;
  y02 = x00*x21 - x20*x01;
  y03 = x00*x31 - x30*x01;
  y12 = x10*x21 - x20*x11;
  y13 = x10*x31 - x30*x11;
  y23 = x20*x31 - x30*x21;

  /* read 2nd two columns of matrix into registers */
  x02 = El(0,2);// src.xz;
  x03 = El(0,3);// src.xw;
  x12 = El(1,2);// src.yz;
  x13 = El(1,3);// src.yw;
  x22 = El(2,2);// src.zz;
  x23 = El(2,3);// src.zw;
  x32 = El(3,2);// src.wz;
  x33 = El(3,3);// src.ww;

  /* compute all 3x3 cofactOMLs for 2nd two columns */
  z33 = x02*y12 - x12*y02 + x22*y01;
  z23 = x12*y03 - x32*y01 - x02*y13;
  z13 = x02*y23 - x22*y03 + x32*y02;
  z03 = x22*y13 - x32*y12 - x12*y23;
  z32 = x13*y02 - x23*y01 - x03*y12;
  z22 = x03*y13 - x13*y03 + x33*y01;
  z12 = x23*y03 - x33*y02 - x03*y23;
  z02 = x13*y23 - x23*y13 + x33*y12;

  /* compute all six 2x2 determinants of 2nd two columns */
  y01 = x02*x13 - x12*x03;
  y02 = x02*x23 - x22*x03;
  y03 = x02*x33 - x32*x03;
  y12 = x12*x23 - x22*x13;
  y13 = x12*x33 - x32*x13;
  y23 = x22*x33 - x32*x23;

  /* read 1st two columns of matrix into registers */
  x00 = El(0,0);// src.xx
  x01 = El(0,1);// src.xy
  x10 = El(1,0);// src.yx
  x11 = El(1,1);// src.yy
  x20 = El(2,0);// src.zx
  x21 = El(2,1);// src.zy
  x30 = El(3,0);// src.wx
  x31 = El(3,1);// src.wy

  /* compute all 3x3 cofactOMLs for 1st column */
  z30 = x11*y02 - x21*y01 - x01*y12;
  z20 = x01*y13 - x11*y03 + x31*y01;
  z10 = x21*y03 - x31*y02 - x01*y23;
  z00 = x11*y23 - x21*y13 + x31*y12;

  /* compute 4x4 determinant & its reciprocal */
  rcp = x30*z30 + x20*z20 + x10*z10 + x00*z00;
  if (rcp == 0.0f)
    {
      /* the matrix can't be inverted */
      return;
    }

  rcp = 1.0f/rcp;

  /* compute all 3x3 cofactOMLs for 2nd column */
  z31 = x00*y12 - x10*y02 + x20*y01;
  z21 = x10*y03 - x30*y01 - x00*y13;
  z11 = x00*y23 - x20*y03 + x30*y02;
  z01 = x20*y13 - x30*y12 - x10*y23;

  Matrix invert;

  /* multiply all 3x3 cofactOMLs by reciprocal */
  /* inverse.xx */ invert(0,0) = (z00*rcp);
  /* inverse.yx */ invert(1,0) = (z01*rcp);
  /* inverse.xy */ invert(0,1) = (z10*rcp);
  /* inverse.zx */ invert(2,0) = (z02*rcp);
  /* inverse.xz */ invert(0,2) = (z20*rcp);
  /* inverse.wx */ invert(3,0) = (z03*rcp);
  /* inverse.xw */ invert(0,3) = (z30*rcp);
  /* inverse.yy */ invert(1,1) = (z11*rcp);
  /* inverse.zy */ invert(2,1) = (z12*rcp);
  /* inverse.yz */ invert(1,2) = (z21*rcp);
  /* inverse.wy */ invert(3,1) = (z13*rcp);
  /* inverse.yw */ invert(1,3) = (z31*rcp);
  /* inverse.zz */ invert(2,2) = (z22*rcp);
  /* inverse.wz */ invert(3,2) = (z23*rcp);
  /* inverse.zw */ invert(2,3) = (z32*rcp);
  /* inverse.ww */ invert(3,3) = (z33*rcp);

  (*this) = invert;

#undef x03
#undef x13
#undef x23
#undef x33
#undef z00
#undef z10
#undef z20
#undef z30
#undef z01
#undef z11
#undef z21
#undef z31
}

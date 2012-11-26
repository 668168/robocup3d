/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Vector.h"

#include "../salt/tvector.h"
#include "../salt/matrix.h"
#include "../salt/gmath.h"





inline salt::Vector2f MakeVector2f(const salt::Vector3f& v)
{
    return salt::Vector2f(v.x(), v.y());
}

inline salt::Vector2f MakeVector2f(float angleDeg)
{
    return salt::Vector2f(salt::gCos(salt::gDegToRad(angleDeg)),
                          salt::gSin(salt::gDegToRad(angleDeg)));
}

inline float Precision(float value, float remain = 3.0f)
{
    float tmp = salt::gPow(10.0f, remain);
    return int(value * tmp) / tmp;
}

inline float Constrain(float value, float min, float max)
{
    return std::min(max, std::max(min, value));
}

bool            IsRi(const salt::Matrix& R);

bool            InverseMatrix(salt::Matrix& m);

salt::Vector3f  RotToOmega(const salt::Matrix& R);

salt::Matrix    RotationMatrixFrom2Vec(salt::Vector3f from, salt::Vector3f to);

salt::Matrix    Rodrigues(const salt::Vector3f& axis, float theta);

float   Cross(const salt::Vector2f& O, const salt::Vector2f& end1, const salt::Vector2f& end2);

float   Dot  (const salt::Vector2f& O, const salt::Vector2f& end1, const salt::Vector2f& end2);

float   DistanceToLine(const salt::Vector2f& p, const salt::Vector2f& lineStart,
                       const salt::Vector2f& lineEnd, salt::Vector2f& proj);

float   getProjectionDistance(const salt::Vector2f& p, const salt::Vector2f& lineStart,
                              const salt::Vector2f& lineEnd);

bool    IsObjectInTheWay(const salt::Vector2f& objectPos, const salt::Vector2f& lineStart,
                         const salt::Vector2f& lineEnd, float radius);

float   getVector2fAngleDeg(const salt::Vector2f &v);

float   getMatrixRotateXRad(const salt::Matrix &m);

float   getMatrixRotateYRad(const salt::Matrix &m);

float   getMatrixRotateZRad(const salt::Matrix &m);

bool    svd(float* X, const float** A, const float* B, int M, int N);
///appolo




namespace Geometry
{
	extern Vector rotate(Vector, float, Vector = Vector(.0f, .0f, .0f));
	extern std::pair<Vector, Vector> getTangentPoint(Vector, float, Vector);
};

#endif // GEOMETRY_H

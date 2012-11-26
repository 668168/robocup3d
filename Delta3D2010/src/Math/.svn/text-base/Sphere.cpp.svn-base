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


#include "Sphere.h"
#include "Mathematics.h"

Sphere::Sphere(const Vector &center, float radius): mCenter(center), mRadius(radius)
{
}

const Vector &Sphere::center() const
{
	return mCenter;
}

float Sphere::radius() const
{
	return mRadius;
}

void Sphere::setCenter(const Vector &center)
{
	mCenter = center;
}

void Sphere::setRadius(float radius)
{
	mRadius = radius;
}

bool Sphere::includes(const Vector &point) const
{
	return (point - mCenter).length() - mRadius < EPS;
}
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


#include "Vector.h"
#include "Mathematics.h"
#include <cmath>
#include <cstdio>
using namespace std;

using namespace Mathematics;
//using namespace Delta;

Vector::Vector(double a, double b, double c, CoordSystem sys) 
{
	switch (sys)
	{
	case CARTESIAN:
		mX = a;
		mY = b;
		mZ = c;
		break;
	case POLAR:
		{
			double r;
			r = a * cos(c);
			mX = r * cos(b);
			mY = r * sin(b);
			mZ = a * sin(c);
		}
		break;
	case DPOLAR:
		{
			double r;
			r = a * cos(c / 180 * M_PI);
			mX = r * cos(b / 180 * M_PI);
			mY = r * sin(b / 180 * M_PI);
			mZ = a * sin(c / 180 * M_PI);
		}
		break;
	}
}

	
Vector::Vector(const Vector& cpy)
{	
	mX = cpy.getX();
	mY = cpy.getY();
	mZ = cpy.getZ();
}

double Vector::length() const
{
	return sqrt(mX * mX + mY * mY + mZ * mZ);
}

double Vector::length2d() const
{
	return sqrt(mX * mX + mY * mY);
}

double Vector::theta() const
{
	return normalizeAngle(atan2(mY, mX));
}

double Vector::phi() const
{
	double r = sqrt(mX * mX + mY * mY);
	if (r < EPS)
		return mZ > 0 ? M_PI_2 : -M_PI_2;
	return normalizeAngle(atan(mZ / r));
}

Vector Vector::normalize() const
{
	double len = length();
	if (len == 0)
		return Vector(0, 0, 0);
	else
		return (*this) / len;
}

void Vector::setLength(double newLen)
{
	double len = length();
	if (len == 0)
		mX = mY = mZ = 0;
	else
		(*this) = (*this) / len * newLen;
}

Vector Vector::make2d() const
{
	return Vector(mX, mY, 0);
}

Vector& Vector::operator=(const Vector& cpy)
{
	mX = cpy.getX();
	mY = cpy.getY();
	mZ = cpy.getZ();
	return *this;
}

Vector& Vector::operator+=(const Vector& v)
{
	mX += v.getX();
	mY += v.getY();
	mZ += v.getZ();
	return *this;
}

Vector& Vector::operator-=(const Vector& v)
{
	mX -= v.getX();
	mY -= v.getY();
	mZ -= v.getZ();
	return *this;
}

Vector& Vector::operator*=(double c)
{
	mX *= c;
	mY *= c;
	mZ *= c;
	return *this;
}

Vector& Vector::operator/=(double c)
{
	//ASSERT(Main, c != 0);
	mX /= c;
	mY /= c;
	mZ /= c;
	return *this;
}

Vector Vector::operator-() const
{
	return Vector(-mX, -mY, -mZ);
}

Vector& Vector::operator^=(const Vector& cpy)
{
	*this = Vector(mX * cpy.getZ() - mZ * cpy.getY(), mZ * cpy.getX() - mX * cpy.getZ(),
			mX * cpy.getY() - mY * cpy.getX());
	return *this;
}

bool operator==(const Vector& v1, const Vector& v2)
{
	if (v1.getX() == v2.getX() && v1.getY() == v1.getY() && v1.getZ() == v2.getZ())
		return true;
	else
		return false;
}

bool operator!=(const Vector& v1, const Vector& v2)
{
	if (v1.getX() != v2.getX() || v1.getY() != v1.getY() || v1.getZ() != v2.getZ())
		return true;
	else
		return false;
}

Vector operator+(const Vector& v1, const Vector& v2)
{
	return Vector(v1.getX() + v2.getX(), v1.getY() + v2.getY(), v1.getZ() + v2.getZ());
}

Vector operator-(const Vector& v1, const Vector& v2)
{
	return Vector(v1.getX() - v2.getX(), v1.getY() - v2.getY(), v1.getZ() - v2.getZ());
}

Vector operator*(double c, const Vector& v)
{
	return Vector(c * v.getX(), c * v.getY(), c * v.getZ());
}

Vector operator*(const Vector& v, double c)
{
	return Vector(c * v.getX(), c * v.getY(), c * v.getZ());
}

Vector operator/(const Vector& v, double c)
{
	//ASSERT(Main, c != 0);
	return Vector(v.getX() / c, v.getY() / c, v.getZ() / c);
}


double operator*(const Vector& v1, const Vector& v2)
{
	return v1.getX() * v2.getX() + v1.getY() * v2.getY() + v1.getZ() * v2.getZ();
}

Vector operator^(const Vector& v1, const Vector& v2)
{
	return Vector(v1.getY() * v2.getZ() - v1.getZ() * v2.getY(), v1.getZ() * v2.getX() - v1.getX() * v2.getZ(),
			v1.getX() * v2.getY() - v1.getY() * v2.getX());
}

ostream& operator<<(ostream& stream, const Vector& vector)
{
	char s[1024];
	sprintf(s, "%2.2f", vector.getX());
	//stream << "(" << setw(6) << setfill(' ') << s;
	sprintf(s, "%2.2f", vector.getY());
	//stream << "," << setw(6) << setfill(' ') << s;
	sprintf(s, "%2.2f", vector.getZ());
	//stream << "," << setw(6) << setfill(' ') << s << ")";
	return stream;
}

double Vector::getX() const
{
	return mX;
}

double Vector::getY() const
{
	return mY;
}

double Vector::getZ() const
{
	return mZ;
}

void Vector::setX(double x)
{
	mX = x;
}

void Vector::setY(double y)
{
	mY = y;
}

void Vector::setZ(double z)
{
	mZ = z;
}

double Vector::getDistanceTo(Vector SecondPoint)
{
	Vector Between = SecondPoint - (*this);
	return Between.length();
}

//faseleye 2d entehaye do bordar ra barmigardanad
double Vector::getDistance2D(const Vector &v) const
{
	double x1=v.getX(), x2=(*this).getX();
	float y1=v.getY(), y2=(*this).getY();
	return sqrt( (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) ); 

}



Vector Vector::operator~()
{
	return Vector(mX, mY, 0);
}

Vector Vector::operator&()
{
	return Vector(1.0f / mX, 1.0f / mY, 1.0f / mZ);
}
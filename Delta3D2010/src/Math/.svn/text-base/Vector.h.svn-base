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

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>
#include "Mathematics.h"
#include <string>
#include <sstream>
#include <cstdarg>

// Geometry types
enum CoordSystem
{
    CARTESIAN,
    POLAR,
    DPOLAR,
};

struct Vector
{
protected:
    float mX, mY, mZ;

public:
    Vector(double = 0.0, double = 0.0, double = 0.0, CoordSystem = CARTESIAN);
    Vector(const Vector&);
    //virtual ~Vector();

    double length() const;
    double length2d() const;
    double theta() const;
    double phi() const;
    Vector make2d() const;

    double getX() const;
    double getY() const;
    double getZ() const;
    void setX(double);
    void setY(double);
    void setZ(double);

    Vector& operator=(const Vector&);
    Vector& operator+=(const Vector&);
    Vector& operator-=(const Vector&);
    Vector& operator*=(double);
    Vector& operator/=(double);
    Vector  operator-() const;
    Vector& operator^=(const Vector&);

    Vector  operator~();
    Vector  operator&();
    Vector  normalize() const;

    void setLength(double);
    double getDistanceTo(Vector);
    double getDistance2D(const Vector& ) const;
};

    bool operator==(const Vector&, const Vector&);
    bool operator!=(const Vector&, const Vector&);
    Vector operator+(const Vector&, const Vector&);
    Vector operator-(const Vector&, const Vector&);
    Vector operator*(double, const Vector&);
    Vector operator*(const Vector&, double);
    Vector operator/(const Vector&, double);
    double operator*(const Vector&, const Vector&);
    Vector operator^(const Vector&, const Vector&);
    std::ostream& operator<<(std::ostream&, const Vector&);

#endif // VECTOR_H

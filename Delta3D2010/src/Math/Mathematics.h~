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

#ifndef MATHEMATICS_H
#define MATHEMATICS_H

//#include <Debugger.h>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <cstdarg>

#define RTD (180.0f / float(M_PI))
#define DTR (float(M_PI) / 180.0f)
#define pow2(x) ((x) * (x))
#define EPS 1e-4f
#define EPSILON 0.0001  /*!< Value used for floating point equality tests. */
#define sqr(x) x*x
class Vector;

namespace Mathematics
{
	extern signed sign(float);

	extern float normalizeAngle(float);
	extern float absoluteAngle(float);

	extern bool isInBetween(float, float, float = 0.25);
	extern bool isInRange(float, float, float);
	extern float toRange(float, float, float, float, float);
	extern std::string toBase(std::string, std::map<char, unsigned>,
		std::map<unsigned, char>);
	extern std::string encrypt(std::map<char, unsigned>,
		std::map<unsigned, char>, std::vector<std::pair<float,
		std::pair<float, std::pair<float, float> > > >&);
	extern std::vector<float> decrypt(std::map<char, unsigned>,
		std::map<unsigned, char>, std::vector<std::pair<float,
		std::pair<float, float> > >, std::string, unsigned&);
	extern std::pair<float, std::map<unsigned, unsigned> >
		findMatchOfObjectsByGreedyAlgorithm(
		std::vector<std::pair<unsigned, Vector> >, std::vector<std::pair<unsigned, Vector> >);


	typedef double AngRad;  /*!< Type definition for angles in degrees. */
	typedef double AngDeg;  /*!< Type definition for angles in radians. */
      // auxiliary goniometric functions which enable you to
	// specify angles in degrees rather than in radians
	AngDeg Rad2Deg ( AngRad x             );
	AngRad Deg2Rad ( AngDeg x             );
	double cosDeg  ( AngDeg x             );
	double sinDeg  ( AngDeg x             );
	double tanDeg  ( AngDeg x             );
	AngDeg atanDeg ( double x             );
	double atan2Deg( double x,  double y  );
	AngDeg acosDeg ( double x             );
	AngDeg asinDeg ( double x             );
	
	double degNormalizeAngle(double angle);

};
#endif // MATHEMATICS_H

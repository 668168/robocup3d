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


#include "Mathematics.h"
#include "Vector.h"
#include "Str.h"

using namespace std;
using namespace Mathematics;
#define LOGLEVEL -1

signed Mathematics::sign(float f)
{
	return f > .0f ? 1 : -1;
}

float Mathematics::normalizeAngle(float angle)
{
	while (angle < -M_PI) angle += 2 * M_PI;
	while (angle > M_PI) angle -= 2 * M_PI;
	return angle;
}

double Mathematics::degNormalizeAngle(double angle)
{
  while(angle > 180) angle -=360;
  while(angle < -180) angle +=360;
  return angle;
}



float Mathematics::absoluteAngle(float angle)
{
	while (angle < 0) angle += 2 * M_PI;
	while (angle >= M_PI) angle -= 2 * M_PI;
	return angle;
}

bool Mathematics::isInBetween(float f, float fp, float dt)
{
	return isInRange(f, fp - dt, fp + dt);
}

bool Mathematics::isInRange(float f, float f1, float f2)
{
	return min(f1, f2) <= f && f <= max(f1, f2);
}

float Mathematics::toRange(float f, float fDown, float fUp, float tDown, float tUp)
{
	if (f <= fDown)
		return tDown;
	else if (f >= fUp)
		return tUp;
	else
		return (f - fDown) / (fUp - fDown) * (tUp - tDown) + tDown;
}

string Mathematics::toBase(string num, map<char, unsigned> fChars, map <unsigned, char> tChars)
{
	unsigned number(0), counter(0);
	for (string::reverse_iterator i = num.rbegin(); i != num.rend(); i++)
	{
		number += fChars.find(*i)->second * unsigned(pow(float(fChars.size()),
				int(counter++)));
	}
	ostringstream convertedString;
	if (!number)
		convertedString << tChars.begin()->first;
	else
		for (int i = int(floor(log(number) / log(tChars.size()))); i >= 0; i--)
		{
			convertedString <<
					tChars[number / unsigned(pow(float(tChars.size()), i))];
			number = number % unsigned(pow(float(tChars.size()), i));
		}
	return convertedString.str();
}

string Mathematics::encrypt(map<char, unsigned> fChars, map<unsigned, char> tChars,
		vector<pair<float, pair<float, pair<float, float> > > >& datas)
{
	ostringstream str;
	long long unsigned number(0);
	long long unsigned states(1);
	for (vector<pair<float, pair<float, pair<float, float> > > >::iterator i =
		datas.begin(); i != datas.end(); i++)
	{
		float begin(i->second.second.first), end(i->second.second.second),
			length(end - begin), step(i->second.first);
		unsigned statesCount(unsigned(floor(length / step)) + 1);
		number *= statesCount;
		number += int(round(toRange(i->first, begin, end, .0f, length / step)));
		states *= statesCount;
	}
	ostringstream tmpStr;
	tmpStr << number;
//	string data(toBase(tmpStr.str(), fChars, tChars));
//	str << setw(int(floor(log(states - 1) / log(tChars.size()) + 1))) <
//		setfill(tChars[0]) << data;
	return str.str();
}

vector<float> Mathematics::decrypt(map<char, unsigned> fChars, map<unsigned, char> tChars,
	vector<pair<float, pair<float, float> > > datas, string str, unsigned& pos)
{
	long long unsigned states(1);
	for (vector<pair<float, pair<float, float> > >::iterator i =
		datas.begin(); i != datas.end(); i++)
	{
		float begin(i->second.first), end(i->second.second), length(end - begin),
			step(i->first);
		unsigned statesCount(unsigned(floor(length / step)) + 1);
		states *= statesCount;
	}
	string data(str.substr(pos, int(floor(log(states - 1) / log(fChars.size()) + 1))));
	pos += int(floor(log(states - 1) / log(fChars.size()) + 1));
	string s;
	for (unsigned i = 0; i < unsigned(floor(log(states - 1) / log(fChars.size()) + 1)); i++)
		s += '1';
	if (data == s)
	{
		vector<float> d;
		d.push_back(1000000.0f);
		return d;
	}
	string tmpStr(toBase(data, fChars, tChars));
	unsigned decryptedNumber(Str(tmpStr).as<unsigned>());
	map<unsigned, float> numbers;
	unsigned counter(datas.size());
	for (vector<pair<float, pair<float, float> > >::reverse_iterator i =
			datas.rbegin(); i != datas.rend(); i++)
	{
		float begin(i->second.first), end(i->second.second), length(end - begin), step(i->first);
		unsigned statesCount(unsigned(floor(length / step)) + 1);
		unsigned n(decryptedNumber % statesCount);
		decryptedNumber /= statesCount;
		numbers[--counter] = toRange(float(n), .0f, length / step, begin, end);
	}
	vector<float> decryptedDatas;
	for (map<unsigned, float>::iterator i = numbers.begin(); i != numbers.end(); i++)
		decryptedDatas.push_back(i->second);
	return decryptedDatas;
}





/*! This function converts an angle in radians to the corresponding angle in
    degrees.
    \param x an angle in radians
    \return the corresponding angle in degrees */
AngDeg Mathematics::Rad2Deg( AngRad x )
{
  return ( x * 180 / M_PI );
}

/*! This function converts an angle in degrees to the corresponding angle in
    radians.
    \param x an angle in degrees
    \return the corresponding angle in radians */
AngRad Mathematics::Deg2Rad( AngDeg x )
{
  return ( x * M_PI / 180 );
}

/*! This function returns the cosine of a given angle in degrees using the
    built-in cosine function that works with angles in radians.
    \param x an angle in degrees
    \return the cosine of the given angle */
double Mathematics::cosDeg( AngDeg x )
{
  return ( cos( Deg2Rad( x ) ) );
}

/*! This function returns the sine of a given angle in degrees using the
    built-in sine function that works with angles in radians.
    \param x an angle in degrees
    \return the sine of the given angle */
double Mathematics::sinDeg( AngDeg x )
{
  return ( sin( Deg2Rad( x ) ) );
}

/*! This function returns the tangent of a given angle in degrees using the
    built-in tangent function that works with angles in radians.
    \param x an angle in degrees
    \return the tangent of the given angle */
double Mathematics::tanDeg( AngDeg x )
{
  return ( tan( Deg2Rad( x ) ) );
}

/*! This function returns the principal value of the arc tangent of x in degrees
    using the built-in arc tangent function which returns this value in radians.
    \param x a double value
    \return the arc tangent of the given value in degrees */
AngDeg Mathematics::atanDeg( double x )
{
  return ( Rad2Deg( atan( x ) ) );
}

/*! This function returns the principal value of the arc tangent of y/x in
    degrees using the signs of both arguments to determine the quadrant of the
    return value. For this the built-in 'atan2' function is used which returns
    this value in radians.
    \param x a double value
    \param y a double value
    \return the arc tangent of y/x in degrees taking the signs of x and y into
    account */
double Mathematics::atan2Deg( double x, double y )
{
  if( fabs( x ) < EPSILON && fabs( y ) < EPSILON )
    return ( 0.0 );

  return ( Rad2Deg( atan2( x, y ) ) );
}

/*! This function returns the principal value of the arc cosine of x in degrees
    using the built-in arc cosine function which returns this value in radians.
    \param x a double value
    \return the arc cosine of the given value in degrees */
AngDeg Mathematics::acosDeg( double x )
{
  if( x >= 1 )
    return ( 0.0 );
  else if( x <= -1 )
    return ( 180.0 );

  return ( Rad2Deg( acos( x ) ) );
}

/*! This function returns the principal value of the arc sine of x in degrees
    using the built-in arc sine function which returns this value in radians.
    \param x a double value
    \return the arc sine of the given value in degrees */
AngDeg Mathematics::asinDeg( double x )
{
  if( x >= 1 )
    return ( 90.0 );
  else if ( x <= -1 )
    return ( -90.0 );

  return ( Rad2Deg( asin( x ) ) );
}







pair<float, map<unsigned, unsigned> > Mathematics::findMatchOfObjectsByGreedyAlgorithm(	vector<pair<unsigned, Vector> > up, vector<pair<unsigned, Vector> > down)
{	pair<float, map<unsigned, unsigned> > best;
	best.first = -1.0f;
	if (up.size() > down.size())
		for (vector<pair<unsigned, Vector> >::iterator i = up.begin();
			i != up.end(); i++)
		{
			vector<pair<unsigned, Vector> > newUp(up);
			for (vector<pair<unsigned, Vector> >::iterator j = newUp.begin();
					j != newUp.end(); j++)
				if (j->first == i->first)
				{
					newUp.erase(j);
					break;
				}
			pair<float, map<unsigned, unsigned> > current(
					findMatchOfObjectsByGreedyAlgorithm(newUp, down));
			if (best.first < .0f || current.first <= best.first)
				best = current;
		}
	else if (up.size() < down.size())
		for (vector<pair<unsigned, Vector> >::iterator i = down.begin();
				i != down.end(); i++)
		{
			vector<pair<unsigned, Vector> > newDown(down);
			for (vector<pair<unsigned, Vector> >::iterator j = newDown.begin();
					j != newDown.end(); j++)
				if (j->first == i->first)
				{
					newDown.erase(j);
					break;
				}
			pair<float, map<unsigned, unsigned> > current(
					findMatchOfObjectsByGreedyAlgorithm(up, newDown));
//			LOG(Main, 1) << best.first << " " << current.first << std::endl;
			if (best.first < .0f || current.first <= best.first)
				best = current;
		}
	else if (up.size() == down.size())
	{
		map<unsigned, map<unsigned, float> > upGraph;
		map<unsigned, map<unsigned, float> > downGraph;
		map<unsigned, unsigned> match;
		float price(.0f);
		for (vector<pair<unsigned, Vector> >::iterator i = up.begin();
				i != up.end(); i++)
			for (vector<pair<unsigned, Vector> >::iterator j = down.begin();
					j != down.end(); j++)
			{
//				LOG(Main, 1) << i->first << " " << j->first << std::endl;
				upGraph[i->first][j->first] = (i->second - j->second).length();
				downGraph[j->first][i->first] = (i->second - j->second).length();
			}
		while(upGraph.size() && downGraph.size())
		{
//			LOG(Main, 1) << "Size: " << upGraph.size() << " " << downGraph.size() << std::endl;
			pair<float, pair<unsigned, unsigned> >
					maxConnector(.0f, make_pair(0u, 0u));
			for (map<unsigned, map<unsigned, float> >::iterator
					i = upGraph.begin(); i != upGraph.end(); i++)
				if (i->second.size() != 1)
					for (map<unsigned, float>::iterator j = i->second.begin();
							j != i->second.end(); j++)
						if (downGraph.find(j->first)->second.size() != 1)
							if (maxConnector.second.first == 0u ||
									maxConnector.second.second == 0u ||
									j->second > maxConnector.first)
								maxConnector = make_pair(j->second, make_pair(i->first,
										j->first));
			if (maxConnector.second.first != 0 &&
					maxConnector.second.second != 0)
			{
				//LOG(Main, 1) << "sc " << maxConnector.second.first << " " << maxConnector.second.second << std::endl;
				upGraph[maxConnector.second.first].erase(
						upGraph[maxConnector.second.first].find(
						maxConnector.second.second));
				downGraph[maxConnector.second.second].erase(
						downGraph[maxConnector.second.second].find(
						maxConnector.second.first));
			}
			bool deleted(true);
			while(deleted)
			{
				deleted = false;
				for (map<unsigned, map<unsigned, float> >::iterator
						i = upGraph.begin(); i != upGraph.end(); i++)
					if (i->second.size() == 1)
					{
						//LOG(Main, 1) << "ud " << i->first << " " << i->second.begin()->first << std::endl;
						//LOG(Main, 1) << "ud " << i->second.size() << std::endl;
						match[i->first] = i->second.begin()->first;
						price += i->second.begin()->second;
						for (map<unsigned, float>::iterator
								j = downGraph[i->second.begin()->first].begin();
								j != downGraph[i->second.begin()->first].end(); j++)
							if (upGraph.find(j->first) != i)
								upGraph[j->first].erase(upGraph[j->first].find(i->second.begin()->first));
						downGraph.erase(downGraph.find(i->second.begin()->first));
						upGraph.erase(i);
						deleted = true;
						break;
					}
			}
			deleted = true;
			while(deleted)
			{
				deleted = false;
				for (map<unsigned, map<unsigned, float> >::iterator
						i = downGraph.begin(); i != downGraph.end(); i++)
					if (i->second.size() == 1)
					{
						//LOG(Main, 1) << "dd " << i->first << " " << i->second.begin()->first << std::endl;
						//LOG(Main, 1) << "dd " << i->second.size() << std::endl;
						match[i->second.begin()->first] = i->first;
						price += i->second.begin()->second;
						for (map<unsigned, float>::iterator
								j = upGraph[i->second.begin()->first].begin();
								j != upGraph[i->second.begin()->first].end(); j++)
							if (downGraph.find(j->first) != i)
								downGraph[j->first].erase(downGraph[j->first].find(i->second.begin()->first));
						upGraph.erase(upGraph.find(i->second.begin()->first));
						downGraph.erase(i);
						deleted = true;
						break;
					}
			}
		}
		best = make_pair(price, match);
	}
	return best;
}
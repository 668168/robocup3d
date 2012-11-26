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

#ifndef STR_H
#define STR_H

#include <string>
#include <vector>
//#include <Debugger.h>
#include "Vector.h"
#include "../Utility/Types.h"
#include <stdlib.h>

class Str
{
protected:
	std::string stringVal;

public:
	template <class _T>
	Str(const _T &value)
	{
		std::ostringstream ss;
		ss << value;
		stringVal = ss.str();
	}

	template <class _T, class _U>
	Str(const std::pair<_T, _U> &value)
	{
		std::ostringstream ss;
		ss << value.first << "," << value.second;
		stringVal = ss.str();
	}

	template <class _T>
	Str(const std::vector<_T> &value)
	{
		std::ostringstream ss;
		for (unsigned it = 0; it < value.size(); it++)
			ss << value[it] << "|";
		stringVal = ss.str();
	}

	template <class _T, class _U>
	Str(const std::map<_T, _U> &value)
	{
		std::ostringstream ss;
		for (unsigned it = 0; it < value.size(); it++)
			ss << value[it].first << ", " << value[it].second << "| ";
		stringVal = ss.str();
	}

	Str(const Vector &value);
	virtual ~Str()
	{
	}
/*
	template<typename _Tp, typename _T, typename _U>
	operator _Tp() const
	{
		if (sameType<_Tp, int>() ||
			sameType<_Tp, bool>() ||
			sameType<_Tp, char>() ||
			sameType<_Tp, unsigned>() ||
			sameType<_Tp, float>() ||
			sameType<_Tp, double>() ||
			sameType<_Tp, std::string>() ||
			sameType<_Tp, std::pair<_T, _U> >() ||
			sameType<_Tp, std::vector<_T> >() ||
			sameType<_Tp, std::map<_T, _U> >() ||
			sameType<_Tp, Vector>())
			return this->as<_Tp>();
		else
			return _Tp();
	}
*/
	template <class _T>
	_T as() const
	{
//		_T s =0;// _T();
//		return value(s);
	}

	template <class _T, class _U>
	std::pair<_T, _U> value(std::pair<_T, _U>) const
	{
		if (stringVal.find(",") != std::string::npos)
			return make_pair(Str(stringVal.substr(0, stringVal.find(","))).as<_T>(),
					Str(stringVal.substr(stringVal.find(",") + 1, stringVal.size() -
					stringVal.find(",") - 1)).as<_U>());
		else
			//ASSERT(MAIN, false);
		_T s1 = 0;//_T();
		_U s2 = _U();
		return std::make_pair(s2, s2);
	}

	template <class _T>
	std::vector<_T> value(std::vector<_T>) const
	{
		std::vector<_T> vectorVal;
		std::string ss(stringVal);
		if (stringVal.find("|") < stringVal.size())
			while (ss.size() > 0)
			{
				vectorVal.push_back(Str(ss.substr(0, ss.find("|"))).as<_T>());
				ss = ss.substr(ss.find("|") + 1, ss.size() - ss.find("|") - 1);
			}
		return vectorVal;
	}

	template <class _T, class _U>
	std::map<_T, _U> value(std::map<_T, _U>) const
	{
		std::map<_T, _U> mapVal;
		std::string ss(stringVal);
		if (stringVal.find("|") < stringVal.size())
			while (ss.size() > 0)
			{
				std::pair<_T, _U> s =
						Str(ss.substr(0, ss.find("|"))).as<std::pair<_T, _U> >();
				mapVal[s.first] = s.second;
				ss = ss.substr(ss.find("|") + 1, ss.size() - ss.find("|") - 1);
			}
		return mapVal;
	}

	std::string value(std::string) const;
	char value(char) const;
	bool value(bool) const;
	int value(int) const;
	unsigned int value(unsigned int) const;
	float  value(float)  const;
	double value(double) const;
	Vector value(Vector) const;
};


#endif // STR_H

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


#include "Str.h"
#include <sstream>

using namespace std;

Str::Str(const Vector &value)
{
	vector<float> values(3);
	values.push_back(value.getX());
	values.push_back(value.getY());
	values.push_back(value.getZ());
	stringVal = Str(values).as<string>();
}

string Str::value(string) const
{
	return stringVal;
}

char Str::value(char) const
{
	return stringVal[0];
}

bool Str::value(bool) const
{
	string tmp;
	tmp.reserve(stringVal.length());
	for (string::const_iterator it = stringVal.begin(); it != stringVal.end(); it++)
		tmp += tolower(*it);
	return tmp == "true" || tmp == "1";
}

int Str::value(int) const
{
	char *end;
	int val = strtol(stringVal.c_str(), &end, 10);
	return val;
}

unsigned int Str::value(unsigned int) const
{
	char *end;
	unsigned val = (unsigned)strtol(stringVal.c_str(), &end, 10);
	return val;
}

float Str::value(float) const
{
	char *end;
	float val = strtof(stringVal.c_str(), &end);
	if (stringVal == "nan")
		val = .0f;
	return val;
}

double Str::value(double) const
{
	char *end;
	double val = strtod(stringVal.c_str(), &end);
	return val;
}

Vector Str::value(Vector) const
{
	vector<float> values(Str(stringVal).as<vector<float> >());
	Vector val(values[0], values[1], values[2]);
	return val;
}
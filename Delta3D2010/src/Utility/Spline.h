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

#ifndef SPLINE_H
#define SPLINE_H

/** spline interpolation from book "Numerical Recipes in C"
    array [] start from 1 (not 0)
    and please make sure that m_x[1] < m_x[2] < m_x[3] < ...
*/
class Spline
{
public:
    Spline();
    ~Spline();

    Spline(float* x, float* y, int n);

    void SetBreakPoints(float* x, float* y, int n,
                        float yp1 = 0.0, float ypn = 0.0);

    bool general();

    float getYGivenX(float x, int der = 0) const;

private:
    float* m_x;

    float* m_y;

    float* m_y2;

    float m_yp1;

    float m_ypn;

    int m_n;
};


#endif // SPLINE_H

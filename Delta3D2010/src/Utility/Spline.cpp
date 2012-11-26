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

#include "Spline.h"

#include <stdio.h>

#define isnan(x) ((x) != (x))

Spline::Spline() :
    m_x(NULL),
    m_y(NULL),
    m_y2(NULL),
    m_yp1(0.0),
    m_ypn(0.0),
    m_n(0)
{
}

Spline::~Spline()
{
    delete [] m_x;
    delete [] m_y;
    delete [] m_y2;
    m_x = m_y = m_y2 = NULL;
}

Spline::Spline(float* x, float* y, int n)
{
    m_x = m_y = m_y2 = NULL;
    SetBreakPoints(x, y, n);
}

void Spline::SetBreakPoints(float* x, float* y, int n, 
                            float yp1, float ypn)
{
    delete [] m_x;
    delete [] m_y;
    delete [] m_y2;
    m_x = m_y = m_y2 = NULL;
    m_n = n;
    m_yp1 = yp1;
    m_ypn = ypn;

    m_x  = new float[m_n + 1];
    m_y  = new float[m_n + 1];
    m_y2 = new float[m_n + 1];

    for (int i = 1; i <= m_n; ++i)
    {
        m_x[i] = x[i - 1];
        m_y[i] = y[i - 1];
    }
}

bool Spline::general()
{
    int i, k;
    float p, qn, sig, un, *u;

    u = new float[m_n];
    if (m_yp1 > 0.99e30)
        m_y2[1] = u[1] = 0.0;
    else {
        m_y2[1] = -0.5;
        u[1] = (3.0 / (m_x[2] - m_x[1])) * 
            ( (m_y[2] - m_y[1]) / (m_x[2] - m_x[1]) - m_yp1);
    }

    for (i = 2; i <= m_n-1; ++i) {
        sig = (m_x[i] - m_x[i-1]) / (m_x[i+1] - m_x[i-1]);
        p = sig * m_y2[i-1] + 2.0;
        m_y2[i] = (sig - 1.0) / p;
        u[i] = (m_y[i+1] - m_y[i]) / 
            (m_x[i+1] - m_x[i]) - (m_y[i] - m_y[i-1]) / (m_x[i] - m_x[i-1]);
        u[i] = (6.0 * u[i] / (m_x[i+1] - m_x[i-1]) - sig * u[i-1]) / p;
    }
    if (m_ypn > 0.99e30)
        qn = un = 0.0;
    else {
        qn = 0.5;
        un = (3.0 / (m_x[m_n] - m_x[m_n-1])) * 
            (m_ypn - (m_y[m_n] - m_y[m_n-1]) / (m_x[m_n] - m_x[m_n-1]));
    }
    m_y2[m_n] = (un - qn * u[m_n-1]) / (qn * m_y2[m_n-1] + 1.0);
    for (k = m_n-1; k >= 1; --k) {
        m_y2[k] = m_y2[k] * m_y2[k+1] + u[k];
    }
    delete u;
    u = NULL;

    for (i = 1; i <= m_n; ++i)
    {
        if (isnan(m_y2[i])) return false;
    }

    return true;
}

float Spline::getYGivenX(float x, int der) const
{
    if (der < 0)
    {
        printf("(Spline) getYGivenX der error");
        return 0.0;
    }

    float rc = 0.0;
    int klo, khi, k;
    float h, b, a;

    klo = 1;
    khi = m_n;
    while (khi - klo > 1) {
        k = (khi + klo) >> 1;
        if (m_x[k] > x) khi = k;
        else klo = k;
    }
    h = m_x[khi] - m_x[klo];
    if (h == 0.0) printf("Bad x input to routine splint");
    a = (m_x[khi] - x) / h;
    b = (x - m_x[klo]) / h;

    if (der == 0)
    {
        rc = a * m_y[klo] + b * m_y[khi] +
             ((a*a*a - a) * m_y2[klo] + (b*b*b - b) * m_y2[khi]
             ) * (h * h) / 6.0;
    }
    else if (der == 1)
    {
        rc = (m_y[khi] - m_y[klo])/ h -
              ( (3.0 * a*a*a - 1.0) * m_y2[klo] -
                (3.0 * b*b*b - 1.0) * m_y2[khi]
              ) * h / 6.0;
    }
    else if (der == 2)
    {
        rc = a * m_y2[klo] + b * m_y2[khi];
    }

    return rc;
}
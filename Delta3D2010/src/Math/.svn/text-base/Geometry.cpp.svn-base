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


#include "Geometry.h"

#include "Line.h"
#include "Mathematics.h"

using namespace std;

using namespace salt;
 

Vector Geometry::rotate(Vector Point, float angle, Vector Center)
{
	Vector relativePoint(Point - Center);
	Vector rotatedPoint(relativePoint.length(), relativePoint.theta() + angle,
		.0f, POLAR);
	return Center + rotatedPoint;
}

pair<Vector, Vector> Geometry::getTangentPoint(Vector center, float radius,
	Vector point)
{
	Vector circleToPoint(center - point);
	float tangentLength(sqrt(circleToPoint * circleToPoint - radius * radius));
	float theta(atan2(tangentLength, radius));

	return make_pair(
			center + Vector(radius, circleToPoint.theta() + theta, .0f, POLAR),
			center + Vector(radius, circleToPoint.theta() - theta, .0f, POLAR));
}



///appolo


Matrix RotationMatrixFrom2Vec(Vector3f from, Vector3f to)
{
    Matrix m;
    m.Identity();
    from.Normalize();
    to.Normalize();

    Vector3f axis = from.Cross(to);
    float angle = gArcCos(from.Dot(to));

    float c = gCos(angle);
    float s = gSin(angle);
    float t = 1.0 - c;
    m(0, 0) = c + axis.x()*axis.x()*t;
    m(1, 1) = c + axis.y()*axis.y()*t;
    m(2, 2) = c + axis.z()*axis.z()*t;

    float tmp1 = axis.x()*axis.y()*t;
    float tmp2 = axis.z()*s;
    m(1, 0) = tmp1 + tmp2;
    m(0, 1) = tmp1 - tmp2;
    tmp1 = axis.x()*axis.z()*t;
    tmp2 = axis.y()*s;
    m(2, 0) = tmp1 - tmp2;
    m(0, 2) = tmp1 + tmp2;
    tmp1 = axis.y()*axis.z()*t;
    tmp2 = axis.x()*s;
    m(2, 1) = tmp1 + tmp2;
    m(1, 2) = tmp1 - tmp2;

    return m;
}

bool InverseMatrix(salt::Matrix& m)
{
    float det = m(0, 0) * m(1, 1) * m(2, 2) +
                m(0, 1) * m(1, 2) * m(2, 0) +
                m(0, 2) * m(1, 0) * m(2, 1) -
                m(0, 0) * m(1, 2) * m(2, 1) -
                m(0, 1) * m(1, 0) * m(2, 2) -
                m(0, 2) * m(1, 1) * m(2, 0);

    if (fabs(det) < 1e-4) return false;

    det = 1.0f / det;

    Matrix mat;
    mat.Identity();
    mat(0, 0) = (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) * det;
    mat(1, 0) = (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) * det;
    mat(2, 0) = (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0)) * det;
    mat(0, 1) = (m(0, 2) * m(2, 1) - m(0, 1) * m(2, 2)) * det;
    mat(1, 1) = (m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0)) * det;
    mat(2, 1) = (m(0, 1) * m(2, 0) - m(0, 0) * m(2, 1)) * det;
    mat(0, 2) = (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * det;
    mat(1, 2) = (m(0, 2) * m(1, 0) - m(0, 0) * m(1, 2)) * det;
    mat(2, 2) = (m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0)) * det;
    m = mat;

    return true;
}

bool IsRi(const salt::Matrix& R)
{
    float ran = 1e-3;
    if (gAbs(R(0,0) - 1.0) > ran ||
        gAbs(R(0,1)      ) > ran ||
        gAbs(R(0,2)      ) > ran ||
        gAbs(R(1,0)      ) > ran ||
        gAbs(R(1,1) - 1.0) > ran ||
        gAbs(R(1,2)      ) > ran ||
        gAbs(R(2,0)      ) > ran ||
        gAbs(R(2,1)      ) > ran ||
        gAbs(R(2,2) - 1.0) > ran
        )
    {
        return false;
    }

    return true;
}

salt::Vector3f RotToOmega(const salt::Matrix& R)
{
    Vector3f w(0, 0, 0);
    float theta = (R(0,0) + R(1,1) + R(2,2) - 1) / 2;
    float gain;

    if (! (IsRi(R) || gAbs(theta) > 1.0))
    {
        theta = gArcCos(theta);
        gain = 0.5 * theta / gSin(theta);
        w[0] = gain * (R(2,1) - R(1,2));
        w[1] = gain * (R(0,2) - R(2,0));
        w[2] = gain * (R(1,0) - R(0,1));
    }
    return w;
}

Matrix Rodrigues(const Vector3f& axis, float theta)
{
    float a = gSin(theta);
    float b = 1.0f - gCos(theta);

    Matrix x1, x2, y;
    x1.Set(       0, -axis.z(),  axis.y(), 0,
           axis.z(),         0, -axis.x(), 0,
          -axis.y(),  axis.x(),         0, 0,
                  0,         0,         0, 0
          );
    x2 = x1 * x1;

    y.Set(1.0f + a*x1(0,0) + b*x2(0,0),
                 a*x1(0,1) + b*x2(0,1),
                 a*x1(0,2) + b*x2(0,2),
                                     0,
                 a*x1(1,0) + b*x2(1,0),
          1.0f + a*x1(1,1) + b*x2(1,1),
                 a*x1(1,2) + b*x2(1,2),
                                     0,
                 a*x1(2,0) + b*x2(2,0),
                 a*x1(2,1) + b*x2(2,1),
          1.0f + a*x1(2,2) + b*x2(2,2),
                                     0,
                                     0,
                                     0,
                                     0,
                                     0
          );
    return y;
}

/*!
    \fn   Cross
    cross operator on vectors
    Basic funtion ,used by other functions in Geomotry
    You may find the formula:  x1 * y2 - x2 * y1 in linear algebra book 

    \param   O      the start point of both vectors

    \param   end1   the end point of one vector

    \param   end2   the end point of the other vector

    @Author: <Rujia Liu rujialiu@hotmail.com>
*/
float Cross(const Vector2f& O, const Vector2f& end1, const Vector2f& end2)
{
    float x1 = end1.x() - O.x();
    float x2 = end2.x() - O.x();
    float y1 = end1.y() - O.y();
    float y2 = end2.y() - O.y();

    return x1 * y2 - x2 * y1;
}

/*!
    \fn Dot

    dot operator on vectors
    Basic funtion ,used by other functions in Geomotry
    you may find the formula:  x1 * y2 + x2 * y1 in linear algebra book 

    \param   O    \ the start point of both vectors

    \param   end1 \ the end point of one vector

    \param   end2 \ the end point of the other vector

    @Author: <Rujia Liu rujialiu@hotmail.com>
*/
float Dot(const Vector2f& O, const Vector2f& end1, const Vector2f& end2)
{
    float x1 = end1.x() - O.x();
    float x2 = end2.x() - O.x();
    float y1 = end1.y() - O.y();
    float y2 = end2.y() - O.y();

    return x1 * x2 + y1 * y2;
}

/*!
    \fn DistanceToLine

    To get the shortest distance from a point to a line

    \param p         \the point

    \param lineStart \the start point of the line

    \param lineEnd   \the end point of the line

    \param &proj     \the projection point on the line

    @Author: <Rujia Liu rujialiu@hotmail.com>

            p  <positive distance>
          /
       /
    lineStart-------lineEnd
       \
         \
           \
             p <negative distance>
*/
float DistanceToLine(const Vector2f& p, const Vector2f& lineStart,
                     const Vector2f& lineEnd, Vector2f& proj)
{
    float d = (lineStart - lineEnd).Length();

//     assert(fabs(d) > 0);
    float disToLine = Cross(lineStart, lineEnd, p) / d;

    float t = Dot(lineStart,lineEnd, p) / Dot(lineStart,lineEnd, lineEnd);
    proj = lineStart +  (lineEnd - lineStart) * t;

    return disToLine; // signed
}

/*!
    \fn  getProjectionDistance

    To get the signed value of distance from lineStart point to projection point

    \param p         \the point

    \param lineStart \the start point of the line

    \param lineEnd   \the end point of the line

    @Author: <Rujia Liu rujialiu@hotmail.com>
                   p
                 /
               /
             /
     lineStart------proj----------------->lineEnd
     <positive value>
*/
float getProjectionDistance(const Vector2f& p, const Vector2f& lineStart,
                            const Vector2f& lineEnd)
{
    // assert((lineStart - lineEnd).Length() > 1e-05);
    return Dot(lineStart, lineEnd, p) / (lineStart - lineEnd).Length();
}

/*!
    \fn  IsObjectInTheWay

    To avoid obstacle, use this fn to test.

    \param objectPos the object possible to be a obstacle

    \param lineStart the start point of the line

    \param lineEnd   the end point of the line

    \param radius    minium distance from me to object to avoid collide

    @author <Lancelot wjqffff@hotmail.com>

                     -------
                    /       \
                   |objectPos|
     lineStart------\       /------------>lineEnd
                     -------
*/
bool IsObjectInTheWay(const Vector2f& objectPos, const Vector2f& lineStart,
                       const Vector2f& lineEnd, float radius)
{
    float dis = (lineStart - lineEnd).Length();
    Vector2f projPoint(0,0);
    float dist2Line = DistanceToLine(objectPos, lineStart, lineEnd, projPoint);
    float projDist =  getProjectionDistance(objectPos, lineStart, lineEnd);

    return (projDist > 0 && gAbs(dist2Line) < radius && projDist < dis);
}

float getVector2fAngleDeg(const Vector2f &v)
{
    return gRadToDeg(gArcTan2(v.y(), v.x()));
}

float getMatrixRotateXRad(const salt::Matrix &m)
{
    return gArcTan2(m(2,1), m(2,2));
}

float getMatrixRotateYRad(const salt::Matrix &m)
{
    return gArcSin(-m(2,0));
}

float getMatrixRotateZRad(const salt::Matrix &m)
{
    return gArcTan2(m(1,0), m(0,0));
}

/*! ------------------------ svd algorithm begin -----------------------*/
inline float pythag(float a, float b);
inline float SIGN(float a, float b);

bool svd(float* X, const float** A, const float* B, int M, int N);
void svdksb(float** u, float w[], float** v, int m, int n, float b[], float x[]);
bool svdcmp(float** a, int m, int n, float w[], float** v);

inline float
SIGN(float a, float b)
{
    if (b > 0) return fabs(a); else return -fabs(a);
}

bool
svd(float* X, const float** A, const float* B, int M, int N)
{
    bool rec = true;
    float wmax, wmin, **u, *w, **v, *b, *x;
    int i, j;

    u = new float*[M + 1];
    v = new float*[N + 1];
    for (i = 0; i < M + 1; ++i) u[i] = new float[N + 1];
    for (i = 0; i < N + 1; ++i) v[i] = new float[N + 1];
    w = new float[N + 1];
    b = new float[M + 1];
    x = new float[N + 1];

    for (i = 1; i < M + 1; ++i)
    {
        b[i] = B[i - 1];
        for (j = 1; j < N + 1; ++j)
            u[i][j] = A[i - 1][j - 1];
    }
    if (! svdcmp(u, M, N, w, v))
    {
        rec = false;
        goto over;
    }

    wmax = 0.0;
    for (j = 1; j <= N; ++j) if (w[j] > wmax) wmax = w[j];
    wmin = wmax * 1.0e-06;
    for (j = 1; j <= N; ++j) if (w[j] < wmin) w[j] = 0.0;
    svdksb(u, w, v, M, N, b, x);

    for (i = 1; i < N + 1; ++i)
        X[i - 1] = x[i];

over:
    // free memory
    for (i = 0; i < M + 1; ++i) delete [] u[i];
    for (i = 0; i < N + 1; ++i) delete [] v[i];
    delete [] u; u = NULL;
    delete [] v; v = NULL;
    delete [] w; w = NULL;
    delete [] b; b = NULL;
    delete [] x; x = NULL;
    return rec;
}

inline float
pythag(float a, float b)
{
    float absa, absb;
    absa = fabs(a);
    absb = fabs(b);
    if (absa > absb) return absa * sqrt(1.0 + (absb * absb) / (absa * absa));
    else return (absb == 0.0 ? 0.0 : absb * sqrt(1.0 + (absa * absa) / (absb * absb)));
}

void
svdksb(float** u, float w[], float** v, int m, int n, float b[], float x[])
{
    int jj, j, i;
    float s, *tmp;

    tmp = new float[n + 1];
    for (j = 1; j <= n; ++j) {
        s = 0.0;
        if (w[j]) {
            for (i = 1; i <= m; ++i) s += u[i][j] * b[i];
            s /= w[j];
        }
        tmp[j] = s;
    }
    for (j = 1; j <= n; ++j) {
        s = 0.0;
        for (jj = 1; jj <= n; ++jj) s += v[j][jj] * tmp[jj];
        x[j] = s;
    }
    delete [] tmp;
    tmp = NULL;
}

bool
svdcmp(float** a, int m, int n, float w[], float** v)
{
    bool rec = true;
    int flag, i, its, j, jj, k, l, nm;
    float anorm, c, f, g, h, s, scale, x, y, z, *rv1;

    rv1 = new float[n + 1];
    g = scale = anorm = 0.0;
    for (i = 1; i <= n; ++i) {
        l = i + 1;
        rv1[i] = scale * g;
        g = s = scale = 0.0;
        if (i <= m) {
            for (k = i; k <= m; ++k) scale += fabs(a[k][i]);
            if (scale) {
                for (k = i; k <= m; ++k) {
                    a[k][i] /= scale;
                    s += a[k][i] * a[k][i];
                }
                f = a[i][i];
                g = -SIGN(sqrt(s), f);
                h = f * g - s;
                a[i][i] = f - g;
                for (j = l; j <= n; ++j) {
                    for (s = 0.0, k = i; k <= m; ++k) s += a[k][i] * a[k][j];
                    f = s / h;
                    for (k = i; k <= m; ++k) a[k][j] += f * a[k][i];
                }
                for (k = i; k <= m; ++k) a[k][i] *= scale;
            }
        }
        w[i] = scale * g;
        g = s = scale = 0.0;
        if (i <= m && i != n) {
            for (k = l; k <= n; ++k) scale += fabs(a[i][k]);
            if (scale) {
                for (k = l; k <= n; ++k) {
                        a[i][k] /= scale;
                        s += a[i][k] * a[i][k];
                }
                f = a[i][l];
                g = -SIGN(sqrt(s), f);
                h = f * g - s;
                a[i][l] = f - g;
                for (k = l; k <= n; ++k) rv1[k] = a[i][k] / h;
                for (j = l; j <= m; ++j) {
                    for (s = 0.0, k = l; k <= n; ++k) s += a[j][k] * a[i][k];
                    for (k = l; k <= n; ++k) a[j][k] += s * rv1[k];
                }
                for (k = l; k <= n; ++k) a[i][k] *= scale;
            }
        }
        // anorm = std::max(anorm, (fabs(w[i]) + fabs(rv1[i])));
        anorm = anorm > (fabs(w[i]) + fabs(rv1[i])) ? anorm : (fabs(w[i]) + fabs(rv1[i]));
    }
    for (i = n; i >= 1; --i) {
        if (i < n) {
            if (g) {
                for (j = l; j <= n; ++j)
                    v[j][i] = (a[i][j] / a[i][l]) / g;
                for (j = l; j <= n; ++j) {
                    for (s = 0.0, k = l; k <= n; ++k) s += a[i][k] * v[k][j];
                    for (k = l; k <= n; ++k) v[k][j] += s * v[k][i];
                }
            }
            for (j = l; j <= n; ++j) v[i][j] = v[j][i] = 0.0;
        }
        v[i][i] = 1.0;
        g = rv1[i];
        l = i;
    }
    // for (i = std::min(m, n); i >= 1; --i) {
    for (i = (m < n ? m : n); i >= 1; --i) {
        l = i + 1;
        g = w[i];
        for (j = l; j <= n; ++j) a[i][j] = 0.0;
        if (g) {
            g = 1.0 / g;
            for (j = l; j <= n; ++j) {
                for (s = 0.0, k = l; k <= m; ++k) s += a[k][i] * a[k][j];
                f = (s / a[i][i]) * g;
                for (k = i; k <= m; ++k) a[k][j] += f * a[k][i];
            }
            for (j = i; j <= m; ++j) a[j][i] *= g;
        } else for (j = i; j <= m; ++j) a[j][i] = 0.0;
        ++a[i][i];
    }
    for (k = n; k >= 1; --k) {
        for (its = 1; its <= 30; ++its) {
            flag = 1;
            for (l = k; l >= 1; --l) {
                nm = l - 1;
                if ((float)(fabs(rv1[l]) + anorm) == anorm) {
                        flag = 0;
                        break;
                }
                if ((float)(fabs(w[nm]) + anorm) == anorm) break;
            }
            if (flag) {
                c = 0.0;
                s = 1.0;
                for (i = l; i <= k; ++i) {
                    f = s * rv1[i];
                    rv1[i] = c * rv1[i];
                    if ((float)(fabs(f) + anorm) == anorm) break;
                    g = w[i];
                    h = pythag(f, g);
                    w[i] = h;
                    h = 1.0 / h;
                    c = g * h;
                    s = -f * h;
                    for (j = 1; j <= m; ++j) {
                        y = a[j][nm];
                        z = a[j][i];
                        a[j][nm] = y * c + z * s;
                        a[j][i] = z * c - y * s;
                    }
                }
            }
            z = w[k];
            if (l == k) {
                if (z < 0.0) {
                    w[k] = -z;
                    for (j = 1; j <= n; ++j) v[j][k] = -v[j][k];
                }
                break;
            }
            if (its == 30)
            {
#ifdef DEBUG
                printf("no convergence in 30 svdcmp iterations\n");
#endif
                rec = false;
                goto over;
            }
            x = w[l];
            nm = k - 1;
            y = w[nm];
            g = rv1[nm];
            h = rv1[k];
            f = ((y - z) * (y + z) + (g - h) * (g + h)) / (2.0 * h * y);
            g = pythag(f, 1.0);
            f = ((x - z) * (x + z) + h * ((y / (f + SIGN(g, f))) - h )) / x;
            c = s = 1.0;
            for (j = l; j <= nm; ++j) {
                i = j + 1;
                g = rv1[i];
                y = w[i];
                h = s * g;
                g = c * g;
                z = pythag(f, h);
                rv1[j] = z;
                c = f / z;
                s = h / z;
                f = x * c + g * s;
                g = g * c - x * s;
                h = y * s;
                y *= c;
                for (jj = 1; jj <= n; ++jj) {
                    x = v[jj][j];
                    z = v[jj][i];
                    v[jj][j] = x * c + z * s;
                    v[jj][i] = z * c - x * s;
                }
                z = pythag(f, h);
                w[j] = z;
                if (z) {
                    z = 1.0 / z;
                    c = f * z;
                    s = h * z;
                }
                f = c * g + s * y;
                x = c * y - s * g;
                for (jj = 1; jj <= m; ++jj) {
                    y = a[jj][j];
                    z = a[jj][i];
                    a[jj][j] = y * c + z * s;
                    a[jj][i] = z * c - y * s;
                }
            }
            rv1[l] = 0.0;
            rv1[k] = f;
            w[k] = x;
        }
    }

over:
    delete [] rv1;
    rv1 = NULL;
    return rec;
}
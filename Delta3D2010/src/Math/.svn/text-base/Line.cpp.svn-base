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

#include "Line.h"
/*! This constructor creates a line by given the three coefficents of the line.
    A line is specified by the formula ay + bx + c = 0.
    \param dA a coefficients of the line
    \param dB b coefficients of the line
    \param dC c coefficients of the line */
Line::Line( double dA, double dB, double dC )
{
  m_a = dA;
  m_b = dB;
  m_c = dC;
}

/*! This function prints the line to the specified output stream in the
    format y = ax + b.
    \param os output stream to which output is written
    \param l line that is written to output stream
    \return output sream to which output is appended. */
ostream& operator <<(ostream & os, Line l)
{
  double a = l.getACoefficient();
  double b = l.getBCoefficient();
  double c = l.getCCoefficient();

  // ay + bx + c = 0 -> y = -b/a x - c/a
  if( a == 0 )
    os << "x = " << -c/b;
  else
  {
    os << "y = ";
    if( b != 0 )
      os << -b/a << "x ";
    if( c > 0 )
       os << "- " <<  fabs(c/a);
    else if( c < 0 )
       os << "+ " <<  fabs(c/a);
  }
  return os;
}

/*! This method prints the line information to the specified output stream.
    \param os output stream to which output is written. */
void Line::show( ostream& os)
{
  os << *this;
}

/*! This method calculates the y coordinate given the x coordinate
    \param x coordinate
    \return y coordinate on this line */
double Line::yGivenX( double x )
{
 if( m_a == 0 )
 {
   cerr << "(Line::yGivenX) Cannot calculate Y coordinate: " ;
   show( cerr );
   cerr << endl;
   return 0;
 }
  // ay + bx + c = 0 ==> y = -(b*x + c)/a
  return -(m_b*x+m_c)/m_a;
}

/*! This method calculates the x coordinate given the x coordinate
    \param y coordinate
    \return x coordinate on this line */
double Line::xGivenY( double y )
{
 if( m_b == 0 )
 {
   cerr << "(Line::xGivenY) Cannot calculate X coordinate\n" ;
   return 0;
 }
  // ay + bx + c = 0 ==> bx = -(a*y + c)/a
  return -(m_a*y+m_c)/m_b;
}

/*! This method creates a line given two points.
    \param pos1 first point
    \param pos2 second point
    \return line that passes through the two specified points. */
Line Line::makeLineFromTwoPoints( salt::Vector3f pos1, salt::Vector3f pos2 )
{
  // 1*y + bx + c = 0 => y = -bx - c
  // with -b the direction coefficient (or slope)
  // and c = - y - bx
  double dA, dB, dC;
  double dTemp = pos2.x() - pos1.x(); // determine the slope
  if( fabs(dTemp) < EPSILON )
  {
    // ay + bx + c = 0 with vertical slope=> a = 0, b = 1
    dA = 0.0;
    dB = 1.0;
  }
  else
  {
    // y = (-b)x -c with -b the slope of the line
    dA = 1.0;
    dB = -(pos2.y() - pos1.y())/dTemp;
  }
  // ay + bx + c = 0 ==> c = -a*y - b*x
  dC =  - dA*pos2.y()  - dB * pos2.x();
  return Line( dA, dB, dC );
}


/*! This method returns the a coefficient from the line ay + bx + c = 0.
    \return a coefficient of the line. */
double Line::getACoefficient() const
{
  return m_a;
}

/*! This method returns the b coefficient from the line ay + bx + c = 0.
    \return b coefficient of the line. */
double Line::getBCoefficient() const
{
 return m_b;
}

/*! This method returns the c coefficient from the line ay + bx + c = 0.
    \return c coefficient of the line. */
double Line::getCCoefficient() const
{
 return m_c;
}

int Line::abcFormula(double a, double b, double c, double *s1, double *s2)
{
  double dDiscr = b*b - 4*a*c;       // discriminant is b^2 - 4*a*c
  if (fabs(dDiscr) < EPSILON )       // if discriminant = 0
  {
    *s1 = -b / (2 * a);              //  only one solution
    return 1;
  }
  else if (dDiscr < 0)               // if discriminant < 0
    return 0;                        //  no solutions
  else                               // if discriminant > 0
  {
    dDiscr = sqrt(dDiscr);           //  two solutions
    *s1 = (-b + dDiscr ) / (2 * a);
    *s2 = (-b - dDiscr ) / (2 * a);
    return 2;
  }
}

/*! This method calculates the intersection points between the current line
    and the circle specified with as center 'posCenter' and radius 'dRadius'.
    The number of solutions are returned and the corresponding points are put
    in the third and fourth argument of the method
    \param circle circle with which intersection points should be found
    \param posSolution1 first intersection (if any)
    \param posSolution2 second intersection (if any) */
int Line::getCircleIntersectionPoints( Circle *circle,
              salt::Vector3f *posSolution1, salt::Vector3f *posSolution2 )
{
  int    iSol;
  double dSol1=0, dSol2=0;
  double h = circle->getCenter().x();
  double k = circle->getCenter().y();

  // line:   x = -c/b (if a = 0)
  // circle: (x-h)^2 + (y-k)^2 = r^2, with h = center.x and k = center.y
  // fill in:(-c/b-h)^2 + y^2 -2ky + k^2 - r^2 = 0
  //         y^2 -2ky + (-c/b-h)^2 + k^2 - r^2 = 0
  // and determine solutions for y using abc-formula
  if( fabs(m_a) < EPSILON )
  {
    iSol = abcFormula( 1, -2*k, ((-m_c/m_b) - h)*((-m_c/m_b) - h)
              + k*k - circle->getRadius()*circle->getRadius(), &dSol1, &dSol2);
    posSolution1 = &salt::Vector3f( (-m_c/m_b), dSol1 , 0);
    posSolution2 = &salt::Vector3f( (-m_c/m_b), dSol2 , 0);
    return iSol;
  }

  // ay + bx + c = 0 => y = -b/a x - c/a, with da = -b/a and db = -c/a
  // circle: (x-h)^2 + (y-k)^2 = r^2, with h = center.x and k = center.y
  // fill in:x^2 -2hx + h^2 + (da*x-db)^2 -2k(da*x-db) + k^2 - r^2 = 0
  //         x^2 -2hx + h^2 + da^2*x^2 + 2da*db*x + db^2 -2k*da*x -2k*db
  //                                                         + k^2 - r^2 = 0
  //       (1+da^2)*x^2 + 2(da*db-h-k*da)*x + h2 + db^2  -2k*db + k^2 - r^2 = 0
  // and determine solutions for x using abc-formula
  // fill in x in original line equation to get y coordinate
  double da = -m_b/m_a;
  double db = -m_c/m_a;

  double dA = 1 + da*da;
  double dB = 2*( da*db - h - k*da );
  double dC = h*h + db*db-2*k*db + k*k - circle->getRadius()*circle->getRadius();

  iSol = abcFormula( dA, dB, dC, &dSol1, &dSol2 );

  posSolution1 = &salt::Vector3f( dSol1, da*dSol1 + db ,0);
  posSolution2 = &salt::Vector3f( dSol2, da*dSol2 + db ,0);
  return iSol;

}



/*****************************************************************************/
/********************* CLASS CIRCLE ******************************************/
/*****************************************************************************/

/*! This is the constructor of a circle.
    \param pos first point that defines the center of circle
    \param dR the radius of the circle
    \return circle with pos as center and radius as radius*/
Circle::Circle( salt::Vector3f pos, double dR )
{
  setCircle( pos, dR );
}

/*! This is the constructor of a circle which initializes a circle with a
    radius of zero. */
Circle::Circle( )
{
  setCircle( salt::Vector3f(-1000.0,-1000.0, -1000.0), 0);
}

/*! This method prints the circle information to the specified output stream
    in the following format: "c: (c_x,c_y,c_z), r: rad" where (c_x,c_y,z_z) denotes
    the center of the circle and rad the radius.
    \param os output stream to which output is written. */
void Circle::show( ostream& os)
{
  os << "c:" << m_posCenter << ", r:" << m_dRadius;
}

/*! This method sets the values of the circle.
    \param pos new center of the circle
    \param dR new radius of the circle
    ( > 0 )
    \return bool indicating whether radius was set */
bool Circle::setCircle( salt::Vector3f pos, double dR )
{
  setCenter( pos );
  return setRadius( dR  );
}
/*! This method sets the radius of the circle.
    \param dR new radius of the circle ( > 0 )
    \return bool indicating whether radius was set */
bool Circle::setRadius( double dR )
{
  if( dR > 0 )
  {
    m_dRadius = dR;
    return true;
  }
  else
  {
    m_dRadius = 0.0;
    return false;
  }
}

/*! This method returns the radius of the circle.
    \return radius of the circle */
double Circle::getRadius() const
{
  return m_dRadius;
}

/*! This method sets the center of the circle.
    \param pos new center of the circle
    \return bool indicating whether center was set */
bool Circle::setCenter( salt::Vector3f pos )
{
  m_posCenter = pos;
  return true;
}

/*! This method returns the center of the circle.
    \return center of the circle */
salt::Vector3f Circle::getCenter()
{
  return m_posCenter;
}

/*! This method returns the circumference of the circle.
    \return circumference of the circle */
double Circle::getCircumference()
{
  return 2.0*M_PI*getRadius();
}

/*! This method returns the area inside the circle.
    \return area inside the circle */
double Circle::getArea()
{
  return M_PI*getRadius()*getRadius();
}

/*! This method returns the volume of a circle.
    \return volume inside the circle */
double Circle::getVolume() const
{
  return M_PI*4/3*getRadius()*getRadius()*getRadius();
}








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

#ifndef LINE_H
#define LINE_H

#include "Vector.h"
#include "../salt/vector.h"



using namespace std;


/*****************************************************************************/
/********************** CLASS CIRCLE *****************************************/
/*****************************************************************************/

/*!This class represents a circle. A circle is defined by one Vector3f
   (which denotes the center) and its radius. */
class Circle
{
    salt::Vector3f m_posCenter;            /*!< Center of the circle  */
    double      m_dRadius;              /*!< Radius of the circle  */

public:
    Circle( );
    Circle( salt::Vector3f pos, double dR );

    void        show                  ( ostream& os = cout                   );

    // get and set methods
    bool        setCircle             ( salt::Vector3f pos,
                                        double      dR                       );
    bool        setRadius             ( double dR                            );
    double      getRadius             (                                      ) const;
    bool        setCenter             ( salt::Vector3f pos                      );
    salt::Vector3f    getCenter             (                                      );
    double      getCircumference      (                                      );
    double      getArea               (                                      );
    double      getVolume             (                                      ) const;

    // calculate intersection points and area with other circle
    bool        isInside              ( salt::Vector3f pos, bool bCircle        );
    int         getCircleIntersectionPoints ( Circle      *c,
                                        salt::Vector3f *p1,
                                        salt::Vector3f *p2                      );
    //double      getIntersectionArea   ( Circle *c, bool bStrict = false       );


}  ;


/*****************************************************************************/
/*********************** CLASS LINE ******************************************/
/*****************************************************************************/

/*!This class contains the representation of a line. A line is defined
   by the formula ay + bx + c = 0. The coefficients a, b and c are stored
   and used in the calculations. */
class Line 
{
  // a line is defined by the formula: ay + bx + c = 0
  double m_a; /*!< This is the a coefficient in the line ay + bx + c = 0 */
  double m_b; /*!< This is the b coefficient in the line ay + bx + c = 0 */
  double m_c; /*!< This is the c coefficient in the line ay + bx + c = 0 */

public:
  Line( double a, double b, double c );
  Line(){m_a=-10000.0;m_b=-10000.0;m_c=-10000.0;}
  
  int         getCircleIntersectionPoints ( Circle      *c,
                                        salt::Vector3f *p1,
                                        salt::Vector3f *p2                      );

  // print methods
  void        show( ostream& os = cout );
  friend      ostream& operator << (ostream & os, Line l);

  // calculate associated variables in the line
  double      yGivenX                 ( double      x );
  double      xGivenY                 ( double      y );
  double      getACoefficient            (               ) const;
  double      getBCoefficient            (               ) const;
  double      getCCoefficient            (               ) const;

  // static methods to make a line using an easier representation.
  static  Line        makeLineFromTwoPoints      ( salt::Vector3f pos1,
                                                   salt::Vector3f pos2 );
  // abc formula
  int    abcFormula(double a,double b, double c, double *s1,double *s2);
};


#endif // LINE_H

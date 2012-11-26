/*****************************************************************************************
 *                                      SEU-3D
 *                     -------------------------------------------------
 * Copyright (c) 2005, Yuan XU<xychn15@yahoo.com.cn>,Chang'e SHI<evelinesce@yahoo.com.cn>
 * Copyright (c) 2006, Yuan XU<xuyuan.cn@gmail.com>,Chunlu JIANG<JamAceWatermelon@gmail.com>
 * Southeast University ,China
 * All rights reserved.
 *
 * Additionally,this program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 ****************************************************************************************/

 
#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#include <algorithm>
#include "math.h"       // needed for M_PI constant
#include <string>
#include <map>
#include <soccer/soccertypes.h>
#include "Settings.h"
#include <deque>

using namespace std;
using namespace salt;


#define EPSILON 0.0001  // Value used for floating point equality tests. 

// auxiliary numeric functions for determining the
// the sign of a value
/*! This function returns the sign of a give value.
    1 is positive, -1 is negative
    \param d1 first parameter
    \return the sign of this value */
template < class Type >
int sign( Type d1 )
{
  return (d1>0)?1:-1;
}

//-* random value in (min,max)
template < class Type >
Type random( Type min, Type max )
{
	//if ( min > max ) swap(min,max);//no need :)
	srand(time(0));
	return (Type(rand())/RAND_MAX)*(max-min)+min;
}

// auxiliary goniometric functions which enable you to
// specify angles in degrees rather than in radians
AngDeg Rad2Deg ( AngRad x );
AngRad Deg2Rad ( AngDeg x );
float cosDeg  ( AngDeg x );
float sinDeg  ( AngDeg x );
float tanDeg  ( AngDeg x );
AngDeg atanDeg ( float x );
AngDeg atan2Deg ( float y, float x );
AngDeg acosDeg ( float x );
AngDeg asinDeg ( float x );

//-* various goniometric functions
bool   isAngInInterval     ( AngDeg ang, AngDeg angMin, AngDeg angMax );
AngDeg getBisectorTwoAngles( AngDeg angMin, AngDeg angMax );
/////////////////// normalize ///////////////////
AngDeg normalizeAngle( AngDeg angle );
Vector3f normalizeVector3f( const Vector3f &v, const float maxLength );
Vector3f normalizeDriveForce( Vector3f driveForce );
float normalizeKickForce( float kickForce );
AngDeg normalizeKickAngle( AngDeg kickAngle );

struct VisionSense
{
    /** distance perceptor to object */
    float distance;

	/** theta is the angle in the X-Y (horizontal) plane */
	AngDeg theta;

	/** phi is the latitude angle */
	AngDeg phi;
	
	//VisionSense() : distance(0), theta(0), phi(0) {};
	VisionSense() : distance(1000.0), theta(0), phi(0) {};
	VisionSense( const float &d, const AngDeg &t, const AngDeg &p): distance(d), theta(t), phi(p) {};
};

//the vision is relative pos in formate POLAR
//the posRelative is relative pos in formate CARTESIAN(X-Y-Z)
Vector3f getPosRelativeFromVision( VisionSense vision );

VisionSense getPosVisionFromRelative( const Vector3f &posRelative );

typedef VisionSense Polar;
#define pol2xyz getPosRelativeFromVision
#define xyz2pol getPosVisionFromRelative

//-* some function about Vector3f
Vector3f setVector3fLength(Vector3f v,float length);
AngDeg	 getClipAng(const Vector3f &v1, const Vector3f &v2);
AngDeg	 getClipAng(const Vector3f &p0, const Vector3f &p1, const Vector3f &p2);
bool	 isThreePointOneLine( Vector3f p1, Vector3f p2, Vector3f p3 , AngDeg angThr = 1.8 );
AngDeg	 getVector3fHorizontalAng( Vector3f v );
float	 getDistToLine( Vector3f p, Vector3f l1, Vector3f l2 );

//////////////////// template ///////////////////////////////
template < class Type >
	Type setMaxNMin( const Type x, const Type max, const Type min )
{
	if ( x > max ) return max;
	if ( x < min ) return min;
	return x;
}

/** set the value to range [min,max]
 *  @param[in] x the orginal value
 *  @param[in] min the range left
 *  @param[in] max the range right
 *  @return the value be clamped
 */
template < class T >
T clamp( T x, T min, T max )
{
	if ( x > max ) return max;
	if ( x < min ) return min;
	return x;
}

template < class Type>
	Type pow2( const Type x )
{
	return x*x;
}

///////////////////////////////////////////////////////////////////
////////////////////// deque operation template////////////////////
///////////////////////////////////////////////////////////////////
template < class Type >
	Type getDequeValue( deque< Type > q, unsigned int i )
{
	if ( q.size() == 0 )
		return Type();
	
	return q[ min( i, q.size()-1 ) ];

}

template < class Type >
	void pushDequeValue( deque< Type > &q, Type value, const unsigned int maxSize )
{
	//-* push the value to the front
	q.push_front( value );
	//-* keep the size of the deque
	while( q.size() > maxSize )
		q.pop_back();
}

template < class Type >
	Type getDequeValueByTime( deque< Time > timeDeque, Time time, deque< Type > q )
{
	deque< Time >::iterator iter = find( timeDeque.begin(), timeDeque.end(), time );

	if ( iter == timeDeque.end() )
		return Type();
	
	unsigned int i = iter - timeDeque.begin();
	return getDequeValue( q, i );
}

/////////////////// some function of time ////////////////////
Second Time2Second( const Time &t);
Time Second2Time( const Second &t);
Step Time2Step( const Time &t);
Step Second2Step( const Second &t);
Time Step2Time ( const Step &t);
Second Step2Second( const Step &t);

// this function convert Vector3f to Vector2f,just skip z dim
Vector2f projection(const Vector3f &pos3 );

// this function convert Vector2f to Vector3f,let z = 0
Vector3f projection(const Vector2f &pos2 );

/***************************************************************/
/******************** CLASS RECTANGLE **************************/
/***************************************************************/
class Rectangle
{
public:
    f_inline                Rectangle() { }
    f_inline                Rectangle(const Rectangle &inOther) : _Left(inOther.Left()), _Top(inOther.Top()), _Right(inOther.Right()), _Bottom(inOther.Bottom()) { } 
    f_inline                Rectangle(float inLeft, float inTop, float inRight, float inBottom)  : _Left(inLeft), _Top(inTop), _Right(inRight), _Bottom(inBottom) { }
 
    f_inline void   Set(float inLeft, float inTop, float inRight, float inBottom)   { _Left=inLeft; _Top=inTop; _Right=inRight; _Bottom=inBottom; }
 
    // member access
    f_inline float    Left() const                    { return _Left; }
    f_inline float    Right() const                   { return _Right; }
    f_inline float    Top() const                     { return _Top; }
    f_inline float    Bottom() const                  { return _Bottom; }
    f_inline float    Width() const                   { return _Right-_Left; }
    f_inline float    Height() const                  { return _Bottom-_Top; }

    f_inline void   Normalize()                                                                             { if (_Right < _Left) gSwap(_Left, _Right); if (_Bottom < _Top) gSwap(_Top, _Bottom); }
    f_inline void   Widen(float inDelta)                                                              { _Left-=inDelta; _Top-=inDelta; _Right+=inDelta; _Bottom+=inDelta;     }
    f_inline void   Widen(float inDeltaWidth, float inDeltaHeight)              { _Right+=inDeltaWidth; _Bottom+=inDeltaHeight; }
    f_inline void   Widen(float inDeltaLeft, float inDeltaTop, float inDeltaRight, float inDeltaBottom)     { _Left-=inDeltaLeft; _Top-=inDeltaTop; _Right+=inDeltaRight; _Bottom+=inDeltaBottom;           }
    f_inline void   Shrink(float inDelta)                                                             { _Left+=inDelta;       _Top+=inDelta;  _Right-=inDelta; _Bottom-=inDelta;      }
    f_inline void   Shrink(float inDeltaWidth, float inDeltaHeight)             { _Right-=inDeltaWidth; _Bottom-=inDeltaHeight; }
    f_inline void   Shrink(float inDeltaLeft, float inDeltaTop, float inDeltaRight, float inDeltaBottom) { _Left+=inDeltaLeft; _Top+=inDeltaTop; _Right-=inDeltaRight; _Bottom-=inDeltaBottom;              }
    f_inline void   Offset(float inDeltaX, float inDeltaY)                              { _Left+=inDeltaX;      _Top+=inDeltaY; _Right+=inDeltaX;       _Bottom+=inDeltaY; }
    f_inline bool   Intersects(const Rectangle &b) const                                 { return !(_Left > b._Right || _Right < b._Left || _Top > b._Bottom || _Bottom < b._Top); }
	 
    // assignment
    f_inline Rectangle& operator=(const Rectangle &inOther)  { _Left=inOther.Left(); _Top=inOther.Top();     _Right=inOther.Right(); _Bottom=inOther.Bottom(); return *this; }
 
    // comparison
    f_inline bool operator==(const Rectangle &inRHS) const  { return (_Left==inRHS.Left()) && (_Top==inRHS.Top()) && (_Right==inRHS.Right()) && (_Bottom==inRHS.Bottom()); }
    f_inline bool operator!=(const Rectangle &inRHS) const  { return (_Left!=inRHS.Left()) || (_Top!=inRHS.Top()) || (_Right!=inRHS.Right()) || (_Bottom!=inRHS.Bottom()); }
	f_inline bool operator[](const Vector3f &p) const { return ( p.x()<_Right && p.x()>_Left && p.y()<_Top && p.y()>_Bottom); }
		
private:
     float _Left;
     float _Top;
     float _Right;
     float _Bottom;
};

/***************************************************************/
/******************** CLASS SECTOR *****************************/
/***************************************************************/
class Sector
{
public:
    f_inline                Sector() { }
//    f_inline                Sector(const Rectangle &inOther) : _Left(inOther.Left()), _Top(inOther.Top()), _Right(inOther.Right()), _Bottom(inOther.Bottom()) { } 
    f_inline                Sector(Vector3f start, Vector3f direction, float radius, AngDeg alpha) :_start(start), _direction(direction), _radius(radius), _alpha(alpha) { }
 
    f_inline void   Set(Vector3f start, Vector3f direction, float radius, AngDeg alpha)   { _start = start; _direction = direction; _radius = radius; _alpha = alpha; }
 
    // member access
    f_inline Vector3f    Start() const                    { return _start; }
    f_inline Vector3f    Direction() const                   { return _direction; }
    f_inline float    Radius() const                     { return _radius; }
    f_inline AngDeg    Alpha() const                  { return _alpha; }

/*    f_inline void   Normalize()                                                                             { if (_Right < _Left) gSwap(_Left, _Right); if (_Bottom < _Top) gSwap(_Top, _Bottom); }
    f_inline void   Widen(float inDelta)                                                              { _Left-=inDelta; _Top-=inDelta; _Right+=inDelta; _Bottom+=inDelta;     }
    f_inline void   Widen(float inDeltaWidth, float inDeltaHeight)              { _Right+=inDeltaWidth; _Bottom+=inDeltaHeight; }
    f_inline void   Widen(float inDeltaLeft, float inDeltaTop, float inDeltaRight, float inDeltaBottom)     { _Left-=inDeltaLeft; _Top-=inDeltaTop; _Right+=inDeltaRight; _Bottom+=inDeltaBottom;           }
    f_inline void   Shrink(float inDelta)                                                             { _Left+=inDelta;       _Top+=inDelta;  _Right-=inDelta; _Bottom-=inDelta;      }
    f_inline void   Shrink(float inDeltaWidth, float inDeltaHeight)             { _Right-=inDeltaWidth; _Bottom-=inDeltaHeight; }
    f_inline void   Shrink(float inDeltaLeft, float inDeltaTop, float inDeltaRight, float inDeltaBottom) { _Left+=inDeltaLeft; _Top+=inDeltaTop; _Right-=inDeltaRight; _Bottom-=inDeltaBottom;              }
    f_inline void   Offset(float inDeltaX, float inDeltaY)                              { _Left+=inDeltaX;      _Top+=inDeltaY; _Right+=inDeltaX;       _Bottom+=inDeltaY; }
    f_inline bool   Intersects(const Rectangle &b) const                                 { return !(_Left > b._Right || _Right < b._Left || _Top > b._Bottom || _Bottom < b._Top); }
	 
    // assignment
    f_inline Rectangle& operator=(const Rectangle &inOther)  { _Left=inOther.Left(); _Top=inOther.Top();     _Right=inOther.Right(); _Bottom=inOther.Bottom(); return *this; }
 
    // comparison
    f_inline bool operator==(const Rectangle &inRHS) const  { return (_Left==inRHS.Left()) && (_Top==inRHS.Top()) && (_Right==inRHS.Right()) && (_Bottom==inRHS.Bottom()); }
    f_inline bool operator!=(const Rectangle &inRHS) const  { return (_Left!=inRHS.Left()) || (_Top!=inRHS.Top()) || (_Right!=inRHS.Right()) || (_Bottom!=inRHS.Bottom()); }
	f_inline bool operator[](const Vector3f &p) const { return ( p.x()<_Right && p.x()>_Left && p.y()<_Top && p.y()>_Bottom); }
*/	
    f_inline Sector& operator=(const Sector &inOther)  { _start=inOther.Start(); _direction=inOther.Direction();     _radius=inOther.Radius(); _alpha=inOther.Alpha(); return *this; }
	bool isInside(const Vector3f &point);
private:
     Vector3f _start;
     Vector3f _direction;
     float _radius;
     AngDeg _alpha;
};

/*****************************************************************************/
/*********************** CLASS LINE2 ******************************************/
/*****************************************************************************/
/*!This class contains the representation of a line in 2D. A line is defined
   by the formula ay + bx + c = 0. The coefficients a, b and c are stored
   and used in the calculations. */
template <typename T>
class Line2
{
  // a line is defined by the formula: ay + bx + c = 0
  T _a; /*!< This is the a coefficient in the line ay + bx + c = 0 */
  T _b; /*!< This is the b coefficient in the line ay + bx + c = 0 */
  T _c; /*!< This is the c coefficient in the line ay + bx + c = 0 */

public:
	Line2( T a, T b, T c ){ _a=a; _b=b; _c=c; }

	T getACoefficient() const { return _a;}
	T getBCoefficient() const { return _b;}
	T getCCoefficient() const { return _c;}
	
	// print methods
	/*! This method prints the line information to the specified output stream.
    \param os output stream to which output is written. */
	void show( ostream& os){ os << *this;}

	/*! This function prints the line to the specified output stream in the
    format y = ax + b.
    \param os output stream to which output is written
    \param l line that is written to output stream
    \return output sream to which output is appended. */
	friend ostream& operator <<(ostream & os, Line2<T> l)
	{
  		T a = l.getACoefficient();
  		T b = l.getBCoefficient();
  		T c = l.getCCoefficient();

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

  	/*! get intersection points with this line
	This method returns the intersection point between the current Line and
    the specified line.
    \param line line with which the intersection should be calculated.
    \return Vector2f position that is the intersection point. */
	Vector2f getIntersection( Line2<T> line ) const
	{
  		Vector2f pos(0,0);
  		T x, y;
  		if( ( _a / _b ) ==  (line.getACoefficient() / line.getBCoefficient() ))
    		return pos; // lines are parallel, no intersection
  		if( _a == 0 )            // bx + c = 0 and a2*y + b2*x + c2 = 0 ==> x = -c/b
  		{                          // calculate x using the current line
    		x = -_c/_b;                // and calculate the y using the second line
    		y = line.getYGivenX(x);
  		}
  		else if( line.getACoefficient() == 0 )
  		{                         // ay + bx + c = 0 and b2*x + c2 = 0 ==> x = -c2/b2
   			x = -line.getCCoefficient()/line.getBCoefficient(); // calculate x using
   			y = getYGivenX(x);       // 2nd line and calculate y using current line
  		}
  		// ay + bx + c = 0 and a2y + b2*x + c2 = 0
  		// y = (-b2/a2)x - c2/a2
  		// bx = -a*y - c =>  bx = -a*(-b2/a2)x -a*(-c2/a2) - c ==>
  		// ==> a2*bx = a*b2*x + a*c2 - a2*c ==> x = (a*c2 - a2*c)/(a2*b - a*b2)
  		// calculate x using the above formula and the y using the current line
  		else
  		{
    		x = (_a*line.getCCoefficient() - line.getACoefficient()*_c)/
                    (line.getACoefficient()*_b - _a*line.getBCoefficient());
    		y = getYGivenX(x);
  		}

  		return Vector2f( x, y );
	}
	

	
	/*! This method returns the closest point on a line to a given position.
    \param pos point to which closest point should be determined
    \return Vector2f closest point on line to 'pos'. */
	Vector2f getPointOnLineClosestTo( const Vector2f &pos ) const
	{
  		Line2<T> l2 = getTangentLine( pos );  // get tangent line
  		return getIntersection( l2 );     // and intersection between the two lines
	}
	
	/*! This method returns the tangent line to a Vector2f. This is the line
    between the specified position and the closest point on the line to this
    position.
    \param pos Vector2f point with which tangent line is calculated.
    \return Line line tangent to this position */
	Line2<T> getTangentLine( const Vector2f &pos ) const
	{
  		// ay + bx + c = 0 -> y = (-b/a)x + (-c/a)
  		// tangent: y = (a/b)*x + C1 -> by - ax + C2 = 0 => C2 = ax - by
  		// with pos.y = y, pos.x = x
  		return Line2<T>( _b, -_a, _a*pos.x() - _b*pos.y() );
	}
	
	/*! This method returns the distance between a specified position and the
    closest point on the given line.
    \param pos position to which distance should be calculated
    \return double indicating the distance to the line. */
	T getDistanceToPoint( const Vector2f &pos ) const
	{
  		return (getPointOnLineClosestTo( pos )-pos).Length();
	}
	
	/*! This method determines whether the projection of a point on the
    current line lies between two other points ('point1' and 'point2')
    that lie on the same line.
    \param pos point of which projection is checked.
    \param point1 first point on line
    \param point2 second point on line
    \return true when projection of 'pos' lies between 'pos1' and 'pos2'.*/
	bool isInBetween( const Vector2f &pos, const Vector2f &pos1,const Vector2f &pos2) const
	{
		Vector2f posP = getPointOnLineClosestTo( pos ); // get closest point
		T dist = (pos1-pos2).Length(); // get distance between 2 pos

  		// if the distance from both points to the projection is smaller than this
  		// dist, the pos lies in between.
  		return (posP-pos1).Length() <= dist &&
         		(posP-pos2).Length() <= dist;
	}
	
  	/*! calculate associated variables in the line
  	This method calculates the y coordinate given the x coordinate
    \param x coordinate
    \return y coordinate on this line */
	T getYGivenX( T x ) const
	{
 		if( _a == 0 )
 		{
   			cerr << __FILE__<<__LINE__<<__FUNCTION__<<" Cannot calculate Y coordinate: "<< endl;
   			return 0;
 		}
  		// ay + bx + c = 0 ==> ay = -(b*x + c)/a
  		return -(_b*x+_c)/_a;
	}
	
  	/*! This method calculates the x coordinate given the x coordinate
    \param y coordinate
    \return x coordinate on this line */
	T getXGivenY( T y ) const
	{
 		if( _b == 0 )
 		{
   			cerr << __FILE__<<__LINE__<<__FUNCTION__<<"Cannot calculate X coordinate\n"<<endl;
   			return 0;
 	}
  	// ay + bx + c = 0 ==> bx = -(a*y + c)/a
  	return -(_a*y+_c)/_b;
	}

  	/*! static methods to make a line using an easier representation.
  	This method creates a line given two points.
    \param pos1 first point
    \param pos2 second point
    \return line that passes through the two specified points. */
	static Line2<T> makeLineFromTwoPoints( const Vector2f &pos1, const Vector2f &pos2 )
	{
  		// 1*y + bx + c = 0 => y = -bx - c
  		// with -b the direction coefficient (or slope)
  		// and c = - y - bx
  		T dA, dB, dC;
  		T dTemp = pos2.x() - pos1.x(); // determine the slope
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
  		return Line2<T>( dA, dB, dC );
	}
	
	/*! This method creates a line given a position and an angle.
    \param vec position through which the line passes
    \param angle direction of the line.
    \return line that goes through position 'pos' with angle 'angle'. */
	static Line2<T> makeLineFromPositionAndAngle( const Vector2f &pos, AngDeg angle )
	{
  		// calculate point somewhat further in direction 'angle' and make
  		// line from these two points.
  		return makeLineFromTwoPoints( pos, pos+projection(pol2xyz(Polar(1,angle,0))));
	}
};
typedef Line2<float> Line2f;


#endif /* _GEOMETRY_H */

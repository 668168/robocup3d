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

 
#include "Geometry.h"

/*! This function converts an angle in radians to the corresponding angle in
    degrees.
    \param x an angle in radians
    \return the corresponding angle in degrees */
AngDeg Rad2Deg( AngRad x )
{
  return ( x * 180 / M_PI );
}

/*! This function converts an angle in degrees to the corresponding angle in
    radians.
    \param x an angle in degrees
    \return the corresponding angle in radians */
AngRad Deg2Rad( AngDeg x )
{
  return ( x * M_PI / 180 );
}

/*! This function returns the cosine of a given angle in degrees using the
    built-in cosine function that works with angles in radians.
    \param x an angle in degrees
    \return the cosine of the given angle */
float cosDeg( AngDeg x )
{
  return ( cos( Deg2Rad( x ) ) );
}

/*! This function returns the sine of a given angle in degrees using the
    built-in sine function that works with angles in radians.
    \param x an angle in degrees
    \return the sine of the given angle */
float sinDeg( AngDeg x )
{
  return ( sin( Deg2Rad( x ) ) );
}

/*! This function returns the tangent of a given angle in degrees using the
    built-in tangent function that works with angles in radians.
    \param x an angle in degrees
    \return the tangent of the given angle */
float tanDeg( AngDeg x )
{
  return ( tan( Deg2Rad( x ) ) );
}

/*! This function returns the principal value of the arc tangent of x
    in degrees using the built-in arc tangent function which returns
    this value in radians.
    \param x a double value
    \return the arc tangent of the given value in degrees */
AngDeg atanDeg( float x )
{
  return ( Rad2Deg( atan( x ) ) );
}

/*! This function returns the principal value of the arc tangent of y/x in
    degrees using the signs of both arguments to determine the quadrant of the
    return value. For this the built-in 'atan2' function is used which returns
    this value in radians.
    \param x a float value
    \param y a float value
    \return the arc tangent of *y/x* in degrees taking the signs of x and y into
    account */
AngDeg atan2Deg( float y, float x )
{
  if( fabs( y ) < EPSILON && fabs( x ) < EPSILON )
    return ( 0.0 );

  return ( Rad2Deg( atan2( y, x ) ) );
}

/*! This function returns the principal value of the arc cosine of x in degrees
    using the built-in arc cosine function which returns this value in radians.
    \param x a double value
    \return the arc cosine of the given value in degrees */
AngDeg acosDeg( float x )
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
AngDeg asinDeg( float x )
{
  if( x >= 1 )
    return ( 90.0 );
  else if ( x <= -1 )
    return ( -90.0 );

  return ( Rad2Deg( asin( x ) ) );
}

/*! This function returns a boolean value which indicates whether the value
   'ang' (from interval [-180..180] lies in the interval [angMin..angMax].
    Examples: isAngInInterval( -100, 4, -150) returns false
             isAngInInterval(   45, 4, -150) returns true
    \param ang angle that should be checked
    \param angMin minimum angle in interval
    \param angMax maximum angle in interval
    \return boolean indicating whether ang lies in [angMin..angMax] */
bool isAngInInterval( AngDeg ang, AngDeg angMin, AngDeg angMax )
{
  // convert all angles to interval 0..360
  if( ( ang    + 360 ) < 360 ) ang    += 360;
  if( ( angMin + 360 ) < 360 ) angMin += 360;
  if( ( angMax + 360 ) < 360 ) angMax += 360;

  if( angMin < angMax ) // 0 ---false-- angMin ---true-----angMax---false--360
    return angMin < ang && ang < angMax ;
  else                  // 0 ---true--- angMax ---false----angMin---true---360
    return !( angMax < ang && ang < angMin );
}

/*! This method returns the bisector (average) of two angles. It deals
    with the boundary problem, thus when 'angMin' equals 170 and 'angMax'
    equals -100, -145 is returned.
    \param angMin minimum angle [-180,180]
    \param angMax maximum angle [-180,180]
    \return average of angMin and angMax. */
AngDeg getBisectorTwoAngles( AngDeg angMin, AngDeg angMax )
{
  // separate sine and cosine part to circumvent boundary problem
  return normalizeAngle(
            atan2Deg( (sinDeg( angMin) + sinDeg( angMax ) )/2.0,
                      (cosDeg( angMin) + cosDeg( angMax ) )/2.0 ) );
}

/*! This method normalizes an angle. This means that the resulting
    angle lies between -180 and 180 degrees.

    \param angle the angle which must be normalized

    \return the result of normalizing the given angle */
AngDeg normalizeAngle( AngDeg angle )
{
  while( angle > 180.0  ) angle -= 360.0;
  while( angle < -180.0 ) angle += 360.0;

  return ( angle );
}

Vector3f getPosRelativeFromVision( VisionSense vision )
{
	return Vector3f
        (
         vision.distance * cosDeg(vision.theta) * cosDeg(vision.phi),

         vision.distance * sinDeg(vision.theta) * cosDeg(vision.phi),

         vision.distance * sinDeg(vision.phi)
         );
}

/*!
	calculate polar from relative Vector3f
\param posRelative relative pos in formate CARTESIAN(X-Y-Z)
\return formate POLAR
*/
VisionSense getPosVisionFromRelative( const Vector3f &posRelative )
{
	VisionSense polar;
	polar.distance = posRelative.Length();
	polar.theta = getVector3fHorizontalAng(posRelative);
	polar.phi = asinDeg(posRelative.z()/polar.distance);
	return polar;
}

Vector3f normalizeVector3f(const Vector3f &v, const float maxLength )
{
	if ( v.Length() > maxLength )
		return v.Normalized() * maxLength;
	else
		return v;
}

Vector3f normalizeDriveForce( Vector3f driveForce )
{
	driveForce[2] = 0;
	return normalizeVector3f( driveForce, max_drive_force ); 
}

float normalizeKickForce( float kickForce )
{
	return setMaxNMin( kickForce, max_kick_force, 0.0f );
}

AngDeg normalizeKickAngle( AngDeg kickAngle )
{
	kickAngle = normalizeAngle( kickAngle );
	return setMaxNMin( kickAngle, min_kick_angle, max_kick_angle );
}

/*!设置矢量的长度
    \param v 原矢量
	\param length 新矢量的长度
	\return 新矢量*/
Vector3f setVector3fLength(Vector3f v,float length)
{
	float l=v.Length();
	if ( l < EPSILON ) return Vector3f(length,0,0);
	v[0]*=(length/l);
	v[1]*=(length/l);
	v[2]*=(length/l);
	return v;
}

/*! return the two vector's clip angle
	just now only consider in 2D !!!!
	\param two vector
	\return the clip angle
*/
AngDeg getClipAng(const Vector3f &v1, const Vector3f &v2)
{
	// just now only consider in 2D !!!!
	AngDeg ang1 = getVector3fHorizontalAng(v1);
	AngDeg ang2 = getVector3fHorizontalAng(v2);
	return normalizeAngle( ang1 - ang2 );
}

/*! return the 3 points clip angle, the 3 points are:
	p0------->p1
	 \
      \
       >p2
	\param 3 points
	\return the clip angle
*/
AngDeg getClipAng(const Vector3f &p0, const Vector3f &p1, const Vector3f &p2)
{
	return getClipAng( p1-p0, p2-p0);
}

/*! return if the 3 points is in one line:
	if p1------->p2---------->p3 return true
	else return false
	\param 3 points
	\return if the 3 points is in one line
*/
bool isThreePointOneLine( Vector3f p1, Vector3f p2, Vector3f p3, AngDeg angThr )
{
	AngDeg ang1 = getVector3fHorizontalAng( p2 - p1 );
	AngDeg ang2 = getVector3fHorizontalAng( p3 - p2 );
	return ( abs( normalizeAngle( ang1 - ang2 ) ) < angThr );
}

/*!得到矢量的水平角度
    \param v 要得到水平角度的矢量
	\return 水平角度*/
AngDeg getVector3fHorizontalAng( Vector3f v )
{
	return atan2Deg( v.y(), v.x() );
}

//-* it return the distance of p to line ( l2-l1 )
//-- when distance is minus, it means p in the left of the line
float getDistToLine( Vector3f p, Vector3f l1, Vector3f l2 )
{
	//-* just now, it calculate in 2D, so let z=0
	p[2] = l1[2] = l2[2] = 0;
	
	AngDeg angLine = getVector3fHorizontalAng( l2 - l1 );
	AngDeg angP = getVector3fHorizontalAng( p - l1 );
	AngDeg angDiff = normalizeAngle( angLine - angP );
	float dist_p_l1 = ( p - l1 ).Length();
	float dist = dist_p_l1 * sin( Deg2Rad( angDiff ) );
	return dist;
}

/////////////////// some function of time ////////////////////
Second Time2Second( const Time &t) { return t*0.01;}
Time Second2Time( const Second &t) { return t*100; }
Step Time2Step( const Time &t) { return static_cast<Step>(t); }
Step Second2Step( const Second &t) { return Time2Step( Second2Time(t)); }
Time Step2Time ( const Step &t) { return static_cast<Time>(t); }
Second Step2Second( const Step &t) { return Time2Second( Step2Time(t));}

/////////////////// Sector Function //////////////////////////
bool Sector::isInside(const Vector3f &point)
{
	float dist = pow2(point[0] - _start[0]) + pow2(point[1] - _start[1]);
	if(dist > pow2(_radius))
		return false;
	AngDeg clip = getVector3fHorizontalAng(point - _start);
	clip -= getVector3fHorizontalAng(_direction);
	if(fabs((float)clip) > _alpha / 2)
		return false;
	return true;
}


/** this function convert Vector3f to Vector2f
 *  just skip z dim
 * @param[in] pos3 Vector3f
 * @return pos Vector2f
 */
Vector2f projection(const Vector3f &pos3 )
{
	return Vector2f(pos3.x(),pos3.y());
}

/** change 2D point or vector to 3D point or vercotr,
 *  just set the Z axis value to zero
 * @param[in] pos2
 * @return Vector3f
 */
Vector3f projection(const Vector2f &pos2 )
{
	return Vector3f(pos2[0],pos2[1],0.0f);
}

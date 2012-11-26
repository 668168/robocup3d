/*
 *  Little Green BATS (2008), AI department, University of Groningen
 *
 *  Authors: 	Martin Klomp (martin@ai.rug.nl)
 *		Mart van de Sanden (vdsanden@ai.rug.nl)
 *		Sander van Dijk (sgdijk@ai.rug.nl)
 *		A. Bram Neijt (bneijt@gmail.com)
 *		Matthijs Platje (mplatje@gmail.com)
 *
 *	All students of AI at the University of Groningen
 *  at the time of writing. See: http://www.ai.rug.nl/
 *
 *  Date: 	November 1, 2008
 *
 *  Website:	http://www.littlegreenbats.nl
 *
 *  Comment:	Please feel free to contact us if you have any 
 *		problems or questions about the code.
 *
 *
 *  License: 	This program is free software; you can redistribute 
 *		it and/or modify it under the terms of the GNU General
 *		Public License as published by the Free Software 
 *		Foundation; either version 3 of the License, or (at 
 *		your option) any later version.
 *
 *   		This program is distributed in the hope that it will
 *		be useful, but WITHOUT ANY WARRANTY; without even the
 *		implied warranty of MERCHANTABILITY or FITNESS FOR A
 *		PARTICULAR PURPOSE.  See the GNU General Public
 *		License for more details.
 *
 *   		You should have received a copy of the GNU General
 *		Public License along with this program; if not, write
 *		to the Free Software Foundation, Inc., 59 Temple Place - 
 *		Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef __INC_BATS_MATH_HH_
#define __INC_BATS_MATH_HH_

#include "../Vector3/vector3.hh"
#include "../Matrix4D/matrix4d.hh"

//#include <cmath>

namespace bats
{
  /** Math has a few helpfull mathematical functions
    */
  class Math
  {
  public:

   /** Calculates the distance from a given point to the closest point on a given line
     *
     * To calculate the distance between a point \f$(x, y)\f$ and a line starting at <br>
     * point \f$(l_{x1}, l_{y1})\f$ with a normalized vector \f$(l_{x2}, l_{y2})\f$: <br>
     *
     * First calculate the perpendicular of the normalized vector, resulting in \f$(p_x, p_y)\f$ <br>
     * The result is then given by the length of \f$(l_{x2}, l_{y2} * u) - (x, y)\f$ where \f$u\f$ equals
     *
     * \f$u = (\frac{p_x}{p_y} * (l_{x2} - y) + (x - l_{x1})) / (l_{x2} - (\frac{p_x}{p_y} * l_{y2}))\f$
     *
     * @param l0 the starting point of the line.
     * @param lVect the normalized vector of the line.
     * @param point The point.
     * @return The distance from the line to the point
     */
    static double distanceLinePoint(Vector3D const &l0,
                                    Vector3D const &lVect,
                                    Vector3D const &point);

    /**
     * Calculates the nearest point on a given line to a given point.
     *
     * First determine wether a perpendicular line between the point and the line exists. <br>
     * If there is such a line, this will give the nearest point on the line.
     *
     * To calculate the distance between a point \f$(x, y)\f$ and a line starting at <br>
     * point \f$(l_{x1}, l_{y1})\f$ with a normalized vector \f$(l_{x2}, l_{y2})\f$: <br>
     *
     * First calculate the perpendicular of the normalized vector, resulting in \f$(p_x, p_y)\f$ <br>
     * The result is then given by the length of \f$(l_{x2}, l_{y2} * u) - (x, y)\f$ where \f$u\f$ equals
     *
     * \f$u = (\frac{p_x}{p_y} * (l_{x2} - y) + (x - l_{x1})) / (l_{x2} - (\frac{p_x}{p_y} * l_{y2}))\f$
     *
     * When no perpendicular line is posible within the segment, use the closest endpoint of the line.
     *
     * @param l0 The starting point of the line.
     * @param lVect The not normalized line vector.
     * @param point The other point.
     * @return The point on the line closest to the given point
     */
    static Vector3D linePointClosestToPoint(Vector3D const &l0,
                        Vector3D const &lVect,
                        Vector3D const &point);

    /**
     * Calculates the perpendicular vector to \a v.
     *
     * The perpendicular vector to \f$v = (x, y)\f$ is given by \f$(1.0, -1.0 / \frac{x}{y})\f$
     *
     * @param v A vector
     * @return The perpendicular vector to v
     */
    static Vector3D calcPerpend(Vector3D const &v);

    /** Calculate the point where a given line intersects a given plane
     *
     * To calculate the point where a line with starting position \f$(l_{x1}, l_{y1}, l_{z1})\f$ and <br>
     * direction \f$(l_{x2}, l_{y2}, l_{z2})\f$ intersects a plane \f$(a, b, c, d)\f$:
     *
     * \f$x = l_{x1} + f * l_{x2}\f$
     *
     * \f$a * x + b * y + c * z + d = 0\f$ <br>
     * \f$a * l_{x1} + a * f * l_{x2} + b * l_{y1} + b * f * l_{y2} + c * l_{z1} + c * f * l_{z2} + d = 0\f$
     *
     * \f$f * (a * l_{x2} + b * l_{y2} + c * l_{z2}) = - a * l_{x1} - b * l_{y1} - c * l_{z1} - d\f$ <br>
     * \f$f = (- a * l_{x1} - b * l_{y1} - c * l_{z1} - d) / (a * l_{x2} + b * l_{y2} + c * l_{z2})\f$
     *
     * The result is than given by the vector: (position + direction * \f$f\f$)
     *
     * @param position The starting point of the line
     * @param direction The direction of the line
     * @param plane The plane to intersect
     * @return The position where the line intersects the plane
     */
    static Vector3D intersectVectorPlane(Vector3D const& position, Vector3D const& direction, double plane[]);
  

    /** Convert polar coordinates to cartesian coordinates
     *
     */
    static Vector3D polarToCartesian(Vector3D const &polar);

    /** Convert cartesian coordinates to polar coordinates
     *
     */
    static Vector3D cartesianToPolar(Vector3D const &cartesian, bool sign = false);

    /** Convert degrees to raqdians */
    static double degToRad(double deg)
    {
      return deg / 180.0 * M_PI;
    }
        
    /** Normalize an angle in radians to the range [-pi, pi] */
    static double normalizeRad(double angle)
    {
      angle = fmod(angle,  (2.0 * M_PI));
      if (angle > M_PI)
        angle = -2.0 * M_PI + angle;
      if (angle < -M_PI)
        angle = 2.0 * M_PI + angle;

      return angle;
    }
    
    /** Convert local cartesian coordinates to self centered pose independent field coordinates
      *
      * @param pos Local cartesian position
      * @param normal Normal vector of the field in the local coordinate system
      * @returns Pose independent coordinates relative to the field
      */
    static Vector3D toFieldCoords(Vector3D const& pos, Vector3D const& normal);
    
    /** Determine whether 2 points are on the same side of a third point
      *
      * @param pivot Reference point
      * @param a First point
      * @param b Second point
      * @returns whether @a a and @ b are on the same side of @a pivot
      */
    static bool atSameSideOf(Vector3D const& pivot, Vector3D const& a, Vector3D const& b);
    
    /** Gaussian kernel function
     *
     * \f$ kernel(d, h) = e^{-\frac{d}{h}} \f$
     */
    static double kernel(double distSqr, double bandWidthSqr)
    {
      return exp(-distSqr/bandWidthSqr);
    }

    /**
     *  A sigmoid function, that starts at y=start and ends at y=end (0 < x < 1).
     *
     *  @param x the position in time or distance or etc. running from 0.0 to 1.0.
     *  @param start the starting output at x=0.0.
     *  @param end the ending output at x=1.0.
     *  @param c this parameter specifies the speedness of the sigmoid, higher is more steeper, lower is less steep.
     */
    static double sigmoid(double x, double start, double end, double c = 8)
    {
      return (1.0 - (1.0/(1+exp((0.5-x)*c))))*(start-end) + end;
    }

    /**
     *  @returns the kwadratic decay at time index x (0<x<1).
     */
    static double quadraticDecay(double x)
    {
      return 1.0-x*x;
    }

    static Matrix4D getTransform(Vector3D x, Vector3D zero, Vector3D y)
    {
      Vector3D worldRight   = (x - zero).normalize();
      Vector3D worldForward = (y - zero).normalize();
      Vector3D worldUp = worldRight.crossProduct(worldForward);

      Matrix4D worldTransform(worldRight, worldForward, worldUp, zero);
      return worldTransform;
    }
  };

};

#endif // __INC_BATS_MATH_HH_

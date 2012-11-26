#ifndef __INC_BATS_MATH_HH_
#define __INC_BATS_MATH_HH_

#include "vector3.hh"
#include "matrix9.hh"

//#include <cmath>

namespace bats {
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

	static double distanceLinePoint(Vector3D const &l0, Vector3D const &lVect,
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
			Vector3D const &lVect, Vector3D const &point);

	/**
	 * Calculates the perpendicular vector to @v.
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
	static Vector3D intersectVectorPlane(Vector3D const& position,
			Vector3D const& direction, double plane[]);

	/** Convert polar coordinates to cartesian coordinates
	 *
	 */
	static Vector3D polarToCartesian(Vector3D const &polar);

	/** Convert cartesian coordinates to polar coordinates
	 *
	 */
	static Vector3D cartesianToPolar(Vector3D const &cartesian);

	/** Normalize an angle in radians to the range [-pi, pi] */
	static double normalizeRad(double angle)
	{
		angle = fmod(angle, (2.0 * M_PI));
		if (angle > M_PI)
			angle = -2.0 * M_PI + angle;
		if (angle < -M_PI)
			angle = 2.0 * M_PI + angle;

		return angle;
	}

	//static double calcRealX(Vector3D const& pos, Vector3D const& normal, double height);

	/** Convert local cartesian coordinates to self centered pose independent field coordinates
	 *
	 * @param pos Local cartesian position
	 * @param normal Normal vector of the field in the local coordinate system
	 * @returns Pose independent coordinates relative to the field
	 */
	static Vector3D toFieldCoords(Vector3D const& pos, Vector3D const& normal);

	static bool atSameSideOf(Vector3D const& pivot, Vector3D const& target,
			Vector3D const& me);

	// check whether P is in the triangle ABC
	static bool inTriangle(Vector3D A, Vector3D B, Vector3D C, Vector3D P)
	{
		// calculate line AB
		double vertex = (C.getY() - A.getY()) * (B.getX() - A.getX())
				- (B.getY() - A.getY()) * (C.getX() - A.getX());
		double point = (P.getY() - A.getY()) * (B.getX() - A.getX())
				- (B.getY() - A.getY()) * (P.getX() - A.getX());
		if (vertex * point < 0)
			return false;
		// calculate line BC
		vertex = (A.getY() - B.getY()) * (C.getX() - B.getX()) - (C.getY()
				- B.getY()) * (A.getX() - B.getX());
		point = (P.getY() - B.getY()) * (C.getX() - B.getX()) - (C.getY()
				- B.getY()) * (P.getX() - B.getX());
		if (vertex * point < 0)
			return false;
		// calculate line CA
		vertex = (B.getY() - C.getY()) * (A.getX() - C.getX()) - (A.getY()
				- C.getY()) * (B.getX() - C.getX());
		point = (P.getY() - C.getY()) * (A.getX() - C.getX()) - (A.getY()
				- C.getY()) * (P.getX() - C.getX());
		if (vertex * point < 0)
			return false;
		return true;
	}

	static Matrix9D makeTransform(Vector3D const& right,
			Vector3D const& forward, Vector3D const& up)
	{
		Matrix9D mat;

		mat.set(0, right);
		mat.set(1, forward);
		mat.set(2, up);

		return mat;
	}

};

}
;

#endif // __INC_BATS_MATH_HH_

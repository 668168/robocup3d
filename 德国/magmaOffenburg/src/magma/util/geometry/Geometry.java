/* Copyright 2009 Hochschule Offenburg
 * Klaus Dorer, Mathias Ehret, Stefan Glaser, Thomas Huber,
 * Simon Raffeiner, Srinivasa Ragavan, Thomas Rinklin,
 * Joachim Schilling, Ingo Schindler, Rajit Shahi
 *
 * This file is part of magmaOffenburg.
 *
 * magmaOffenburg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * magmaOffenburg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with magmaOffenburg. If not, see <http://www.gnu.org/licenses/>.
 */
package magma.util.geometry;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Utilities for geometric calculations
 * @author dorer
 */
public class Geometry
{
	/**
	 * Checks if the passed 2D point is inside the passed polygon
	 * @param position the point to check (x,y) (it has to be in the same
	 *        coordinate system as the points of the polygon
	 * @param polygon corner points 2D of the polygon in clockwise direction
	 * @return true if the passed point is inside the polygon
	 */
	public static boolean isInsidePolygon(Vector3D position, Vector3D[] polygon)
	{
		int index0 = polygon.length - 1;
		int index1 = 0;
		double x2 = position.getX();
		double y2 = position.getY();
		for (int i = 0; i < polygon.length; i++) {
			double x0 = polygon[index0].getX();
			double y0 = polygon[index0].getY();
			double x1 = polygon[index1].getX();
			double y1 = polygon[index1].getY();
			// if points are clockwise then the determinant has to be positive
			// ----1 | x0 y0 1 |
			// A = - | x1 y1 1 |
			// ----2 | x2 y2 1 |
			double result = 0.5 * (x1 * y2 - y1 * x2 - x0 * y2 + y0 * x2 + x0 * y1 - y0
					* x1);
			if (result > 0) {
				return false;
			}

			index0 = index1;
			index1++;
		}

		return true;
	}

	/**
	 * Converts the passed points to a Vector3D array representing a polygon
	 * @param points the corner points (x,y)
	 * @return a Vector3D array representing a polygon
	 */
	public static Vector3D[] getPolygon(double[][] points)
	{
		Vector3D[] polygon = new Vector3D[points.length];
		for (int i = 0; i < points.length; i++) {
			double[] point = points[i];
			polygon[i] = new Vector3D(point[0], point[1], 0);
		}
		return polygon;
	}
}

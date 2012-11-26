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
package magma.agent.worldmodel.localizer.impl;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import magma.agent.worldmodel.localizer.ILocalizationFlag;
import magma.util.geometry.Angle;
import magma.util.geometry.PositionOrientation;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Implementation of the ILocalizer interface that uses triangulation for
 * localization
 * @author dorer
 */
public class LocalizerTriangulation extends Localizer
{
	/** handle for logging */
	private static Logger logger = Logger.getLogger("");

	/**
	 * Calculates absolute position and directions by performing triangulation
	 * for all pairs of flags taking the average of all calculations.
	 * @param flags visible landmarks with known position to be used for
	 *        localization
	 * @param neckYawAngle the horizontal neck angle (yaw) of the viewer
	 * @param neckPitchAngle the vertical neck angle (pitch) of the viewer (not
	 *        used at the moment)
	 * @return an array of two Vector3Ds, the first containing the absolute x,y,z
	 *         position of the viewer on the field, the second containing no real
	 *         vector, but the horizontal, latitudal and rotational absolute body
	 *         angles of the viewer
	 */
	public PositionOrientation localize(
			HashMap<String, ILocalizationFlag> flags, float neckYawAngle,
			float neckPitchAngle, Vector3D gyro)
	{
		if (flags.size() < 2) {
			// there are not 2 visible flags
			logger.log(Level.FINER,
					"Localization not possible, only have {0} flags", flags.size());
			return null;
		}

		// sort the flags according to their angle
		List<ILocalizationFlag> sortedFlags = new ArrayList<ILocalizationFlag>(
				flags.values());
		Collections.sort(sortedFlags);

		// get the two flags with maximum angle difference
		int triangulations = sortedFlags.size() * (sortedFlags.size() - 1) / 2;
		assert triangulations > 0 : "we need at least one triangulation";

		PositionOrientation[] results = new PositionOrientation[triangulations];
		int count = 0;
		for (int i = 0; i < sortedFlags.size() - 1; i++) {
			ILocalizationFlag flag1 = sortedFlags.get(i);
			for (int j = i + 1; j < sortedFlags.size(); j++) {
				ILocalizationFlag flag2 = sortedFlags.get(j);
				results[count] = triangulate(flag1, flag2, neckYawAngle);
				count++;
			}
		}

		PositionOrientation result = PositionOrientation.average(results);

		return result;
	}

	/**
	 * Calculates absolute position and directions from the two flags passed
	 * using triangulation. Absolute means with respect to the game fields
	 * coordinate system.
	 * @param flag1 first visible landmark with known position
	 * @param flag2 second visible landmark with known position (has to be right
	 *        of first)
	 * @param neckAngle the horizontal neck angle of the viewer
	 * @return an array of two Vector3Ds, the first containing the absolute x,y,z
	 *         position of the viewer on the field, the second containing no real
	 *         vector, but the horizontal, latitudal and rotational absolute body
	 *         angles of the viewer
	 */
	private PositionOrientation triangulate(ILocalizationFlag flag1,
			ILocalizationFlag flag2, float neckAngle)
	{
		float flag1Direction;
		float flag2Direction;
		double r1, r2; // the distance of the player to the flags
		double dist, dist2; // the distance (square) of the two flags
		double a; // distance from one flag to intersection
		// point P3
		double h; // distance from P3 to the intersection
		// Points P1 and P2 of the two circles
		double x, x1, x2, x3;
		double y, y1, y2, y3;
		double ratio;
		Angle horizontalAbsDirection;
		float beta;

		logger.log(Level.FINER, "Triangulation with flags 1:{0} 2:{1}",
				new Object[] { flag1, flag2 });

		// do the calculations
		flag1Direction = (float) flag1.getHorizontalDirection();
		flag2Direction = (float) flag2.getHorizontalDirection();

		r1 = flag1.getDistance();
		r2 = flag2.getDistance();

		x1 = flag1.getKnownPosition().getX();
		x2 = flag2.getKnownPosition().getX();

		y1 = flag1.getKnownPosition().getY();
		y2 = flag2.getKnownPosition().getY();

		// calculate the square distance of the two flags
		dist2 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
		dist = Math.sqrt(dist2);
		if (dist > r1 + r2) {
			// the circles would not intersect
			dist = r1 + r2;
			dist2 = dist * dist;
		} else if ((r1 > r2) && (dist + r2 < r1)) {
			// the circles would not intersect
			dist = r1 - r2;
			dist2 = dist * dist;
		} else if ((r2 > r1) && (dist + r1 < r2)) {
			// the circles would not intersect
			dist = r2 - r1;
			dist2 = dist * dist;
		}

		r1 *= r1;
		r2 *= r2;

		// a = (r1^2 - r2^2 + d^2 ) / (2 d)
		// a = distance from flag1 to base point of height line
		a = (r1 - r2 + dist2) / (2.0 * dist);

		// h^2 = r1^2 - a^2
		// h = height of the triangle flag1, flag2 and my position
		h = r1 - a * a;
		if (h < 0.0)
			h = 0.0;
		else
			h = Math.sqrt(h);

		// calculate middle of intersection line
		// P3 = P1 + a ( P2 - P1 ) / d
		x3 = x1 + a * (x2 - x1) / dist;
		y3 = y1 + a * (y2 - y1) / dist;

		// two circles intersect usually in 2 points. Find out which one to
		// select
		if (flag1Direction > flag2Direction) {
			// result x = x3 + h ( y2 - y1 ) / d
			x = x3 + h * (y2 - y1) / dist;
			// result y = y3 - h ( x2 - x1 ) / d
			y = y3 - h * (x2 - x1) / dist;
		} else {
			x = x3 - h * (y2 - y1) / dist;
			y = y3 + h * (x2 - x1) / dist;
		}

		// TODO: add z position calculation
		Vector3D position = new Vector3D(x, y, 0);

		// calculate the absolute direction
		r1 = flag1.getDistance();
		ratio = (y1 - y) / r1;
		beta = (float) Math.asin(ratio);
		if (x > x1) {
			horizontalAbsDirection = Angle.RAD180.subtract(beta).subtract(
					flag1Direction);
		} else {
			horizontalAbsDirection = Angle.rad(beta).subtract(flag1Direction);
		}
		// adjust to head angle
		horizontalAbsDirection = horizontalAbsDirection.subtract(neckAngle);

		// TODO add vertical direction

		logger.log(Level.FINER, "Localize pos:({0}, {1}), angles:{2}, neck:{3}",
				new Object[] { x, y, horizontalAbsDirection, neckAngle });
		return new PositionOrientation(position, horizontalAbsDirection);
	}
}

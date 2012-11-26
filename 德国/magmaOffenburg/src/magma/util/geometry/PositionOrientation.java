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
 * Stores position and orientation
 */
public class PositionOrientation
{
	private Vector3D position;

	/** horizontal angle in radians */
	private Angle orientationX;

	/**
	 * @param position position
	 * @param orientationX horizontal angle (rad)
	 */
	public PositionOrientation(Vector3D position, Angle orientationX)
	{
		this.position = position;
		this.orientationX = orientationX;
	}

	/**
	 * @return the position
	 */
	public Vector3D getPosition()
	{
		return position;
	}

	/**
	 * @param position the position to set
	 */
	public void setPosition(Vector3D position)
	{
		this.position = position;
	}

	/**
	 * @return the horizontal angle (rad)
	 */
	public Angle getOrientationX()
	{
		return orientationX;
	}

	/**
	 * @param orientationX the horizontal angle (rad) to set
	 */
	public void setOrientationX(Angle orientationX)
	{
		this.orientationX = orientationX;
	}

	public static PositionOrientation average(PositionOrientation[] result)
	{
		// float angle = averageAngle(angles);
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;

		// average position
		for (PositionOrientation value : result) {
			x += value.getPosition().getX();
			y += value.getPosition().getY();
			z += value.getPosition().getZ();
		}
		if (result.length > 1) {
			x /= result.length;
			y /= result.length;
			z /= result.length;
		}
		Vector3D pos = new Vector3D(x, y, z);

		// average angles
		Angle[] angles = new Angle[result.length];
		for (int i = 0; i < result.length; i++) {
			angles[i] = result[i].getOrientationX();
		}
		Angle angle = Angle.average(angles);
		return new PositionOrientation(pos, angle);
	}
}

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
package magma.agent.perception;

import org.apache.commons.math.geometry.Vector3D;

/**
 * The Visible Object Perceptor represents a single object as reported by the
 * visual sensor sub-system.
 * 
 * @author Simon Raffeiner
 * 
 */
public interface IVisibleObjectPerceptor extends IPerceptor
{
	/**
	 * Get Object Position
	 * 
	 * @return Object Position
	 */
	Vector3D getPosition();

	/**
	 * Set object position
	 * 
	 * @param position Position
	 */
	public void setPosition(Vector3D position);

	/**
	 * Get object distance
	 * 
	 * @return Distance
	 */
	double getDistance();

	/**
	 * Get horizontal angle
	 * 
	 * @return Angle
	 */
	double getHorizontalAngle();

	/**
	 * Get vertical angle
	 * 
	 * @return Angle
	 */
	double getLatitudeAngle();

	/**
	 * Get horizontal angle (in degrees)
	 * 
	 * @return Angle
	 */
	public double getHorizontalAngleDeg();

	/**
	 * Get vertical angle (in degrees)
	 * 
	 * @return Angle
	 */
	public double getLatitudeAngleDeg();
}
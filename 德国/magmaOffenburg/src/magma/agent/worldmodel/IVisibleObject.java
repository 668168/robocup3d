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
package magma.agent.worldmodel;

import magma.util.geometry.Angle;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Base Interface for all visible objects in the world model
 * @author dorer
 */
public interface IVisibleObject
{
	/**
	 * @return the current position in the global coordinate system
	 */
	Vector3D getPosition();

	/**
	 * @return the previous position in the global coordinate system, null,
	 *         before the first perception update.
	 */
	Vector3D getPreviousPosition();

	/**
	 * @return time stamp when this object was last updated by perception
	 */
	float getLastSeenTime();

	/**
	 * Returns the delta of current time passed and the last time this object was
	 * seen
	 * @param currentTime the current global time
	 * @return delta of current time passed and the last time this object was
	 *         seen
	 */
	float getAge(float currentTime);

	/**
	 * Calculates the distance of this visible object to the passed one
	 * @param other the object to which to calculate distance
	 * @return the distance of this visible object to the passed one
	 */
	public double getDistanceTo(IVisibleObject other);

	/**
	 * Calculates the distance of this visible object to the passed position
	 * @param other the position to which to calculate distance
	 * @return the distance of this visible object to the passed position
	 */
	public double getDistanceTo(Vector3D other);

	/**
	 * Calculates the Direction of this visible object to the passed one
	 * @param other the object to which to calculate direction
	 * @return the direction (rad) of this visible object to the passed one
	 */
	public Angle getDirectionTo(IVisibleObject other);

	/**
	 * Calculates the global absolute Direction of this visible object to the
	 * passed Vector3D
	 * @param other the Vector3D to which to calculate direction
	 * @return the global absolute direction (rad) of this visible object to the
	 *         passed Vector
	 */
	public Angle getDirectionTo(Vector3D other);

	/**
	 * Returns the horizontal direction of this visible object as received from
	 * perception
	 * @return the horizontal direction of this visible object as received from
	 *         perception (in radians)
	 */
	public double getHorizontalDirection();

	/**
	 * Returns the latitudal direction of this visible object as received from
	 * perception
	 * @return the latitudal direction of this visible object as received from
	 *         perception (in radians)
	 */
	public double getLatitudalDirection();

	/**
	 * @return true if this object was seen last perception
	 */
	public boolean isVisible();

	/**
	 * @return the distance as perceived
	 */
	public double getDistance();

	/**
	 * @param other the point to which to calculate
	 * @return the distance projection to the x y plane between this object and
	 *         the passed coordinate
	 */
	public double getDistanceToXY(Vector3D other);
}
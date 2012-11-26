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
package magma.agent.worldmodel.impl;

import java.io.Serializable;
import java.util.logging.Level;
import java.util.logging.Logger;

import magma.agent.perception.IVisibleObjectPerceptor;
import magma.agent.worldmodel.IThisPlayer;
import magma.agent.worldmodel.IVisibleObject;
import magma.util.FuzzyCompare;
import magma.util.geometry.Angle;

import org.apache.commons.math.geometry.Vector3D;

import static java.lang.Math.cos;
import static java.lang.Math.sin;

/**
 * Base class for all visible objects on the field
 */
public abstract class VisibleObject implements IVisibleObject, Serializable
{
	// handle for logging
	protected static Logger logger = Logger.getLogger("");

	private static final long serialVersionUID = 1L;

	protected double distance;

	/** the horizontal direction (radians) in which this object was perceived */
	protected double horizontalDirection;

	/** the latitudal direction (radians) in which this object was perceived */
	protected double latitudalDirection;

	/** the current position in the global coordinate system */
	protected Vector3D position;

	/** the previous position in the global coordinate system */
	protected Vector3D previousPosition;

	/** time stamp when this object was last updated by perception */
	private float lastSeenTime;

	/** true if this object was seen in last perception */
	private boolean visible;

	public VisibleObject()
	{
		distance = 0;
		horizontalDirection = 0;
		latitudalDirection = 0;
		position = null;
		previousPosition = null;
		visible = false;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.worldmodel.impl.IVisibleObject#getPosition()
	 */
	public Vector3D getPosition()
	{
		if (position == null)
			return new Vector3D(0.0, 0.0, 0.0);

		return position;
	}

	/**
	 * Setting this objects position is usually done when updating the object.
	 * This method is used to set the ball position from hear message only.
	 * @param pos
	 */
	public void setPosition(Vector3D pos)
	{
		position = pos;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.worldmodel.impl.IVisibleObject#getPosition()
	 */
	public Vector3D getPreviousPosition()
	{
		return previousPosition;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.worldmodel.impl.IVisibleObject#getLastSeenTime()
	 */
	public float getLastSeenTime()
	{
		return lastSeenTime;
	}

	/**
	 * Updates this object with the latest perception
	 * @param vision new perception of movable object
	 * @param time the current absolute time
	 * @param thisPlayer the position of the viewing agent in the global
	 *        coordinate system
	 */
	public void update(IVisibleObjectPerceptor vision, float time,
			IThisPlayer thisPlayer)
	{
		preUpdate(vision);

		// calculate global coordinate of object
		// rotation (we assume that the agent can only change view angle in z-axis
		Vector3D localPos = vision.getPosition();

		previousPosition = getPosition();

		// Rotation around y axis with angle c:
		// to compensate neck angle
		// TODO: add player vertical angle once we know
		Angle horizontalAngle = thisPlayer.getHorizontalAngle();
		Angle verticalAngle = Angle.rad(0);
		double neckPitchAngle = thisPlayer.getNeckPitchAngle();
		double neckYawAngle = thisPlayer.getNeckYawAngle();

		Vector3D global = getGlobalFromLocalPosition(localPos, thisPlayer
				.getPosition(), horizontalAngle, verticalAngle, neckPitchAngle,
				neckYawAngle);

		position = global;

		logger.log(Level.FINEST, "position of: {0} ({1}, {2}, {3})",
				new Object[] { vision.getName(), position.getX(), position.getY(),
						position.getZ() });

		visible = true;
		lastSeenTime = time;
	}

	public Vector3D getGlobalFromLocalPosition(Vector3D localPos,
			Vector3D playerPosition, Angle horizontalAngle, Angle verticalAngle,
			double neckPitchAngle, double neckYawAngle)
	{
		// Rotation around z axis with angle1
		double angle1 = (float) -neckPitchAngle;
		double sinus = sin(angle1);
		double cosinus = cos(angle1);
		double newX = localPos.getX() * cosinus + localPos.getZ() * sinus;
		double newY = localPos.getY();
		double newZ = localPos.getX() * (-sinus) + localPos.getZ() * cosinus;

		// Rotation around z axis with angle2
		double angle2 = horizontalAngle.add(neckYawAngle).radians();
		sinus = sin(angle2);
		cosinus = cos(angle2);
		double newX2 = newX * cosinus - newY * sinus;
		double newY2 = newX * sinus + newY * cosinus;
		double newZ2 = newZ;

		// Rotation around x axis with angle b:
		// x' = x
		// y' = y * cos(b) - z * sin(b)
		// z' = y * sin(b) + z * cos(b)

		// translation
		return new Vector3D(newX2, newY2, newZ2).add(playerPosition);
	}

	/**
	 * @param vision
	 */
	public void preUpdate(IVisibleObjectPerceptor vision)
	{
		distance = vision.getDistance();
		horizontalDirection = vision.getHorizontalAngle();
		latitudalDirection = vision.getLatitudeAngle();
	}

	/**
	 * @param other the point to which to calculate
	 * @return the distance projection to the x y plane between this object and
	 *         the passed coordinate
	 */
	public double getDistanceToXY(Vector3D other)
	{
		Vector3D delta = getPosition().subtract(other);
		return new Vector3D(delta.getX(), delta.getY(), 0).getNorm();
	}

	/**
	 * @return the distance projection to the x y plane
	 */
	public double getDistance()
	{
		return distance;
	}

	/**
	 * Calculates the distance of this visible object to the passed one
	 * @param other the object to which to calculate distance
	 * @return the distance of this visible object to the passed one
	 */
	public double getDistanceTo(IVisibleObject other)
	{
		return getDistanceTo(other.getPosition());
	}

	/**
	 * Calculates the distance of this visible object to the passed position
	 * @param other the position to which to calculate distance
	 * @return the distance of this visible object to the passed position
	 */
	public double getDistanceTo(Vector3D other)
	{
		return getPosition().subtract(other).getNorm();
	}

	/**
	 * Calculates the Direction of this visible object to the passed one
	 * @param other the object to which to calculate direction
	 * @return the direction (rad) of this visible object to the passed one
	 */
	public Angle getDirectionTo(IVisibleObject other)
	{
		return getDirectionTo(other.getPosition());
	}

	/**
	 * Calculates the global absolute Direction of this visible object to the
	 * passed Vector3D
	 * @param other the Vector3D to which to calculate direction
	 * @return the global absolute direction (rad) of this visible object to the
	 *         passed Vector
	 */
	public Angle getDirectionTo(Vector3D other)
	{
		return Angle.rad(other.subtract(getPosition()).getAlpha());
	}

	/**
	 * @see IVisibleObject#getHorizontalDirection()
	 */
	public double getHorizontalDirection()
	{
		return horizontalDirection;
	}

	/**
	 * @see IVisibleObject#getLatitudalDirection()
	 */
	public double getLatitudalDirection()
	{
		return latitudalDirection;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object other)
	{
		if (!(other instanceof VisibleObject)) {
			return false;
		}
		VisibleObject otherVis = (VisibleObject) other;

		if (!FuzzyCompare.eq(position, otherVis.position, 0.00001f)) {
			return false;
		}
		if (!FuzzyCompare.eq(previousPosition, otherVis.previousPosition,
				0.00001f)) {
			return false;
		}
		if (!FuzzyCompare.eq(lastSeenTime, otherVis.lastSeenTime, 0.00001f)) {
			return false;
		}
		return true;
	}

	public void setVisible(boolean b)
	{
		visible = b;
	}

	/**
	 * @return the visible
	 */
	public boolean isVisible()
	{
		return visible;
	}

	public float getAge(float currentTime)
	{
		return currentTime - lastSeenTime;
	}
}
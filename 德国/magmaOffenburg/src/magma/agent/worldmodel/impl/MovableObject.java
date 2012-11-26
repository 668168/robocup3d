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

import magma.agent.perception.IVisibleObjectPerceptor;
import magma.agent.worldmodel.IThisPlayer;
import magma.util.FuzzyCompare;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Base class for all movable objects on the field
 */

public abstract class MovableObject extends VisibleObject
{
	private static final long serialVersionUID = 1L;

	/** the speed calculated from previous and current positions */
	private Vector3D speed;

	/**
	 * Returns a list of future positions as predicted by the speed
	 * @param aHowMany the number of future positions that should be returned
	 * @return a list of future positions
	 */
	public Vector3D[] getFuturePositions(int aHowMany)
	{
		Vector3D[] futurePositions = new Vector3D[aHowMany];
		futurePositions[0] = getPosition().add(getSpeed());

		for (int i = 1; i < aHowMany; i++) {
			futurePositions[i] = futurePositions[i - 1].add(getSpeed());
		}
		return futurePositions;
	}

	/**
	 * @return the speed of this object
	 */
	public Vector3D getSpeed()
	{
		// we don't want null pointers!
		if (speed == null)
			speed = new Vector3D(0.0, 0.0, 0.0);
		return speed;
	}

	/**
	 * Updates this object with the latest perception
	 * @param vision new perception of movable object
	 * @param time the current absolute time
	 */
	@Override
	public void update(IVisibleObjectPerceptor vision, float time,
			IThisPlayer thisPlayer)
	{
		float lastSeenTime = getLastSeenTime();
		super.update(vision, time, thisPlayer);
		calculateSpeed(lastSeenTime, time);
	}

	public double getPossibleSpeed()
	{
		return 0.0;
	}

	public void calculateSpeed(float lastSeenTime, float time)
	{
		// need previousPosition, hence speed is calculated after update
		if (getPreviousPosition() != null) {
			Vector3D checkSpeed = new Vector3D();
			checkSpeed = getPosition().subtract(getPreviousPosition());
			if (time - lastSeenTime > 1)
				checkSpeed = new Vector3D(
						checkSpeed.getX() / (time - lastSeenTime), checkSpeed.getY()
								/ (time - lastSeenTime), checkSpeed.getZ()
								/ (time - lastSeenTime));

			// we don't set speed for impossible values
			if (checkSpeed.getNorm() < getPossibleSpeed())
				speed = checkSpeed;
		} else
			speed = new Vector3D(0.0, 0.0, 0.0);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object o)
	{
		if (!(o instanceof MovableObject)) {
			return false;
		}
		MovableObject other = (MovableObject) o;
		if (!super.equals(other)) {
			return false;
		}
		if (!FuzzyCompare.eq(speed, other.speed, 0.00001f)) {
			return false;
		}
		return true;
	}
}
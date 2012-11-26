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

import magma.agent.worldmodel.ILandmark;
import magma.agent.worldmodel.localizer.ILocalizationFlag;
import magma.util.FuzzyCompare;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Non movable orientation point on the field
 */
public class Landmark extends VisibleObject implements ILandmark,
		ILocalizationFlag
{
	/** id of this class for serialization */
	private static final long serialVersionUID = -5016797299200496064L;

	/** the position as defined in robocup configuration files */
	private Vector3D knownPosition;

	/**
	 * @param knownPosition
	 */
	public Landmark(Vector3D knownPosition)
	{
		super();
		this.knownPosition = knownPosition;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.worldmodel.impl.ILandmark#getKnownPosition()
	 */
	public Vector3D getKnownPosition()
	{
		return knownPosition;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object o)
	{
		if (!(o instanceof Landmark)) {
			return false;
		}
		Landmark other = (Landmark) o;
		if (!super.equals(other)) {
			return false;
		}
		if (!FuzzyCompare.eq(knownPosition, other.knownPosition, 0.00001f)) {
			return false;
		}
		return true;
	}

	@Override
	public int compareTo(ILocalizationFlag other)
	{

		if (horizontalDirection < other.getHorizontalDirection()) {
			return 1;
		} else if (horizontalDirection > other.getHorizontalDirection()) {
			return -1;
		}
		return 0;
	}
}
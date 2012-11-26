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
package magma.agent.agentmodel.impl;

import magma.agent.agentmodel.IUniversalJoint;
import magma.util.FuzzyCompare;

public class UniversalJoint extends Sensor implements IUniversalJoint
{
	/** id for serialization */
	private static final long serialVersionUID = 3124679237337000038L;

	/** angle of first axis */
	private float ax1;

	/** angle of second axis */
	private float ax2;

	public UniversalJoint(String name)
	{
		super(name);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.agentmodel.impl.IUniversalJoint#getAx1()
	 */
	public float getAx1()
	{
		return ax1;
	}

	public void setAx1(float ax1)
	{
		this.ax1 = ax1;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.agentmodel.impl.IUniversalJoint#getAx2()
	 */
	public float getAx2()
	{
		return ax2;
	}

	public void setAx2(float ax2)
	{
		this.ax2 = ax2;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object o)
	{
		if (!(o instanceof UniversalJoint)) {
			return false;
		}
		UniversalJoint other = (UniversalJoint) o;
		if (!super.equals(other)) {
			return false;
		}
		if (!FuzzyCompare.eq(ax1, other.ax1, 0.00001f)) {
			return false;
		}
		if (!FuzzyCompare.eq(ax2, other.ax2, 0.00001f)) {
			return false;
		}
		return true;
	}

}

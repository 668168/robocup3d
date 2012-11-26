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

import magma.agent.agentmodel.IHingeJoint;
import magma.util.FuzzyCompare;

public class HingeJoint extends Sensor implements IHingeJoint
{
	/** id for serialization */
	private static final long serialVersionUID = -9142499983257109635L;

	/** angle of the joint */
	private float ax;

	/** last angle of the joint */
	private float last_ax;

	private final float min_ax;

	private final float max_ax;

	/** the name of the corresponding effector */
	private String effectorName;

	public HingeJoint(String name, String effectorName, float min, float max)
	{
		super(name);
		this.effectorName = effectorName;
		this.ax = 0;
		this.min_ax = min;
		this.max_ax = max;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.agentmodel.impl.IHingeJoint#getAxis()
	 */
	public float getAxis()
	{
		return ax;
	}

	public void setAxis(float ax)
	{
		this.last_ax = this.ax;
		this.ax = ax;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.agentmodel.impl.IHingeJoint#getLastAxis()
	 */
	public float getLastAxis()
	{
		return last_ax;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.agentmodel.impl.IHingeJoint#getMin()
	 */
	public float getMin()
	{
		return min_ax;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.agentmodel.impl.IHingeJoint#getMax()
	 */
	public float getMax()
	{
		return max_ax;
	}

	public float checkTarget(float targetposition, float range)
	{
		float ret = 0f;

		if (targetposition > max_ax) {
			range += 3;
			targetposition = max_ax;
		} else if (targetposition < min_ax) {
			range += 3;
			targetposition = min_ax;
		}

		if (FuzzyCompare.eq(ax, targetposition, range)) {
			ret = 0f;
		} else if (ax < targetposition) {
			// if Axis is less than Target, move up
			ret = 1f;
		} else if (ax > targetposition) {
			// if Axis is less than Target, move down
			ret = -1f;
		}

		return ret;
	}

	public boolean checkTrigger(float targetposition, float range)
	{
		boolean reached = false;

		if (targetposition > max_ax) {
			range += 3;
			targetposition = max_ax;
		} else if (targetposition < min_ax) {
			range += 3;
			targetposition = min_ax;
		}

		if (FuzzyCompare.eq(ax, targetposition, range)) {
			reached = true;
		} else if (FuzzyCompare.lt(ax, targetposition, range)) {
			// if Axis is less than Target, check if Last-Axis was grater than
			// Target
			if (last_ax > ax) {
				reached = true;
			}
		} else if (FuzzyCompare.gt(ax, targetposition, range)) {
			// if Axis is less than Target, check if Last-Axis was grater than
			// Target
			if (last_ax < ax) {
				reached = true;
			}
		}
		return reached;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object o)
	{
		if (!(o instanceof HingeJoint)) {
			return false;
		}
		HingeJoint other = (HingeJoint) o;
		if (!super.equals(other)) {
			return false;
		}
		if (!FuzzyCompare.eq(ax, other.ax, 0.00001f)) {
			return false;
		}
		if (!FuzzyCompare.eq(last_ax, other.last_ax, 0.00001f)) {
			return false;
		}
		if (!FuzzyCompare.eq(min_ax, other.min_ax, 0.00001f)) {
			return false;
		}
		if (!FuzzyCompare.eq(max_ax, other.max_ax, 0.00001f)) {
			return false;
		}
		return true;
	}

	/**
	 * @return the name of the corresponding effector
	 */
	public String getEffectorName()
	{
		return effectorName;
	}
}

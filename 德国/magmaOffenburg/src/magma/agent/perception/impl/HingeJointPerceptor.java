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
package magma.agent.perception.impl;

import magma.agent.perception.IHingeJointPerceptor;
import magma.agent.perception.IPerceptor;

/**
 * Hinge Joint Perceptor
 * 
 * @author Simon Raffeiner
 */
public class HingeJointPerceptor extends Perceptor implements
		IHingeJointPerceptor
{
	private float axis;

	/**
	 * Default constructor, initializes the axis to (0.0)
	 * 
	 * @param name Perceptor name
	 */
	public HingeJointPerceptor(String name)
	{
		this(name, 0.0f);
	}

	/**
	 * Assignment constructor
	 * 
	 * @param name Perceptor name
	 * @param axis Axis value
	 */
	public HingeJointPerceptor(String name, float axis)
	{
		super(name);
		this.axis = axis;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.perception.impl.IHingeJointPerceptor#getAxis()
	 */
	public float getAxis()
	{
		return this.axis;
	}

	/**
	 * Copy values from an existing HingeJoint perceptor
	 * 
	 * @param source
	 */
	public void assign(IPerceptor source)
	{
		if (source instanceof HingeJointPerceptor) {
			HingeJointPerceptor input = (HingeJointPerceptor) source;

			axis = input.axis;
		}
	}
}

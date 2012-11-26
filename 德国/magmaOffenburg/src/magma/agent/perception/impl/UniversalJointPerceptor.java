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

import magma.agent.perception.IPerceptor;
import magma.agent.perception.IUniversalJointPerceptor;

/**
 * Universal Joint perceptor
 * 
 * @author Simon Raffeiner
 */
public class UniversalJointPerceptor extends Perceptor implements
		IUniversalJointPerceptor
{
	private float axis1, axis2;

	/**
	 * Default constructor, initalizes the axes to (0.0, 0.0)
	 * 
	 * @param name Perceptor name
	 */
	public UniversalJointPerceptor(String name)
	{
		this(name, 0.0f, 0.0f);
	}

	/**
	 * Assignment constructor
	 * 
	 * @param name Perceptor name
	 * @param axis1 Axis 1 value
	 * @param axis2 Axis 2 value
	 */
	public UniversalJointPerceptor(String name, float axis1, float axis2)
	{
		super(name);
		this.axis1 = axis1;
		this.axis2 = axis2;
	}

	@Override
	public float getAxis1()
	{
		return this.axis1;
	}

	@Override
	public float getAxis2()
	{
		return this.axis2;
	}

	@Override
	public void assign(IPerceptor source)
	{
		if (source instanceof UniversalJointPerceptor) {
			UniversalJointPerceptor input = (UniversalJointPerceptor) source;

			axis1 = input.axis1;
			axis2 = input.axis2;
		}
	}
}

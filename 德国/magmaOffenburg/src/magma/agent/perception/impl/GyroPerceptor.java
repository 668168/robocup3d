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

import magma.agent.perception.IGyroPerceptor;
import magma.agent.perception.IPerceptor;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Gyro perceptor
 * 
 * @author Simon Raffeiner
 */
public class GyroPerceptor extends Perceptor implements IGyroPerceptor
{
	private Vector3D vector;

	/**
	 * Default constructor, initializes the gyro to (0, 0, 0)
	 * 
	 * @param name Perceptor name
	 */
	public GyroPerceptor(String name)
	{
		this(name, 0.0f, 0.0f, 0.0f);
	}

	/**
	 * Assignment constructor
	 * 
	 * @param name Perceptor name
	 * @param rotationX X rotation
	 * @param rotationY Y rotation
	 * @param rotationZ Z rotation
	 */
	public GyroPerceptor(String name, float rotationX, float rotationY,
			float rotationZ)
	{
		super(name);
		this.vector = new Vector3D(rotationX, rotationY, rotationZ);
	}

	@Override
	public Vector3D getGyro()
	{
		return vector;
	}

	@Override
	public void assign(IPerceptor source)
	{
		if (source instanceof GyroPerceptor) {
			GyroPerceptor input = (GyroPerceptor) source;

			vector = input.vector;
		}
	}
}

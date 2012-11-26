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
import magma.agent.perception.IVisibleObjectPerceptor;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Visible Object
 * 
 * @author Simon Raffeiner
 * 
 */
public class VisibleObjectPerceptor extends Perceptor implements
		IVisibleObjectPerceptor
{
	// Object position
	protected Vector3D position;

	/**
	 * Default constructor
	 * 
	 * @param name Object name
	 */
	public VisibleObjectPerceptor(String name)
	{
		this(name, new Vector3D());
	}

	/**
	 * Assignment constructor
	 * @param name Object name
	 * @param position Object Position
	 */
	public VisibleObjectPerceptor(String name, Vector3D position)
	{
		super(name);
		this.position = position;
	}

	@Override
	public Vector3D getPosition()
	{
		return position;
	}

	@Override
	public void setPosition(Vector3D position)
	{
		this.position = position;
	}

	@Override
	public double getDistance()
	{
		return position.getNorm();
	}

	@Override
	public double getHorizontalAngle()
	{
		return position.getAlpha();
	}

	@Override
	public double getHorizontalAngleDeg()
	{
		return Math.toDegrees(position.getAlpha());
	}

	@Override
	public double getLatitudeAngle()
	{
		return position.getDelta();
	}

	@Override
	public double getLatitudeAngleDeg()
	{
		return Math.toDegrees(position.getDelta());
	}

	@Override
	public void assign(IPerceptor source)
	{
		if (source instanceof VisibleObjectPerceptor) {
			VisibleObjectPerceptor input = (VisibleObjectPerceptor) source;

			position = input.position;
		}
	}
}

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

/*
 * Copyright (c) 2009 Simon Raffeiner
 *
 * Hochschule Offenburg
 */
import magma.agent.perception.IForceResistancePerceptor;
import magma.agent.perception.IPerceptor;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Force resistance perceptor
 */
public class ForceResistancePerceptor extends Perceptor implements
		IForceResistancePerceptor
{
	// point where the force acts
	private Vector3D forceOrigin;

	// the force itself
	private Vector3D force;

	/**
	 * Default constructor, initializes origin and force to (0.0, 0.0, 0.0)
	 * @param name the name of the sensor
	 */
	public ForceResistancePerceptor(String name)
	{
		this(name, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	}

	/**
	 * Assignment constructor
	 * 
	 * @param name Perceptor name
	 * @param fox Force Origin - X
	 * @param foy Force Origin - Y
	 * @param foz Force Origin - Z
	 * @param fx Force - X
	 * @param fy Force - Y
	 * @param fz Force - Z
	 */
	public ForceResistancePerceptor(String name, float fox, float foy,
			float foz, float fx, float fy, float fz)
	{
		super(name);

		forceOrigin = new Vector3D(fox, foy, foz);
		force = new Vector3D(fx, fy, fz);
	}

	@Override
	public Vector3D getForceOrigin()
	{
		return forceOrigin;
	}

	@Override
	public Vector3D getForce()
	{
		return force;
	}

	@Override
	public void assign(IPerceptor source)
	{
		if (source instanceof ForceResistancePerceptor) {
			ForceResistancePerceptor input = (ForceResistancePerceptor) source;

			forceOrigin = input.forceOrigin;
			force = input.force;
		}
	}
}

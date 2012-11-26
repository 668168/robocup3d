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

import magma.agent.agentmodel.IForceResistance;
import magma.util.FuzzyCompare;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Sensor for forces to body parts of the agent
 * @author dorer
 */
public class ForceResistance extends Sensor implements IForceResistance
{
	/** id for serialization */
	private static final long serialVersionUID = 7431711977473627245L;

	/** point where the force acts */
	private Vector3D forceOrigin;

	/** the force itself */
	private Vector3D force;

	public ForceResistance(String name)
	{
		super(name);
		forceOrigin = new Vector3D();
		force = new Vector3D();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.agentmodel.impl.IForceResistance#getForceOrigin()
	 */
	public Vector3D getForceOrigin()
	{
		return forceOrigin;
	}

	public void setForceOrigin(Vector3D forceOrigin)
	{
		this.forceOrigin = forceOrigin;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.agentmodel.impl.IForceResistance#getForce()
	 */
	public Vector3D getForce()
	{
		return force;
	}

	public void setForce(Vector3D force)
	{
		this.force = force;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object o)
	{
		if (!(o instanceof ForceResistance)) {
			return false;
		}
		ForceResistance other = (ForceResistance) o;
		if (!super.equals(other)) {
			return false;
		}
		if (!FuzzyCompare.eq(force, other.force, 0.00001f)) {
			return false;
		}
		if (!FuzzyCompare.eq(forceOrigin, other.forceOrigin, 0.00001f)) {
			return false;
		}
		return true;
	}
}

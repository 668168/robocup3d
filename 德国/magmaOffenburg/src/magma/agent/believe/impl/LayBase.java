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
package magma.agent.believe.impl;

import magma.agent.agentmodel.IAgentModel;
import magma.agent.worldmodel.IGlobalMap;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Base class for laying believes
 * @author Stefan Glaser, Srinivasa Ragavan
 */
public abstract class LayBase extends Believe
{
	/**
	 * Default constructor
	 * 
	 * @param name the name of the behavior
	 * @param agent Agent model
	 * @param worldModel World model
	 */
	public LayBase(String name, IAgentModel agent, IGlobalMap worldModel)
	{
		super(name, agent, worldModel);
	}

	protected boolean laying()
	{
		Vector3D gyro = agent.getGyroRate("TorsoGyro").getTranslation();
		if (gyro.getZ() < 0.5) {
			return true;
		}
		return false;
	}
}

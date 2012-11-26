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
package magma.agent.behavior.basic;

import java.util.logging.Level;

import magma.agent.IServerConfigFilesConstants;
import magma.agent.agentmodel.IAgentModel;
import magma.agent.behavior.ICoordinator;
import magma.agent.worldmodel.IGlobalMap;

import org.apache.commons.math.geometry.Vector3D;

/**
 * This Behavior is to beam the agent somewhere to the field
 * 
 * @author Ingo Schindler
 */
public class BeamHomeBehavior extends BeamBehavior
{
	/**
	 * Default constructor
	 * @param name identifier for this behavior
	 * @param worldModel reference to the world model information
	 * @param agentModel reference to the agent's own information
	 * @param coordinator handle for action sending to server
	 */
	public BeamHomeBehavior(String name, IGlobalMap worldModel,
			IAgentModel agentModel, ICoordinator coordinator)
	{
		super(name, worldModel, agentModel, coordinator);
	}

	@Override
	public void perform(float intensity)
	{
		// the position is based on if we play left to right or right to left
		Vector3D position = worldModel.getThisPlayer().getHomePosition(
				worldModel.getPlaymode());
		// the z component is the rotation of the player
		setPos((float) position.getX(), (float) position.getY(), (float) position
				.getZ());

		super.perform(1.0f);

		// after beaming we init gyro
		agentModel.getGyroRate(IServerConfigFilesConstants.GYRORATE_NAMES[0])
				.initialize();
		logger.log(Level.FINER, "init gyro");
	}
}

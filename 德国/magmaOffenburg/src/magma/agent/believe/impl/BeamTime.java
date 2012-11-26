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

import java.util.logging.Level;

import magma.agent.IServerConfigFilesConstants;
import magma.agent.agentmodel.IAgentModel;
import magma.agent.believe.IBelieve;
import magma.agent.worldmodel.IGlobalMap;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Checks if the game is running and if not if we should beam
 * @author Klaus Dorer
 */
public class BeamTime extends Believe
{
	/**
	 * Default constructor
	 * 
	 * @param agent Agent model
	 * @param worldModel World model
	 */
	public BeamTime(IAgentModel agent, IGlobalMap worldModel)
	{
		super(IBelieve.BEAM_TIME, agent, worldModel);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.believe.impl.Believe#getTruthValue()
	 */
	@Override
	public float getTruthValue()
	{
		String playmode = worldModel.getPlaymode();
		if (playmode
				.equalsIgnoreCase(IServerConfigFilesConstants.PLAYMODE_GOAL_RIGHT)
				|| playmode
						.equalsIgnoreCase(IServerConfigFilesConstants.PLAYMODE_GOAL_LEFT)
				|| playmode
						.equalsIgnoreCase(IServerConfigFilesConstants.PLAYMODE_BEFORE_KICK_OFF)) {
			Vector3D position = worldModel.getThisPlayer().getPosition();
			Vector3D homePosition = worldModel.getThisPlayer().getHomePosition(
					playmode);

			logger.log(Level.FINE,
					"position: ({0}, {1}) home position: ({2}, {3})", new Object[] {
							position.getX(), position.getY(), homePosition.getX(),
							homePosition.getY() });

			double distance = position.subtract(homePosition).getNorm();
			if (distance > 0.3) {
				return 1.0f;
			}
		}
		return 0.0f;
	}
}

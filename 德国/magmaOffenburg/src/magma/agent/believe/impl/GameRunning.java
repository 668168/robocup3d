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
import magma.agent.believe.IBelieve;
import magma.agent.worldmodel.IGlobalMap;

/**
 * Checks if the game is running already
 * @author Klaus Dorer
 */
public class GameRunning extends Believe
{
	/**
	 * Default constructor
	 * 
	 * @param agent Agent model
	 * @param worldModel World model
	 */
	public GameRunning(IAgentModel agent, IGlobalMap worldModel)
	{
		super(IBelieve.GAME_RUNNING, agent, worldModel);
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
		if (playmode.equalsIgnoreCase("PlayOn")
				|| playmode.equalsIgnoreCase("KickOff_Left")
				|| playmode.equalsIgnoreCase("KickOff_Right")
				|| playmode.equalsIgnoreCase("Goal_Kick_Left")
				|| playmode.equalsIgnoreCase("Goal_Kick_Right")
				|| playmode.equalsIgnoreCase("Free_Kick_Left")
				|| playmode.equalsIgnoreCase("Free_Kick_Right")
				|| playmode.equalsIgnoreCase("KickIn_Left")
				|| playmode.equalsIgnoreCase("KickIn_Right")) {
			return 1.0f;
		}
		return 0.0f;
	}
}

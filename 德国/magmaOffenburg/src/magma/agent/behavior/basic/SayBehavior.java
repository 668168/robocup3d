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

import magma.agent.agentmodel.IAgentModel;
import magma.agent.behavior.ICoordinator;
import magma.agent.worldmodel.IGlobalMap;

/**
 * @author dorer Used for communication with the server
 */
public class SayBehavior extends Behavior
{
	private int callCount;

	/**
	 * @param name
	 * @param worldModel
	 * @param agentModel
	 * @param coordinator
	 */
	public SayBehavior(String name, IGlobalMap worldModel,
			IAgentModel agentModel, ICoordinator coordinator)
	{
		super(name, worldModel, agentModel, coordinator);
		callCount = 0;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.behavior.IBehavior#perform(float)
	 */
	@Override
	public void perform(float intensity)
	{
		callCount++;
		// we may only say every 3rd cycle
		if (callCount % 3 != 0) {
			return;
		}

		// only say if ball has been seen recently
		if (worldModel.getBall().getAge(worldModel.getGlobalTime()) > 2.0) {
			return;
		}

		double x = worldModel.getBall().getPosition().getX();
		double y = worldModel.getBall().getPosition().getY();
		int xShort = (int) ((x + 10) * 100);
		int yShort = (int) ((y + 5) * 100);
		String message = xShort + "-" + yShort;
		coordinator.performSay(message);
	}
}

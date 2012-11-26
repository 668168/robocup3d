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

import magma.agent.IServerConfigFilesConstants;
import magma.agent.behavior.ICoordinator;

/**
 * @author Klaus Dorer This is a class which sends each effector a command to
 *         stop
 */
public class StopBehavior extends Behavior
{
	/**
	 * Default constructor
	 * @param coordinator handle for action sending to server
	 */
	public StopBehavior(ICoordinator coordinator)
	{
		super(STOP, null, null, coordinator);
	}

	@Override
	public void perform(float intensity)
	{
		// we send a 0.0 to each effector
		for (String hingeName : IServerConfigFilesConstants.HINGEJOINT_NAMES) {
			coordinator.performAxisSpeed(hingeName, 0);
		}
	}
}

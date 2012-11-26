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
package magma.agent.behavior.motor;

import java.util.Map;

import magma.agent.agentmodel.IAgentModel;
import magma.agent.behavior.IBehavior;
import magma.agent.behavior.ICoordinator;
import magma.agent.behavior.basic.Behavior;
import magma.agent.behavior.basic.Step;
import magma.agent.worldmodel.IGlobalMap;

public abstract class MotorBehavior extends Behavior implements IBehavior
{
	/** flag to switch on and off motor file logging */
	protected static final boolean LOG = false;

	/**  */
	protected boolean finished;

	/**
	 * Default constructor for motor behaviors
	 * 
	 * @param name identifier for this behavior
	 * @param worldModel reference to the world model information
	 * @param agentModel reference to the agent's own information
	 * @param coordinator handle for action sending to server
	 */
	public MotorBehavior(String name, IGlobalMap worldModel,
			IAgentModel agentModel, ICoordinator coordinator)
	{
		super(name, worldModel, agentModel, coordinator);
		this.finished = false;
	}

	@Override
	public void init()
	{
		super.init();
		finished = false;
	}

	@Override
	public boolean isFinished()
	{
		return finished;
	}

	public Map<Integer, Step> getSteps()
	{
		return null;
	}
}
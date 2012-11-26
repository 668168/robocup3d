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
package magma.agent.behavior.complex;

import java.util.Map;

import magma.agent.agentmodel.IAgentModel;
import magma.agent.behavior.IBehavior;
import magma.agent.behavior.ICoordinator;
import magma.agent.behavior.basic.Behavior;
import magma.agent.behavior.basic.BehaviorParameter;
import magma.agent.worldmodel.IGlobalMap;

/**
 * Base class for all behaviors that use a couple of other behaviors
 * @author dorer
 */
public abstract class ComplexBehavior extends Behavior
{
	/** the behaviors that are available */
	protected final Map<String, IBehavior> behaviors;

	protected IBehavior currentBehavior;

	/**
	 * Default constructor for complex behaviors
	 * @param name name of behavior
	 * @param worldModel link to world model
	 * @param agentModel link to agent model
	 * @param params behavior parameters
	 * @param behaviors map of all available behaviors
	 */
	public ComplexBehavior(String name, IGlobalMap worldModel,
			IAgentModel agentModel, BehaviorParameter params,
			Map<String, IBehavior> behaviors)
	{
		super(name, worldModel, agentModel, null);
		this.behaviors = behaviors;
		currentBehavior = null;
	}

	public ComplexBehavior(String name, IGlobalMap worldModel,
			IAgentModel agentModel, BehaviorParameter params,
			Map<String, IBehavior> behaviors, ICoordinator coordinator)
	{
		super(name, worldModel, agentModel, coordinator);
		this.behaviors = behaviors;
		currentBehavior = null;
	}

	@Override
	public void init()
	{
		super.init();
		currentBehavior = null;
	}

}

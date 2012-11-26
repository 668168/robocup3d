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
package magma.agent.behavior.function;

import java.io.IOException;
import java.util.Collection;
import java.util.Map;

import magma.agent.agentmodel.IAgentModel;
import magma.agent.behavior.ICoordinator;
import magma.agent.behavior.motor.BasicMotorBehavior;
import magma.agent.worldmodel.IGlobalMap;

/**
 * Behavior representing motor commands based on a mathematical function
 * @author dorer
 */
public class FunctionBehavior extends BasicMotorBehavior
{
	/** map containing an entry for all joints involved in the behavior */
	protected Map<String, Function> joints;

	/** the x value at which the function should be repeated from front */
	private float period;

	/**
	 * Default constructor for motor behaviors
	 * @param name identifier for this behavior
	 * @param coordinator handle for action sending to server
	 * @param model reference to the world model information
	 * @param agentModel reference to the agent's own information
	 * @param filename the name of a file containing the parameters for this
	 *        behavior
	 * @param slowDown factor of the speed with which the behavior is performed.
	 *        2 means half the speed.
	 * @param startSlowDown the speed to approach the first value
	 */
	public FunctionBehavior(String name, ICoordinator coordinator,
			IGlobalMap model, IAgentModel agentModel, String filename,
			float slowDown, float startSlowDown)
	{
		super(name, model, agentModel, coordinator, slowDown, startSlowDown);

		FunctionBehaviorParameter parameters;
		try {
			parameters = new FunctionBehaviorParameter(filename);
			joints = parameters.getJoints();
			period = parameters.getPeriod();
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(-1);
		}
	}

	/**
	 * Default constructor for motor behaviors
	 * @param name identifier for this behavior
	 * @param coordinator handle for action sending to server
	 * @param model reference to the world model information
	 * @param agentModel reference to the agent's own information
	 * @param params parameters to control the behavior
	 * @param slowDown factor of the speed with which the behavior is performed.
	 *        2 means half the speed.
	 * @param startSlowDown the speed to approach the first value
	 */
	public FunctionBehavior(String name, ICoordinator coordinator,
			IGlobalMap model, IAgentModel agentModel,
			FunctionBehaviorParameter params, float slowDown, float startSlowDown)
	{
		super(name, model, agentModel, coordinator, slowDown, startSlowDown);
		joints = params.getJoints();
		period = params.getPeriod();
	}

	/**
	 * Returns the joint angle (in degrees) where we want to have the joint with
	 * passed name at the passed time step
	 * @param name the name of the joint as specified in
	 *        IServerConfigFilesConstants.HINGEJOINT_NAMES
	 * @param step the time step at which to calculate the angle
	 * @return the joint angle (in degrees) where we want to have the joint with
	 */
	@Override
	protected float getDesiredAngle(String name, float step)
	{
		return (float) joints.get(name).value(step);
	}

	/**
	 * @return a collection of names of those joints that are moved in this
	 *         behavior
	 */
	@Override
	protected Collection<String> getInvolvedJointNames()
	{
		return joints.keySet();
	}

	/**
	 * @return true if this behavior will finish after this step
	 */
	@Override
	protected boolean willFinish()
	{
		return currentStep >= period;
	}
}

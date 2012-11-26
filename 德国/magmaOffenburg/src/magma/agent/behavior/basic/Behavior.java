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
import java.util.logging.Logger;

import magma.agent.IServerConfigFilesConstants;
import magma.agent.agentmodel.IAgentModel;
import magma.agent.behavior.IBehavior;
import magma.agent.behavior.ICoordinator;
import magma.agent.worldmodel.IGlobalMap;

public abstract class Behavior implements IBehavior
{
	/** handle for logging */
	protected static Logger logger = Logger.getLogger("");

	/** the name of this behavior */
	protected final String name;

	/** parameters to influence the behavior */
	protected BehaviorParameter params;

	/** link to the world model */
	protected IGlobalMap worldModel;

	/** link to the agent model */
	protected IAgentModel agentModel;

	/** link to the coordinator module */
	protected ICoordinator coordinator;

	/** number of times this behavior was performed since creation */
	protected int performs;

	/**
	 * Default constructor for Behaviors
	 * 
	 * @param name Behavior name
	 * @param worldModel World model
	 * @param agentModel Agent model
	 * @param coordinator Coordinator
	 */
	public Behavior(String name, IGlobalMap worldModel, IAgentModel agentModel,
			ICoordinator coordinator)
	{
		this.name = name;
		this.worldModel = worldModel;
		this.agentModel = agentModel;
		this.coordinator = coordinator;
		this.performs = 0;
	}

	/**
	 * @return the number of times this behavior has been performed (inited)
	 */
	public int getPerforms()
	{
		return performs;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.behavior.IBehavior#getName()
	 */
	@Override
	public final String getName()
	{
		return name;
	}

	@Override
	public void init()
	{
		performs++;
		logger.log(Level.FINE, "triggering behavior: {0}", name);
	}

	/**
	 * By default, behaviors are finished immediately
	 * @see magma.agent.behavior.IBehavior#isFinished()
	 */
	@Override
	public boolean isFinished()
	{
		return true;
	}

	protected void checkGyro()
	{
		double error = worldModel.getLandmarkError();
		if (error < Double.MAX_VALUE) {
			logger.log(Level.FINER, "flag error: {0}", error);
		}

		if (error < 1.0 && agentModel.standingStill()) {
			// vision and agent model indicate we are standing
			agentModel.getGyroRate(IServerConfigFilesConstants.GYRORATE_NAMES[0])
					.initialize();
			logger.log(Level.FINER, "init gyro");
		} else {
			logger.log(Level.FINER, "do not init gyro error: {0}", error);
		}
	}

}

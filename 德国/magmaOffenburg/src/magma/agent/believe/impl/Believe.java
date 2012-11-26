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

import java.util.logging.Logger;

import magma.agent.agentmodel.IAgentModel;
import magma.agent.believe.IBelieve;
import magma.agent.worldmodel.IGlobalMap;

/**
 * Base class for all Believes
 */
public abstract class Believe implements IBelieve
{
	/** handle for logging */
	protected static Logger logger = Logger.getLogger("");

	/** the name of the believe used to display */
	protected String name;

	/** link to the perception module */
	// TODO to be replaced by world model and agent model
	protected IAgentModel agent;

	protected IGlobalMap worldModel;

	/**
	 * Default constructor
	 * @param name
	 */
	public Believe(String name, IAgentModel agent, IGlobalMap worldModel)
	{
		this.name = name;
		this.agent = agent;
		this.worldModel = worldModel;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.believe.IBelieve#getTruthValue()
	 */
	@Override
	public abstract float getTruthValue();

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.believe.IBelieve#getName()
	 */
	@Override
	public String getName()
	{
		return name;
	}
}

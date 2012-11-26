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
package magma.agent.decision.simple;

import java.util.Map;
import java.util.logging.Logger;

import magma.agent.behavior.IBehavior;
import magma.agent.believe.IBelieve;
import magma.agent.decision.IDecisionMaker;
import magma.agent.worldmodel.IGlobalMap;

/**
 * Base class for all decision makers
 * @author dorer
 */
public abstract class DecisionMakerBase implements IDecisionMaker
{
	/** handle for logging */
	protected static Logger logger = Logger.getLogger("");

	/** the behavior that is currently selected */
	protected IBehavior currentBehavior;

	/** the believes that are available */
	protected final Map<String, IBelieve> believes;

	/** the behaviors that are available */
	protected final Map<String, IBehavior> behaviors;

	/** the number of decisions taken */
	protected int numberOfDecisions;

	/**
	 * Default constructor
	 * @param believes believes that are available
	 * @param behaviors behaviors that are available
	 */
	public DecisionMakerBase(Map<String, IBelieve> believes,
			Map<String, IBehavior> behaviors)
	{
		this.believes = believes;
		this.behaviors = behaviors;
		numberOfDecisions = 0;
		currentBehavior = null;
	}

	@Override
	public void update(IGlobalMap map)
	{
		decide();
		numberOfDecisions++;
	}

	/**
	 * @param name the name of the believe as specified in IBelieve
	 * @return the specified believe, null if not existing
	 */
	public IBelieve getBelieve(String name)
	{
		return believes.get(name);
	}

	/**
	 * @param name the name of the behavior as specified in IBelieve
	 * @return the specified behavior, null if not existing
	 */
	public IBehavior getBehavior(String name)
	{
		return behaviors.get(name);
	}

	/**
	 * @return the number of times decide() was called
	 */
	public int getNumberOfDecisions()
	{
		return numberOfDecisions;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.decision.IDecisionMaker#decide()
	 */
	@Override
	public boolean decide()
	{
		IBehavior toExecute;

		if (numberOfDecisions == 0) {
			// we have to send the init message first
			toExecute = behaviors.get(IBehavior.INIT_BEHAVIOR);

		} else if (numberOfDecisions > 10) {
			toExecute = decideSoccer();

		} else {
			toExecute = behaviors.get(IBehavior.NONE);
		}

		if (toExecute != currentBehavior || currentBehavior.isFinished()) {
			currentBehavior = toExecute;
			currentBehavior.init();
		}

		currentBehavior.perform(1);

		return true;
	}

	/**
	 * @return the behavior to select as next to execute
	 */
	protected IBehavior decideSoccer()
	{
		if (currentBehavior != null && !currentBehavior.isFinished()) {
			// currently we are not allowing interrupting a behavior
			return currentBehavior;
		}
		return null;
	}
}

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
package magma.agent.decision;

import magma.agent.behavior.IBehavior;
import magma.agent.believe.IBelieve;
import magma.agent.worldmodel.IGlobalMap;
import magma.util.observer.IObserver;

/**
 * Interface to decision making modules
 */
public interface IDecisionMaker extends IObserver<IGlobalMap>
{
	/**
	 * Called to take a decision on what to do next. The effect of the decision
	 * will be that one or more behaviors are performed
	 * @return true if there was a decision for a behavior
	 */
	boolean decide();

	/**
	 * @param name the name of the believe as specified in IBelieve
	 * @return the specified believe, null if not existing
	 */
	IBelieve getBelieve(String name);

	/**
	 * @param name the name of the behavior as specified in IBelieve
	 * @return the specified behavior, null if not existing
	 */
	public IBehavior getBehavior(String name);
}

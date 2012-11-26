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

import magma.agent.behavior.IBehavior;
import magma.agent.believe.IBelieve;

/**
 * Basic decision making class used for testing mainly
 * @author dorer
 */
public class SimpleDecisionMaker extends DecisionMakerBase
{
	public SimpleDecisionMaker(Map<String, IBelieve> believes,
			Map<String, IBehavior> behaviors)
	{
		super(believes, behaviors);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.decision.IDecisionMaker#decide()
	 */
	@Override
	protected IBehavior decideSoccer()
	{
		IBehavior toExecute;

		if (numberOfDecisions == 2) {
			toExecute = behaviors.get(IBehavior.BEAM_HOME);

		} else if (numberOfDecisions > 20) {
			toExecute = behaviors.get(IBehavior.NONE);
		} else {
			toExecute = behaviors.get(IBehavior.NONE);
		}

		behaviors.get("Balance").perform(1);
		toExecute.perform(1);

		return toExecute;
	}
}

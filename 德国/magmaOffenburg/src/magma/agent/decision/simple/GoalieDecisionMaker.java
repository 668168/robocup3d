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
 * Simple decision maker for primitive field player
 * @author dorer
 */
public class GoalieDecisionMaker extends SoccerPlayerDecisionMaker
{

	static boolean changedMode = false;

	public GoalieDecisionMaker(Map<String, IBelieve> believes,
			Map<String, IBehavior> behaviors, int serverVersion)
	{
		super(believes, behaviors, serverVersion);
	}

	/**
	 * @return Walk behavior if no team mate is closer to ball side step behavior
	 *         to ball
	 */
	@Override
	protected IBehavior movement()
	{
		IBelieve criticalArea = believes.get(IBelieve.BALL_IN_CRITICAL_AREA);
		if (criticalArea.getTruthValue() > 0.5) {
			return behaviors.get(IBehavior.GET_IN_SCORE_POSITION);
		}

		return behaviors.get(IBehavior.GET_TO_INITIAL_POSITION);
	}
}

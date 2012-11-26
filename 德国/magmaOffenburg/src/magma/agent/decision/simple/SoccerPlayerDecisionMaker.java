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
import magma.agent.worldmodel.IGlobalMap;

/**
 * Simple decision maker for primitive field player
 * @author dorer
 */
public class SoccerPlayerDecisionMaker extends SoccerDecisionMaker
{
	private IBehavior alternatingBehavior;

	public SoccerPlayerDecisionMaker(Map<String, IBelieve> believes,
			Map<String, IBehavior> behaviors, int serverVersion)
	{
		super(believes, behaviors, serverVersion);

		alternatingBehavior = null;
	}

	/**
	 * Called by the receiver of messages to trigger decision
	 */
	@Override
	public void update(IGlobalMap map)
	{
		super.update(map);

		// "turn head left to right and back", alternate "look down"
		if (serverVersion >= 61) {
			if (alternatingBehavior == null || alternatingBehavior.isFinished()) {
				alternatingBehavior = behaviors.get(IBehavior.TURN_HEAD);
				alternatingBehavior.init();
			}
			alternatingBehavior.perform(1);
		}

		// say something
		IBehavior sayBehavior = behaviors.get(IBehavior.SAY_BEHAVIOR);
		sayBehavior.perform(1);
	}
}

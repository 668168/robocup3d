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

import java.util.Iterator;
import java.util.List;
import java.util.logging.Level;

import magma.agent.agentmodel.IAgentModel;
import magma.agent.believe.IBelieve;
import magma.agent.worldmodel.IGlobalMap;
import magma.agent.worldmodel.IMoveableObject;
import magma.agent.worldmodel.IPlayer;
import magma.agent.worldmodel.IThisPlayer;

/**
 * Checks if any teammate is closer to the ball
 * @author Klaus Dorer
 */
public class TeammateCloserToBall extends Believe
{
	/**
	 * Default constructor
	 * 
	 * @param agent Agent model
	 * @param worldModel World model
	 */
	public TeammateCloserToBall(IAgentModel agent, IGlobalMap worldModel)
	{
		super(IBelieve.TEAMMATE_CLOSER_TO_BALL, agent, worldModel);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.believe.impl.Believe#getTruthValue()
	 */
	@Override
	public float getTruthValue()
	{
		// TODO: change to use getOwnTeam once available. Or even better create
		// indexical functional object teammateAtBall
		IPlayer playerAtBall = null;
		IThisPlayer thisPlayer = worldModel.getThisPlayer();
		List<IPlayer> players = worldModel.getOwnPlayers();
		Iterator<IPlayer> playerIterator = players.iterator();
		double smallestDistance = Double.MAX_VALUE;
		IMoveableObject ball = worldModel.getBall();
		float age = -1;

		float time = worldModel.getGlobalTime();
		while (playerIterator.hasNext()) {
			IPlayer currentPlayer = playerIterator.next();
			if (currentPlayer != null && currentPlayer.isOwnTeam()
					&& currentPlayer.getID() != thisPlayer.getID()) {
				age = currentPlayer.getAge(time);
				if (age < 4.0) {
					// only take into account recently seen players
					if (!currentPlayer.isGoalie()) {
						// we do not want to include the goalie into calculation
						double distance = currentPlayer.getDistanceTo(ball);
						if (distance < smallestDistance) {
							smallestDistance = distance;
							playerAtBall = currentPlayer;
						}
					}
				}
			}
		}

		if (playerAtBall == null) {
			// no other team mates visible
			logger.log(Level.FINE, "Teammate closer: no other player");
			return 0.0f;
		} else {
			double ownDistanceToBall = thisPlayer.getDistanceTo(ball);
			// TODO use fuzzy compare with some overlap
			logger
					.log(
							Level.FINE,
							"Teammate closer: smallestDistance: {0} myDistance: {1} age: {2} id: {3}",
							new Object[] { smallestDistance, ownDistanceToBall, age,
									playerAtBall.getID() });

			boolean iShouldStart = true;
			double delta = ownDistanceToBall - smallestDistance;
			if (delta > 0.3) {
				return 1.0f;

			} else if (delta < -0.3) {
				return 0.0f;

			} else {
				if ((worldModel.getGlobalTime() % 6) / 3 < 1) {
					if (thisPlayer.getID() == 2) {
						iShouldStart = false;
					}
				} else {
					if (thisPlayer.getID() == 3) {
						iShouldStart = false;
					}
				}
				if (iShouldStart) {
					return 0.0f;
				} else {
					return 1.0f;
				}
			}
		}
	}
}

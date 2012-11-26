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

import java.util.logging.Level;

import magma.agent.agentmodel.IAgentModel;
import magma.agent.believe.IBelieve;
import magma.agent.worldmodel.IGlobalMap;
import magma.agent.worldmodel.IMoveableObject;
import magma.agent.worldmodel.IThisPlayer;

/**
 * Checks if the ball is close enough to be kicked
 * @author Klaus Dorer
 */
public class BallKickable extends Believe
{
	/**
	 * Default constructor
	 * 
	 * @param agent Agent model
	 * @param worldModel World model
	 */
	public BallKickable(IAgentModel agent, IGlobalMap worldModel)
	{
		super(IBelieve.BALL_KICKABLE, agent, worldModel);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.believe.impl.Believe#getTruthValue()
	 */
	@Override
	public float getTruthValue()
	{
		IThisPlayer thisPlayer = worldModel.getThisPlayer();
		IMoveableObject ball = worldModel.getBall();
		double ownDistanceToBall = thisPlayer.getDistanceToXY(ball.getPosition());
		double ballAngle = thisPlayer.getBodyDirectionTo(ball.getPosition())
				.degrees();

		logger.log(Level.FINE, "Kickable: Distance: {0}, Angle: {1}",
				new Object[] { ownDistanceToBall, ballAngle });

		// TODO use fuzzy compare with some overlap
		if (ownDistanceToBall < 0.4) {
			return 1.0f;
		}
		return 0.0f;
	}
}

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
package magma.agent.behavior.complex;

import java.util.Map;
import java.util.logging.Level;

import magma.agent.agentmodel.IAgentModel;
import magma.agent.behavior.IBehavior;
import magma.agent.behavior.basic.BehaviorParameter;
import magma.agent.worldmodel.IGlobalMap;
import magma.agent.worldmodel.IMoveableObject;
import magma.agent.worldmodel.IThisPlayer;
import magma.util.geometry.Angle;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Behavior to run to the ball
 * @author dorer
 */
public class RunToBall extends ComplexBehavior
{
	protected IBehavior currentBehavior;

	/**
	 * Default constructor
	 * 
	 * @param globalMap Global map
	 * @param agentModel Agent model
	 * @param params Behavior parameters
	 * @param behaviors behavior list
	 */
	public RunToBall(IGlobalMap globalMap, IAgentModel agentModel,
			BehaviorParameter params, Map<String, IBehavior> behaviors)
	{
		super(IBehavior.RUN_TO_BALL, globalMap, agentModel, params, behaviors);
		currentBehavior = null;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.behavior.IBehavior#perform(float)
	 */
	@Override
	public void perform(float intensity)
	{

		if (currentBehavior == null || currentBehavior.isFinished()) {
			double ballAngle = Math.toDegrees(worldModel.getBall()
					.getHorizontalDirection());

			logger.log(Level.FINE, "runToBall angle: {0}", ballAngle);

			if (ballAngle > 40) {
				currentBehavior = behaviors.get(IBehavior.TURN_LEFT_40);
			} else if (ballAngle < -40) {
				currentBehavior = behaviors.get(IBehavior.TURN_RIGHT_40);
			} else {
				currentBehavior = behaviors.get(IBehavior.WALK);
			}

			// Calculate whether the straight line between player and ball hits the
			// goal
			IThisPlayer thisPlayer = worldModel.getThisPlayer();
			IMoveableObject ball = worldModel.getBall();
			Vector3D ballPos = ball.getPosition();
			Vector3D ownPos = thisPlayer.getPosition();
			// double goalDistance = thisPlayer.getDistanceTo(worldModel
			// .getOtherGoalPosition());
			// double ownGoalDistance = thisPlayer.getDistanceTo(worldModel
			// .getOwnGoalPosition());
			Angle ballAngle1 = thisPlayer.getBodyDirectionTo(ballPos);
			// Angle goalAngle1 = thisPlayer.getBodyDirectionTo(worldModel
			// .getOtherGoalPosition());
			// Angle delta = goalAngle1.subtract(ballAngle1);

			double ballAngle2 = ballAngle1.degrees();
			// double goalAngle = goalAngle1.degrees();

			// Calculate the position where the straight line through the player
			// and
			// the ball will cross the end of the field

			double m = 0;
			double b = 0;

			// Decide on which goal are we playing and calculate the straight line
			double x = worldModel.getOtherGoalPosition().getX();
			if (x < 0) {
				// Playing to the left goal
				m = (ballPos.getY() - ownPos.getY())
						/ (ballPos.getX() - ownPos.getX());

				b = ballPos.getY() - m * ownPos.getX();

			} else {
				// Playing to the right goal
				m = (ownPos.getY() - ballPos.getY())
						/ (ownPos.getX() - ballPos.getX());

				b = ownPos.getY() - m * ballPos.getX();

			}

			// Calculate the Y point of the goal line where the ball will cross the
			// line if we perform a straight kick
			double y = m * x + b;

			// The straight line will not hit the goal
			logger.log(Level.FINE, "runToBall2 ballAngle2: {0} y:{1}",
					new Object[] { ballAngle2, y });

			if (y > 0.7 && ballAngle2 < 15) {
				currentBehavior = behaviors.get(IBehavior.TURN_RIGHT_40);
			} else if (y < -0.7 && ballAngle2 > -15) {
				currentBehavior = behaviors.get(IBehavior.TURN_LEFT_40);
			} else {
				currentBehavior = behaviors.get(IBehavior.WALK);
			}

			currentBehavior.init();
		}

		currentBehavior.perform(intensity);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.behavior.impl.Behavior#isFinished()
	 */
	@Override
	public boolean isFinished()
	{
		if (currentBehavior != null) {
			return currentBehavior.isFinished();
		} else {
			return true;
		}
	}
}

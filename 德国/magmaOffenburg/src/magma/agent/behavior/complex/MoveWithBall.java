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

import magma.agent.IMagmaConstants;
import magma.agent.agentmodel.IAgentModel;
import magma.agent.behavior.IBehavior;
import magma.agent.behavior.basic.BehaviorParameter;
import magma.agent.worldmodel.IGlobalMap;
import magma.agent.worldmodel.IThisPlayer;
import magma.util.FuzzyCompare;
import magma.util.geometry.Angle;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Behavior to run to the ball
 * 
 * @author Klaus Dorer
 */
public class MoveWithBall extends ComplexBehavior
{

	private IBehavior currentBehavior;

	private char side;

	private IThisPlayer thisPlayer = worldModel.getThisPlayer();

	private Vector3D ballPosition;

	private Vector3D goalCentre;

	private boolean leftSide;

	private boolean rightSide;

	private double zAngle;

	/**
	 * Default constructor
	 * 
	 * @param globalMap Global map
	 * @param agentModel Agent model
	 * @param params Behavior parameters
	 * @param behaviors behavior list
	 */
	public MoveWithBall(IGlobalMap globalMap, IAgentModel agentModel,
			BehaviorParameter params, Map<String, IBehavior> behaviors)
	{
		super(IBehavior.MOVE_WITH_BALL, globalMap, agentModel, params, behaviors);
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

			side = worldModel.getThisPlayer().getSide();
			rightSide = side == IMagmaConstants.RIGHT_SIDE;
			leftSide = side == IMagmaConstants.LEFT_SIDE;
			ballPosition = worldModel.getBall().getPosition();
			zAngle = 0.0;

			Vector3D newPosition = calculateNewXY();
			if (rightSide)// invert values for playing from right side
			{
				newPosition = new Vector3D(-newPosition.getX(),
						-newPosition.getY(), 0);
				zAngle = 180.0;
			}

			if (!checkAngle(zAngle)) { // player is facing somewhere other than
				// opponent's goal
				turnPlayer(zAngle);
			}

			else if (thisPlayer.getPosition().getY() - newPosition.getY() < -0.3) {
				// move left
				currentBehavior = behaviors.get(STEP_LEFT);
			}

			else if (thisPlayer.getPosition().getY() - newPosition.getY() > 0.3) {
				// move right
				currentBehavior = behaviors.get(STEP_RIGHT);
			}

			else if (thisPlayer.getPosition().getX() - newPosition.getX() < -1.5) {
				// move forward
				currentBehavior = behaviors.get(STEP_FORWARD);
			}

			else if (thisPlayer.getPosition().getX() - newPosition.getX() > 1.5) {
				// move backward
				currentBehavior = behaviors.get(STEP_BACKWARD);
			}

			else
				currentBehavior = behaviors.get(NONE);

			currentBehavior.init();
		}
		currentBehavior.perform(intensity);
	}

	// TODO to be used after extreme testing. unable to view in real time so far!
	// :-(

	private boolean checkAngle(double angle)
	{
		return equals(thisPlayer.getHorizontalAngle(), Angle.deg(zAngle), Math
				.toRadians(10))
				|| equals(thisPlayer.getHorizontalAngle(), Angle.deg(-zAngle), Math
						.toRadians(10));
	}

	public boolean equals(Angle angle1, Angle angle2, double range)
	{

		if (angle1.radians() < angle2.radians() + range
				&& angle1.radians() > angle2.radians() - range) {
			return true;
		}

		return false;
	}

	private void turnPlayer(double angle)
	{
		if (Angle.deg(zAngle).isLeftOf(thisPlayer.getHorizontalAngle())) {
			currentBehavior = behaviors.get(TURN_LEFT_20);
		} else
			currentBehavior = behaviors.get(TURN_RIGHT_20);
	}

	private Vector3D calculateNewXY()
	{
		double newY = 0;
		double slope;
		float maxForwardGoalie;
		float maxForwardPlayer;
		double goalieDistanceWithBall;
		double playerDistanceWithBall;

		if (leftSide) {
			maxForwardGoalie = -5.0f;
			maxForwardPlayer = -2.0f;
			goalieDistanceWithBall = -5.0;
			playerDistanceWithBall = -2.0;
		}
		// right side
		else {
			maxForwardGoalie = 5.0f;
			maxForwardPlayer = 2.0f;
			goalieDistanceWithBall = 5.0;
			playerDistanceWithBall = 2.0;
		}

		goalCentre = worldModel.getOwnGoalPosition();

		// straight line equation
		slope = ballPosition.getY() / (ballPosition.getX() - goalCentre.getX());
		newY = slope * thisPlayer.getPosition().getX() - slope
				* goalCentre.getX();

		double newX = 0;

		if (thisPlayer.getID() == 1) {

			if (FuzzyCompare.eq((float) thisPlayer.getPosition().getX(),
					maxForwardGoalie, 0.1f)) // so that goalie doesn't leave the
				// penalty rectangle.
				newX = thisPlayer.getPosition().getX();
			else
				newX = ballPosition.getX() + goalieDistanceWithBall;

		} else if (thisPlayer.getID() == 2) {
			if (FuzzyCompare.eq((float) thisPlayer.getPosition().getX(),
					maxForwardPlayer, 0.1f))// so that player doesn't leave our half.
				newX = ballPosition.getX() + playerDistanceWithBall;
			else
				newX = ballPosition.getX() + 2.0;
		}
		return new Vector3D(newX, newY, 0);
	}

	// private float calculateRot()
	// {
	// return (float) worldModel.getOwnGoalPosition().subtract(ballPosition)
	// .negate().getNorm();
	// }

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.behavior.impl.Behavior#isFinished()
	 */
	@Override
	public boolean isFinished()
	{
		if (currentBehavior != null)
			return currentBehavior.isFinished();
		else
			return true;
	}
}

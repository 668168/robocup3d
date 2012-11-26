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

import magma.agent.IMagmaConstants;
import magma.agent.agentmodel.IAgentModel;
import magma.agent.behavior.IBehavior;
import magma.agent.behavior.basic.BehaviorParameter;
import magma.agent.worldmodel.IGlobalMap;
import magma.agent.worldmodel.IThisPlayer;
import magma.util.geometry.Angle;
import magma.util.geometry.Geometry;

import org.apache.commons.math.geometry.Vector3D;

/**
 * @author Pret
 * 
 */

public class GoalieBehavior extends ComplexBehavior
{
	Vector3D ballPosition;

	IThisPlayer goalie;

	boolean rightSide;

	boolean leftSide;

	private double zAngle;

	/**
	 * @param action
	 * @param params
	 */
	public GoalieBehavior(IGlobalMap globalMap, IAgentModel agentModel,
			BehaviorParameter params, Map<String, IBehavior> behaviors)
	{
		super(IBehavior.GOALIE_BEHAVIOR, globalMap, agentModel, params, behaviors);
		currentBehavior = null;
	}

	@Override
	public void perform(float intensity)
	{
		if (currentBehavior == null || currentBehavior.isFinished()) {

			ballPosition = worldModel.getBall().getPosition();
			goalie = worldModel.getThisPlayer();
			leftSide = goalie.getSide() == IMagmaConstants.LEFT_SIDE;
			rightSide = goalie.getSide() == IMagmaConstants.RIGHT_SIDE;
			boolean none = false;

			float newY = calculateNewGoaliePos(ballPosition.getX(), ballPosition
					.getY());
			if (newY == 0.7f || newY == -0.7f)
				none = true;
			zAngle = 0.0;
			if (rightSide)// inverting y values for right side.
			{
				newY = -newY;
				zAngle = 180.0;
			}
			Vector3D newPosition = new Vector3D(goalie.getPosition().getX(), newY,
					0.0);

			// log
			logger.log(Level.FINE,
					"Goalie behavior. new position - x,y,z : ({0}, {1}, {2})",
					new Object[] { newPosition.getX(), newPosition.getY(),
							newPosition.getZ() });

			// ball kick-able and isSafeToKick(when kicked will not be self goal)
			if (isSafeToKick()) {
				// kick with right or left foot
				currentBehavior = behaviors.get(IBehavior.SHOOT_TO_GOAL);

			} else if (!checkAngle(zAngle)) { // player is facing somewhere other
				// than
				// opponent's goal
				turnPlayer(zAngle);
			} else if (Geometry.isInsidePolygon(ballPosition,
					getBallToBeKickedRectangle())) {
				currentBehavior = behaviors.get(IBehavior.GET_IN_SCORE_POSITION);
			} else if (!none
					&& goalie.getPosition().getY() - newPosition.getY() < -0.2) {
				// move left
				currentBehavior = behaviors.get(STEP_LEFT);
			} else if (!none
					&& goalie.getPosition().getY() - newPosition.getY() > 0.2) {
				// move right
				currentBehavior = behaviors.get(STEP_RIGHT);
			}
			// else
			// currentBehavior = behaviors.get(NONE);
			//
			// // distance to newPosition is greater than distance to ball
			// // TODO also check if opponent is closer than you
			// else if (FuzzyCompare.gt((float) worldModel.getThisPlayer()
			// .getDistanceTo(newPosition), (float) worldModel.getThisPlayer()
			// .getDistanceTo(worldModel.getBall()), 0.3f)) {
			// // run to ball
			// // TODO change run_to_ball to something else
			// System.out
			// .println("----------------------------------------********----------run to ball");
			// currentBehavior = behaviors.get(IBehavior.RUN_TO_BALL);
			// }
			// // distance to position smaller
			// else if (FuzzyCompare.lt((float) worldModel.getThisPlayer()
			// .getDistanceTo(newPosition), (float) worldModel.getThisPlayer()
			// .getDistanceTo(worldModel.getBall()), 0.3f)) {
			// // run to position
			// System.out
			// .println("----------------------------------------********----------run to p");
			// /** ====> */
			// System.out.println("my x=" + thisPlayer.getPosition().getX()
			// + " y=" + thisPlayer.getPosition().getY() + " z="
			// + thisPlayer.getPosition().getZ());
			//
			// System.out.println("x=" + newPosition.getX() + " y="
			// + newPosition.getY() + " z=" + newPosition.getZ());
			//
			// System.out.println("new ops="
			// + worldModel.getThisPlayer().getDistanceTo(newPosition)
			// + " ball="
			// + worldModel.getThisPlayer().getDistanceTo(
			// worldModel.getBall()));
			// currentBehavior = behaviors.get(IBehavior.RUN_TO_POSITION);
			// ((RunToPosition) currentBehavior).setPosition(newPosition,
			// calculateRot());
			//
			// }
			else {
				currentBehavior = behaviors.get(IBehavior.NONE);
			}
			currentBehavior.init();
		}
		currentBehavior.perform(intensity);

	}

	@SuppressWarnings("unused")
	private boolean isCoordinateOnLeft()
	{
		return false;
	}

	@SuppressWarnings("unused")
	private boolean isCoordinateOnRight()
	{
		return false;
	}

	private boolean isSafeToKick()
	{
		// ball kick-able, goalie facing the ball and kick angle away from the
		// goal
		double ballAngle = worldModel.getBall().getHorizontalDirection();
		if (worldModel.getThisPlayer().getDistanceTo(worldModel.getBall()) < 0.3
				&& ballAngle > Math.toRadians(-60)
				&& ballAngle < Math.toRadians(60)
				&& worldModel.getThisPlayer().getPosition().getZ() < 1.6
				&& worldModel.getThisPlayer().getPosition().getZ() > -1.6) {

			return true;
		}

		// log
		// logger.log(Level.FINE,
		// "safe to kick is false : ({0}, {1}, {2})",
		// new Object[] { newPosition.getX(), newPosition.getY(),
		// newPosition.getZ() });

		return false;
	}

	// private Vector3D calculateNewXY()
	// {
	// double newY = 0;
	// double slope;
	//
	// Vector3D goalCentre = worldModel.getOwnGoalPosition();
	//
	// // straight line equation
	// slope = ballPosition.getY() / (ballPosition.getX() - goalCentre.getX());
	// newY = slope * thisPlayer.getPosition().getX() - slope
	// * goalCentre.getX();
	//
	// double factor = 0.0;
	// if (thisPlayer.getSide() == IMagmaConstants.LEFT_SIDE)
	// factor = -0.2;
	// else
	// factor = 0.2;
	//
	// double newX = ballPosition.getX() + factor;
	//
	// return new Vector3D(newX, newY, 0);
	// }

	@SuppressWarnings("unused")
	private float calculateRot()
	{
		return (float) worldModel.getOwnGoalPosition().subtract(ballPosition)
				.negate().getNorm();
	}

	private float calculateNewGoaliePos(double ballX, double ballY)
	{
		float newY = (float) ((1.1) * (ballY) / (6.1 + ballY));
		if (newY < -0.7f || goalie.getPosition().getY() < -0.7f)
			return -0.7f;
		else if (newY > 0.7f || goalie.getPosition().getY() > 0.7f)
			return 0.7f;

		return newY;
	}

	/**
	 * @return the rectangle in which the ball is kickable sidewise by right leg
	 */
	private Vector3D[] getBallToBeKickedRectangle()
	{

		// points are relative to player coordinates
		if (leftSide) {
			double[][] points = { { -6, 1.2 }, { -4, 1.2 }, { -4, -1.2 },
					{ -6, -1.2 } };
			return Geometry.getPolygon(points);
		}

		else if (rightSide) {
			double[][] points = { { 6, 1.2 }, { 6, -1.2 }, { 4, -1.2 }, { 4, 1.2 } };
			return Geometry.getPolygon(points);
		}
		return new Vector3D[2];

	}

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

	private boolean checkAngle(double angle)
	{
		return equals(goalie.getHorizontalAngle(), Angle.deg(zAngle), Math
				.toRadians(10))
				|| equals(goalie.getHorizontalAngle(), Angle.deg(-zAngle), Math
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
		if (Angle.deg(zAngle).isLeftOf(goalie.getHorizontalAngle())) {
			currentBehavior = behaviors.get(TURN_LEFT_20);
		} else
			currentBehavior = behaviors.get(TURN_RIGHT_20);
	}

}

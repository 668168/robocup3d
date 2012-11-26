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
import magma.util.geometry.Geometry;

import org.apache.commons.math.geometry.Vector3D;

public class ShootToGoal extends ComplexBehavior
{
	private static final double MAX_X_KICK = 0.21;

	private static final double MAX_Y_KICK = 0.15;

	private static final double MAX_X_BOTH = 0.15;

	private static final double MAX_Y_BOTH = 0.015;

	private static final double MAX_X_SIDEKICK = 0.12;

	private static final double MAX_Y_SIDEKICK = 0.17;

	public ShootToGoal(IGlobalMap worldModel, IAgentModel agentModel,
			BehaviorParameter params, Map<String, IBehavior> behaviors)
	{
		super(IBehavior.SHOOT_TO_GOAL, worldModel, agentModel, params, behaviors);
	}

	@Override
	public void perform(float intensity)
	{
		if (currentBehavior == null || currentBehavior.isFinished()) {
			currentBehavior = getBehavior();
			currentBehavior.init();
		}
		currentBehavior.perform(intensity);
	}

	/**
	 * @return the appropriate behavior for kicking
	 */
	private IBehavior getBehavior()
	{
		IBehavior result;
		IThisPlayer thisPlayer = worldModel.getThisPlayer();
		IMoveableObject ball = worldModel.getBall();
		Vector3D ballPos = ball.getPosition();
		Vector3D ownPos = thisPlayer.getPosition();

		double ownDistanceToBall = thisPlayer.getDistanceToXY(ballPos);
		double goalDistance = thisPlayer.getDistanceTo(worldModel
				.getOtherGoalPosition());
		double ownGoalDistance = thisPlayer.getDistanceTo(worldModel
				.getOwnGoalPosition());
		Angle ballAngle1 = thisPlayer.getBodyDirectionTo(ballPos);
		Angle goalAngle1 = thisPlayer.getBodyDirectionTo(worldModel
				.getOtherGoalPosition());
		Angle delta = goalAngle1.subtract(ballAngle1);

		double ballAngle = ballAngle1.degrees();
		double goalAngle = goalAngle1.degrees();

		// Calculate the position where the straight line through the player and
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

		// LOG
		logger.log(Level.FINE,
				"Kick: Distance: {0} BallAngle: {1} goalAngle: {2} "
						+ "ball observed distance: {3} last seen: {4}", new Object[] {
						ownDistanceToBall, ballAngle, goalAngle, ball.getDistance(),
						ball.getLastSeenTime() });

		logger.log(Level.FINE, "Kick: ballPos: {0};{1} playerPos: {2};{3} ",
				new Object[] { ballPos.getX(), ballPos.getY(),
						thisPlayer.getPosition().getX(),
						thisPlayer.getPosition().getY() });

		// if (Math.abs(goalAngle) < 30) {
		// if your direction is pointed to the ball
		// and you are able to shoot between the two goalPost
		// then kick

		if ((goalDistance < 2 && y < 0.7 && y > -0.7 && Math.abs(ballAngle) < 45)
				|| (goalDistance > 2 && ownGoalDistance > 3
						&& Math.abs(ballAngle) < 30 && Math.abs(goalAngle) < 30)
				|| (ownGoalDistance < 3 && Math.abs(ballAngle) < 30 && Math
						.abs(goalAngle) < 80)) {

			// we are aligned to goal
			if (thisPlayer.isInsidePolygonXY(ballPos, getBothLegKickRectangle())) {
				// ball is kickable by both feet
				if (goalAngle < 0) {
					// the goal is to the right, kicking with left leg in this
					// area usually lets the ball drift right of the straight line
					// from robot through ball is of the left side of the goal center
					return behaviors.get(IBehavior.SHOOT_LEFT);

				} else {
					return behaviors.get(IBehavior.SHOOT_RIGHT);
				}

				// ball kickable by single leg?
			} else if (thisPlayer.isInsidePolygonXY(ballPos,
					getLeftLegKickRectangle())) {
				return behaviors.get(IBehavior.SHOOT_LEFT);

			} else if (thisPlayer.isInsidePolygonXY(ballPos,
					getRightLegKickRectangle())) {
				return behaviors.get(IBehavior.SHOOT_RIGHT);

			} else if (Math.abs(ballAngle) < 20) {
				// ball is ahead
				return behaviors.get(IBehavior.FORWARD);

			} else if (ballAngle > 50 && ballAngle < 90) {
				// ball is left and in front
				return behaviors.get(IBehavior.STEP_LEFT);

			} else if (ballAngle < -50 && ballAngle > -90) {
				// ball is right and in front

				return behaviors.get(IBehavior.STEP_RIGHT);

			}
		}

		// not facing to goal direction
		if (Math.abs(delta.degrees()) < 35) {
			// ball and goal direction are aligned
			/*
			 * if (ballAngle > 70) { return
			 * behaviors.get(IBehavior.SIDE_KICK_LEFT); } else if (ballAngle < -70)
			 * { return behaviors.get(IBehavior.SIDE_KICK_RIGHT); } else
			 */
			// side kick possible ?
			if (thisPlayer.isInsidePolygonXY(ballPos,
					getLeftLegSideKickRectangle())) {
				return behaviors.get(IBehavior.SIDE_KICK_LEFT);

			} else if (thisPlayer.isInsidePolygonXY(ballPos,
					getRightLegSideKickRectangle())) {
				return behaviors.get(IBehavior.SIDE_KICK_RIGHT);

				// turn necessary?
			} else if ((result = getTurnBehavior(ballAngle)) != null) {
				return result;

			} else {
				return behaviors.get(IBehavior.FORWARD);
			}

		} else {
			// ball and goal are not aligned
			if (Math.abs(ballAngle) < 50) {
				// ball is in front: move round ball
				if (goalAngle < 0) {
					return behaviors.get(IBehavior.INWARD_TURN_LEFT45);
				} else {
					return behaviors.get(IBehavior.INWARD_TURN_RIGHT45);
				}

			} else if (goalAngle > 0 && delta.degrees() > 0) {
				// goal is further left than ball
				return behaviors.get(IBehavior.FORWARD);

			} else if (goalAngle < 0 && delta.degrees() < 0) {
				// goal is further right than ball
				return behaviors.get(IBehavior.FORWARD);

			} else {
				// ball angle is bigger than goal angle, so we turn
				return getTurnBehavior(ballAngle);
			}
		}
	}

	/**
	 * @param angle the angle of the desired direction (in degrees)
	 * @return the appropriate turn behavior, null if turning is not appropriate
	 */
	private IBehavior getTurnBehavior(double angle)
	{
		if (angle > 60) {
			return behaviors.get(IBehavior.TURN_LEFT_60);
		} else if (angle < -60) {
			return behaviors.get(IBehavior.TURN_RIGHT_60);
		} else if (angle > 40) {
			return behaviors.get(IBehavior.TURN_LEFT_40);
		} else if (angle < -40) {
			return behaviors.get(IBehavior.TURN_RIGHT_40);
		} else if (angle > 20) {
			return behaviors.get(IBehavior.TURN_LEFT_20);
		} else if (angle < -20) {
			return behaviors.get(IBehavior.TURN_RIGHT_20);
		}
		return null;
	}

	/**
	 * @return the rectangle in which the ball is kickable by both legs
	 */
	private Vector3D[] getBothLegKickRectangle()
	{
		// points are relative to player coordinates
		double[][] points = { { 0, MAX_Y_BOTH }, { MAX_X_BOTH, MAX_Y_BOTH },
				{ MAX_X_BOTH, -MAX_Y_BOTH }, { 0, -MAX_Y_BOTH } };
		return Geometry.getPolygon(points);
	}

	/**
	 * @return the rectangle in which the ball is kickable by left leg
	 */
	private Vector3D[] getLeftLegKickRectangle()
	{
		// points are relative to player coordinates
		double[][] points = { { 0, MAX_Y_KICK }, { MAX_X_KICK, MAX_Y_KICK },
				{ MAX_X_KICK, 0 }, { 0, 0 } };
		return Geometry.getPolygon(points);
	}

	/**
	 * @return the rectangle in which the ball is kickable by right leg
	 */
	private Vector3D[] getRightLegKickRectangle()
	{
		// points are relative to player coordinates
		double[][] points = { { 0, 0 }, { MAX_X_KICK, 0 },
				{ MAX_X_KICK, -MAX_Y_KICK }, { 0, -MAX_Y_KICK } };
		return Geometry.getPolygon(points);
	}

	/**
	 * @return the rectangle in which the ball is kickable sidewise by left leg
	 */
	private Vector3D[] getLeftLegSideKickRectangle()
	{
		// points are relative to player coordinates
		double[][] points = { { -MAX_X_SIDEKICK, MAX_Y_SIDEKICK },
				{ MAX_X_SIDEKICK, MAX_Y_SIDEKICK }, { MAX_X_SIDEKICK, 0 },
				{ -MAX_X_SIDEKICK, 0 } };
		return Geometry.getPolygon(points);
	}

	/**
	 * @return the rectangle in which the ball is kickable sidewise by right leg
	 */
	private Vector3D[] getRightLegSideKickRectangle()
	{
		// points are relative to player coordinates
		double[][] points = { { -MAX_X_SIDEKICK, 0 }, { MAX_X_SIDEKICK, 0 },
				{ MAX_X_SIDEKICK, -MAX_Y_SIDEKICK },
				{ -MAX_X_SIDEKICK, -MAX_Y_SIDEKICK } };
		return Geometry.getPolygon(points);
	}

	@Override
	public boolean isFinished()
	{
		if (currentBehavior == null) {
			return true;
		}
		return currentBehavior.isFinished();
	}
}

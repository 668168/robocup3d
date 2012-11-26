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
import magma.agent.worldmodel.IThisPlayer;

import org.apache.commons.math.geometry.Vector3D;

public class RunToPosition extends ComplexBehavior
{
	protected static final int ANGULAR_PRECISION = 30;

	protected static final float DISTANCE_PRECISION = 0.3f;

	private static final float STOP_RUN_DISTANCE = 0.5f;

	protected float rotation;

	protected Vector3D position;

	protected boolean turnedLeftBefore;

	protected boolean turnedRightBefore;

	public RunToPosition(IGlobalMap worldModel, IAgentModel agentModel,
			BehaviorParameter params, Map<String, IBehavior> behaviors)
	{
		this(IBehavior.RUN_TO_POSITION, worldModel, agentModel, params, behaviors);
	}

	public RunToPosition(String name, IGlobalMap worldModel,
			IAgentModel agentModel, BehaviorParameter params,
			Map<String, IBehavior> behaviors)
	{
		super(name, worldModel, agentModel, params, behaviors);

		position = new Vector3D();
		turnedLeftBefore = false;
		turnedRightBefore = false;
	}

	@Override
	public void perform(float intensity)
	{
		if (currentBehavior == null || currentBehavior.isFinished()) {

			IThisPlayer thisPlayer = worldModel.getThisPlayer();
			float distanceToTarget = (float) thisPlayer.getDistanceToXY(position);
			double directionToTarget = thisPlayer.getBodyDirectionTo(position)
					.degrees();

			if (distanceToTarget < DISTANCE_PRECISION) {
				// once reached the position we turn to the desired direction
				directionToTarget = rotation;
			}

			logger
					.log(
							Level.FINE,
							"runToPosition far distanceToTarget: {0} directionToTarget: {1}",
							new Object[] { distanceToTarget, directionToTarget });

			// check if we can make side steps
			// if (distanceToTarget > DISTANCE_PRECISION && distanceToTarget < 0.7)
			// {
			// if (targetAngle > Math.toRadians(45)
			// && targetAngle < Math.toRadians(90)) {
			// sideStepLeft();
			// } else if (targetAngle < Math.toRadians(-45)
			// && targetAngle > Math.toRadians(-90)) {
			// sideStepRight();
			// }
			// }

			// or do we prefer to turn
			if (!turnedRightBefore && directionToTarget > ANGULAR_PRECISION) {
				turnLeft(directionToTarget);

			} else if (!turnedLeftBefore && directionToTarget < -ANGULAR_PRECISION) {
				turnRight(directionToTarget);

			} else {
				walk(distanceToTarget);
			}
		}
		currentBehavior.perform(intensity);
	}

	protected void turnLeft(double deltaAngle)
	{
		switchTo(getTurnLeftBehavior(deltaAngle));
	}

	protected void turnRight(double deltaAngle)
	{
		switchTo(getTurnRightBehavior(deltaAngle));
	}

	// private void sideStepLeft()
	// {
	// switchTo(IBehavior.STEP_LEFT);
	// }
	//
	// private void sideStepRight()
	// {
	// switchTo(IBehavior.STEP_RIGHT);
	// }

	private void walk(float distance)
	{
		boolean checkGyro = false;
		turnedLeftBefore = false;
		turnedRightBefore = false;

		if (currentBehavior == null) {
			if (distance > DISTANCE_PRECISION) {
				currentBehavior = behaviors.get(IBehavior.START_WALK);
				checkGyro = true;
			} else {
				// at destination
				currentBehavior = behaviors.get(IBehavior.NONE);
			}
			currentBehavior.init();
			checkGyro = true;

		} else if (currentBehavior.isFinished()) {
			if (walking()) {
				if (distance > STOP_RUN_DISTANCE) {
					currentBehavior = behaviors.get(IBehavior.CONTINUE_RUN);
				} else if (distance > DISTANCE_PRECISION) {
					currentBehavior = behaviors.get(IBehavior.CONTINUE_WALK);
				} else {
					currentBehavior = behaviors.get(IBehavior.STOP_WALK);
				}
			} else {
				if (distance > DISTANCE_PRECISION) {
					currentBehavior = behaviors.get(IBehavior.START_WALK);
					checkGyro = true;
				} else {
					// at destination
					currentBehavior = behaviors.get(IBehavior.NONE);
				}
			}
			currentBehavior.init();
		}

		// resetting gyro
		if (checkGyro) {
			checkGyro();
		}
	}

	/**
	 * 
	 */
	private void switchTo(String behavior)
	{
		if (currentBehavior == null) {
			currentBehavior = behaviors.get(behavior);
			currentBehavior.init();

		} else if (currentBehavior.isFinished()) {
			if (!walking()) {
				currentBehavior = behaviors.get(behavior);
			} else {
				currentBehavior = behaviors.get(IBehavior.STOP_WALK);
			}
			currentBehavior.init();
		}
	}

	/**
	 * @return
	 */
	private String getTurnLeftBehavior(double deltaAngle)
	{
		turnedLeftBefore = true;
		turnedRightBefore = false;
		if (deltaAngle > 50) {
			return IBehavior.TURN_LEFT_60;
		}
		if (deltaAngle > 30) {
			return IBehavior.TURN_LEFT_40;
		}
		return IBehavior.TURN_LEFT_20;
	}

	/**
	 * @return
	 */
	private String getTurnRightBehavior(double deltaAngle)
	{
		turnedRightBefore = true;
		turnedLeftBefore = false;
		if (deltaAngle < -50) {
			return IBehavior.TURN_RIGHT_60;
		}
		if (deltaAngle < -30) {
			return IBehavior.TURN_RIGHT_40;
		}
		return IBehavior.TURN_RIGHT_20;
	}

	/**
	 * @return
	 */
	private boolean walking()
	{
		if (currentBehavior == null) {
			return false;
		}
		return IBehavior.START_WALK.equals(currentBehavior.getName())
				|| IBehavior.CONTINUE_WALK.equals(currentBehavior.getName())
				|| IBehavior.CONTINUE_RUN.equals(currentBehavior.getName());
	}

	public void setPosition(float x, float y, float rotation)
	{
		setPosition(new Vector3D(x, y, 0), rotation);
	}

	public void setPosition(Vector3D newPosition, float rotation)
	{
		this.position = newPosition;
		this.rotation = rotation;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.behavior.impl.Behavior#isFinished()
	 */
	@Override
	public boolean isFinished()
	{
		if (!walking()) {
			return currentBehavior.isFinished();
		} else {
			return false;
		}
	}
}

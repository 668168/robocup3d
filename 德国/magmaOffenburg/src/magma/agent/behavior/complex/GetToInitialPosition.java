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

import magma.agent.IServerConfigFilesConstants;
import magma.agent.agentmodel.IAgentModel;
import magma.agent.behavior.IBehavior;
import magma.agent.behavior.basic.BehaviorParameter;
import magma.agent.worldmodel.IGlobalMap;
import magma.agent.worldmodel.IThisPlayer;

import org.apache.commons.math.geometry.Vector3D;

/**
 * @author Pret
 * 
 */
public class GetToInitialPosition extends RunToPosition
{

	/**
	 * @param action
	 * @param params
	 */
	public GetToInitialPosition(IGlobalMap globalMap, IAgentModel agentModel,
			BehaviorParameter params, Map<String, IBehavior> behaviors)
	{
		super(IBehavior.GET_TO_INITIAL_POSITION, globalMap, agentModel, params,
				behaviors);
		currentBehavior = null;
	}

	// right now this behavior used only for goalie.
	// TODO To use for other players if needed.
	@Override
	public void perform(float intensity)
	{
		if (currentBehavior == null || currentBehavior.isFinished()) {
			boolean didSomething = getCurrentBehavior();
			if (!didSomething) {
				super.perform(intensity);
				return;
			}
		}
		currentBehavior.perform(intensity);
	}

	/**
	 * calculates a point on a circle from the own goal to which to go
	 */
	private boolean getCurrentBehavior()
	{
		IThisPlayer thisPlayer = worldModel.getThisPlayer();
		Vector3D home = thisPlayer.getHomePosition("doesNotMatter");
		Vector3D ourPos = thisPlayer.getPosition();
		Vector3D ownGoal = worldModel.getOwnGoalPosition();
		Vector3D ball = worldModel.getBall().getPosition();
		double distanceX = IServerConfigFilesConstants.FIELD_LENGTH
				- Math.abs(home.getX());

		// destination position is certain distance from goal in line with ball
		Vector3D goalBallDir = new Vector3D(distanceX, ball.subtract(ownGoal)
				.normalize());
		Vector3D goalBall = ownGoal.add(goalBallDir);

		setPosition((float) goalBall.getX(), (float) goalBall.getY(),
				(float) goalBall.getAlpha());
		double directionToTarget = thisPlayer.getBodyDirectionTo(position)
				.degrees();

		rotation = (float) directionToTarget;
		float distanceToTarget = (float) thisPlayer.getDistanceToXY(position);

		if (distanceToTarget < DISTANCE_PRECISION) {
			directionToTarget = thisPlayer.getBodyDirectionTo(ball).degrees();
			rotation = (float) directionToTarget;
		}

		logger.log(Level.FINE,
				"initial pos: ({0},{1}) distanceToTarget: {2} directionToTarget: {3} "
						+ "ourpos: ({4},{5})", new Object[] { goalBall.getX(),
						goalBall.getY(), distanceToTarget, directionToTarget,
						ourPos.getX(), ourPos.getY() });

		if (distanceToTarget < DISTANCE_PRECISION) {
			// we are at the desired position
			// make sure that we are also in desired direction
			if (!turnedLeftBefore && directionToTarget > ANGULAR_PRECISION
					&& directionToTarget <= 90) {
				turnLeft(directionToTarget);
				return true;
			}

			if (!turnedLeftBefore && directionToTarget < -ANGULAR_PRECISION
					&& directionToTarget >= -90) {
				turnRight(directionToTarget - 180);
				return true;
			}

			if (!turnedLeftBefore && directionToTarget > 90
					&& directionToTarget < (180 - ANGULAR_PRECISION)) {
				turnRight(directionToTarget - 180);
				return true;
			}

			if (!turnedRightBefore && directionToTarget < -90
					&& directionToTarget > -180 + ANGULAR_PRECISION) {
				turnLeft(180 + directionToTarget);
				return true;
			}
		}

		if (directionToTarget > 50 && directionToTarget < 130) {
			// position is left
			currentBehavior = behaviors.get(IBehavior.STEP_LEFT);
			return true;
		}

		if (directionToTarget < -50 && directionToTarget > -130) {
			// position is right
			currentBehavior = behaviors.get(IBehavior.STEP_RIGHT);
			return true;
		}

		if (directionToTarget > 90 || directionToTarget < -90) {
			// or do we prefer to turn
			if (!turnedLeftBefore && directionToTarget > 0
					&& directionToTarget < (180 - ANGULAR_PRECISION)) {
				turnRight(directionToTarget - 180);
				return true;
			}

			if (!turnedRightBefore && directionToTarget < -ANGULAR_PRECISION) {
				turnLeft(180 + directionToTarget);
				return true;
			}
			currentBehavior = behaviors.get(IBehavior.STEP_BACKWARD);
			return true;
		}
		return false;
	}
}

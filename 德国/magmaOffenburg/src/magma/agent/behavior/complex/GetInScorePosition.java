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

import magma.agent.agentmodel.IAgentModel;
import magma.agent.behavior.IBehavior;
import magma.agent.behavior.basic.BehaviorParameter;
import magma.agent.worldmodel.IGlobalMap;
import magma.agent.worldmodel.IThisPlayer;
import magma.agent.worldmodel.IVisibleObject;
import magma.util.geometry.Angle;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Behavior to get in a suitable scoring position, behind the ball, in line with
 * opponent's goal and ball
 * 
 * @author Mathias Ehret
 */
public class GetInScorePosition extends ComplexBehavior
{
	private static final float BALL_KEEP_AWAY_DISTANCE = 0.7f;

	/**
	 * Default constructor
	 * 
	 * @param globalMap Global map
	 * @param agentModel Agent model
	 * @param params Behavior parameters
	 * @param behaviors behavior list
	 */
	public GetInScorePosition(IGlobalMap globalMap, IAgentModel agentModel,
			BehaviorParameter params, Map<String, IBehavior> behaviors)
	{
		super(IBehavior.GET_IN_SCORE_POSITION, globalMap, agentModel, params,
				behaviors);
		currentBehavior = null;
	}

	@Override
	public void perform(float intensity)
	{
		if (currentBehavior == null || currentBehavior.isFinished()) {

			currentBehavior = behaviors.get(IBehavior.RUN_TO_POSITION);

			currentBehavior.init();
		}

		double[] position = getPosition();
		Vector3D posVector = new Vector3D(position[0], position[1], 0);
		float angle = (float) position[2];
		RunToPosition run = (RunToPosition) currentBehavior;

		if (worldModel.getThisPlayer().getDistanceTo(posVector) > 0.4) {
			run.setPosition(posVector, angle);
		} else {
			// when close we run directly to ball
			run.setPosition(worldModel.getBall().getPosition(), angle);
		}

		currentBehavior.perform(intensity);
	}

	double[] getPosition()
	{
		Vector3D ballPosition = worldModel.getBall().getPosition();
		IThisPlayer thisPlayer = worldModel.getThisPlayer();

		Vector3D shootVector = worldModel.getOtherGoalPosition().subtract(
				ballPosition);
		Vector3D scorePosition = ballPosition.add(-0.25, shootVector.normalize());

		if (thisPlayer.getDistanceTo(ballPosition) < thisPlayer
				.getDistanceTo(scorePosition)) {
			Angle delta1 = thisPlayer.getDirectionTo(ballPosition).subtract(
					thisPlayer.getDirectionTo(scorePosition));
			double delta = Math.abs(delta1.degrees());

			if (delta < 90) {
				// We have to run around the ball
				scorePosition = calculateAlternativePosition(ballPosition,
						thisPlayer, scorePosition);
			} else if (delta < 140) {
				scorePosition = ballPosition.add(-BALL_KEEP_AWAY_DISTANCE,
						shootVector.normalize());
			}
		}
		return new double[] { scorePosition.getX(), scorePosition.getY(),
				shootVector.getAlpha() };
	}

	private Vector3D calculateAlternativePosition(Vector3D ballPosition,
			IVisibleObject thisPlayer, Vector3D scorePosition)
	{
		Vector3D intermediatePosition = ballPosition.subtract(
				thisPlayer.getPosition()).normalize();

		// find out which way is shorter
		Vector3D intermediate1 = new Vector3D(intermediatePosition.getY(),
				-intermediatePosition.getX(), intermediatePosition.getZ());
		Vector3D intermediate2 = new Vector3D(-intermediatePosition.getY(),
				intermediatePosition.getX(), intermediatePosition.getZ());

		intermediate1 = ballPosition.add(new Vector3D(BALL_KEEP_AWAY_DISTANCE,
				intermediate1));
		intermediate2 = ballPosition.add(new Vector3D(BALL_KEEP_AWAY_DISTANCE,
				intermediate2));

		float way1 = (float) (thisPlayer.getDistanceTo(intermediate1) + scorePosition
				.subtract(intermediate1).getNorm());
		float way2 = (float) (thisPlayer.getDistanceTo(intermediate2) + scorePosition
				.subtract(intermediate2).getNorm());

		if (way1 < way2) {
			scorePosition = intermediate1;
		} else {
			scorePosition = intermediate2;
		}
		return (scorePosition);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.behavior.impl.Behavior#isFinished()
	 */
	@Override
	public boolean isFinished()
	{
		return currentBehavior.isFinished();
	}
}

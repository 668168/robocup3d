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
package magma.agent.worldmodel.impl;

import magma.agent.IServerConfigFilesConstants;
import magma.agent.perception.IVisibleObjectPerceptor;
import magma.agent.worldmodel.IMoveableObject;
import magma.agent.worldmodel.IThisPlayer;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Represents the ball of the game
 */
public class Ball extends MovableObject implements IMoveableObject
{
	/** id of this class for serialization */
	private static final long serialVersionUID = 9252371297804616L;

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.worldmodel.impl.IBall#getFuturePositions(int)
	 */
	@Override
	public Vector3D[] getFuturePositions(int aHowMany)
	{
		Vector3D[] futurePositions = new Vector3D[aHowMany];
		futurePositions[0] = getPosition().add(
				getSpeed().scalarMultiply(IServerConfigFilesConstants.BALL_DECAY));
		if (aHowMany > 1) {
			futurePositions[1] = futurePositions[0].add(futurePositions[0]
					.subtract(getPosition()).scalarMultiply(
							IServerConfigFilesConstants.BALL_DECAY));
			for (int i = 2; i < aHowMany; i++) {
				futurePositions[i] = futurePositions[i - 1]
						.add(futurePositions[i - 1].subtract(futurePositions[i - 2])
								.scalarMultiply(IServerConfigFilesConstants.BALL_DECAY));
			}
		}
		return futurePositions;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.worldmodel.impl.MovableObject#getPossibleSpeed()
	 */
	@Override
	public double getPossibleSpeed()
	{
		return 6.0;
	}

	/**
	 * Updates this object with the latest perception
	 * @param time the global time stamp of the vision
	 * @param ballVision new perception of Ball
	 */
	@Override
	public void update(IVisibleObjectPerceptor ballVision, float time,
			IThisPlayer thisPlayer)
	{
		super.update(ballVision, time, thisPlayer);
	}
}
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
package magma.agent.worldmodel.localizer.impl;

import java.util.HashMap;

import magma.agent.worldmodel.localizer.ILocalizationFlag;
import magma.util.geometry.PositionOrientation;

import org.apache.commons.math.geometry.Vector3D;

// Attention!! Support for setting coordinates of flags discontinued
// Fix this before using this localizer
public class LocalizerInsideRectangle extends Localizer
{
	@Override
	public PositionOrientation localize(
			HashMap<String, ILocalizationFlag> flags, float neckYaw,
			float neckPitch, Vector3D gyro)
	{
		return null;
		// float xTop = 0; // x position of the agent calculated from F1L and F1R
		// float yLeft = 0; // y position of the agent calculated from F1L and F2L
		// float xBottom = 0; // x position of the agent calculated from F2L and
		// // F2R
		// float yRight = 0; // x position of the agent calculated from F1R and
		// F2R
		// float x = 0; // final x position of the agent
		// float y = 0; // final y position of the agent
		// float[] absViewAngle = { 0, 0, 0, 0 }; // Absolute view angle
		// // F1L,F2L,F1R,F2R
		// ILocalizationFlag F1L = flags
		// .get(IServerConfigFilesConstants.LANDMARK_NAMES[4]);
		// ILocalizationFlag F2L = flags
		// .get(IServerConfigFilesConstants.LANDMARK_NAMES[5]);
		// ILocalizationFlag F1R = flags
		// .get(IServerConfigFilesConstants.LANDMARK_NAMES[6]);
		// ILocalizationFlag F2R = flags
		// .get(IServerConfigFilesConstants.LANDMARK_NAMES[7]);
		// if (F1L == null || F2L == null || F1R == null || F2R == null) {
		// return null;
		// }
		// // Convert the field x and y value into a normal coordinate system with
		// // 0/0 in the left bottom
		// // Attention!! Support for setting coordinates of flags discontinued
		// // Fix this before using this localizer
		// // float fieldLength = 0; // length of the field
		// // float fieldWidth = 0; // width of the field
		// // fieldLength = (float) Math.sqrt(Math.pow(F1L.getPosition().getX(),
		// 2))
		// // + (float) Math.sqrt(Math.pow(F1R.getPosition().getX(), 2));
		// // fieldWidth = (float) Math.sqrt(Math.pow(F1L.getPosition().getY(),
		// 2))
		// // + (float) Math.sqrt(Math.pow(F2L.getPosition().getY(), 2));
		// // Change the X,Y values of the flags to the normal coordinate system
		//
		// // F1L.setX(0f);
		// // F1L.setY(fieldWidth);
		// // F2L.setX(0f);
		// // F2L.setY(0f);
		// // F1R.setX(fieldLength);
		// // F1R.setY(fieldWidth);
		// // F2R.setX(fieldLength);
		// // F2R.setY(0f);
		//
		// // Calculate xTop
		// xTop = calculateXPosition(F1L, F1R);
		// // Calculate yLeft
		// yLeft = calculateYPosition(F2L, F1L);
		// // Calculate xBottom
		// xBottom = calculateXPosition(F2L, F2R);
		// // Calculate yRight
		// yRight = calculateYPosition(F2R, F1R);
		// // Calculate the average value of x and y
		// x = (xTop + xBottom) / 2;
		// y = (yLeft + yRight) / 2;
		//
		// // Convert from x axis to the field x values
		// if (y <= 4) {
		// y = -1 * (4 - y);
		// } else {
		// y = y - 4;
		// }
		//
		// // Convert from y axis to the field y values
		// if (x <= 6) {
		// x = -1 * (6 - x);
		// } else {
		// x = x - 6;
		// }
		//
		// // Print out the actual calculated position of the agent on the field
		// // Reset the X,Y values of the flags
		//
		// // Attention!! Support for setting coordinates of flags discontinued
		// // Fix this before using this localizer
		// // F1L.setX((float)
		// IServerConfigFilesConstants.LANDMARK_POSITIONS[4][0]);
		// // F1L.setY((float)
		// IServerConfigFilesConstants.LANDMARK_POSITIONS[4][1]);
		// // F2L.setX((float)
		// IServerConfigFilesConstants.LANDMARK_POSITIONS[5][0]);
		// // F2L.setY((float)
		// IServerConfigFilesConstants.LANDMARK_POSITIONS[5][1]);
		// // F1R.setX((float)
		// IServerConfigFilesConstants.LANDMARK_POSITIONS[6][0]);
		// // F1R.setY((float)
		// IServerConfigFilesConstants.LANDMARK_POSITIONS[6][1]);
		// // F2R.setX((float)
		// IServerConfigFilesConstants.LANDMARK_POSITIONS[7][0]);
		// // F2R.setY((float)
		// IServerConfigFilesConstants.LANDMARK_POSITIONS[7][1]);
		//
		// // Calculate the view angle for the four flags
		// absViewAngle[0] = calculateViewAngle(x, y, F1L);
		// absViewAngle[1] = calculateViewAngle(x, y, F2L);
		// absViewAngle[2] = calculateViewAngle(x, y, F1R);
		// absViewAngle[3] = calculateViewAngle(x, y, F2R);
		// double finalViewAngle = averageAngle(absViewAngle);
		//
		// Vector3D[] result = new Vector3D[2];
		// result[0] = new Vector3D(x, y, 0);
		// result[1] = new Vector3D(finalViewAngle, 0, 0);
		// return result;
	}

	/**
	 * @param x the x coordinate of the player (global coordinate system)
	 * @param y the y coordinate of the player (global coordinate system)
	 * @param flag the flag with respect to which to calculate
	 * @return the absolute view angle of the player (rad)
	 */
	float calculateViewAngle(float x, float y, ILocalizationFlag flag)
	{
		return 0;
		// float deltaX = (float) flag.getKnownPosition().getX() - x;
		// float deltaY = (float) flag.getKnownPosition().getY() - y;
		// if (FuzzyCompare.eq(deltaX, 0.0f, 0.001f)) {
		// if (y > flag.getKnownPosition().getY()) {
		// // directly above flag
		// return (float) (-Angle.RAD90 - flag.getHorizontalDirection());
		// } else {
		// // directly below flag
		// return (float) (Angle.RAD90 - flag.getHorizontalDirection());
		// }
		// }
		//
		// float result;
		// if (x > flag.getKnownPosition().getX()) {
		// // right of flag
		// result = (float) (Math.atan(deltaY / deltaX)
		// - flag.getHorizontalDirection() + Angle.RAD180);
		// } else {
		// // left of flag
		// result = (float) (Math.atan(deltaY / deltaX) - flag
		// .getHorizontalDirection());
		// }
		// return (float) Angle.normalize(result);
	}

	/**
	 * 
	 * @param F1
	 * @param F2
	 * @return
	 */
	@SuppressWarnings("unused")
	private float calculateYPosition(ILocalizationFlag F1, ILocalizationFlag F2)
	{
		return (float) (((Math.pow(F2.getDistance(), 2))
				- (Math.pow(F1.getDistance(), 2))
				- (Math.pow(F2.getKnownPosition().getY(), 2)) - (Math.pow(F1
				.getKnownPosition().getY(), 2))) / (-2
				* F2.getKnownPosition().getY() + 2 * F1.getKnownPosition().getY()));
	}

	/**
	 * 
	 * @param F1
	 * @param F2
	 * @return
	 */
	@SuppressWarnings("unused")
	private float calculateXPosition(ILocalizationFlag F1, ILocalizationFlag F2)
	{
		return (float) (((Math.pow(F2.getDistance(), 2))
				- (Math.pow(F1.getDistance(), 2))
				- (Math.pow(F2.getKnownPosition().getX(), 2)) - (Math.pow(F1
				.getKnownPosition().getX(), 2))) / (-2
				* F2.getKnownPosition().getX() + 2 * F1.getKnownPosition().getX()));
	}
}

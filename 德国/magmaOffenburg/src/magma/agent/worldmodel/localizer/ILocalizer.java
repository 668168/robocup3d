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
package magma.agent.worldmodel.localizer;

import java.util.HashMap;

import magma.util.geometry.PositionOrientation;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Implementations are able to calculate the agent's position from the passed
 * relative information of landmarks
 */
public interface ILocalizer
{
	/**
	 * Calculates absolute position and directions.
	 * @param flags visible landmarks with known position to be used for
	 *        localization
	 * @param neckYawAngle the horizontal neck angle (yaw) of the viewer
	 * @param neckPitchAngle the vertical neck angle (pitch) of the viewer
	 * @return an array of two Vector3Ds, the first containing the absolute x,y,z
	 *         position of the viewer on the field, the second containing no real
	 *         vector, but the horizontal, latitudal and rotational absolute
	 *         angles of the viewer.
	 */
	PositionOrientation localize(HashMap<String, ILocalizationFlag> flags,
			float neckYawAngle, float neckPitchAngle, Vector3D gyro);
}

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
package magma.agent.worldmodel;

import magma.agent.perception.IPerception;
import magma.util.geometry.Angle;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Interface to access visible player information
 * @author dorer
 */
public interface IThisPlayer extends IPlayer
{
	/**
	 * @return the rotation (rad) of the body around the z-axis
	 */
	Angle getHorizontalAngle();

	/**
	 * @return the rotation (rad) of the body around the y-axis
	 */
	Angle getVerticalAngle();

	/**
	 * Returns the relative angle (rad) this player's torso has to the specified
	 * position
	 * @param position the position to which to calculate the body angle
	 * @return the relative angle (rad) this player's torso has to the specified
	 *         position
	 */
	Angle getBodyDirectionTo(Vector3D position);

	/**
	 * @return the rotation of the camera around the x-axis
	 */
	Angle getTiltAngle();

	/**
	 * @param
	 * @return vector of the start position of the player (to which it beams)
	 */
	Vector3D getHomePosition(String playmode);

	/**
	 * @return IMagmaConstants.RIGHT_SIDE if player is playing from right to
	 *         left, IMagmaConstants.LEFT_SIDE if playing from left to right
	 */
	char getSide();

	/**
	 * @return true if this is the goal keeper of our team
	 */
	boolean isGoalie();

	/**
	 * Called on each perception to update this player's state
	 * @param perception link to the current perception
	 */
	void updateThisPlayer(IPerception perception);

	/**
	 * @return the neckAngle (rad) turning left (>0) or right (<0)
	 */
	double getNeckYawAngle();

	/**
	 * @return the neckAngle (rad) turning up (>0) or down (<0)
	 */
	double getNeckPitchAngle();

	/**
	 * Checks if the passed 2D xy-point (absolute coordinate system) is inside
	 * the passed polygon (xy, relative coordinate system)
	 * @param absolutePosition 2D vector (x,y) of the point to check in the
	 *        global coordinate system
	 * @param polygon corner points of the polygon (x, y), in this player's
	 *        coordinate system and in clockwise order. The coordinates should
	 *        NOT take neck angles into account, i.e. assume head is straight.
	 * @return true if the point is inside the polygon
	 */
	public boolean isInsidePolygonXY(Vector3D absolutePosition,
			Vector3D[] polygon);
}
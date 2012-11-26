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

import java.util.logging.Level;

import magma.agent.IMagmaConstants;
import magma.agent.IServerConfigFilesConstants;
import magma.agent.perception.IHingeJointPerceptor;
import magma.agent.perception.IPerception;
import magma.agent.worldmodel.IThisPlayer;
import magma.util.geometry.Angle;
import magma.util.geometry.Geometry;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Container for this agent's information that is unique to the player this
 * agent is representing
 * @author dorer
 */
public class ThisPlayer extends Player implements IThisPlayer
{
	/** id of this class for serialization */
	private static final long serialVersionUID = 3307599892830771538L;

	/**
	 * the view angles (rad) of the agent with respect to the global coordinate
	 * system
	 */
	private Angle[] agentViewAngles;

	private Vector3D homePosition;

	/** the side which the player is playing */
	private char side;

	/** the angle of the head turn (rad) >0 -> left */
	private double neckYawAngle;

	/** the angle of the head turn (rad) >0 -> up */
	private double neckPitchAngle;

	public ThisPlayer(String teamname, int id)
	{
		super(id, teamname, true);
		assert id < IMagmaConstants.startPositionsOwnKickoff.length : "No startPositionLeft for player id: "
				+ id;

		agentViewAngles = new Angle[1];
		agentViewAngles[0] = Angle.rad(0);
		homePosition = null;
		side = ' ';
	}

	@Override
	public void setPosition(Vector3D position)
	{
		if (this.position == null) {
			playerInitialPosition = position;
		}
		this.position = position;

		if (homePosition == null) {
			// we can set the home position only after we know which side we play
			setHomePosition();
		}
	}

	public void updateThisPlayer(IPerception perception)
	{
		String teamSide = perception.getGameState().getTeam();
		if ("right".equalsIgnoreCase(teamSide))
			side = IMagmaConstants.RIGHT_SIDE;
		else if ("left".equalsIgnoreCase(teamSide))
			side = IMagmaConstants.LEFT_SIDE;

		IHingeJointPerceptor neck = perception
				.getHingeJointPerceptor(IServerConfigFilesConstants.HINGEJOINT_PERCEPTORS[0]);
		if (neck != null) {
			neckYawAngle = Math.toRadians(neck.getAxis());
		}

		neck = perception
				.getHingeJointPerceptor(IServerConfigFilesConstants.HINGEJOINT_PERCEPTORS[1]);
		if (neck != null) {
			neckPitchAngle = Math.toRadians(neck.getAxis());
		}
	}

	private void setHomePosition()
	{

		if (side == ' ') {
			// we still have no side information from server
			return;
		}

		int id = getID();
		float[] startPos = { 0.0f, 0.0f, 0.0f };
		if (id >= 0) {
			if (side == IMagmaConstants.LEFT_SIDE) {
				startPos = IMagmaConstants.startPositionsOwnKickoff[id];
			} else if (side == IMagmaConstants.RIGHT_SIDE) {
				startPos = IMagmaConstants.startPositionsOtherKickoff[id];
			}
		}
		homePosition = new Vector3D(startPos[0], startPos[1], startPos[2]);
	}

	/**
	 * @return 'l' if playing left, 'r' if right
	 */
	public char getSide()
	{
		return side;
	}

	@Override
	public Angle getHorizontalAngle()
	{
		return agentViewAngles[0];
	}

	@Override
	public Angle getTiltAngle()
	{
		return agentViewAngles[2];
	}

	@Override
	public Angle getVerticalAngle()
	{
		return agentViewAngles[1];
	}

	public void setHorizontalAngle(Angle angle)
	{
		agentViewAngles[0] = angle;
	}

	/**
	 * @return the homePosition
	 */
	public Vector3D getHomePosition(String playmode)
	{
		float[] startPos = { 0.0f, 0.0f, 0.0f };

		logger.log(Level.FINE, "playmode: {0}", new Object[] { playmode });

		if ((homePosition == null) || (side == IMagmaConstants.LEFT_SIDE)) {

			if (playmode
					.equalsIgnoreCase(IServerConfigFilesConstants.PLAYMODE_GOAL_RIGHT)
					|| playmode
							.equalsIgnoreCase(IServerConfigFilesConstants.PLAYMODE_BEFORE_KICK_OFF)) {
				startPos = IMagmaConstants.startPositionsOwnKickoff[getID()];
			} else {
				startPos = IMagmaConstants.startPositionsOtherKickoff[getID()];
			}
			homePosition = new Vector3D(startPos[0], startPos[1], startPos[2]);
		} else {
			if (playmode
					.equalsIgnoreCase(IServerConfigFilesConstants.PLAYMODE_GOAL_LEFT)) {
				startPos = IMagmaConstants.startPositionsOwnKickoff[getID()];
			} else {
				startPos = IMagmaConstants.startPositionsOtherKickoff[getID()];
			}
			homePosition = new Vector3D(startPos[0], startPos[1], startPos[2]);

		}

		return homePosition;
	}

	@Override
	public boolean isGoalie()
	{
		return getID() == 1;
	}

	/**
	 * @return the neckAngle (rad) turning left (>0) or right (<0)
	 */
	public double getNeckYawAngle()
	{
		return neckYawAngle;
	}

	/**
	 * @return the neckAngle (rad) turning up (>0) or down (<0)
	 */
	public double getNeckPitchAngle()
	{
		return neckPitchAngle;
	}

	/**
	 * Returns the relative angle (rad) this player's torso has to the specified
	 * position
	 * @param position the position to which to calculate the body angle
	 * @return the relative angle (rad) this player's torso has to the specified
	 *         position
	 */
	public Angle getBodyDirectionTo(Vector3D position)
	{
		return getDirectionTo(position).subtract(getHorizontalAngle());
	}

	/**
	 * Checks if the passed 2D xy-point (absolute coordinate system) is inside
	 * the passed polygon (xy, relative coordinate system)
	 * @param relativePosition 2D vector (x,y) of the point to check in the
	 *        global coordinate system
	 * @param polygon corner points of the polygon (x, y), in this player's
	 *        coordinate system and in clockwise order. The coordinates should
	 *        NOT take neck angles into account, i.e. assume head is straight.
	 * @return true if the point is inside the polygon
	 */
	public boolean isInsidePolygonXY(Vector3D absolutePosition,
			Vector3D[] polygon)
	{
		Vector3D[] polygonGlobal = new Vector3D[polygon.length];
		for (int i = 0; i < polygon.length; i++) {
			polygonGlobal[i] = getGlobalFromLocalPosition(polygon[i],
					getPosition(), getHorizontalAngle(), Angle.rad(0), 0, 0);
		}

		return Geometry.isInsidePolygon(absolutePosition, polygonGlobal);
	}
}

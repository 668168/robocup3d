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
package magma.agent.action;

/**
 * Interface to all actions an agent can perform on the server
 */
public interface IAction
{
	/**
	 * Sets the speeds of the specified universal joint to be sent with next
	 * motor action
	 * @param name name of the effector as specified in
	 *        IServerConfigFilesConstants.UNIVERSAL_JOINT_EFFECTORS
	 * @param speed1 the angular velocity1 for the joint
	 * @param speed2 the angular velocity2 for the joint
	 */
	void setUniversalEffectorSpeed(String name, float speed1, float speed2);

	/**
	 * Sets the speed of the specified hinge joint to be sent with next motor
	 * action
	 * @param name name of the effector as specified in
	 *        IServerConfigFilesConstants.HINGEJOINT_EFFECTORS
	 * @param speed the angular velocity for the joint
	 */
	void setHingeEffectorSpeed(String name, float speed);

	/**
	 * Sends the scene string which sets up the simulator
	 */
	void sendSceneString();

	/**
	 * Sends the initialization message to the server
	 */
	void sendInitString();

	/**
	 * Beams the player to specified position with specified direction
	 * @param x x coordinate on the field
	 * @param y y coordinate on the field
	 * @param rotation direction the player is facing
	 */
	void sendBeamString(float x, float y, float rotation);

	/**
	 * shouts out a message to other players
	 * @param message the message to send (max 8 bytes)
	 */
	void sendSayString(String message);

	/**
	 * Sends a motor command to the server. Includes commands to all universals
	 * and hinge joints. The speed of each joint has to be set before by
	 * setHingeEffectorSpeed()
	 */
	String sendMotorString();
}
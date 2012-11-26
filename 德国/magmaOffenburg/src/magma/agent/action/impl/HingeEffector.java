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
package magma.agent.action.impl;

import magma.agent.IServerConfigFilesConstants;

public class HingeEffector extends Effector
{
	private float speed; // zero no change of the angle

	private float last_speed; // zero no change of the angle

	public HingeEffector(String name)
	{
		super(name);
		setAxisSpeed(0.0f);
		last_speed = 0.0f;
	}

	public void setAxisSpeed(float speed)
	{
		this.speed = speed;
	}

	// returns part of the String that will be transmitted to the server
	@Override
	public String getMessageString()
	{
		String msg = "";

		if (speed != last_speed) {
			StringBuilder buffer = new StringBuilder(30);

			if (speed > IServerConfigFilesConstants.MAX_JOINT_SPEED) {
				// System.out.println("Motor speed too high: " + speed);
				speed = IServerConfigFilesConstants.MAX_JOINT_SPEED;
			} else if (speed < -IServerConfigFilesConstants.MAX_JOINT_SPEED) {
				// System.out.println("Motor speed too high: " + speed);
				speed = -IServerConfigFilesConstants.MAX_JOINT_SPEED;
			}

			buffer.append("(").append(getName());
			buffer.append(" ").append(speed).append(")");

			msg = buffer.toString();

			last_speed = speed;
		}
		speed = 0.0f;

		return msg;
	}
}

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

public class UniversalEffector extends Effector
{
	private float ax1; // zero no change of the angle

	private float ax2; // zero no change of the angle

	public UniversalEffector(String name)
	{
		super(name);

		setAxis(0, 0);
	}

	public void setAxis(float ax1, float ax2)
	{
		this.ax1 = ax1;
		this.ax2 = ax2;
	}

	// returns part of the String that will be transmitted to the server
	@Override
	public String getMessageString()
	{
		StringBuilder buffer = new StringBuilder(50);

		buffer.append("(").append(getName());
		buffer.append(" ").append(ax1);
		buffer.append(" ").append(ax2).append(")");

		ax1 = 0.0f;
		ax2 = 0.0f;

		return buffer.toString();
	}

}

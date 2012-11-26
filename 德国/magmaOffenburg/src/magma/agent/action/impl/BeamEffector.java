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

public class BeamEffector extends Effector
{
	private final float[] beam = new float[3]; // all zero no beam action

	// appears

	public BeamEffector()
	{
		super("beam");
		setBeam(0.0f, 0.0f, 0.0f); // sets values of the beam to zero
	}

	public void setBeam(float x, float y, float z)
	{
		beam[0] = x;
		beam[1] = y;
		beam[2] = z;
	}

	public float[] getBeam()
	{
		return beam;
	}

	// returns part of the String that will be transmitted to the server
	@Override
	public String getMessageString()
	{
		String msg;

		msg = "(beam " + beam[0] + " " + beam[1] + " " + beam[2] + ")";
		setBeam(0.0f, 0.0f, 0.0f); // sets values of the beam to zero

		return msg;
	}

}

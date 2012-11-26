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

/**
 * Used to register a player at the server
 * @author dorer
 */
public class InitEffector extends Effector
{
	/** the number of this player in the game */
	private int number;

	private String teamname;

	/**
	 * @param teamname name of this player's team
	 * @param number the number of this player in the game
	 */
	public InitEffector(String teamname, int number)
	{
		super("init");
		this.teamname = teamname;
		this.number = number;
	}

	/**
	 * @return number the number of this player in the game
	 */
	public int getNumber()
	{
		return number;
	}

	/**
	 * @return the String that will be transmitted to the server to setup a
	 *         player
	 */
	@Override
	public String getMessageString()
	{
		String msg;
		msg = "(init (unum " + number + ")(teamname " + teamname + "))";
		return msg;
	}
}

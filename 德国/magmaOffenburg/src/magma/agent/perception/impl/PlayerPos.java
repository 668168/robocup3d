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
package magma.agent.perception.impl;

import magma.agent.perception.IPlayerPos;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Player object
 * 
 * @author Simon Raffeiner
 * 
 */
public class PlayerPos extends VisibleObjectPerceptor implements IPlayerPos
{
	private final int id;

	private String teamname;

	/**
	 * Assignment constructor
	 * 
	 * @param position Player position
	 * @param id Player ID
	 * @param teamname Team name
	 */
	public PlayerPos(Vector3D position, int id, String teamname)
	{
		super("P", position);
		this.id = id;
		this.teamname = teamname;
	}

	@Override
	public int getId()
	{
		return id;
	}

	@Override
	public String getTeamname()
	{
		return teamname;
	}
}

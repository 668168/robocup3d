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

import magma.agent.worldmodel.IPlayer;
import magma.util.FuzzyCompare;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Represents all visible players of the own and other team. Also the own
 * position is stored as such a player object
 */
public class Player extends MovableObject implements IPlayer
{
	/** id of this class for serialization */
	private static final long serialVersionUID = 4856779909555166046L;

	/**
	 * at some point in time we might want to know how fast the opponent can be
	 * this is the fastest absolute value of the speed of this object
	 */
	private float maxObservedSpeed;

	/** the player number */
	private int id;

	/** the team name of this player */
	// TODO write teamname only once to logfiles and make it transient
	private String teamname;

	/** true if this is a player of our own team */
	private boolean ownTeam;

	/** initialPosition beforeKickoff */
	protected Vector3D playerInitialPosition;

	/**
	 * @param id the number of the player on the field
	 * @param teamname the name of the team this player plays in
	 * @param ownTeam true if this is a player of our own team
	 */
	public Player(int id, String teamname, boolean ownTeam)
	{
		super();
		this.id = id;
		this.teamname = teamname;
		this.ownTeam = ownTeam;
	}

	/**
	 * @return the fastest absolute value of the speed of this object observed so
	 *         far
	 */
	public float getMaxObservedSpeed()
	{
		return maxObservedSpeed;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.worldmodel.impl.IPlayer#getID()
	 */
	public int getID()
	{
		return id;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.worldmodel.impl.IPlayer#getTeamname()
	 */
	public String getTeamname()
	{
		return teamname;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.worldmodel.impl.MovableObject#getPossibleSpeed()
	 */
	@Override
	public double getPossibleSpeed()
	{
		return 2.0;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object o)
	{
		if (!(o instanceof Player)) {
			return false;
		}
		Player other = (Player) o;
		if (!super.equals(other)) {
			return false;
		}

		if (id != other.id) {
			return false;
		}
		if (!FuzzyCompare.eq(maxObservedSpeed, other.maxObservedSpeed, 0.00001f)) {
			return false;
		}

		return teamname.equals(other.teamname);
	}

	/**
	 * @return true if this is a player of our team
	 */
	public boolean isOwnTeam()
	{
		return ownTeam;
	}

	/**
	 * @return true if this is the goal keeper
	 */
	public boolean isGoalie()
	{
		return id == 1;
	}
}
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

import magma.agent.perception.IGameStatePerceptor;
import magma.agent.perception.IPerceptor;

public class GameStatePerceptor extends Perceptor implements
		IGameStatePerceptor
{
	private String playmode;

	private String team;

	private int unum;

	private float time;

	/*
	 * gameState: BeforeKickOff KickOff Left KickOff Right PlayOn KickIn Left
	 * KickIn Right corner kick left corner kick right goal kick left goal kick
	 * right offside left offside right GameOver Goal Left Goal Right free kick
	 * left free kick right unknown
	 */

	/**
	 * Default constructor, initializes time to 0.00 and PlayMode to "unknown"
	 */
	public GameStatePerceptor()
	{
		this(0.00f, "unknown", "unknown", 0);
	}

	/**
	 * Assignment constructor
	 * 
	 * @param time Time
	 * @param playmode Playmode
	 */
	public GameStatePerceptor(float time, String playmode, String team, int unum)
	{
		super("GS");

		this.time = time;
		this.playmode = playmode;
		this.team = team;
		this.unum = unum;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.perception.impl.IGameStatePerceptor#getPlaymode()
	 */
	public String getPlaymode()
	{
		return playmode;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.perception.impl.IGameStatePerceptor#getTime()
	 */
	public float getTime()
	{
		return time;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.perception.impl.IGameStatePerceptor#getTeam()
	 */
	public String getTeam()
	{
		return team;
	}

	/**
	 * Copy values from an existing GameState perceptor
	 * 
	 * @param source
	 */
	public void assign(IPerceptor source)
	{
		if (source instanceof GameStatePerceptor) {
			GameStatePerceptor input = (GameStatePerceptor) source;

			playmode = input.playmode;
			time = input.time;
			team = input.team;
			unum = input.unum;
		}
	}
}

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
package magma.agent.general;

import java.util.logging.Level;

import magma.agent.behavior.basic.BehaviorParameter;

public class PlayerParameters
{
	private String teamname;

	private int playerNumber;

	private String host;

	private int port;

	private BehaviorParameter behaviorParams;

	private Level level;

	private int serverVersion;

	ComponentFactory factory;

	public PlayerParameters(String teamname, int playerNumber, String host,
			int port, BehaviorParameter behaviorParams, Level level,
			int serverVersion, ComponentFactory factory)
	{
		this.teamname = teamname;
		this.playerNumber = playerNumber;
		this.host = host;
		this.port = port;
		this.behaviorParams = behaviorParams;
		this.level = level;
		this.serverVersion = serverVersion;
		if (factory == null) {
			this.factory = new ComponentFactory();
		} else {
			this.factory = factory;
		}
	}

	public String getTeamname()
	{
		return teamname;
	}

	public int getPlayerNumber()
	{
		return playerNumber;
	}

	public String getHost()
	{
		return host;
	}

	public int getPort()
	{
		return port;
	}

	public BehaviorParameter getBehaviorParams()
	{
		return behaviorParams;
	}

	public Level getLevel()
	{
		return level;
	}

	/**
	 * @return the serverVersion
	 */
	public int getServerVersion()
	{
		return serverVersion;
	}

	/**
	 * @return the factory
	 */
	public ComponentFactory getComponentFactory()
	{
		return factory;
	}
}
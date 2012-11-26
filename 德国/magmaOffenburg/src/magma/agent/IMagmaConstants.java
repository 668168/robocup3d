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
package magma.agent;

/**
 * Interface for all constants that should be globally accessible and are
 * specific to our team
 * @author dorer
 */
public interface IMagmaConstants
{
	/** the name of our team */
	String OUR_TEAMNAME = "magmaOffenburg";

	/** the number of players that play at most in one team */
	int NUMBER_OF_PLAYERS_PER_TEAM = 4;

	/** constant used to identify the id of a player that is not known */
	int UNKNOWN_PLAYER_NUMBER = -1;

	/** constant used to identify the team name of a player that is not known */
	String UNKNOWN_PLAYER_TEAMNAME = "";

	/** positions the agents beam to before start if playing from left to right */
	float[][] startPositionsOwnKickoff = { { -0.17f, -0.05f, -5.0f },
			{ -5.5f, 0.0f, 0.0f }, // goalie
			{ -4.0f, 0.0f, 0.0f }, // 2
			{ -0.17f, -0.05f, -5.0f }, // 3
			{ -1.5f, 2.0f, 0.0f } // 4
	};

	/** positions the agents beam to before start if playing from right to left */
	float[][] startPositionsOtherKickoff = { { -1.5f, 0.0f, 0.0f },
			{ -5.5f, 0.0f, 0.0f }, // goalie
			{ -4.0f, 0f, 0.0f }, // 2
			{ -1.5f, 0.5f, 0.0f }, // 3
			{ -0.0f, 2.0f, 0.0f } // 4
	};

	/** side from which we play */
	char LEFT_SIDE = 'l';

	char RIGHT_SIDE = 'r';
}

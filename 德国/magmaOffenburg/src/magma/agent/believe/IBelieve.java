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
package magma.agent.believe;

/**
 * Interface to access the state of the world as propositions
 */
public interface IBelieve
{
	String LAY_ON_FRONT = "LayOnFront";

	String LAY_ON_BACK = "LayOnBack";

	String TEAMMATE_CLOSER_TO_BALL = "teammateCloserToBall";

	String BALL_KICKABLE = "ballKickable";

	String SOCCER_POSITION = "soccerPosition";

	String GAME_RUNNING = "gameRunning";

	String BEAM_TIME = "beamTime";

	String STANDING = "standing";

	String LAY_ON_SIDE = "layOnSide";

	String PLAY_DEFENSE = "defensive";

	String PLAY_OFFENSE = "offensive";

	String BALL_IN_CRITICAL_AREA = "ballInCriticalArea";

	/**
	 * Returns the truth value associated with this believe as a value between
	 * 0.0 (false) and 1.0 (true)
	 * 
	 * @return the truth value associated with this believe as a value between
	 *         0.0 (false) and 1.0 (true)
	 */
	public float getTruthValue();

	/**
	 * @return the name of the believe
	 */
	public String getName();
}

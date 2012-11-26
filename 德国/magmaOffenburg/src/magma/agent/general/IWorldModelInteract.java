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

/**
 * Interface that defines general methods for interacting with the WorldModel
 * @author Rajit Shahi
 * 
 */
public interface IWorldModelInteract
{
	/**
	 * Called to notify an observer about a Beaming
	 * @param x x coordinate to beam to
	 * @param y y coordinate to beam to
	 * @param rot rotation angle of the player
	 */
	public void beam(float x, float y, float rot);

	/**
	 * Called to notify an observer about a moving to supplied coordinate
	 * @param x x coordinate to move to
	 * @param y y coordinate to move to
	 * @param rot rotation angle of the player
	 */
	public void moveto(float x, float y, float rot);
}

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
package magma.agent.behavior;

import magma.agent.worldmodel.IGlobalMap;
import magma.util.observer.IObserver;

public interface ICoordinator extends IObserver<IGlobalMap>
{
	/**
	 * Performe axis movement with a given speed
	 * 
	 * @param hjName HingeJoint
	 * @param speed Movement speed
	 */
	public void performAxisSpeed(String hjName, float speed);

	/**
	 * Send the initialization string
	 */
	public void performInit();

	/**
	 * Beams the player to the given location with the given rotation
	 * 
	 * @param x X coordinate
	 * @param y Y coordinate
	 * @param rotation Rotation
	 */
	public void performBeam(float x, float y, float rotation);

	/**
	 * Shouts out a message to other players
	 * 
	 * @param message the message to send (max 8 bytes)
	 */
	public void performSay(String message);
}

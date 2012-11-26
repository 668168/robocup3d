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
package magma.agent.agentmodel;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Provides read only access to gyro rate sensors
 * @author dorer
 */
public interface IGyroRate
{
	/**
	 * @return the orientation of the body with respect to the global coordinate
	 *         system
	 */
	// TODO check if this is true and if not also change user manual section
	// 4.1.2
	Vector3D getGyro();

	/**
	 * @return the position of reference point (0,0,1)
	 */
	public Vector3D getTranslation();

	/**
	 * resets the gyro to upright position
	 */
	public void initialize();
}
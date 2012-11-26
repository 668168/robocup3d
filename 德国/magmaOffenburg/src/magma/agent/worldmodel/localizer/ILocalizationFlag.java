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
package magma.agent.worldmodel.localizer;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Flag / landmark that can be used for localization
 * @author dorer
 */
public interface ILocalizationFlag extends Comparable<ILocalizationFlag>
{

	/**
	 * @return the position at which we know the flag is
	 */
	Vector3D getKnownPosition();

	/**
	 * @return the observed horizontal angle under which we see the flag (rad)
	 */
	double getHorizontalDirection();

	/**
	 * @return the observed latitudal angle under which we see the flag (rad)
	 */
	double getLatitudalDirection();

	/**
	 * @return the observed distance in which we see the flag
	 */
	double getDistance();
}
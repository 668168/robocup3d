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
package magma.agent.behavior.function;

import java.io.Serializable;

/**
 * Base class for all functions used as motor functions.
 * @author dorer
 */
public interface Function extends Serializable
{
	/**
	 * Returns the function value at the passed x coordinate.
	 * @param x the coordinate at which to return the functions value
	 * @return the function value at the passed x coordinate
	 */
	double value(double x);

	/**
	 * Returns a String with comma separated values of this function to be used
	 * e.g. for file writing
	 * @param joint the name of the joint
	 * @return the String with comma separated values
	 */
	String toCSVString(String joint);
}
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
package magma.util;

/**
 * Utility to print Strings idented by tabs
 */
public class PrintUtil
{
	/**
	 * Creates and returns string containing new line character and specified
	 * number of tabs to provide indentation
	 * 
	 * @param tabs number of tabs required
	 * @return string containing new line character and the required number of
	 *         tabs
	 */
	public static String addTabs(int tabs)
	{
		StringBuffer tabBuffer = new StringBuffer((3 * tabs) + 2);

		tabBuffer.append("\n");

		for (int i = 0; i < tabs; i++) {
			tabBuffer.append("   ");
		}

		return tabBuffer.toString();
	}

}

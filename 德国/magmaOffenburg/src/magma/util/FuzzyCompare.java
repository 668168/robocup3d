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

import org.apache.commons.math.geometry.Vector3D;

/**
 * @author Ingo Schindler
 * 
 *         This class contains functions to use Fuzzy-Logic to compare float
 *         values
 */
public class FuzzyCompare
{
	/**
	 * Equal ( == )
	 * 
	 * @param first First value you want to compare
	 * @param second Second value you want to compare with the first one
	 * @param range The range within the two values are equal
	 * @return true if the both values are within the same range
	 */
	public static boolean eq(float first, float second, float range)
	{
		float g;
		float s;
		float r = range;

		if (first > second) {
			g = first;
			s = second;
		} else {
			g = second;
			s = first;
		}

		if (g - r <= s)
			return true;
		else
			return false;
	}

	/**
	 * Greater Than or Equal ( >= )
	 * 
	 * @param greater
	 * @param lower
	 * @param range
	 * @return True if greater or equal, false if not
	 */
	public static boolean gte(float greater, float lower, float range)
	{

		if (eq(greater, lower, range)) {
			return true;
		} else {
			if (greater > lower) {
				return true;
			} else {
				return false;
			}
		}

	}

	/**
	 * Lower Than or Equal ( <= )
	 * 
	 * @param lower
	 * @param greater
	 * @param range
	 * @return True if less than or equal, false if not
	 */
	public static boolean lte(float lower, float greater, float range)
	{
		return gte(greater, lower, range);
	}

	/**
	 * Greater Than ( > )
	 * 
	 * @param greater the greater of two values
	 * @param lower the lower of two values
	 * @param range the range within the greater value is not longer greater
	 * @return true if the first parameter is greater than the second one and the
	 *         second one is not within the range of the first value
	 */
	public static boolean gt(float greater, float lower, float range)
	{
		return gte(greater, lower, range);
	}

	/**
	 * Lower Than ( < )
	 * 
	 * @param lower
	 * @param greater
	 * @param range
	 * @return True if lower, false if not
	 */
	public static boolean lt(float lower, float greater, float range)
	{
		return gte(greater, lower, range);
	}

	/**
	 * Equal ( == )
	 * 
	 * @param first first vector to compare
	 * @param second second vector to compare
	 * @param range The range within the vector values are equal
	 * @return true if the both values are within the same range
	 */
	public static boolean eq(Vector3D first, Vector3D second, float range)
	{
		if (first == null && second == null) {
			return true;
		}
		if (first == null || second == null) {
			return false;
		}

		if (!eq((float) first.getX(), (float) second.getX(), range)) {
			return false;
		}
		if (!eq((float) first.getY(), (float) second.getY(), range)) {
			return false;
		}
		if (!eq((float) first.getZ(), (float) second.getZ(), range)) {
			return false;
		}
		return true;
	}

}

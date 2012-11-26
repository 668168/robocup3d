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

import org.junit.Test;

import static org.junit.Assert.assertEquals;

/**
 * @author stilnox
 * 
 */
public class FuzzyCompareTest
{

	/**
	 * Test method for {@link magma.util.FuzzyCompare#eq(float, float, float)}.
	 */
	@Test
	public void testEq()
	{
		assertEquals("EQ 10 = 10 | Range 0", true, FuzzyCompare.eq(10, 10, 0));
		assertEquals("EQ 10 = 10 | Range 5", true, FuzzyCompare.eq(10, 10, 5));
		assertEquals("EQ 10 = 9 | Range 1", true, FuzzyCompare.eq(10, 9, 1));
		assertEquals("EQ 10 = 11 | Range 1", true, FuzzyCompare.eq(10, 11, 1));
		assertEquals("EQ 10 = 8 | Range 1", false, FuzzyCompare.eq(10, 8, 1));
		assertEquals("EQ 10 = 12 | Range 1", false, FuzzyCompare.eq(10, 12, 1));
	}

	/**
	 * Test method for {@link magma.util.FuzzyCompare#gt(float, float, float)}.
	 */
	@Test
	public void testGt()
	{
		assertEquals("GT 10 > 10 | Range 0", true, FuzzyCompare.gt(10, 10, 0));
		assertEquals("GT 10 > 10 | Range 5", true, FuzzyCompare.gt(10, 10, 5));
		assertEquals("GT 10 > 9 | Range 1", true, FuzzyCompare.gt(10, 9, 1));
		assertEquals("GT 10 > 11 | Range 1", true, FuzzyCompare.gt(10, 11, 1));
		assertEquals("GT 10 > 8 | Range 1", true, FuzzyCompare.gt(10, 8, 1));
		assertEquals("GT 10 > 12 | Range 1", false, FuzzyCompare.gt(10, 12, 1));
	}

	/**
	 * Test method for {@link magma.util.FuzzyCompare#lt(float, float, float)}.
	 */
	@Test
	public void testLt()
	{
		assertEquals("LT 10 < 10 | Range 0", true, FuzzyCompare.lt(10, 10, 0));
		assertEquals("LT 10 < 10 | Range 5", true, FuzzyCompare.lt(10, 10, 5));
		assertEquals("LT 10 < 9 | Range 1", true, FuzzyCompare.lt(10, 9, 1));
		assertEquals("LT 10 < 11 | Range 1", true, FuzzyCompare.lt(10, 11, 1));
		assertEquals("LT 10 < 8 | Range 1", false, FuzzyCompare.lt(10, 8, 1));
		assertEquals("LT 10 < 12 | Range 1", true, FuzzyCompare.lt(10, 12, 1));
	}

	/**
	 * Test method for {@link magma.util.FuzzyCompare#gte(float, float, float)}.
	 */
	@Test
	public void testGte()
	{
		assertEquals("GTE 10 > 10 | Range 0", true, FuzzyCompare.gte(10, 10, 0));
		assertEquals("GTE 10 > 10 | Range 5", true, FuzzyCompare.gte(10, 10, 5));
		assertEquals("GTE 10 > 9 | Range 1", true, FuzzyCompare.gte(10, 9, 1));
		assertEquals("GTE 10 > 11 | Range 1", true, FuzzyCompare.gte(10, 11, 1));
		assertEquals("GTE 10 > 8 | Range 1", true, FuzzyCompare.gte(10, 8, 1));
		assertEquals("GTE 10 > 12 | Range 1", false, FuzzyCompare.gte(10, 12, 1));
	}

	/**
	 * Test method for {@link magma.util.FuzzyCompare#lte(float, float, float)}.
	 */
	@Test
	public void testLte()
	{
		assertEquals("LTE 10 < 10 | Range 0", true, FuzzyCompare.lte(10, 10, 0));
		assertEquals("LTE 10 < 10 | Range 5", true, FuzzyCompare.lte(10, 10, 5));
		assertEquals("LTE 10 < 9 | Range 1", true, FuzzyCompare.lte(10, 9, 1));
		assertEquals("LTE 10 < 11 | Range 1", true, FuzzyCompare.lte(10, 11, 1));
		assertEquals("LTE 10 < 8 | Range 1", false, FuzzyCompare.lte(10, 8, 1));
		assertEquals("LTE 10 < 12 | Range 1", true, FuzzyCompare.lte(10, 12, 1));
	}

}

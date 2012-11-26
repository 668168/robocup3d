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
package magma.util.geometry;

import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

/**
 * @author dorer
 * 
 */
public class AngleTest
{

	@Test
	public void testNormalize()
	{
		assertEquals(-90.0, Angle.deg(270).degrees(), 0.0001);
		assertEquals(-170.0, Angle.deg(190).degrees(), 0.0001);
		assertEquals(170.0, Angle.deg(-190).degrees(), 0.0001);
		assertEquals(-170.0, Angle.deg(-170).degrees(), 0.0001);
		assertEquals(-180.0, Angle.deg(-180).degrees(), 0.0001);
		assertEquals(-180.0, Angle.deg(180).degrees(), 0.0001);
		assertEquals(10.0, Angle.deg(370).degrees(), 0.0001);
		assertEquals(-10.0, Angle.deg(-370).degrees(), 0.0001);
	}

	@Test
	public void testAdd()
	{
		assertEquals(5.0, Angle.deg(2).add(Angle.deg(3)).degrees(), 0.0001);
		assertEquals(-160.0, Angle.deg(100).add(Angle.deg(100)).degrees(), 0.0001);
	}

	@Test
	public void testSubtract()
	{
		assertEquals(-1.0, Angle.deg(2).subtract(Angle.deg(3)).degrees(), 0.0001);
		assertEquals(160.0, Angle.deg(-100).subtract(Angle.deg(100)).degrees(),
				0.0001);
	}

	/**
	 * Test method for {@link magma.util.geometry.Angle#isLeftOf(float, float)}.
	 */
	@Test
	public void testIsLeftOf()
	{
		assertTrue(Angle.deg(10).isLeftOf(Angle.deg(-10)));
		assertFalse(Angle.deg(90).isLeftOf(Angle.deg(-100)));
		assertTrue(Angle.deg(-100).isLeftOf(Angle.deg(100)));
		assertFalse(Angle.deg(100).isLeftOf(Angle.deg(-100)));
	}

}

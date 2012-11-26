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

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

/**
 * @author dorer
 * 
 */
public class PiecewiseLinearFunctionTest
{
	PiecewiseLinearFunction testee;

	/**
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception
	{
		String[] data = { "Joint", "linear", "4", "0", "-2", "4", "2", "5", "2",
				"6", "0" };
		testee = new PiecewiseLinearFunction(data);
	}

	/**
	 * Test method for
	 * {@link magma.agent.behavior.function.PiecewiseLinearFunction#value(double)}
	 * .
	 */
	@Test(expected = IllegalArgumentException.class)
	public void testValueInvalidSmall()
	{
		testee.value(-1);
	}

	/**
	 * Test method for
	 * {@link magma.agent.behavior.function.PiecewiseLinearFunction#value(double)}
	 * .
	 */
	@Test(expected = IllegalArgumentException.class)
	public void testValueInvalidBig()
	{
		testee.value(6.1);
	}

	/**
	 * Test method for
	 * {@link magma.agent.behavior.function.PiecewiseLinearFunction#value(double)}
	 * .
	 */
	@Test
	public void testValueValid()
	{
		assertEquals(-2, testee.value(0), 0.0001);
		assertEquals(0, testee.value(6), 0.0001);
		assertEquals(1, testee.value(5.5), 0.0001);
		assertEquals(2, testee.value(4.5), 0.0001);
	}

}

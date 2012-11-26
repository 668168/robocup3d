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
package magma.util.symboltreeparser;

import junit.framework.TestCase;

import org.junit.Before;
import org.junit.Test;

/**
 * @author Simon Raffeiner
 */
public class SymbolTreeParserTest extends TestCase
{
	private SymbolTreeParser testee = null;

	@Override
	@Before
	public void setUp()
	{
		testee = new SymbolTreeParser();
	}

	/**
	 * Test a basic on-level string
	 */
	@Test
	public void testSimpleCase()
	{
		try {
			SymbolNode list = testee.parse("(A A)");

			assertEquals(list.toString(), "(A A)");
		} catch (IllegalSymbolInputException isie) {
			fail("No exception expected here");
		}
	}

	/**
	 * Test a two-level string
	 */
	@Test
	public void testTwoLevelCase()
	{
		try {
			SymbolNode list = testee.parse("(A (B B))");

			assertEquals(list.toString(), "(A (B B))");

			list = testee.parse("(time (now 2.h18))");

			assertEquals(list.toString(), "(time (now 2.h18))");
		} catch (IllegalSymbolInputException isie) {
			fail("No exception expected here");
		}
	}

	/**
	 * Test a three-level string
	 */
	@Test
	public void testThreeLevelCase()
	{
		try {
			SymbolNode list = testee.parse("(A (B B (C C C)))");

			assertEquals(list.toString(), "(A (B B (C C C)))");
		} catch (IllegalSymbolInputException isie) {
			fail("No exception expected here");
		}
	}

	/**
	 * Test a string with mixed levels
	 */
	@Test
	public void testMixedLevelCases()
	{
		try {
			SymbolNode list = testee.parse("(A (B B (C (D) C) B) A A)");

			assertEquals(list.toString(), "(A (B B (C (D) C) B) A A)");

			list = testee.parse("(A (B B) (C C C))");

			assertEquals(list.toString(), "(A (B B) (C C C))");
		} catch (IllegalSymbolInputException isie) {
			fail("No exception expected here");
		}
	}

	/**
	 * Test corner cases (should throw exceptions)
	 */
	@Test
	public void testCornerCases()
	{
		try {
			SymbolNode node = testee.parse("(A A");
			node = testee.parse("(A (B B)");
			node = testee.parse("(A (B B) (C C C)");
			System.out.println(node);

			fail("Should have thrown an exception");
		} catch (IllegalSymbolInputException isie) {

		}
	}

	/**
	 * Test a complete SimSpark-like String
	 */
	@Test
	public void testSimSparkComplete()
	{
		try {
			SymbolNode list = testee
					.parse("(time (now 51.82))(GS (t 0.00) (pm BeforeKickOff))(GYR (n torso) (rt 0.00 -0.00 0.00))(HJ (n hj1) (ax -0.00))(HJ (n hj2) (ax -0.00))(HJ (n raj1) (ax -0.00))(HJ (n raj2) (ax -0.00))(HJ (n raj3) (ax -0.00))(HJ (n raj4) (ax -0.00))(HJ (n laj1) (ax -0.00))(HJ (n laj2) (ax -0.00))(HJ (n laj3) (ax -0.00))(HJ (n laj4) (ax -0.00))(HJ (n rlj1) (ax -0.00))(HJ (n rlj2) (ax -0.00))(HJ (n rlj3) (ax -0.00))(HJ (n rlj4) (ax -0.00))(HJ (n rlj5) (ax -0.00))(HJ (n rlj6) (ax -0.00))(HJ (n llj1) (ax -0.00))(HJ (n llj2) (ax -0.00))(HJ (n llj3) (ax -0.00))(HJ (n llj4) (ax -0.00))(HJ (n llj5) (ax -0.00))(HJ (n llj6) (ax -0.00))");

			assertTrue(list.getChild(0) instanceof SymbolNode);

			SymbolNode timeNode = (SymbolNode) list.getChild(0);
			SymbolNode timeSubNode = (SymbolNode) timeNode.getChild(1);
			assertEquals(timeNode.getChild(0).content(), "time");
			assertEquals(timeSubNode.getChild(0).content(), "now");
			assertEquals(timeSubNode.getChild(1).content(), "51.82");

			SymbolNode gameStateNode = (SymbolNode) list.getChild(1);
			SymbolNode gameStateSubNode = (SymbolNode) gameStateNode.getChild(1);
			assertEquals(gameStateNode.getChild(0).content(), "GS");
			assertEquals(gameStateSubNode.getChild(0).content(), "t");
			assertEquals(gameStateSubNode.getChild(1).content(), "0.00");
		} catch (IllegalSymbolInputException isie) {
			fail("No exception expected here");
		}
	}

}

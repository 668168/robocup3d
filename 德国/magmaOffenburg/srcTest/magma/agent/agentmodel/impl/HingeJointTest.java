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
package magma.agent.agentmodel.impl;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

/**
 * @author stilnox
 * 
 */
public class HingeJointTest
{
	private HingeJoint testee1;

	private HingeJoint testee2;

	private HingeJoint testee3;

	/**
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception
	{
		testee1 = new HingeJoint("test", "test", -120, 120);
		testee1.setAxis(60);
		testee1.setAxis(50);
		// testee1.setLastAxis(60);
		testee2 = new HingeJoint("test", "test", -120, 120);
		testee2.setAxis(50);
		testee2.setAxis(50);
		// testee2.setLastAxis(50);
		testee3 = new HingeJoint("test", "test", -120, 120);
		testee3.setAxis(50);
		testee3.setAxis(60);
		// testee3.setLastAxis(50);
	}

	/**
	 * Test method for
	 * {@link magma.agent.agentmodel.impl.HingeJoint#checkTarget(float, float)} .
	 */
	@Test
	public void testCheckTarget()
	{
		assertEquals("Equals failed", 0f, testee1.checkTarget(50, 2));
		assertEquals("Lower failed", -1.0f, testee1.checkTarget(40, 2));
		assertEquals("Greather failed", 1.0f, testee1.checkTarget(60, 2));

		assertEquals("Equals failed", 0f, testee2.checkTarget(50, 2));
		assertEquals("Lower failed", -1.0f, testee2.checkTarget(40, 2));
		assertEquals("Greather failed", 1f, testee2.checkTarget(60, 2));

		assertEquals("Equals failed", -1.0f, testee3.checkTarget(50, 2));
		assertEquals("Lower failed", -1.0f, testee3.checkTarget(40, 2));
		assertEquals("Greather failed", 1f, testee3.checkTarget(70, 2));
	}

	/**
	 * Test method for
	 * {@link magma.agent.agentmodel.impl.HingeJoint#checkTrigger(float, float)}
	 * .
	 */
	@Test
	public void testCheckTrigger()
	{
		assertEquals(true, testee1.checkTrigger(50, 2));
		assertEquals(false, testee1.checkTrigger(40, 2));
		assertEquals(true, testee1.checkTrigger(60, 2));

		assertEquals(true, testee2.checkTrigger(50, 2));
		assertEquals(false, testee2.checkTrigger(40, 2));
		assertEquals(false, testee2.checkTrigger(60, 2));

		assertEquals(true, testee3.checkTrigger(50, 2));
		assertEquals(true, testee3.checkTrigger(40, 2));
		assertEquals(false, testee3.checkTrigger(70, 2));
	}
}

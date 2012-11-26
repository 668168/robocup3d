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

import magma.util.SerializationUtil;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

/**
 * Tests for Serialization of agent model
 * @author dorer
 */
public class SerializationTest
{
	private HingeJoint testee1;

	/**
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception
	{
		testee1 = new HingeJoint("test", "test", -120, 120);
		testee1.setAxis(60);
		testee1.setAxis(50);
	}

	@Test
	public void testHingeJointSerialization() throws Exception
	{
		HingeJoint result = (HingeJoint) SerializationUtil
				.doubleSerialize(testee1);
		assertEquals(testee1, result);
	}

	@Test
	public void testAgentModelSerialization() throws Exception
	{
		AgentModel model = new AgentModelNAO();
		AgentModel result = (AgentModel) SerializationUtil.doubleSerialize(model);
		assertEquals(result, model);
	}

}

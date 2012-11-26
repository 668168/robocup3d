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
package magma.agent.worldmodel.impl;

import magma.agent.IMagmaConstants;
import magma.agent.perception.impl.VisibleObjectPerceptor;
import magma.util.SerializationUtil;

import org.apache.commons.math.geometry.Vector3D;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

/**
 * Tests for Serialization of global map
 * @author dorer
 */
public class SerializationTest
{
	private ThisPlayer thisPlayer;

	/**
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception
	{
		thisPlayer = new ThisPlayer(IMagmaConstants.OUR_TEAMNAME,
				IMagmaConstants.UNKNOWN_PLAYER_NUMBER);
	}

	@Test
	public void testBallSerialization() throws Exception
	{
		VisibleObjectPerceptor vision = new VisibleObjectPerceptor("test",
				new Vector3D(1.0, 2.0, 3.0));
		thisPlayer.setPosition(new Vector3D(4.0, -2.0, 1.0));
		Ball testee = new Ball();
		testee.update(vision, 1.0f, thisPlayer);

		Ball result = (Ball) SerializationUtil.doubleSerialize(testee);
		assertEquals(testee, result);
	}

	@Test
	public void testWorldModelSerialization() throws Exception
	{
		GlobalMap testee = new GlobalMap(null, "team", 0);
		GlobalMap result = (GlobalMap) SerializationUtil.doubleSerialize(testee);
		assertEquals(testee, result);
	}
}

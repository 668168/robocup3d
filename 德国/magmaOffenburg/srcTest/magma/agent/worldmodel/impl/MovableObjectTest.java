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
import magma.util.FuzzyCompare;

import org.apache.commons.math.geometry.Vector3D;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertTrue;

/**
 * @author Srinivas
 * 
 */
public class MovableObjectTest
{

	private MovableObject testee;

	private ThisPlayer thisPlayer;

	/**
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception
	{
		testee = new Player(IMagmaConstants.UNKNOWN_PLAYER_NUMBER,
				IMagmaConstants.OUR_TEAMNAME, true);
		thisPlayer = new ThisPlayer(IMagmaConstants.OUR_TEAMNAME,
				IMagmaConstants.UNKNOWN_PLAYER_NUMBER);
	}

	/**
	 * Test method for
	 * {@link magma.agent.worldmodel.impl.MovableObject#getFuturePositions(int)}.
	 */
	@Test
	public void testGetFuturePositionsPlayer()
	{
		VisibleObjectPerceptor vision = new VisibleObjectPerceptor("test",
				new Vector3D(2.0, 0.0, 0.0));
		thisPlayer.setPosition(new Vector3D(1.0, 0.0, 0.0));
		testee.update(vision, 1.0f, thisPlayer);
		Vector3D[] expected = new Vector3D[3];
		expected[0] = new Vector3D(3.0, 0.0, 0.0);
		expected[1] = new Vector3D(3.0, 0.0, 0.0);
		expected[2] = new Vector3D(3.0, 0.0, 0.0);

		testVectorArray(expected, testee.getFuturePositions(3));

		vision.setPosition(new Vector3D(3.0, 0.0, 0.0));
		testee.update(vision, 2.0f, thisPlayer);

		expected[0] = new Vector3D(5.0, 0.0, 0.0);
		expected[1] = new Vector3D(6.0, 0.0, 0.0);
		expected[2] = new Vector3D(7.0, 0.0, 0.0);

		testVectorArray(expected, testee.getFuturePositions(3));
	}

	/**
	 * Test method for
	 * {@link magma.agent.worldmodel.impl.MovableObject#getSpeed()}.
	 */
	@Test
	public void testGetSpeedForPlayers()
	{
		/** Tests for Players */

		VisibleObjectPerceptor vision = new VisibleObjectPerceptor("test",
				new Vector3D(2.0, 0.0, 0.0));

		// first-time perception, no prevPosition
		thisPlayer.setPosition(new Vector3D(1.0, 0.0, 0.0));
		testee.update(vision, 1.0f, thisPlayer);
		testVector(new Vector3D(0.0, 0.0, 0.0), testee.getSpeed());

		// speed < 2
		vision.setPosition(new Vector3D(3.0, 0.0, 0.0));
		testee.update(vision, 2.0f, thisPlayer);
		testVector(new Vector3D(1.0, 0.0, 0.0), testee.getSpeed());

		// speed > 2
		vision.setPosition(new Vector3D(6.0, 0.0, 0.0));
		testee.update(vision, 3.0f, thisPlayer);
		testVector(new Vector3D(1.0, 0.0, 0.0), testee.getSpeed());

		// speed < 2, time gap > 1
		vision.setPosition(new Vector3D(7.0, 0.0, 0.0));
		testee.update(vision, 5.0f, thisPlayer);
		testVector(new Vector3D(0.5, 0.0, 0.0), testee.getSpeed());
	}

	/**
	 * Test method for
	 * {@link magma.agent.worldmodel.impl.MovableObject#getSpeed()}.
	 */
	@Test
	public void testGetSpeedForBall()
	{

		/** Tests for Ball */
		testee = new Ball();

		VisibleObjectPerceptor vision = new VisibleObjectPerceptor("test",
				new Vector3D(2.0, 0.0, 0.0));
		// thisPlayer.setPosition(new Vector3D(0.0, 0.0, 0.0));

		// first-time perception, initial position 0,0
		testee.update(vision, 1.0f, thisPlayer);
		testVector(new Vector3D(2.0, 0.0, 0.0), testee.getSpeed());

		// speed < 6
		vision.setPosition(new Vector3D(3.0, 2.0, 0.0));
		testee.update(vision, 2.0f, thisPlayer);
		testVector(new Vector3D(1.0, 2.0, 0.0), testee.getSpeed());

		// speed > 6
		vision.setPosition(new Vector3D(6.0, -6.0, 0.0));
		testee.update(vision, 3.0f, thisPlayer);
		testVector(new Vector3D(1.0, 2.0, 0.0), testee.getSpeed());

		// speed < 6, time gap > 1
		vision.setPosition(new Vector3D(4.0, -4.0, 0.0));
		testee.update(vision, 5.0f, thisPlayer);
		testVector(new Vector3D(-1.0, 1.0, 0.0), testee.getSpeed());
	}

	/**
	 * Test method for
	 * {@link magma.agent.worldmodel.impl.MovableObject#getFuturePositions(int)}.
	 */
	@Test
	public void testGetFuturePositionsBall()
	{
		testee = new Ball();
		thisPlayer.setPosition(new Vector3D(0.0, 1.0, 0.0));

		VisibleObjectPerceptor vision = new VisibleObjectPerceptor("test",
				new Vector3D(2.0, 0.0, 0.0));

		testee.update(vision, 1.0f, thisPlayer);
		Vector3D[] expected = new Vector3D[3];
		expected[0] = new Vector3D(3.88, 1.94, 0.0);
		expected[1] = new Vector3D(5.6472, 2.8236, 0.0);
		expected[2] = new Vector3D(7.308368, 3.654184, 0.0);

		testVectorArray(expected, testee.getFuturePositions(3));

		vision.setPosition(new Vector3D(0.0, 0.0, 0.0));
		testee.update(vision, 2.0f, thisPlayer);

		expected[0] = new Vector3D(-1.88, 1.0, 0.0);
		expected[1] = new Vector3D(-3.647199, 1.0, 0.0);
		expected[2] = new Vector3D(-5.308368, 1.0, 0.0);

		testVectorArray(expected, testee.getFuturePositions(3));
	}

	/**
	 * @param expected
	 */
	private void testVector(Vector3D expected, Vector3D was)
	{
		assertTrue(FuzzyCompare.eq(expected, was, 0.00001f));
	}

	/**
	 * @param expected
	 * @param futurePositions
	 */
	private void testVectorArray(Vector3D[] expected, Vector3D[] was)
	{
		for (int i = 0; i < expected.length; i++) {
			testVector(expected[i], was[i]);
		}
	}
}

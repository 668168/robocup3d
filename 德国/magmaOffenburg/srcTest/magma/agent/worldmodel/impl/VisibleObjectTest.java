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
import magma.agent.worldmodel.IThisPlayer;
import magma.agent.worldmodel.IVisibleObject;
import magma.util.FuzzyCompare;
import magma.util.geometry.Angle;

import org.apache.commons.math.geometry.Vector3D;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

/**
 * @author dorer
 * 
 */
public class VisibleObjectTest
{
	private VisibleObject testee;

	private ThisPlayer thisPlayer;

	/**
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception
	{
		testee = new Ball();
		thisPlayer = new ThisPlayer(IMagmaConstants.OUR_TEAMNAME,
				IMagmaConstants.UNKNOWN_PLAYER_NUMBER);
	}

	/**
	 * Test method for
	 * {@link magma.agent.worldmodel.impl.VisibleObject#update(magma.agent.perception.impl.VisibleObjectPerceptor, float, ThisPlayer)}
	 * .
	 */
	@Test
	public void testUpdateX()
	{
		VisibleObjectPerceptor vision = new VisibleObjectPerceptor("test",
				new Vector3D(2.0, 0.0, 0.0));
		thisPlayer.setPosition(new Vector3D(1.0, 0.0, 0.0));

		testee.update(vision, 1.0f, thisPlayer);
		Vector3D position = testee.getPosition();
		testVector(new Vector3D(3.0, 0.0, 0.0), position);
		assertEquals(1.0, testee.getLastSeenTime(), 0.001);
	}

	/**
	 * Test method for
	 * {@link magma.agent.worldmodel.impl.VisibleObject#update(magma.agent.perception.impl.VisibleObjectPerceptor, float, ThisPlayer)}
	 * .
	 */
	@Test
	public void testUpdateY()
	{
		VisibleObjectPerceptor vision = new VisibleObjectPerceptor("test",
				new Vector3D(0.0, 2.0, 0.0));
		thisPlayer.setPosition(new Vector3D(0.0, 1.0, 0.0));

		testee.update(vision, 1.0f, thisPlayer);
		Vector3D position = testee.getPosition();
		testVector(new Vector3D(0.0, 3.0, 0.0), position);
	}

	/**
	 * Test method for
	 * {@link magma.agent.worldmodel.impl.VisibleObject#update(magma.agent.perception.impl.VisibleObjectPerceptor, float, ThisPlayer)}
	 * .
	 */
	@Test
	public void testUpdateZ()
	{
		VisibleObjectPerceptor vision = new VisibleObjectPerceptor("test",
				new Vector3D(0.0, 0.0, 2.0));
		thisPlayer.setPosition(new Vector3D(0.0, 0.0, 1.0));

		testee.update(vision, 1.0f, thisPlayer);
		Vector3D position = testee.getPosition();
		testVector(new Vector3D(0.0, 0.0, 3.0), position);
	}

	/**
	 * Test method for
	 * {@link magma.agent.worldmodel.impl.VisibleObject#update(magma.agent.perception.impl.VisibleObjectPerceptor, float, ThisPlayer)}
	 * .
	 */
	@Test
	public void testUpdateXYZ()
	{
		VisibleObjectPerceptor vision = new VisibleObjectPerceptor("test",
				new Vector3D(1.0, 2.0, 3.0));
		thisPlayer.setPosition(new Vector3D(4.0, -2.0, 1.0));

		testee.update(vision, 1.0f, thisPlayer);
		Vector3D position = testee.getPosition();
		testVector(new Vector3D(5.0, 0.0, 4.0), position);
	}

	/**
	 * Test method for
	 * {@link magma.agent.worldmodel.impl.VisibleObject#update(magma.agent.perception.impl.VisibleObjectPerceptor, float, IThisPlayer)}
	 * .
	 */
	@Test
	public void testUpdateRotation90()
	{
		VisibleObjectPerceptor vision = new VisibleObjectPerceptor("test",
				new Vector3D(2.0, 0.0, 0.0));
		thisPlayer.setPosition(new Vector3D(0.0, 0.0, 0.0));
		thisPlayer.setHorizontalAngle(Angle.deg(90));

		testee.update(vision, 1.0f, thisPlayer);
		Vector3D position = testee.getPosition();
		testVector(new Vector3D(0.0, 2.0, 0.0), position);
	}

	/**
	 * Test method for
	 * {@link magma.agent.worldmodel.impl.VisibleObject#update(magma.agent.perception.impl.VisibleObjectPerceptor, float, IThisPlayer)}
	 * .
	 */
	@Test
	public void testUpdateRotation45()
	{
		VisibleObjectPerceptor vision = new VisibleObjectPerceptor("test",
				new Vector3D(2.0, 2.0, 0.0));
		thisPlayer.setPosition(new Vector3D(0.0, 0.0, 0.0));
		thisPlayer.setHorizontalAngle(Angle.deg(-45.0));
		double x = 2.0 / Math.cos(Math.toRadians(-45.0));

		testee.update(vision, 1.0f, thisPlayer);
		Vector3D position = testee.getPosition();
		testVector(new Vector3D(x, 0.0, 0.0), position);
	}

	/**
	 * Test method for
	 * {@link magma.agent.worldmodel.impl.VisibleObject#update(magma.agent.perception.impl.VisibleObjectPerceptor, float, IThisPlayer)}
	 * .
	 */
	@Test
	public void testUpdateRotation45Translation()
	{
		VisibleObjectPerceptor vision = new VisibleObjectPerceptor("test",
				new Vector3D(0.0, Math.sqrt(3 * 3 + 3 * 3), 0.0));
		thisPlayer.setPosition(new Vector3D(-3.0, -3.0, 0.0));
		thisPlayer.setHorizontalAngle(Angle.deg(-45));

		testee.update(vision, 1.0f, thisPlayer);
		Vector3D position = testee.getPosition();
		testVector(new Vector3D(0.0, 0.0, 0.0), position);
	}

	@Test
	/*
	 * * Test method for {@link
	 * magma.agent.worldmodel.impl.VisibleObject#getDistanceTo
	 * (magma.agent.worldmodel.IVisibleObject other)} .
	 */
	public void testGetDistance() throws Exception
	{
		thisPlayer.setPosition(new Vector3D(3.0, 0.0, 0.0));
		testee.position = new Vector3D(0.0, 0.0, 0.0);
		assertEquals(3.0, testee.getDistanceTo(thisPlayer), 0.0001);

		thisPlayer.setPosition(new Vector3D(-3.0, 0.0, 0.0));
		testee.position = new Vector3D(0.0, -4.0, 0.0);
		assertEquals(5.0, testee.getDistanceTo(thisPlayer), 0.0001);
	}

	/**
	 * Compare two vectors using fuzzy comparison
	 * 
	 * @param expected Expected vector
	 * @param was Actual vector
	 */
	private void testVector(Vector3D expected, Vector3D was)
	{
		assertTrue(FuzzyCompare.eq(expected, was, 0.00001f));
	}

	/**
	 * Test method for
	 * {@link magma.agent.worldmodel.impl.VisibleObject#getDirectionTo(IVisibleObject)}
	 * .
	 */
	@Test
	public void testGetDirectionTo() throws Exception
	{
		thisPlayer.setPosition(new Vector3D(1.0, 1.0, 0.0));
		testee.position = new Vector3D(2.0, 2.0, 0.0);

		assertEquals(-135.0, testee.getDirectionTo(thisPlayer).degrees(), 0.0001);
		assertEquals(45.0, thisPlayer.getDirectionTo(testee).degrees(), 0.0001);
	}

}

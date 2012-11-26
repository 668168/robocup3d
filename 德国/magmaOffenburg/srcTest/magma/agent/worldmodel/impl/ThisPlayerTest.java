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

import magma.util.geometry.Angle;

import org.apache.commons.math.geometry.Vector3D;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

/**
 * @author dorer
 * 
 */
public class ThisPlayerTest
{
	ThisPlayer testee;

	/**
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception
	{
		testee = new ThisPlayer("test", 0);
	}

	/**
	 * Test method for
	 * {@link magma.agent.worldmodel.impl.ThisPlayer#isInsidePolygonXY(org.apache.commons.math.geometry.Vector3D, org.apache.commons.math.geometry.Vector3D[])}
	 * .
	 */
	@Test
	public void testIsInsidePolygonXY()
	{
		Vector3D[] polygon = new Vector3D[4];
		polygon[0] = new Vector3D(0, 1, 0);
		polygon[1] = new Vector3D(1, 1, 0);
		polygon[2] = new Vector3D(1, -1, 0);
		polygon[3] = new Vector3D(0, -1, 0);

		testee.setPosition(new Vector3D(2.0, 0.0, 0.0));
		testee.setHorizontalAngle(Angle.deg(90));

		assertEquals(false, testee.isInsidePolygonXY(new Vector3D(0, 0, 0),
				polygon));
		assertEquals(false, testee.isInsidePolygonXY(new Vector3D(2, -0.1, 0),
				polygon));
		assertEquals(true, testee.isInsidePolygonXY(new Vector3D(1.01, 0.99, 0),
				polygon));
		assertEquals(true, testee.isInsidePolygonXY(new Vector3D(2.9, 0.99, 0),
				polygon));
	}
}

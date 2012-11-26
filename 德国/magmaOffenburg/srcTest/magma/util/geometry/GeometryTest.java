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

import org.apache.commons.math.geometry.Vector3D;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

/**
 * @author dorer
 * 
 */
public class GeometryTest
{

	/**
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception
	{
	}

	@Test
	public void testIsInsidePolygon()
	{
		double[][] points = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
		Vector3D[] polygon = Geometry.getPolygon(points);

		// point outside
		assertEquals(false, Geometry.isInsidePolygon(new Vector3D(1, 1, 0),
				polygon));
		assertEquals(false, Geometry.isInsidePolygon(new Vector3D(-1, 1, 0),
				polygon));
		// point inside
		assertEquals(true, Geometry.isInsidePolygon(new Vector3D(0, 0, 0),
				polygon));
		// point on corner
		assertEquals(true, Geometry.isInsidePolygon(new Vector3D(0, 1, 0),
				polygon));
		// point on edge
		assertEquals(true, Geometry.isInsidePolygon(new Vector3D(0.5, 0.5, 0),
				polygon));
	}
}

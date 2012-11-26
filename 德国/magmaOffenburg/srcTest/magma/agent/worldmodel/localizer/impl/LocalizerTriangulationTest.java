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
package magma.agent.worldmodel.localizer.impl;

import magma.agent.worldmodel.localizer.ILocalizationFlag;
import magma.util.FuzzyCompare;
import magma.util.geometry.PositionOrientation;

import org.apache.commons.math.geometry.Vector3D;
import org.junit.Before;
import org.junit.Test;

import static java.lang.Math.toRadians;
import static org.easymock.EasyMock.anyObject;
import static org.easymock.EasyMock.expect;
import static org.easymock.EasyMock.replay;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

public class LocalizerTriangulationTest extends LocalizerBaseTest
{
	@Override
	@Before
	public void setUp()
	{
		super.setUp();
		testee = new LocalizerTriangulation();
	}

	@Test
	public void testLocalize()
	{
		expect(F1R.getDistance()).andStubReturn(7.21110);
		expect(F1R.getHorizontalDirection()).andStubReturn(toRadians(33.6900));

		expect(F2R.getDistance()).andStubReturn(7.21110);
		expect(F2R.getHorizontalDirection()).andStubReturn(toRadians(-33.6900));

		expect(F1R.compareTo(F2R)).andStubReturn(-1);

		replay(F1R, F2R);

		flags.put("F1R", F1R);
		flags.put("F2R", F2R);

		PositionOrientation localizeInfo = testee.localize(flags, 0, 0,
				Vector3D.zero);
		assertNotNull(localizeInfo);
		assertTrue(FuzzyCompare.eq(new Vector3D(0, 0, 0), localizeInfo
				.getPosition(), 0.001f));
		assertEquals(0, localizeInfo.getOrientationX().degrees(), 0.001f);
	}

	@Test
	public void testLocalizeMoreFlagsRight()
	{
		expect(F1R.getDistance()).andStubReturn(7.21110);
		expect(F1R.getHorizontalDirection()).andStubReturn(toRadians(33.6900));

		expect(F2R.getDistance()).andStubReturn(7.21110);
		expect(F2R.getHorizontalDirection()).andStubReturn(toRadians(-33.6900));

		expect(G1R.getDistance()).andStubReturn(6.22);
		expect(G1R.getHorizontalDirection()).andStubReturn(toRadians(15.94));

		expect(G2R.getDistance()).andStubReturn(6.22);
		expect(G2R.getHorizontalDirection()).andStubReturn(toRadians(-15.94));

		expect(F1R.compareTo((ILocalizationFlag) anyObject())).andStubReturn(-1);
		expect(G1R.compareTo(F1R)).andStubReturn(1);
		expect(G1R.compareTo(G2R)).andStubReturn(-1);
		expect(G1R.compareTo(F2R)).andStubReturn(-1);
		expect(G2R.compareTo(F1R)).andStubReturn(1);
		expect(G2R.compareTo(G1R)).andStubReturn(1);
		expect(G2R.compareTo(F2R)).andStubReturn(-1);
		expect(F2R.compareTo((ILocalizationFlag) anyObject())).andStubReturn(1);

		replay(F1R, F2R, G1R, G2R);

		// player is at position -4,-1 looking 45 deg
		flags.put("G1R", G1R);
		flags.put("G2R", G2R);
		flags.put("F1R", F1R);
		flags.put("F2R", F2R);

		PositionOrientation localizeInfo = testee.localize(flags, 0, 0,
				Vector3D.zero);
		assertNotNull(localizeInfo);
		assertTrue(FuzzyCompare.eq(new Vector3D(-0.149, -0.001, 0), localizeInfo
				.getPosition(), 0.01f));
		assertEquals(-1.592629, localizeInfo.getOrientationX().degrees(), 0.001);
	}

	@Test
	public void testLocalizeMoreFlagsLeft()
	{
		expect(F1L.getDistance()).andStubReturn(7.21110);
		expect(F1L.getHorizontalDirection()).andStubReturn(toRadians(-33.6900));

		expect(F2L.getDistance()).andStubReturn(7.21110);
		expect(F2L.getHorizontalDirection()).andStubReturn(toRadians(33.6900));

		expect(G1L.getDistance()).andStubReturn(6.08);
		expect(G1L.getHorizontalDirection()).andStubReturn(toRadians(-15.94));

		expect(G2L.getDistance()).andStubReturn(6.08);
		expect(G2L.getHorizontalDirection()).andStubReturn(toRadians(15.94));

		expect(F1L.compareTo((ILocalizationFlag) anyObject())).andStubReturn(1);
		expect(G1L.compareTo(F1L)).andStubReturn(-1);
		expect(G1L.compareTo(G2L)).andStubReturn(1);
		expect(G1L.compareTo(F2L)).andStubReturn(1);
		expect(G2L.compareTo(F1L)).andStubReturn(-1);
		expect(G2L.compareTo(G1L)).andStubReturn(-1);
		expect(G2L.compareTo(F2L)).andStubReturn(1);
		expect(F2L.compareTo((ILocalizationFlag) anyObject())).andStubReturn(-1);

		replay(F1L, F2L, G1L, G2L);
		flags.put("G1L", G1L);
		flags.put("G2L", G2L);
		flags.put("F1L", F1L);
		flags.put("F2L", F2L);

		PositionOrientation localizeInfo = testee.localize(flags, 0, 0,
				Vector3D.zero);
		assertNotNull(localizeInfo);
		assertTrue(FuzzyCompare.eq(new Vector3D(0.0336, 0.0, 0), localizeInfo
				.getPosition(), 0.01f));
		assertEquals(3.1144, localizeInfo.getOrientationX().radians(), 0.001);
	}

	@Test
	public void testLocalizeTurned()
	{
		expect(F1L.getDistance()).andStubReturn(5.385164);
		expect(F1L.getHorizontalDirection()).andStubReturn(1.16590);

		expect(F1R.getDistance()).andStubReturn(11.18034);
		expect(F1R.getHorizontalDirection()).andStubReturn(-0.32175);

		expect(F1L.compareTo(F1R)).andStubReturn(-1);

		replay(F1L, F1R);

		flags.put("F1L", F1L);
		flags.put("F1R", F1R);

		PositionOrientation localizeInfo = testee.localize(flags, 0, 0,
				Vector3D.zero);
		assertNotNull(localizeInfo);
		assertTrue(FuzzyCompare.eq(new Vector3D(-4.0, -1.0, 0), localizeInfo
				.getPosition(), 0.001f));
		assertEquals(45, localizeInfo.getOrientationX().degrees(), 0.001);
	}

	@Test
	public void testLocalizeGoalPosts()
	{
		expect(G1R.getDistance()).andStubReturn(6.22);
		expect(G1R.getHorizontalDirection()).andStubReturn(toRadians(15.94));

		expect(F2R.getDistance()).andStubReturn(7.35);
		expect(F2R.getHorizontalDirection()).andStubReturn(toRadians(-23.67));

		expect(G1R.compareTo(F2R)).andStubReturn(-1);

		replay(G1R, F2R);

		flags.put("G1R", G1R);
		flags.put("F2R", F2R);

		PositionOrientation localizeInfo = testee.localize(flags, 0, 0,
				Vector3D.zero);
		assertNotNull(localizeInfo);
		assertTrue(FuzzyCompare.eq(new Vector3D(-0.178, -0.0187, 0), localizeInfo
				.getPosition(), 0.01f));
		assertEquals(-0.162, localizeInfo.getOrientationX().radians(), 0.001);
	}

	@Test
	public void testLocalizeBug1()
	{
		expect(G2R.getDistance()).andStubReturn(6.22);
		expect(G2R.getHorizontalDirection()).andStubReturn(toRadians(48.779998));

		expect(F2R.getDistance()).andStubReturn(7.34);
		expect(F2R.getHorizontalDirection()).andStubReturn(toRadians(21.93000));

		expect(G2R.compareTo(F2R)).andStubReturn(-1);

		replay(G2R, F2R);

		flags.put("G2R", G2R);
		flags.put("F2R", F2R);

		PositionOrientation localizeInfo = testee.localize(flags, 0, 0,
				Vector3D.zero);
		assertNotNull(localizeInfo);
		assertTrue(FuzzyCompare.eq(new Vector3D(-0.185829, -0.0489, 0),
				localizeInfo.getPosition(), 0.01f));
		assertEquals(-0.95624, localizeInfo.getOrientationX().radians(), 0.001);
	}
}

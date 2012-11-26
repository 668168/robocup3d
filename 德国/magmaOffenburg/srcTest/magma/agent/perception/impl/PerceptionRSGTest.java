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
package magma.agent.perception.impl;

//
//import static org.junit.Assert.assertEquals;
//import static org.junit.Assert.fail;
//
//import java.util.NoSuchElementException;
//
//import org.junit.Before;
//import org.junit.Test;
//
///**
// * Unit Test class for Perceptor
// * @author joachim
// * 
// */
//public class PerceptionRSGTest
//{
//
//	/** instance of the class to test */
//	PerceptionRSG testee;
//
//	/**
//	 * Called before each test method to create data that we need in each test
//	 * @throws java.lang.Exception
//	 */
//	@Before
//	public void setUp() throws Exception
//	{
//		testee = new PerceptionRSG(null);
//	}
//
//	@Test
//	public void testForceResistanceOk()
//	{
//		ForceResistanceParser fr1 = testee
//				.getForceResistanceParser(PerceptionRSG.FORCE_RESISTANCE_0);
//		ForceResistanceParser fr2 = testee
//				.getForceResistanceParser(PerceptionRSG.FORCE_RESISTANCE_1);
//
//		// normal call
//		testee.parse("(FRP (n lf) (c -0.14 0.08 -0.051) (f 1 -0.26 -3)) "
//				+ "(FRP (n rf) (c -0 0 -0.0000) (f 0.0000 -0.00 0.00))");
//
//		assertEquals("", -0.14, fr1.getForceOrigin().getX(), 0.0001);
//		assertEquals("", 0.08, fr1.getForceOrigin().getY(), 0.0001);
//		assertEquals("", -0.051, fr1.getForceOrigin().getZ(), 0.0001);
//
//		assertEquals("", 1, fr1.getForce().getX(), 0.0001);
//		assertEquals("", -0.26, fr1.getForce().getY(), 0.0001);
//		assertEquals("", -3, fr1.getForce().getZ(), 0.0001);
//
//		assertEquals("", 0, fr2.getForceOrigin().getX(), 0.0001);
//		assertEquals("", 0, fr2.getForceOrigin().getY(), 0.0001);
//		assertEquals("", 0, fr2.getForceOrigin().getZ(), 0.0001);
//
//		assertEquals("", 0, fr2.getForce().getX(), 0.0001);
//		assertEquals("", 0, fr2.getForce().getY(), 0.0001);
//		assertEquals("", 0, fr2.getForce().getZ(), 0.0001);
//	}
//
//	@Test
//	public void testForceResistanceParseExceptionlf()
//	{
//		// error in string in first command
//		ForceResistanceParser fr1 = testee
//				.getForceResistanceParser(PerceptionRSG.FORCE_RESISTANCE_0);
//		ForceResistanceParser fr2 = testee
//				.getForceResistanceParser(PerceptionRSG.FORCE_RESISTANCE_1);
//
//		try {
//			testee.parse("(FRP (n lf) (c mist 0.08 -0.051) (f 1 -0 -3)) "
//					+ "(FRP (n rf) (c -1 0 -0.0000) (f 0.0000 -0.00 0.00))");
//			fail("Expected exception, but was none");
//		} catch (NumberFormatException e) {
//			// expected
//		}
//
//		assertEquals("", 0.0, fr1.getForceOrigin().getX(), 0.0001);
//		assertEquals("", 0.0, fr1.getForceOrigin().getY(), 0.0001);
//		assertEquals("", 0.0, fr1.getForceOrigin().getZ(), 0.0001);
//
//		assertEquals("", 0, fr1.getForce().getX(), 0.0001);
//		assertEquals("", 0, fr1.getForce().getY(), 0.0001);
//		assertEquals("", 0, fr1.getForce().getZ(), 0.0001);
//
//		assertEquals("", 0, fr2.getForceOrigin().getX(), 0.0001);
//		assertEquals("", 0, fr2.getForceOrigin().getY(), 0.0001);
//		assertEquals("", 0, fr2.getForceOrigin().getZ(), 0.0001);
//
//		assertEquals("", 0, fr2.getForce().getX(), 0.0001);
//		assertEquals("", 0, fr2.getForce().getY(), 0.0001);
//		assertEquals("", 0, fr2.getForce().getZ(), 0.0001);
//	}
//
//	@Test
//	public void testForceResistanceParseExceptionf()
//	{
//		// error in string in first command
//		ForceResistanceParser fr1 = testee
//				.getForceResistanceParser(PerceptionRSG.FORCE_RESISTANCE_0);
//		ForceResistanceParser fr2 = testee
//				.getForceResistanceParser(PerceptionRSG.FORCE_RESISTANCE_1);
//
//		try {
//			testee.parse("(FRP (n f) (c mist 0.08 -0.051) (f 1 -0 -3)) "
//					+ "(FRP (n ) (c -1 0 -0.0000) (f 0.0000 -0.00 0.00))");
//			// will not fail if assertions are not switched on
//		} catch (AssertionError e) {
//			// expected if assertions switched on
//			assertEquals("Unknown sensor: f", e.getMessage());
//		}
//
//		assertEquals("", 0, fr1.getForceOrigin().getX(), 0.0001);
//		assertEquals("", 0, fr1.getForceOrigin().getY(), 0.0001);
//		assertEquals("", 0, fr1.getForceOrigin().getZ(), 0.0001);
//
//		assertEquals("", 0, fr1.getForce().getX(), 0.0001);
//		assertEquals("", 0, fr1.getForce().getY(), 0.0001);
//		assertEquals("", 0, fr1.getForce().getZ(), 0.0001);
//
//		assertEquals("", 0, fr2.getForceOrigin().getX(), 0.0001);
//		assertEquals("", 0, fr2.getForceOrigin().getY(), 0.0001);
//		assertEquals("", 0, fr2.getForceOrigin().getZ(), 0.0001);
//
//		assertEquals("", 0, fr2.getForce().getX(), 0.0001);
//		assertEquals("", 0, fr2.getForce().getY(), 0.0001);
//		assertEquals("", 0, fr2.getForce().getZ(), 0.0001);
//
//	}
//
//	@Test
//	public void testForceResistanceIncompletePart2()
//	{
//		// missing zero before . and incomplete second part
//		ForceResistanceParser fr1 = testee
//				.getForceResistanceParser(PerceptionRSG.FORCE_RESISTANCE_0);
//		ForceResistanceParser fr2 = testee
//				.getForceResistanceParser(PerceptionRSG.FORCE_RESISTANCE_1);
//
//		try {
//			testee.parse("(FRP (n lf) (c -0.14 .8 -.51) (f 1 -0.26 -3)) "
//					+ "(FRP (n rf) (c -1 -");
//			fail("Expected exception, but was none");
//		} catch (NumberFormatException e) {
//			// expected
//		} catch (Exception e) {
//			fail("Expected other type of exception as: " + e);
//		}
//
//		assertEquals("", -0.14, fr1.getForceOrigin().getX(), 0.0001);
//		assertEquals("", 0.8, fr1.getForceOrigin().getY(), 0.0001);
//		assertEquals("", -0.51, fr1.getForceOrigin().getZ(), 0.0001);
//
//		assertEquals("", 1, fr1.getForce().getX(), 0.0001);
//		assertEquals("", -0.26, fr1.getForce().getY(), 0.0001);
//		assertEquals("", -3, fr1.getForce().getZ(), 0.0001);
//
//		assertEquals("", 0, fr2.getForceOrigin().getX(), 0.0001);
//		assertEquals("", 0, fr2.getForceOrigin().getY(), 0.0001);
//		assertEquals("", 0, fr2.getForceOrigin().getZ(), 0.0001);
//
//		assertEquals("", 0, fr2.getForce().getX(), 0.0001);
//		assertEquals("", 0, fr2.getForce().getY(), 0.0001);
//		assertEquals("", 0, fr2.getForce().getZ(), 0.0001);
//	}
//
//	@Test
//	public void testForceResistanceIncompletePart1()
//	{
//		// incomplete part 1
//		ForceResistanceParser fr1 = testee
//				.getForceResistanceParser(PerceptionRSG.FORCE_RESISTANCE_0);
//		ForceResistanceParser fr2 = testee
//				.getForceResistanceParser(PerceptionRSG.FORCE_RESISTANCE_1);
//
//		try {
//			testee.parse("(FRP (n l");
//			// will not fail if assertions are not switched on
//		} catch (AssertionError e) {
//			// expected if assertions switched on
//			assertEquals("Unknown sensor: l", e.getMessage());
//		}
//
//		assertEquals("", 0, fr1.getForceOrigin().getX(), 0.0001);
//		assertEquals("", 0, fr1.getForceOrigin().getY(), 0.0001);
//		assertEquals("", 0, fr1.getForceOrigin().getZ(), 0.0001);
//
//		assertEquals("", 0, fr1.getForce().getX(), 0.0001);
//		assertEquals("", 0, fr1.getForce().getY(), 0.0001);
//		assertEquals("", 0, fr1.getForce().getZ(), 0.0001);
//
//		assertEquals("", 0, fr2.getForceOrigin().getX(), 0.0001);
//		assertEquals("", 0, fr2.getForceOrigin().getY(), 0.0001);
//		assertEquals("", 0, fr2.getForceOrigin().getZ(), 0.0001);
//
//		assertEquals("", 0, fr2.getForce().getX(), 0.0001);
//		assertEquals("", 0, fr2.getForce().getY(), 0.0001);
//		assertEquals("", 0, fr2.getForce().getZ(), 0.0001);
//
//	}
//
//	@Test
//	public void testGyroRate()
//	{
//		GyroRateParser gyr = testee.getGyroRateParser(PerceptionRSG.GYRO_TORSO);
//
//		// normal
//		testee.parse("(GYR (n torso) (rt 0.01 0.07 0.46))");
//		assertEquals("", 0.01, gyr.getGyro().getX(), 0.0001);
//		assertEquals("", 0.07, gyr.getGyro().getY(), 0.0001);
//		assertEquals("", 0.46, gyr.getGyro().getZ(), 0.0001);
//
//		// invalid name
//		try {
//			testee.parse("(GYR (n ger) (rt 0.01 0.07 0.46))");
//			fail("Expected exception, but was none");
//		} catch (NoSuchElementException e) {
//			// expected if assertions not switched on
//		} catch (AssertionError e) {
//			// expected if assertions are switched on
//			assertEquals("Unknown sensor: ger", e.getMessage());
//		}
//		assertEquals("", 0.01, gyr.getGyro().getX(), 0.0001);
//		assertEquals("", 0.07, gyr.getGyro().getY(), 0.0001);
//		assertEquals("", 0.46, gyr.getGyro().getZ(), 0.0001);
//
//		// incomplete
//		try {
//			testee.parse("(GYR (n torso) (rt 5");
//			fail("Expected exception, but was none");
//		} catch (NoSuchElementException e) {
//			// expected
//		} catch (Exception e) {
//			fail("Expected other type of exception as: " + e);
//		}
//		assertEquals("", 0.01, gyr.getGyro().getX(), 0.0001);
//		assertEquals("", 0.07, gyr.getGyro().getY(), 0.0001);
//		assertEquals("", 0.46, gyr.getGyro().getZ(), 0.0001);
//
//		// incomplete 2
//		try {
//			testee.parse("(GYR (n ");
//			fail("Expected exception, but was none");
//		} catch (NoSuchElementException e) {
//			// expected
//		} catch (Exception e) {
//			fail("Expected other type of exception as: " + e);
//		}
//		assertEquals("", 0.01, gyr.getGyro().getX(), 0.0001);
//		assertEquals("", 0.07, gyr.getGyro().getY(), 0.0001);
//		assertEquals("", 0.46, gyr.getGyro().getZ(), 0.0001);
//	}
//
//	@Test
//	public void testHingeJoint()
//	{
//		HingeJointParser hinge1 = testee.getHingeJointParser(PerceptionRSG.HingeJoint0);
//		HingeJointParser hinge2 = testee.getHingeJointParser(PerceptionRSG.HingeJoint1);
//
//		// normal
//		testee.parse("(HJ (n laj3) (ax -1.02)) (HJ (n raj3) (ax 5))");
//		assertEquals("", -1.02, hinge1.getAxis(), 0.0001);
//		assertEquals("", 5, hinge2.getAxis(), 0.0001);
//
//		// invalid name + incomplete
//		try {
//			testee.parse("(HJ (n laj) (ax -1.02)) (HJ (n raj3) (ax ");
//			// will not fail if assertions are not switched on
//		} catch (AssertionError e) {
//			// expected if assertions switched on
//			assertEquals("Unknown sensor: laj", e.getMessage());
//		}
//		assertEquals("", -1.02, hinge1.getAxis(), 0.0001);
//		assertEquals("", 5, hinge2.getAxis(), 0.0001);
//
//		// incomplete 2
//		try {
//			testee.parse("(HJ ");
//			fail("Expected exception, but was none");
//		} catch (NoSuchElementException e) {
//			// expected
//		} catch (Exception e) {
//			fail("Expected other type of exception as: " + e);
//		}
//		assertEquals("", -1.02, hinge1.getAxis(), 0.0001);
//		assertEquals("", 5, hinge2.getAxis(), 0.0001);
//	}
//
//	@Test
//	public void testUniversalJoint()
//	{
//		UniversalJointParser universal1 = testee
//				.getUniversalJointParser(PerceptionRSG.UniversalJoint0);
//		UniversalJointParser universal2 = testee
//				.getUniversalJointParser(PerceptionRSG.UniversalJoint1);
//
//		// normal
//		testee.parse("(UJ (n laj1_2) (ax1 -1.32) (ax2 2.00)) "
//				+ "(UJ (n raj1_2) (ax1 -32) (ax2 62.0))");
//
//		assertEquals("", -1.32, universal1.getAxis1(), 0.0001);
//		assertEquals("", 2, universal1.getAxis2(), 0.0001);
//		assertEquals("", -32, universal2.getAxis1(), 0.0001);
//		assertEquals("", 62, universal2.getAxis2(), 0.0001);
//	}
//
//	@Test
//	public void testUniversalJointIncomplete1()
//	{
//		UniversalJointParser universal1 = testee
//				.getUniversalJointParser(PerceptionRSG.UniversalJoint0);
//		UniversalJointParser universal2 = testee
//				.getUniversalJointParser(PerceptionRSG.UniversalJoint1);
//
//		// incomplete 1
//		try {
//			testee.parse("(UJ (n laj1_2) (ax1 1.32) (ax2 -2.00)) "
//					+ "(UJ (n raj1_2) (ax1 32) (a");
//			fail("Expected exception, but was none");
//		} catch (NoSuchElementException e) {
//			// expected
//		} catch (AssertionError e) {
//			assertEquals("Invalid prefix: a", e.getMessage());
//		}
//		assertEquals("", 1.32, universal1.getAxis1(), 0.0001);
//		assertEquals("", -2, universal1.getAxis2(), 0.0001);
//		assertEquals("", 0, universal2.getAxis1(), 0.0001);
//		assertEquals("", 0, universal2.getAxis2(), 0.0001);
//	}
//
//	@Test
//	public void testUniversalJointIncomplete2()
//	{
//		UniversalJointParser universal1 = testee
//				.getUniversalJointParser(PerceptionRSG.UniversalJoint0);
//		UniversalJointParser universal2 = testee
//				.getUniversalJointParser(PerceptionRSG.UniversalJoint1);
//
//		try {
//			testee.parse("(UJ");
//			fail("Expected exception, but was none");
//		} catch (NoSuchElementException e) {
//			// expected
//		} catch (Exception e) {
//			fail("Expected other type of exception as: " + e);
//		}
//
//		assertEquals("", 0, universal1.getAxis1(), 0.0001);
//		assertEquals("", 0, universal1.getAxis2(), 0.0001);
//		assertEquals("", 0, universal2.getAxis1(), 0.0001);
//		assertEquals("", 0, universal2.getAxis2(), 0.0001);
//	}
//
//	@Test
//	public void testAll()
//	{
//		String message = "(time (now 12.62))(GS (t 0.00) (pm BeforeKickOff))"
//				+ "(GYR (n torso) (rt 0.00 -0.01 -0.04))"
//				+ "(See (G1L (pol 27.21 -176.65 -87.48)) "
//				+ "(G2L (pol 27.26 -128.97 -86.02)) (G2R (pol 27.65 -16.82 -79.53)) "
//				+ "(G1R (pol 27.61 -0.65 -79.97)) (F1L (pol 27.64 134.17 -86.44)) "
//				+ "(F2L (pol 27.76 -113.18 -83.77)) (F1R (pol 28.03 14.54 -79.80)) "
//				+ "(F2R (pol 28.14 -29.77 -78.63)) (B (pol 27.62 -22.83 -85.92)))"
//				+ "(UJ (n laj1_2) (ax1 0.70) (ax2 -0.70))"
//				+ "(UJ (n raj1_2) (ax1 0.80) (ax2 -0.80))"
//				+ "(HJ (n laj3) (ax 0.10))(HJ (n raj3) (ax -0.10))"
//				+ "(HJ (n laj4) (ax 0.20))(HJ (n raj4) (ax -0.20))"
//				+ "(HJ (n llj1) (ax 0.30))(HJ (n rlj1) (ax -0.30))"
//				+ "(UJ (n llj2_3) (ax1 0.40) (ax2 -0.40))"
//				+ "(UJ (n rlj2_3) (ax1 0.50) (ax2 -0.50))"
//				+ "(HJ (n llj4) (ax -0.05))(HJ (n rlj4) (ax 0.05))"
//				+ "(UJ (n llj5_6) (ax1 -0.08) (ax2 0.09))"
//				+ "(UJ (n rlj5_6) (ax1 0.08) (ax2 0.09))";
//
//		testee.parse(message);
//		UniversalJointParser universal1 = testee.getUniversalJointParser("llj5_6");
//		UniversalJointParser universal2 = testee.getUniversalJointParser("rlj5_6");
//		assertEquals("", -0.08, universal1.getAxis1(), 0.0001);
//		assertEquals("", 0.09, universal1.getAxis2(), 0.0001);
//		assertEquals("", 0.08, universal2.getAxis1(), 0.0001);
//		assertEquals("", 0.09, universal2.getAxis2(), 0.0001);
//	}
// }
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

public class LocalizerInsideRectangleTest extends LocalizerBaseTest
{
	/*
	 * @Override @Before public void setUp() { super.setUp(); testee = new
	 * LocalizerInsideRectangle(); } // TODO: Switch back this test when this
	 * localizer supports the new IFlag // interface @Ignore @Test public void
	 * testLocalize() { F1L = new Flag(-6.0f, 4.0f, 7.21110f, (float)
	 * toRadians(180.0f - 33.6900), true); F2L = new Flag(-6.0f, -4.0f, 7.21110f,
	 * (float) toRadians(-180 + 33.6900f), true); F1R = new Flag(6.0f, 4.0f,
	 * 7.21110f, (float) toRadians(33.6900f), true); F2R = new Flag(6.0f, -4.0f,
	 * 7.21110f, (float) toRadians(-33.6900f), true); flags = new HashMap<String,
	 * Flag>(); flags.put("F1L", F1L); flags.put("F2L", F2L); flags.put("F1R",
	 * F1R); flags.put("F2R", F2R);
	 * 
	 * Vector3D[] localizeInfo = testee.localize(flags, 0);
	 * assertNotNull(localizeInfo); assertTrue(FuzzyCompare .eq(new Vector3D(0,
	 * 0, 0), localizeInfo[0], 0.001f)); assertTrue(FuzzyCompare .eq(new
	 * Vector3D(0, 0, 0), localizeInfo[1], 0.001f)); } // TODO: Switch back this
	 * test when this localizer supports the new IFlag // interface @Ignore @Test
	 * public void testLocalizeTurned() { // player is at position -4,-1 looking
	 * 45 deg F1L = new Flag(-6.0f, 4.0f, 5.385164f, 1.16590f, true); F2L = new
	 * Flag(-6.0f, -4.0f, 3.60555f, -2.94420f, true); F1R = new Flag(6.0f, 4.0f,
	 * 11.18034f, -0.32175f, true); F2R = new Flag(6.0f, -4.0f, 10.44031f,
	 * -1.07685f, true); flags = new HashMap<String, Flag>(); flags.put("F1L",
	 * F1L); flags.put("F2L", F2L); flags.put("F1R", F1R); flags.put("F2R", F2R);
	 * 
	 * Vector3D[] localizeInfo = testee.localize(flags, 0);
	 * assertNotNull(localizeInfo); assertTrue(FuzzyCompare.eq(new Vector3D(-4.0,
	 * -1.0, 0), localizeInfo[0], 0.001f)); assertTrue(FuzzyCompare.eq(new
	 * Vector3D(Math.toRadians(45), 0, 0), localizeInfo[1], 0.001f)); }
	 * 
	 * @Test public void testCalculateViewAngleLookingToFlagLeftOfFlag() throws
	 * Exception { ILocalizationFlag flag = new Flag(6.0f, 4.0f, 5.65685f, 0f,
	 * true); assertEquals(45, toDegrees(((LocalizerInsideRectangle) testee)
	 * .calculateViewAngle(2f, 0f, flag)), 0.0001); }
	 * 
	 * @Test public void testCalculateViewAngleLookingToFlagBelowFlag() {
	 * ILocalizationFlag flag = new Flag(6.0f, 4.0f, 4.0f, 0f, true);
	 * assertEquals(90, toDegrees(((LocalizerInsideRectangle) testee)
	 * .calculateViewAngle(6f, 0f, flag)), 0.0001); }
	 * 
	 * @Test public void testCalculateViewAngleLookingToFlagRightOfFlag() {
	 * ILocalizationFlag flag = new Flag(6.0f, 4.0f, 5.65685f, 0f, true);
	 * assertEquals(135, toDegrees(((LocalizerInsideRectangle) testee)
	 * .calculateViewAngle(10f, 0f, flag)), 0.0001); }
	 * 
	 * @Test public void testCalculateViewAngleLookingToFlagLeftAboveFlag() {
	 * ILocalizationFlag flag = new Flag(6.0f, -4.0f, 5.65685f, 0f, true);
	 * assertEquals(-45, toDegrees(((LocalizerInsideRectangle) testee)
	 * .calculateViewAngle(2f, 0f, flag)), 0.0001); }
	 * 
	 * @Test public void testCalculateViewAngleLookingToFlagAboveFlag() {
	 * ILocalizationFlag flag = new Flag(6.0f, -4.0f, 4.0f, 0f, true);
	 * assertEquals(-90, toDegrees(((LocalizerInsideRectangle) testee)
	 * .calculateViewAngle(6f, 0f, flag)), 0.0001); }
	 * 
	 * @Test public void testCalculateViewAngleLeftOfFlagLookingLeft() throws
	 * Exception { ILocalizationFlag flag = new Flag(6.0f, 4.0f, 5.65685f,
	 * (float) toRadians(-45), true); assertEquals(90,
	 * toDegrees(((LocalizerInsideRectangle) testee) .calculateViewAngle(2f, 0f,
	 * flag)), 0.0001); }
	 * 
	 * @Test public void testCalculateViewAngleRightOfFlagLookingLeft() throws
	 * Exception { ILocalizationFlag flag = new Flag(6.0f, 4.0f, 5.65685f,
	 * (float) toRadians(-45), true); assertEquals(-180,
	 * toDegrees(((LocalizerInsideRectangle) testee) .calculateViewAngle(10f, 0f,
	 * flag)), 0.0001); }
	 * 
	 * @Test public void testCalculateViewAngleRightAboveFlagLookingLeft() throws
	 * Exception { ILocalizationFlag flag = new Flag(6.0f, 4.0f, 5.65685f,
	 * (float) toRadians(-45), true); assertEquals(-90,
	 * toDegrees(((LocalizerInsideRectangle) testee) .calculateViewAngle(10f, 8f,
	 * flag)), 0.0001); }
	 * 
	 * @Test public void testAverageAngle() { assertEquals(0f,
	 * toDegrees(((Localizer) testee).averageAngle(new float[] { 0.1f, -0.1f,
	 * 0.2f, -0.2f })), 0.0001); assertEquals(180f, toDegrees(((Localizer)
	 * testee) .averageAngle(new float[] { (float) toRadians(-179.99999), (float)
	 * toRadians(-179.99999), (float) toRadians(179.99999), (float)
	 * toRadians(179.99998) })), 0.0001); }
	 */
}

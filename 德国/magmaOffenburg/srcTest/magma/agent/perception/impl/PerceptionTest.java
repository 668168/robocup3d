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

import magma.agent.IServerConfigFilesConstants;
import magma.agent.perception.IGameStatePerceptor;
import magma.agent.perception.ITimerPerceptor;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;

/**
 * Unit Test class for a complete "End-to-End" Test case: SimSpark message in,
 * decode, pass decoded message to Perception, Check Perception.
 * 
 * @author joachim
 * @author Simon Raffeiner
 * 
 */
public class PerceptionTest
{
	Perception testee;

	/**
	 * Called before each test method to create data that we need in each test
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception
	{
		testee = new Perception();
	}

	@Test
	public void testGyroPerceptor()
	{
		String msg = "(GYR (n torso) (rt 0.01 0.07 0.46))";

		try {
			testee.parse(msg);
		} catch (Exception e) {
			fail("No exception expected at this point");
		}

		GyroPerceptor gyro = testee.getGyroRatePerceptor("torso");

		assertEquals(gyro.getName(), "torso");
	}

	@Test
	public void testGyroPerceptorException()
	{
		try {
			testee.parse("(GYR )");
			fail("Exception expected but none got");
		} catch (Exception e) {
			// Exception expected
		}

		try {
			testee.parse("(GYR (k torso) )");
			fail("Exception expected but none got");
		} catch (Exception e) {
			// Exception expected
		}

		try {
			testee.parse("(GYR (k torso) (rt 0.01 0.07))");
			fail("Exception expected but none got");
		} catch (Exception e) {
			// Exception expected
		}

		try {
			testee.parse("(GYR (n torso) (rotation 0.01 0.07))");
			fail("Exception expected but none got");
		} catch (Exception e) {
			// Exception expected
		}

		try {
			testee.parse("(GYR (k torso) (rt 0.01 0.07) (id 1))");
			fail("Exception expected but none got");
		} catch (Exception e) {
			// Exception expected
		}
	}

	@Test
	public void testGameStatePerceptor()
	{
		// normal call
		try {
			testee.parse("(GS (t 7.98) (pm BeforeKickOff))");
		} catch (Exception e) {
			fail("No exception expected at this point, but got: " + e);
		}

		IGameStatePerceptor gs = testee.getGameState();

		assertEquals("", 7.98, gs.getTime(), 0.0001);
		assertEquals("", IServerConfigFilesConstants.PLAYMODE_BEFORE_KICK_OFF, gs
				.getPlaymode());

		// string in time
		try {
			testee.parse("(GS (t bk) (pm 34))");
			fail("Expected exception, but was none");
		} catch (PerceptorConversionException e) {
			// expected
		} catch (Exception e) {
			fail("Expected other type of exception as: " + e);
		}
		assertEquals("", 7.98, gs.getTime(), 0.0001);
		assertEquals("", IServerConfigFilesConstants.PLAYMODE_BEFORE_KICK_OFF, gs
				.getPlaymode());

		// number in playmode
		try {
			testee.parse("(GS (t 65) (pm 34))");
		} catch (Exception e) {
			fail("No exception expected at this point");
		}

		assertEquals("", 65, gs.getTime(), 0.0001);
		assertEquals("", "34", gs.getPlaymode());

		// incomplete message
		try {
			testee.parse("(GS (t 13");
			fail("Expected exception, but was none");
		} catch (PerceptorConversionException e) {
			// expected
		} catch (Exception e) {
			fail("Expected other type of exception as: " + e);
		}
		assertEquals("", 65, gs.getTime(), 0.0001);
		assertEquals("", "34", gs.getPlaymode());

		// incomplete message
		try {
			testee.parse("(GS ");
			fail("Expected exception, but was none");
		} catch (PerceptorConversionException e) {
			// expected
		} catch (Exception e) {
			fail("Expected other type of exception as: " + e);
		}
		assertEquals("", 65, gs.getTime(), 0.0001);
		assertEquals("", "34", gs.getPlaymode());
	}

	@Test
	public void testGameStatePerceptorException()
	{
		try {
			testee.parse("(GS (bla))");
			fail("Exception expected but none got");
		} catch (Exception e) {
		}

		try {
			testee.parse("(GS (em BeforeKickOff))");
			fail("Exception expected but none got");
		} catch (Exception e) {
		}

		try {
			testee.parse("(GS a)");
			fail("Exception expected but none got");
		} catch (Exception e) {
		}

		try {
			testee.parse("(GS (t 7.98) (pm BlaKick) (bla bla))");
			fail("Exception expected but none got");
		} catch (Exception e) {
		}

	}

	@Test
	public void testGamestateWithUnum()
	{
		IGameStatePerceptor gs = testee.getGameState();

		// normal call
		try {
			testee.parse("(GS (unum 1) (team left) (t 7.98) (pm BeforeKickOff))");
		} catch (Exception e) {
			fail("No exception expected at this point");
		}

		assertEquals("", 7.98, gs.getTime(), 0.0001);
		assertEquals("", IServerConfigFilesConstants.PLAYMODE_BEFORE_KICK_OFF, gs
				.getPlaymode());
	}

	@Test
	public void testTime()
	{
		ITimerPerceptor time;

		time = testee.getTime();

		// normal call
		try {
			testee.parse("(time (now 231.18))");
		} catch (Exception e) {
			fail("No exception expected at this point, but got: " + e);
		}

		assertEquals("", 231.18, time.getTime(), 0.0001);

		// char in float
		try {
			testee.parse("(time (now 2.h18))");
			fail("Expected exception, but was none");
		} catch (PerceptorConversionException e) {
			// expected
		} catch (Exception e) {
			fail("Expected other type of exception as: " + e);
		}
		assertEquals("", 231.18, time.getTime(), 0.0001);

		// incomplete 1
		try {
			testee.parse("(time (now ");
			fail("Expected exception, but was none");
		} catch (PerceptorConversionException e) {
			// expected
		} catch (Exception e) {
			fail("Expected other type of exception as: " + e);
		}

		assertEquals("", 231.18, time.getTime(), 0.0001);

		// incomplete 2
		try {
			testee.parse("(time ");
			fail("Expected exception, but was none");
		} catch (PerceptorConversionException e) {
			// expected
		} catch (Exception e) {
			fail("Expected other type of exception as: " + e);
		}
		assertEquals("", 231.18, time.getTime(), 0.0001);
	}

	@Test
	public void testTimeException()
	{
		// Broken messages
		try {
			testee.parse("(time)");
			fail("Exception expected but none got");
		} catch (Exception e) {
		}

		try {
			testee.parse("(time 125.9)");
			fail("Exception expected but none got");
		} catch (Exception e) {
		}

		try {
			testee.parse("(time (now 3.a) a)");
			fail("Exception expected but none got");
		} catch (Exception e) {
		}

		try {
			testee.parse("(time (now 3.) (pm KickOff))");
			fail("Exception expected but none got");
		} catch (Exception e) {
		}
	}

	@Test
	public void testVision()
	{
		VisibleObjectPerceptor flag1;
		VisibleObjectPerceptor goal2;
		VisibleObjectPerceptor ball;
		PlayerPos player1;
		PlayerPos player2;
		PlayerPos player3;

		// normal
		try {
			testee.parse("(See (F1L (pol 19.11 111.69 -9.57)) "
					+ "(G1R (pol 9.88 139.29 -21.07)) (B (pol 18.34 4.66 -9.90)) "
					+ "(P (team RoboLog) (id 1) (pol 37.50 16.15 -0.00)))");
		} catch (Exception e) {
			fail("No exception expected at this point");
		}

		player1 = testee.getVisiblePlayers().get(0);

		flag1 = testee.getObject("F1L");
		goal2 = testee.getObject("G1R");
		ball = testee.getObject("B");

		assertEquals("", 19.11, flag1.getDistance(), 0.0001);
		assertEquals("", 111.69, flag1.getHorizontalAngleDeg(), 0.0001);
		assertEquals("", -9.57, flag1.getLatitudeAngleDeg(), 0.0001);
		assertEquals("", 9.88, goal2.getDistance(), 0.0001);
		assertEquals("", 139.29, goal2.getHorizontalAngleDeg(), 0.0001);
		assertEquals("", -21.07, goal2.getLatitudeAngleDeg(), 0.0001);
		assertEquals("", 18.34, ball.getDistance(), 0.0001);
		assertEquals("", 4.66, ball.getHorizontalAngleDeg(), 0.0001);
		assertEquals("", -9.9, ball.getLatitudeAngleDeg(), 0.0001);
		assertEquals("", 37.5, player1.getDistance(), 0.0001);
		assertEquals("", 16.15, player1.getHorizontalAngleDeg(), 0.0001);
		assertEquals("", 0, player1.getLatitudeAngleDeg(), 0.0001);
		assertEquals("", "RoboLog", player1.getTeamname());
		assertEquals("", 1, player1.getId());

		// new player
		try {
			testee
					.parse("(See (P (team RoboLog) (id 1) (pol 3.50 16.5 -9.00)) "
							+ "(P (team magmaOffenburg) (id 2) (pol 5 1.15 0.01))"
							+ "(P (team RoboLog) (id 3) (pol 4.12 -2.15 1.66) (llowerarm 1.0 2.0 3.0)))");
		} catch (Exception e) {
			fail("No exception expected at this point, but got: " + e);
		}

		player1 = testee.getVisiblePlayers().get(0);
		player2 = testee.getVisiblePlayers().get(1);
		player3 = testee.getVisiblePlayers().get(2);

		assertEquals("", 3.5, player1.getDistance(), 0.0001);
		assertEquals("", 16.5, player1.getHorizontalAngleDeg(), 0.0001);
		assertEquals("", -9, player1.getLatitudeAngleDeg(), 0.0001);
		assertEquals("", "RoboLog", player1.getTeamname());
		assertEquals("", 1, player1.getId());

		assertEquals("", 5, player2.getDistance(), 0.0001);
		assertEquals("", 1.15, player2.getHorizontalAngleDeg(), 0.0001);
		assertEquals("", 0.01, player2.getLatitudeAngleDeg(), 0.0001);
		assertEquals("", "magmaOffenburg", player2.getTeamname());
		assertEquals("", 2, player2.getId());

		assertEquals("", 4.12, player3.getDistance(), 0.0001);
		assertEquals("", -2.15, player3.getHorizontalAngleDeg(), 0.0001);
		assertEquals("", 1.66, player3.getLatitudeAngleDeg(), 0.0001);
		assertEquals("", "RoboLog", player3.getTeamname());
		assertEquals("", 3, player3.getId());

		// incomplete 1
		try {
			testee.parse("(See (F1L (pol 1.11 111.6");
			fail("Expected exception, but was none");
		} catch (PerceptorConversionException e) {
			// expected
		}
		assertEquals("", 19.11, flag1.getDistance(), 0.0001);
		assertEquals("", 111.69, flag1.getHorizontalAngleDeg(), 0.0001);
		assertEquals("", -9.57, flag1.getLatitudeAngleDeg(), 0.0001);

		// incomplete 2
		try {
			testee.parse("(See (F1L (pol ");
			fail("Expected exception, but was none");
		} catch (PerceptorConversionException e) {
			// expected
		}
		assertEquals("", 19.11, flag1.getDistance(), 0.0001);
		assertEquals("", 111.69, flag1.getHorizontalAngleDeg(), 0.0001);
		assertEquals("", -9.57, flag1.getLatitudeAngleDeg(), 0.0001);

		// incomplete 3
		try {
			testee.parse("(See (F1L ");
			fail("Expected exception, but was none");
		} catch (PerceptorConversionException e) {
			// expected
		}
		assertEquals("", 19.11, flag1.getDistance(), 0.0001);
		assertEquals("", 111.69, flag1.getHorizontalAngleDeg(), 0.0001);
		assertEquals("", -9.57, flag1.getLatitudeAngleDeg(), 0.0001);

		// incomplete 4
		try {
			testee.parse("(See ");
			fail("Expected exception, but was none");
		} catch (PerceptorConversionException e) {
			// expected
		}
		assertEquals("", 19.11, flag1.getDistance(), 0.0001);
		assertEquals("", 111.69, flag1.getHorizontalAngleDeg(), 0.0001);
		assertEquals("", -9.57, flag1.getLatitudeAngleDeg(), 0.0001);

		// incomplete 5
		try {
			testee.parse("(See (P (team RoboLo) (id 2) ");
			fail("Expected exception, but was none");
		} catch (PerceptorConversionException e) {
			// expected
		}

		// incomplete 6
		try {
			testee.parse("(See (P (team RoboLo");
			fail("Expected exception, but was none");
		} catch (PerceptorConversionException e) {
			// expected
		}
	}

	@Test
	public void testPlayerPMissing() throws Exception
	{
		// NOTE: IMO this actually IS an illegal string and the test SHOULD fail.
		// Players may lack a team name but the letter "P" is not a part of the
		// player information but a part of the protocol!.
		String message = "(See (B (pol 0.36 16.48 -60.37)) ( (id 0) (pol 1.50 -79.82 49.85)))";

		try {
			testee.parse(message);
			fail("No exception expected at this point");
		} catch (AssertionError e) {
		}
	}

	@Test
	public void testHearPerceptor()
	{
		String message = "(hear 7.98 self \"Das ist ein Test\")";

		try {
			testee.parse(message);
		} catch (PerceptorConversionException e) {
			fail("No exception expected at this point");
		}

		HearPerceptor hear = testee.getHearPerceptor();

		assertEquals(hear.getTime(), 7.98, 0.0001);
		assertEquals(hear.getTarget(), "self");
		assertEquals(hear.getMessage(), "\"Das ist ein Test\"");
	}

	@Test
	public void testHearPerceptorException()
	{
		// Incomplete 1: Empty
		String message = "(hear)";

		try {
			testee.parse(message);
			fail("Exception expected!");
		} catch (PerceptorConversionException e) {
		} catch (Exception e) {
			fail("Expected a PerceptorConversionException but got a "
					+ e.getClass());
		}

		// Incomplete 2: Missing target
		message = "(hear 7.98)";

		try {
			testee.parse(message);
			fail("Exception expected!");
		} catch (PerceptorConversionException e) {
		} catch (Exception e) {
			fail("Expected a PerceptorConversionException but got a "
					+ e.getClass());
		}

		// Incomplete 3: Time is a string
		message = "(hear bla)";

		try {
			testee.parse(message);
			fail("Exception expected!");
		} catch (PerceptorConversionException e) {
		} catch (Exception e) {
			fail("Expected a PerceptorConversionException but got a "
					+ e.getClass());
		}

		// Incomplete 4: Missing message
		message = "(hear 9.75 self)";

		try {
			testee.parse(message);
			fail("Exception expected!");
		} catch (PerceptorConversionException e) {
		} catch (Exception e) {
			fail("Expected a PerceptorConversionException but got a "
					+ e.getClass());
		}
	}
}
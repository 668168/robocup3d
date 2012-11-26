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

import java.util.List;

import magma.agent.IServerConfigFilesConstants;
import magma.agent.perception.IGameStatePerceptor;
import magma.agent.perception.IHearPerceptor;
import magma.agent.perception.ITimerPerceptor;
import magma.agent.perception.IVisibleObjectPerceptor;

import org.apache.commons.math.geometry.Vector3D;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

/**
 * @author Simon Raffeiner
 */
public class ServerMessageParserTest
{
	private ServerMessageParser testee;

	@Before
	public void setUp()
	{
		testee = new ServerMessageParser();
	}

	@Test
	public void testGyroPerceptor()
	{
		String msg = "(GYR (n torso) (rt 0.01 0.07 0.46))";

		try {
			List<Perceptor> list = testee.parseString(msg);

			assertEquals(list.size(), 1);

			Perceptor perceptor = list.get(0);
			assertTrue(perceptor instanceof GyroPerceptor);

			GyroPerceptor gyro = (GyroPerceptor) perceptor;

			assertEquals(gyro.getName(), "torso");

			Vector3D rotation = gyro.getGyro();
			assertEquals(rotation.getX(), 0.01f, 0.0001);
			assertEquals(rotation.getY(), 0.07f, 0.0001);
			assertEquals(rotation.getZ(), 0.46f, 0.0001);
		} catch (Exception e) {
			fail("No exception expected");
		}
	}

	@Test
	public void testHingeJointPerceptor()
	{
		String msg = "(HJ (n laj3) (ax -1.02))";

		try {
			List<Perceptor> list = testee.parseString(msg);

			assertEquals(list.size(), 1);

			Perceptor perceptor = list.get(0);
			assertTrue(perceptor instanceof HingeJointPerceptor);

			HingeJointPerceptor hinge = (HingeJointPerceptor) perceptor;

			assertEquals(hinge.getName(), "laj3");
			assertEquals(hinge.getAxis(), -1.02f, 0.0001);
		} catch (Exception e) {
			fail("No exception expected");
		}
	}

	@Test
	public void testUniversalJointPerceptor()
	{
		String msg = "(UJ (n laj1 2) (ax1 -1.32) (ax2 2.00))";

		try {
			List<Perceptor> list = testee.parseString(msg);

			assertEquals(list.size(), 1);

			Perceptor perceptor = list.get(0);
			assertTrue(perceptor instanceof UniversalJointPerceptor);

			UniversalJointPerceptor hinge = (UniversalJointPerceptor) perceptor;

			assertEquals(hinge.getName(), "laj1");
			assertEquals(hinge.getAxis1(), -1.32f, 0.0001);
			assertEquals(hinge.getAxis2(), 2.00f, 0.0001);
		} catch (Exception e) {
			fail("No exception expected");
		}
	}

	@Test
	public void testForceResistancePerceptor()
	{
		String msg = "(FRP (n lf) (c -0.14 0.08 -0.05) (f 1.12 -0.26 13.07))";

		try {
			List<Perceptor> list = testee.parseString(msg);

			assertEquals(list.size(), 1);

			Perceptor perceptor = list.get(0);
			assertTrue(perceptor instanceof ForceResistancePerceptor);

			ForceResistancePerceptor frp = (ForceResistancePerceptor) perceptor;

			assertEquals(frp.getName(), "lf");

			Vector3D origin = frp.getForceOrigin();
			Vector3D force = frp.getForce();

			assertEquals(origin.getX(), -0.14f, 0.0001);
			assertEquals(origin.getY(), 0.08f, 0.0001);
			assertEquals(origin.getZ(), -0.05f, 0.0001);
			assertEquals(force.getX(), 1.12f, 0.0001);
			assertEquals(force.getY(), -0.26f, 0.0001);
			assertEquals(force.getZ(), 13.07f, 0.0001);
		} catch (Exception e) {
			fail("No exception expected");
		}
	}

	@Test
	public void testVisionPerceptor()
	{
		String msg = "(See (F1L (pol 19.11 111.69 -9.57)) "
				+ "(G1R (pol 9.88 139.29 -21.07)) (B (pol 18.34 4.66 -9.90)) "
				+ "(P (team RoboLog) (id 1) (pol 37.50 16.15 -0.00))"
				+ "(P (team RoboLog) (id 2) (pol 37.50 16.15 -0.00)))";

		try {

			List<Perceptor> list = testee.parseString(msg);

			assertEquals(list.size(), 1);

			Perceptor perceptor = list.get(0);
			assertTrue(perceptor instanceof VisionPerceptor);

			VisionPerceptor vision = (VisionPerceptor) perceptor;

			// Check Flags
			IVisibleObjectPerceptor flag1 = vision.getObject(0);
			IVisibleObjectPerceptor goal2 = vision.getObject(1);
			IVisibleObjectPerceptor ball = vision.getObject(2);
			PlayerPos player1 = (PlayerPos) vision.getObject(3);

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

			PlayerPos player2 = (PlayerPos) vision.getObject(4);
			assertEquals("", 2, player2.getId());
			assertEquals(37.5, player2.getDistance(), 0.001);
		} catch (Exception e) {
			fail("No exception expected");
		}

		// Minimum message
		try {
			testee.parse("(See)");
		} catch (Exception e) {
			fail("No exception expected");
		}

		// Message containing one player
		try {
			List<Perceptor> list = testee
					.parseString("(See (P (team RoboLog) (pol 37.50 16.15 -0.00)))");
			VisionPerceptor vision = (VisionPerceptor) list.get(0);
			PlayerPos player2 = (PlayerPos) vision.getObject(0);
			assertEquals("RoboLog", player2.getTeamname());
			assertEquals(37.5, player2.getDistance(), 0.001);
			assertEquals(16.15, player2.getHorizontalAngleDeg(), 0.001);
		} catch (Exception e) {
			fail("No exception expected");
		}

		// Player message with lower arm information
		try {
			List<Perceptor> list = testee
					.parse("(See (P (team RoboLog) (pol 27.50 16.15 -0.00) "
							+ "(llowerarm (pol 37.50 16.15 -0.00))))");

			VisionPerceptor vision = (VisionPerceptor) list.get(0);
			PlayerPos player2 = (PlayerPos) vision.getObject(0);
			assertEquals("RoboLog", player2.getTeamname());
			assertEquals(27.5, player2.getDistance(), 0.001);
			assertEquals(16.15, player2.getHorizontalAngleDeg(), 0.001);
		} catch (Exception e) {
			fail("No exception expected");
		}

		// message from server logfile
		try {
			List<Perceptor> list = testee
					.parse("(See (F2R (pol 7.34 50.15 -4.31)) "
							+ "(P (team magmaOffenburg) (id 2) (head (pol 2.36 -41.55 -0.03)) "
							+ "(rlowerarm (pol 2.38 -37.08 -1.47)) (llowerarm (pol 2.20 -39.95 -1.89)) "
							+ "(rfoot (pol 2.45 -40.18 -12.30)) (lfoot (pol 2.36 -41.42 -12.58))) "
							+ "(P (team magmaOffenburg) (id 3) (rlowerarm (pol 0.19 48.14 -22.49))))");

			VisionPerceptor vision = (VisionPerceptor) list.get(0);
			PlayerPos player2 = (PlayerPos) vision.getObject(1);
			assertEquals("magmaOffenburg", player2.getTeamname());
			assertEquals(2.36, player2.getDistance(), 0.001);
			assertEquals(-41.55, player2.getHorizontalAngleDeg(), 0.001);

			PlayerPos player3 = (PlayerPos) vision.getObject(2);
			assertEquals("magmaOffenburg", player3.getTeamname());
			assertEquals(0.19, player3.getDistance(), 0.001);
			assertEquals(48.14, player3.getHorizontalAngleDeg(), 0.001);
		} catch (Exception e) {
			fail("No exception expected");
		}

	}

	@Test
	public void testAgentStatePerceptor()
	{
		String msg = "(AgentState (temp 48) (battery 75))";

		try {
			List<Perceptor> list = testee.parseString(msg);

			assertEquals(list.size(), 1);

			Perceptor perceptor = list.get(0);
			assertTrue(perceptor instanceof AgentStatePerceptor);

			AgentStatePerceptor agentstate = (AgentStatePerceptor) perceptor;

			assertEquals(agentstate.getTemperature(), 48);
			assertEquals(agentstate.getBattery(), 75);
		} catch (Exception e) {
			fail("No exception expected");
		}
	}

	@Test
	public void testGameStatePerceptor()
	{
		String msg = "(GS (t 1.12) (pm BeforeKickOff))";

		try {
			List<Perceptor> list = testee.parseString(msg);

			assertEquals(list.size(), 1);

			Perceptor perceptor = list.get(0);
			assertTrue(perceptor instanceof GameStatePerceptor);

			IGameStatePerceptor gamestate = (IGameStatePerceptor) perceptor;

			assertEquals(gamestate.getTime(), 1.12f, 0.0001);
			assertEquals(IServerConfigFilesConstants.PLAYMODE_BEFORE_KICK_OFF,
					gamestate.getPlaymode());
		} catch (Exception e) {
			fail("No exception expected");
		}
	}

	@Test
	public void testTouchPerceptor()
	{
		String msg = "(TCH n bumper val 1)";

		try {
			List<Perceptor> list = testee.parseString(msg);

			assertEquals(list.size(), 1);

			Perceptor perceptor = list.get(0);
			assertTrue(perceptor instanceof TouchPerceptor);

			TouchPerceptor touch = (TouchPerceptor) perceptor;

			assertEquals(touch.getName(), "bumper");
			assertEquals(touch.getState(), true);
		} catch (Exception e) {
			fail("No exception expected");
		}
	}

	@Test
	public void testHearPerceptor() throws Exception
	{
		String msg = "(hear 12.3 self \"Hello RoboCup World\")";

		List<Perceptor> list = testee.parseString(msg);

		assertEquals(list.size(), 1);

		Perceptor perceptor = list.get(0);
		assertTrue(perceptor instanceof HearPerceptor);

		IHearPerceptor hear = (IHearPerceptor) perceptor;

		assertEquals(hear.getTime(), 12.3f, 0.0001f);
		assertEquals(hear.getTarget(), "self");
		assertEquals(hear.getMessage(), "\"Hello RoboCup World\"");
	}

	@Test
	public void testTimePerceptor() throws Exception
	{
		String msg = "(time (now 2.18))";

		List<Perceptor> list = testee.parseString(msg);

		assertEquals(list.size(), 1);

		Perceptor perceptor = list.get(0);
		assertTrue(perceptor instanceof TimePerceptor);

		ITimerPerceptor time = (ITimerPerceptor) perceptor;

		assertEquals(time.getTime(), 2.18f, 0.0001f);
	}

	@Test
	public void testGoalsScored() throws Exception
	{
		String msg = "(GS (t 1.0)(pm goal_r))";

		List<Perceptor> list = testee.parseString(msg);

		assertEquals(list.size(), 1);

		Perceptor perceptor = list.get(0);
		assertTrue(perceptor instanceof GameStatePerceptor);

		// previous playmode will be goal_r. number of goals wil not be updated.
		/*
		 * msg = "((GS)(t)(2.0)(pm)(goal_r))"; p.update(msg);
		 * testee.updateGoalsScored(p); assertEquals(1,
		 * testee.getGoalsWeScored());
		 * 
		 * msg = "((GS)(t)(2.0)(pm)(goal_l))"; p.update(msg);
		 * testee.updateGoalsScored(p); assertEquals(1,
		 * testee.getGoalsTheyScored());
		 * 
		 * msg = "((GS)(t)(2.0)(pm)(playon))"; p.update(msg);
		 * testee.updateGoalsScored(p); assertEquals(1,
		 * testee.getGoalsTheyScored());
		 * 
		 * msg = "((GS)(t)(2.0)(pm)(goal_r))"; p.update(msg);
		 * testee.updateGoalsScored(p); assertEquals(2,
		 * testee.getGoalsWeScored());
		 */
	}

	@Test
	public void testHeavyRobocupString() throws Exception
	{
		String msg = "(time (now 136.99))(GS (t 126.47) (pm PlayOn))(GYR (n torso) (rt 12.09 -0.08 -5.45))(HJ (n hj1) (ax -115.78))(HJ (n hj2) (ax -4.80))(See (G1L (pol 9.20 -48.87 13.29)) (G2L (pol 8.97 -40.23 13.15)) (F2L (pol 9.35 -19.44 7.39)) (P (team magmaOffenburg) (id 2) (rlowerarm (pol 0.25 27.34 -57.54))))(HJ (n raj1) (ax -89.43))(HJ (n raj2) (ax -7.84))(HJ (n raj3) (ax 0.18))(HJ (n raj4) (ax -0.06))(HJ (n laj1) (ax -86.08))(HJ (n laj2) (ax 13.36))(HJ (n laj3) (ax -1.05))(HJ (n laj4) (ax 0.69))(HJ (n rlj1) (ax -0.11))(HJ (n rlj2) (ax 14.36))(HJ (n rlj3) (ax 42.12))(HJ (n rlj4) (ax -69.36))(HJ (n rlj5) (ax 18.74))(FRP (n rf) (c 0.00 -0.08 -0.01) (f -0.19 2.64 36.08))(HJ (n rlj6) (ax -14.37))(HJ (n llj1) (ax -0.13))(HJ (n llj2) (ax 14.37))(HJ (n llj3) (ax 41.93))(HJ (n llj4) (ax -69.18))(HJ (n llj5) (ax 18.55))(FRP (n lf) (c -0.02 -0.03 -0.02) (f -0.13 -2.46 8.90))(HJ (n llj6) (ax -14.37))";

		List<Perceptor> list = testee.parseString(msg);

		assertNotNull(list);
	}
}

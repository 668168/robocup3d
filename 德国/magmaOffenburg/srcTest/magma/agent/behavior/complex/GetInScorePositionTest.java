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
package magma.agent.behavior.complex;

import magma.agent.worldmodel.IGlobalMap;
import magma.agent.worldmodel.IMoveableObject;
import magma.agent.worldmodel.impl.ThisPlayer;

import org.apache.commons.math.geometry.Vector3D;
import org.junit.Before;
import org.junit.Test;

import static org.easymock.EasyMock.expect;
import static org.easymock.classextension.EasyMock.createMock;
import static org.easymock.classextension.EasyMock.replay;
import static org.junit.Assert.assertEquals;

public class GetInScorePositionTest
{
	private GetInScorePosition testee;

	private IGlobalMap worldModelMock;

	private IMoveableObject ballMock;

	private ThisPlayer thisPlayer;

	@Before
	public void setUp() throws Exception
	{
		worldModelMock = createMock(IGlobalMap.class);
		ballMock = createMock(IMoveableObject.class);
		thisPlayer = new ThisPlayer("test", 1);
		testee = new GetInScorePosition(worldModelMock, null, null, null);
	}

	@Test
	public void testPerform()
	{
		thisPlayer.setPosition(new Vector3D(0, 0, 0));
		expect(worldModelMock.getBall()).andReturn(ballMock);
		expect(worldModelMock.getThisPlayer()).andReturn(thisPlayer);
		expect(worldModelMock.getOtherGoalPosition()).andReturn(
				new Vector3D(6.0, 0.0, 0.0));
		Vector3D ballPosition = new Vector3D(2.0, 0.0, 0.0);
		expect(ballMock.getPosition()).andReturn(ballPosition);
		// this is the expected position
		replay(worldModelMock, ballMock);

		double[] result = testee.getPosition();

		assertEquals(1.75, result[0], 0.001);
		assertEquals(0.0, result[1], 0.001);
		assertEquals(0.0, result[2], 0.001);

	}

	@Test
	public void testPerformMoveAround()
	{
		thisPlayer.setPosition(new Vector3D(4, 0, 0));
		expect(worldModelMock.getBall()).andReturn(ballMock);
		expect(worldModelMock.getThisPlayer()).andReturn(thisPlayer);
		expect(worldModelMock.getOtherGoalPosition()).andReturn(
				new Vector3D(6.0, 0.0, 0.0));
		Vector3D ballPosition = new Vector3D(2.0, 0.0, 0.0);
		expect(ballMock.getPosition()).andReturn(ballPosition);
		// this is the expected position
		replay(worldModelMock, ballMock);

		double[] result = testee.getPosition();

		assertEquals(2.0, result[0], 0.001);
		assertEquals(-0.7, result[1], 0.001);
		assertEquals(0.0, result[2], 0.001);

	}

	@Test
	public void testPerformMoveAroundAnywhere()
	{
		thisPlayer.setPosition(new Vector3D(-2, -2.5, 0));
		expect(worldModelMock.getBall()).andReturn(ballMock);
		expect(worldModelMock.getThisPlayer()).andReturn(thisPlayer);
		expect(worldModelMock.getOtherGoalPosition()).andReturn(
				new Vector3D(6.0, 0.0, 0.0));
		Vector3D ballPosition = new Vector3D(-3, -1, 0.0);
		expect(ballMock.getPosition()).andReturn(ballPosition);
		// this is the expected position
		replay(worldModelMock, ballMock);

		double[] result = testee.getPosition();

		assertEquals(-3.5824, result[0], 0.001);
		assertEquals(-1.3882, result[1], 0.001);
		assertEquals(0.11065, result[2], 0.001);
	}

}

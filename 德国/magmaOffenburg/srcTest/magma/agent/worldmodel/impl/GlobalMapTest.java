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

import java.util.ArrayList;
import java.util.List;

import magma.agent.perception.IPerception;
import magma.agent.perception.impl.PlayerPos;
import magma.agent.worldmodel.IPlayer;

import org.apache.commons.math.geometry.Vector3D;
import org.junit.Before;
import org.junit.Test;

import static org.easymock.EasyMock.expect;
import static org.easymock.classextension.EasyMock.createMock;
import static org.easymock.classextension.EasyMock.replay;
import static org.junit.Assert.assertEquals;

public class GlobalMapTest
{
	private GlobalMap testee;

	private IPerception perceptionMock;

	@Before
	public void setUp() throws Exception
	{
		perceptionMock = createMock(IPerception.class);

		testee = new GlobalMap(null, "team", 0);
	}

	@Test
	public void testUpdatePlayers()
	{
		testee.thisPlayer = new ThisPlayer("self", 0);
		testee.thisPlayer.setPosition(new Vector3D(0.0, 0.0, 0.0));
		PlayerPos playerVision = new PlayerPos(new Vector3D(2.0, 3.0, 0.0), 1,
				"test");
		List<PlayerPos> playersVision = new ArrayList<PlayerPos>();
		playersVision.add(playerVision);
		expect(perceptionMock.getVisiblePlayers()).andStubReturn(playersVision);
		replay(perceptionMock);

		testee.updatePlayers(perceptionMock);

		List<IPlayer> players = testee.getVisiblePlayers();
		assertEquals(1, players.size());
		IPlayer player = players.get(0);
		assertEquals(1, player.getID());
		assertEquals("test", player.getTeamname());

		// test clear of list if called twice
		testee.updatePlayers(perceptionMock);
		assertEquals(1, testee.getVisiblePlayers().size());

	}
}

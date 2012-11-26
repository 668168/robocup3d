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
package magma.agent.believe.impl;

import java.util.Collections;
import java.util.List;

import magma.agent.worldmodel.IGlobalMap;
import magma.agent.worldmodel.IMoveableObject;
import magma.agent.worldmodel.IPlayer;
import magma.agent.worldmodel.IThisPlayer;

import org.junit.Before;
import org.junit.Test;

import static org.easymock.EasyMock.createMock;
import static org.easymock.EasyMock.expect;
import static org.easymock.EasyMock.replay;
import static org.junit.Assert.assertEquals;

/**
 * @author dorer
 * 
 */
public class TeammateCloserToBallTest
{
	TeammateCloserToBall testee;

	IGlobalMap worldModelMock;

	IThisPlayer thisPlayerMock;

	IPlayer playerMock;

	IMoveableObject ballMock;

	/**
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception
	{
		ballMock = createMock(IMoveableObject.class);
		playerMock = createMock(IPlayer.class);
		thisPlayerMock = createMock(IThisPlayer.class);
		worldModelMock = createMock(IGlobalMap.class);
		expect(worldModelMock.getThisPlayer()).andReturn(thisPlayerMock);
		expect(worldModelMock.getBall()).andReturn(ballMock);
		testee = new TeammateCloserToBall(null, worldModelMock);
	}

	/**
	 * Test method for
	 * {@link magma.agent.believe.impl.TeammateCloserToBall#getTruthValue()}.
	 */
	@Test
	public void testGetTruthValueNoTeammates()
	{
		List<IPlayer> empty = Collections.emptyList();
		expect(worldModelMock.getOwnPlayers()).andReturn(empty);
		expect(worldModelMock.getGlobalTime()).andReturn(0f);
		replay(worldModelMock, thisPlayerMock);

		assertEquals(0.0, testee.getTruthValue(), 0.0001);
	}

	/**
	 * Test method for
	 * {@link magma.agent.believe.impl.TeammateCloserToBall#getTruthValue()}.
	 */
	@Test
	public void testGetTruthValueFarerTeammate()
	{
		expect(playerMock.isOwnTeam()).andReturn(true);
		expect(playerMock.getDistanceTo(ballMock)).andReturn(1.0);
		expect(playerMock.getAge(0)).andReturn(0.0f);
		expect(playerMock.isGoalie()).andReturn(false);
		expect(playerMock.getID()).andStubReturn(1);
		expect(thisPlayerMock.getDistanceTo(ballMock)).andReturn(0.5);
		expect(thisPlayerMock.getID()).andStubReturn(2);
		List<IPlayer> teammates = Collections.singletonList(playerMock);
		expect(worldModelMock.getOwnPlayers()).andReturn(teammates);
		expect(worldModelMock.getGlobalTime()).andReturn(0f);
		replay(worldModelMock, thisPlayerMock, playerMock);

		assertEquals(0.0, testee.getTruthValue(), 0.0001);
	}

	/**
	 * Test method for
	 * {@link magma.agent.believe.impl.TeammateCloserToBall#getTruthValue()}.
	 */
	@Test
	public void testGetTruthValueCloserTeammate()
	{
		expect(playerMock.isOwnTeam()).andReturn(true);
		expect(playerMock.getDistanceTo(ballMock)).andReturn(1.0);
		expect(playerMock.getAge(0)).andReturn(0.0f);
		expect(playerMock.isGoalie()).andReturn(false);
		expect(playerMock.getID()).andStubReturn(1);
		expect(thisPlayerMock.getDistanceTo(ballMock)).andReturn(1.5);
		expect(thisPlayerMock.getID()).andStubReturn(2);
		List<IPlayer> teammates = Collections.singletonList(playerMock);
		expect(worldModelMock.getOwnPlayers()).andReturn(teammates);
		expect(worldModelMock.getGlobalTime()).andReturn(0f);
		replay(worldModelMock, thisPlayerMock, playerMock);

		assertEquals(1.0, testee.getTruthValue(), 0.0001);
	}

}

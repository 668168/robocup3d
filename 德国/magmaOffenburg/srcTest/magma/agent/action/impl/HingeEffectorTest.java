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
package magma.agent.action.impl;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class HingeEffectorTest
{

	private HingeEffector testee1;

	private HingeEffector testee2;

	// private HingeEffector testee3;

	@Before
	public void setUp() throws Exception
	{
		testee1 = new HingeEffector("he1");
		testee1.setAxisSpeed(1.0f);

		testee2 = new HingeEffector("he1");
		testee2.setAxisSpeed(0.0f);
		testee2.setAxisSpeed(0.0f);
	}

	@Test
	public void checkEffectorMessage()
	{
		assertEquals("Message fails", "(he1 1.0)", testee1.getMessageString());

		assertEquals("Supressing Message fails", "", testee2.getMessageString());

	}
}

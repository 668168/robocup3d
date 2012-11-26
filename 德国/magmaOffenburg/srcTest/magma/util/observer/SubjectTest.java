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
package magma.util.observer;

import org.junit.Before;
import org.junit.Test;

import static org.easymock.EasyMock.createMock;
import static org.easymock.EasyMock.replay;
import static org.easymock.EasyMock.verify;
import static org.junit.Assert.assertFalse;

/**
 * Tests for Observer pattern Subject class
 */
public class SubjectTest
{
	IPublishSubscribe<String> testee;

	IObserver<String> observerMock1;

	IObserver<String> observerMock2;

	/**
	 * @throws java.lang.Exception
	 */
	@SuppressWarnings("unchecked")
	@Before
	public void setUp() throws Exception
	{
		testee = new Subject<String>();
		observerMock1 = createMock(IObserver.class);
		observerMock2 = createMock(IObserver.class);
	}

	/**
	 * Test method for
	 * {@link magma.util.observer.Subject#attach(magma.util.observer.IObserver)}.
	 */
	@Test
	public void testAttach()
	{
		String testString = "test";
		observerMock1.update(testString);
		replay(observerMock1);

		testee.attach(observerMock1);
		testee.onStateChange(testString);
		verify(observerMock1);
	}

	/**
	 * Test method for
	 * {@link magma.util.observer.Subject#attach(magma.util.observer.IObserver)}.
	 */
	@Test
	public void testAttachNoDuplicates()
	{
		String testString = "test";
		observerMock1.update(testString);
		replay(observerMock1);

		testee.attach(observerMock1);
		testee.attach(observerMock1);
		testee.onStateChange(testString);
		verify(observerMock1);
	}

	/**
	 * Test method for
	 * {@link magma.util.observer.Subject#attach(magma.util.observer.IObserver)}.
	 */
	@Test
	public void testAttachTwo()
	{
		String testString = "test";
		observerMock1.update(testString);
		observerMock2.update(testString);
		replay(observerMock1, observerMock2);

		testee.attach(observerMock1);
		testee.attach(observerMock2);
		testee.onStateChange(testString);
		verify(observerMock1);
	}

	/**
	 * Test method for
	 * {@link magma.util.observer.Subject#detach(magma.util.observer.IObserver)}.
	 */
	@Test
	public void testDetach()
	{
		String testString = "test";
		observerMock1.update(testString);
		replay(observerMock1, observerMock2);

		testee.attach(observerMock1);
		testee.attach(observerMock2);
		testee.detach(observerMock2);
		testee.onStateChange(testString);

		testee.detach(observerMock1);
		testee.onStateChange(testString);

		assertFalse(testee.detach(observerMock1));
		verify(observerMock1);
	}
}

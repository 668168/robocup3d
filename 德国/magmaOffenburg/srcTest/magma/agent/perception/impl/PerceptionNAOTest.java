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

import magma.agent.perception.IHingeJointPerceptor;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

/**
 * Unit Test class for Perceptor
 * @author joachim
 * 
 */
public class PerceptionNAOTest
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
	public void testAll() throws Exception
	{
		String message = "(GYR (n torso) (rt 0.00 0.00 0.00))"
				+ "(HJ (n hj1) (ax -0.00))(HJ (n hj2) (ax -0.00))"
				+ "(time (now 6.26))(GS (t 0.00) (pm BeforeKickOff))"
				+ "(See (G1L (pol 3.66 60.39 -19.87)) (G2L (pol 3.26 84.50 -22.24)) "
				+ "(G2R (pol 3.26 -84.26 -22.24)) (G1R (pol 3.67 -60.56 -19.78)) "
				+ "(F1L (pol 4.55 45.10 -21.07)) (F2L (pol 3.55 108.07 -27.78)) "
				+ "(F1R (pol 4.55 -45.20 -21.24)) (F2R (pol 3.57 -108.00 -26.97)) "
				+ "(B (pol 1.89 -0.31 -58.15)))"
				+ "(FRP (n lf) (c 0.01 -0.02 -0.02) (f -0.54 0.06 168.04))"
				+ "(FRP (n rf) (c 0.01 -0.01 -0.02) (f -1.31 0.86 167.29))"
				+ "(HJ (n raj1) (ax -0.00))(HJ (n raj2) (ax -0.00))"
				+ "(HJ (n raj3) (ax -0.00))(HJ (n raj4) (ax -0.00))"
				+ "(HJ (n laj1) (ax -0.00))(HJ (n laj2) (ax -0.00))"
				+ "(HJ (n laj3) (ax -0.00))(HJ (n laj4) (ax -0.00))"
				+ "(HJ (n rlj1) (ax -0.00))(HJ (n rlj2) (ax -0.00))"
				+ "(HJ (n rlj3) (ax -0.00))(HJ (n rlj4) (ax -0.00))"
				+ "(HJ (n rlj5) (ax -0.00))(HJ (n rlj6) (ax -0.00))"
				+ "(HJ (n llj1) (ax -0.00))(HJ (n llj2) (ax -0.00))"
				+ "(HJ (n llj3) (ax -0.00))(HJ (n llj4) (ax -0.00))"
				+ "(HJ (n llj5) (ax -0.00))(HJ (n llj6) (ax -1.20))";

		testee.parse(message);
		IHingeJointPerceptor hinge = testee.getHingeJointPerceptor("llj6");
		assertEquals(-1.20, hinge.getAxis(), 0.0001);
	}
}
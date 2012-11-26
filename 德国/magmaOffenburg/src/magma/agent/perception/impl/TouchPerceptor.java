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

import magma.agent.perception.IPerceptor;
import magma.agent.perception.ITouchPerceptor;

/**
 * Touch perceptor
 * 
 * @author Simon Raffeiner
 */
public class TouchPerceptor extends Perceptor implements ITouchPerceptor
{
	private boolean state;

	/**
	 * Default constructor, initializes the state to false
	 * 
	 * @param name Perceptor name
	 */
	public TouchPerceptor(String name)
	{
		this(name, false);
	}

	/**
	 * Assignment constructor
	 * 
	 * @param name Perceptor name
	 * @param state Sensor state
	 */
	public TouchPerceptor(String name, boolean state)
	{
		super(name);
		this.state = state;
	}

	@Override
	public boolean getState()
	{
		return this.state;
	}

	@Override
	public void assign(IPerceptor source)
	{
		if (source instanceof TouchPerceptor) {
			TouchPerceptor input = (TouchPerceptor) source;

			state = input.state;
		}
	}
}

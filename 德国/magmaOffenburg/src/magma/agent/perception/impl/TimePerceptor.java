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
import magma.agent.perception.ITimerPerceptor;

/**
 * Time Perceptor
 * @author Simon Raffeiner
 */
public class TimePerceptor extends Perceptor implements ITimerPerceptor
{
	// Time
	private float time;

	/**
	 * Default constructor
	 */
	public TimePerceptor()
	{
		this(0.00f);
	}

	/**
	 * Assignment constructor
	 * 
	 * @param time Time
	 */
	public TimePerceptor(float time)
	{
		super("time");
		this.time = time;
	}

	@Override
	public float getTime()
	{
		return time;
	}

	@Override
	public void assign(IPerceptor source)
	{
		if (source instanceof TimePerceptor) {
			TimePerceptor input = (TimePerceptor) source;

			time = input.time;
		}
	}
}

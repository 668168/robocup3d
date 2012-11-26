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

import magma.agent.perception.IHearPerceptor;
import magma.agent.perception.IPerceptor;

/**
 * Hear Perceptor
 * 
 * @author Ingo Schindler
 * @author Simon Raffeiner
 * 
 */
public class HearPerceptor extends Perceptor implements IHearPerceptor
{
	// Time the message was heard
	private float time;

	// Target the message is directed to
	private String target;

	// The actual message
	private String message;

	/**
	 * Default constructor, nothing heard
	 */
	public HearPerceptor()
	{
		this(0.00f, "", "");
	}

	/**
	 * Assignment constructor
	 * 
	 * @param time Time
	 * @param target Target
	 * @param message Message
	 */
	public HearPerceptor(float time, String target, String message)
	{
		super("hear");

		this.time = time;
		this.target = target;
		this.message = message;
	}

	@Override
	public float getTime()
	{
		return this.time;
	}

	@Override
	public String getTarget()
	{
		return this.target;
	}

	@Override
	public String getMessage()
	{
		return this.message;
	}

	@Override
	public void assign(IPerceptor source)
	{
		if (source instanceof HearPerceptor) {
			HearPerceptor input = (HearPerceptor) source;

			time = input.time;
			target = input.target;
			message = input.message;
		}
	}
}

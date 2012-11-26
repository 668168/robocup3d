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

import magma.agent.perception.IAgentStatePerceptor;
import magma.agent.perception.IPerceptor;

public class AgentStatePerceptor extends Perceptor implements
		IAgentStatePerceptor
{
	private int temperature;

	private int battery;

	/**
	 * Default constructor, initializes temperature and battery level to 0.00
	 */
	public AgentStatePerceptor()
	{
		this(0, 0);
	}

	/**
	 * Assignment constructor
	 * 
	 * @param temperature Temperature (in degrees)
	 * @param battery Battery level (in percent)
	 */
	public AgentStatePerceptor(int temperature, int battery)
	{
		super("AgentState");

		this.temperature = temperature;
		this.battery = battery;
	}

	@Override
	public int getTemperature()
	{
		return this.temperature;
	}

	@Override
	public int getBattery()
	{
		return battery;
	}

	@Override
	public void assign(IPerceptor source)
	{
		if (source instanceof AgentStatePerceptor) {
			AgentStatePerceptor input = (AgentStatePerceptor) source;

			temperature = input.temperature;
			battery = input.battery;
		}
	}
}

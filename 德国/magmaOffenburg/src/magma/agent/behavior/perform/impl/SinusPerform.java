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
package magma.agent.behavior.perform.impl;

import magma.agent.agentmodel.IAgentModel;
import magma.agent.worldmodel.IGlobalMap;

public class SinusPerform extends HingePerform
{
	private double start_time;

	private double amplitude;

	private double period;

	private double phase;

	private double offset;

	public SinusPerform(String name, double amplitude, double period,
			double phase, double offset)
	{
		super(name);
		this.amplitude = amplitude;
		this.period = period;
		this.phase = phase;
		this.offset = offset;
	}

	@Override
	public void init()
	{
		super.init();
		this.start_time = 0d;
	}

	@Override
	public float getNextSpeed(IAgentModel agentModel, IGlobalMap worldModel)
	{
		double time;

		// set start_time
		if (start_time == 0d) {
			start_time = worldModel.getGlobalTime();
		}

		// calculate perform-running time
		time = worldModel.getGlobalTime() - start_time;

		return new Float(amplitude
				* Math.sin(time / period * 2 * Math.PI + phase) + offset);
	}
}

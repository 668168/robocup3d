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
package magma.agent.behavior.function;

/**
 * Represents a sin function with amplitude, period, phase and offset
 * @author dorer
 */
public class SinFunction implements Function
{
	/** serial ID for serialization */
	private static final long serialVersionUID = 1L;

	/**
	 * parameters needed for the sin 0: period, 1: amplitude, 2: phase, 3: offset
	 */
	protected double params[];

	/**
	 * Creates the function from a sin line in a motor function file
	 * @param csvLineContents the values that were comma separated in the file
	 */
	public SinFunction(String[] csvLineContents, int period)
	{
		params = new double[4];
		params[0] = period;
		params[1] = Double.valueOf(csvLineContents[2]);
		params[2] = Double.valueOf(csvLineContents[3]);
		params[3] = Double.valueOf(csvLineContents[4]);
	}

	/**
	 * Returns the sin value at the passed x coordinate. Parameters are used as
	 * written in constructor.
	 * @param x the coordinate at which to return the functions value
	 * @return the sin value at the passed x coordinate
	 */
	@Override
	public double value(double t)
	{
		return params[1] * Math.sin(t / params[0] * 2 * Math.PI + params[2])
				+ params[3];
	}

	@Override
	public String toCSVString(String joint)
	{
		StringBuilder result = new StringBuilder();
		result.append(joint + ",sinus,");
		for (int i = 1; i < params.length; i++) {
			result.append(params[i]).append(",");
		}
		return result.toString();
	}
}
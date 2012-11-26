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
 * Represents a polynomial function with a degree depending on the number of
 * parameters passed in the constructor
 * @author dorer
 */
public class PolynomFunction implements Function
{
	/** serial ID for serialization */
	private static final long serialVersionUID = 1L;

	/**
	 * parameters needed for the sin 0: amplitude, 1: period, 2: phase, 3: offset
	 */
	protected double params[];

	/**
	 * Creates a polynomial function of params.length degree
	 * @param params the parameters of the polynom. The index corresponds to the
	 *        exponent of x (params[0] -> x^0
	 */
	public PolynomFunction(double[] params)
	{
		this.params = params;
	}

	/**
	 * Returns the polynomial value at the passed x coordinate. The degree of the
	 * polynom depends on how many parameters have been passed (see constructor).
	 * 
	 * @param t The coordinate at which to return the functions value
	 * @return The polynomial value at the passed x coordinate
	 */
	@Override
	public double value(double t)
	{
		t = t + 1;
		double x = t;
		double result = params[0];
		for (int i = 1; i < params.length; i++) {
			result += x * params[i];
			x *= t;
		}
		return result;
	}

	@Override
	public String toCSVString(String joint)
	{
		StringBuilder result = new StringBuilder();
		result.append(joint + ",poly," + params.length);
		for (double param : params) {
			result.append(param).append(",");
		}
		return result.toString();
	}
}
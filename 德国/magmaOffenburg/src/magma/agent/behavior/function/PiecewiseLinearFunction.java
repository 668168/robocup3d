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
 * Represents a piecewise linear function with any number of pieces
 * @author dorer
 */
public class PiecewiseLinearFunction implements Function
{
	/** serial ID for serialization */
	private static final long serialVersionUID = 1L;

	/**
	 * parameters needed for the start and end points
	 */
	protected double xValues[];

	protected double yValues[];

	/**
	 * Creates the function from a sin line in a motor function file
	 * @param csvLineContents the values that were comma separated in the file
	 */
	public PiecewiseLinearFunction(String[] csvLineContents)
	{
		int size = Integer.valueOf(csvLineContents[2]);
		xValues = new double[size];
		yValues = new double[size];

		int xpos = 3;
		for (int i = 0; i < size; i++) {
			xValues[i] = Double.valueOf(csvLineContents[xpos++]);
			yValues[i] = Double.valueOf(csvLineContents[xpos++]);
		}
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
		int x0Index = 0;
		int x1Index = 1;

		if (t < xValues[x0Index]) {
			throw new IllegalArgumentException(
					"Too small x value for linear function! x: " + t + " minX: "
							+ xValues[x0Index]);
		}

		// find suitable values
		while (t > xValues[x1Index]) {
			x0Index = x1Index;
			x1Index++;
			if (x1Index >= xValues.length) {
				throw new IllegalArgumentException(
						"Too big x value for linear function! x: " + t + " maxX: "
								+ xValues[x0Index]);
			}
		}

		// linear interpolation
		double result = yValues[x0Index] + (yValues[x1Index] - yValues[x0Index])
				/ (xValues[x1Index] - xValues[x0Index]) * (t - xValues[x0Index]);
		return result;
	}

	@Override
	public String toCSVString(String joint)
	{
		StringBuilder result = new StringBuilder();
		result.append(joint + ",linear," + xValues.length + ",");
		for (int i = 0; i < xValues.length; i++) {
			result.append(xValues[i]).append(",");
			result.append(yValues[i]).append(",");
		}
		return result.toString();
	}
}
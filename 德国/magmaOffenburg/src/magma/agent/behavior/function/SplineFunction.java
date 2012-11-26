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

import java.awt.geom.Point2D.Double;
import java.util.Arrays;
import java.util.List;

import org.apache.commons.math.ArgumentOutsideDomainException;
import org.apache.commons.math.analysis.PolynomialSplineFunction;
import org.apache.commons.math.analysis.SplineInterpolator;

/**
 * Represents a spline function. Adapter to the PolynomialSplineFunction class.
 * @author dorer
 */
public class SplineFunction implements Function
{
	/** serial ID for serialization */
	private static final long serialVersionUID = 1L;

	/** x values of the supporting points */
	protected double xValues[];

	/** y values of the supporting points */
	protected double yValues[];

	PolynomialSplineFunction spline;

	private final double phase;

	private double xMin;

	private double xMax;

	/**
	 * Creates a Spline Function. Adapter to the PolynomialSplineFunction class.
	 * The supporting points passed have to make sure that x0 is the minimum x
	 * value needed later and xn is the highest x value.
	 * @param xValues the x coordinates of the supporting points
	 * @param yValues the y coordinates of the supporting points
	 */
	public SplineFunction(double xValues[], double yValues[])
	{
		this(xValues, yValues, 0.0);
	}

	/**
	 * Creates the function from a spline line in a motor function file
	 * @param csvLineContents the values that were comma separated in the file
	 */
	public SplineFunction(String[] csvLineContents)
	{
		xValues = new double[Integer.valueOf(csvLineContents[2])];
		yValues = new double[Integer.valueOf(csvLineContents[2])];

		int xpos = 3;

		phase = java.lang.Double.valueOf(csvLineContents[xpos++]);
		for (int i = 0; i < Integer.valueOf(csvLineContents[2]); i++) {
			xValues[i] = java.lang.Double.valueOf(csvLineContents[xpos++]);
			yValues[i] = java.lang.Double.valueOf(csvLineContents[xpos++]);
		}
		initialize();
	}

	@Override
	public String toCSVString(String joint)
	{
		StringBuilder result = new StringBuilder();
		result.append(joint + ",spline," + xValues.length + "," + phase + ",");
		for (int i = 0; i < xValues.length; i++) {
			result.append(xValues[i]).append(",");
			result.append(yValues[i]).append(",");
		}
		return result.toString();
	}

	/**
	 * Creates a Spline Function. Adapter to the PolynomialSplineFunction class.
	 * The supporting points passed have to make sure that x0 is the minimum x
	 * value needed later and xn is the highest x value.
	 * @param xValues the x coordinates of the supporting points
	 * @param yValues the y coordinates of the supporting points
	 * @param phase phase subtracted from x. Has to be within xMin and xMax
	 */
	public SplineFunction(double xValues[], double yValues[], double phase)
	{
		this.xValues = xValues;
		this.yValues = yValues;
		this.phase = phase;
		initialize();
	}

	public SplineFunction(List<Double> values)
	{
		this.xValues = new double[values.size()];
		this.yValues = new double[values.size()];

		for (int i = 0; i < xValues.length; i++) {
			xValues[i] = values.get(i).x;
			yValues[i] = values.get(i).y;
		}

		this.phase = 0;
		initialize();
	}

	/**
	 * Creates a spline function from the previously set x and y values
	 */
	public void initialize()
	{
		try {
			SplineInterpolator interpolator = new SplineInterpolator();
			spline = (PolynomialSplineFunction) interpolator.interpolate(xValues,
					yValues);
			xMin = xValues[0];
			xMax = xValues[xValues.length - 1];
		} catch (IllegalArgumentException e) {
			System.out.println(e + "\n" + Arrays.toString(xValues));
			throw e;
		}
	}

	/**
	 * Returns the spline value at t - phase mapped to [xMin, xMax].
	 * @param t the coordinate at which to return the functions value
	 * @return the spline value at the calculated x coordinate
	 */
	@Override
	public double value(double t)
	{
		try {
			double x = t - phase;
			if (x < xMin) {
				x += xMax;
			} else if (x > xMax) {
				x -= xMax;
			}
			return spline.value(x);

		} catch (ArgumentOutsideDomainException e) {
			assert false : "Invalid spline value: " + t;
			e.printStackTrace();
			return 0.0;
		}
	}

	public double[] getXValues()
	{
		return xValues;
	}

	public double[] getYValues()
	{
		return yValues;
	}
}
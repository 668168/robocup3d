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

import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;

import magma.agent.behavior.basic.BehaviorParameter;

/**
 * @author dorer
 * 
 */
public class FunctionBehaviorParameter extends BehaviorParameter implements
		Serializable
{
	/** serial ID for serialization */
	private static final long serialVersionUID = 1L;

	/** map containing an entry for all joints involved in the behavior */
	protected Map<String, Function> joints;

	/** the version of the file format we use */
	private int version;

	/** the name of the corresponding behavior */
	private String name;

	/** the number of cycles the behavior takes */
	private int period;

	/**
	 * Creates joint functions from behavior function files
	 * @param filename the file to read from
	 * @throws IOException
	 */
	public FunctionBehaviorParameter(String filename) throws IOException
	{
		joints = new HashMap<String, Function>();
		String line = null;
		String[] csvLineContents = null;

		ClassLoader cl = this.getClass().getClassLoader();
		InputStream is = cl.getResourceAsStream(filename);
		BufferedReader in2 = new BufferedReader(new InputStreamReader(is));
		line = in2.readLine();
		// read the date from the first line
		csvLineContents = line.split(",");
		version = Integer.valueOf(csvLineContents[0]);
		name = csvLineContents[1];
		period = Integer.valueOf(csvLineContents[2]);

		// read all data for each joint
		while ((line = in2.readLine()) != null) {
			csvLineContents = line.split(",");
			Function jointFunction = null;
			if (csvLineContents[1].toString().equals("spline")) {
				// new joint need to be a spline
				jointFunction = new SplineFunction(csvLineContents);

			} else if (csvLineContents[1].toString().equals("sinus")) {
				// new joint need to be a sinus
				jointFunction = new SinFunction(csvLineContents, period);

			} else if (csvLineContents[1].toString().equals("linear")) {
				// new joint need to be a piecewise linear
				jointFunction = new PiecewiseLinearFunction(csvLineContents);
			}
			joints.put(csvLineContents[0], jointFunction);
		}
	}

	/**
	 * Writes a function motor file
	 * @param filename the name to use as filename
	 */
	public void writeToFile(String filename)
	{
		PrintWriter out = null;
		try {
			out = new PrintWriter(new FileWriter(filename));
			out.println(version + "," + name + "," + period);

			// write all data for each joint
			for (String key : joints.keySet()) {
				Function jointFunction = joints.get(key);
				String line = jointFunction.toCSVString(key);
				out.println(line);
			}

		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (out != null) {
				out.close();
			}
		}

	}

	/**
	 * @return a map of functions for each joint that is involved in the behavior
	 */
	public Map<String, Function> getJoints()
	{
		return joints;
	}

	/**
	 * @return the period
	 */
	public int getPeriod()
	{
		return period;
	}

}

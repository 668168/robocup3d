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
package magma.agent.behavior.motor;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Reads a CSV file of the format: (BOF) Time,Pose,Effector1,Effector2
 * TimeValue,PoseId1,Effector1_Value,Effector2_Value
 * TimeValue,PoseId2,Effector1_Value,Effector2_Value ... (EOF)
 * 
 * @author Srinivasa Ragavan
 */
public class ReadCSV
{
	/**
	 * The formattedCSV holds the whole CSV file in the format: ArrayList of each
	 * line in CSV. Each line is held as a HashMap of Effectors as 'key' and
	 * Target_Angle(in Radians) as 'value'. formattedCSV.size() will give the
	 * number of steps for the motion.
	 */
	private ArrayList<HashMap<String, Float>> formattedCSV = null;

	private ArrayList<String[]> csvContents = new ArrayList<String[]>();

	/** Number of records in each line of CSV */
	private int noOfRecords = 0;

	private String filePath = null;

	/**
	 * @param pathOfFile
	 */
	public ReadCSV(String pathOfFile)
	{
		super();
		this.filePath = pathOfFile;
	}

	/**
	 * @return ArrayList<HashMap<String, String>> formattedCSV
	 * @throws IOException
	 */
	public ArrayList<HashMap<String, Float>> getFormattedCSV()
			throws IOException
	{
		readCsvFile();
		formatCsv();
		return formattedCSV;
	}

	/**
	 * Reads the CSV file and populates the contents in an ArrayList of Strings.
	 * @throws IOException
	 */
	private void readCsvFile() throws IOException
	{
		ClassLoader cl = this.getClass().getClassLoader();
		InputStream is = cl.getResourceAsStream(filePath);
		if (is == null) {
			Logger.getLogger("").log(Level.SEVERE, "File can not be found: {0}",
					filePath);
			return;
		}
		BufferedReader br = new BufferedReader(new InputStreamReader(is));
		String line = null;
		while ((line = br.readLine()) != null) {
			String[] csvLineContents = line.split(",");
			noOfRecords = csvLineContents.length;
			csvContents.add(csvLineContents);
		}
		br.close();
	}

	/**
	 * Formats the CSV and populates formattedCSV
	 * @see formattedCSV
	 */
	private void formatCsv()
	{
		String effectorName = null;
		String effectorValue = null;
		HashMap<String, Float> poseNameAndValue = null;
		formattedCSV = new ArrayList<HashMap<String, Float>>();
		for (int i = 1; i < csvContents.size(); i++) {
			poseNameAndValue = new HashMap<String, Float>();
			for (int arrayLen = 2; arrayLen < noOfRecords; arrayLen++) {
				effectorName = csvContents.get(0)[arrayLen];
				effectorName = effectorName.replace("Ankle", "Foot");
				effectorName = effectorName.replace("Head", "Neck");
				effectorName = effectorName.replace("Elbow", "Arm");
				effectorName = effectorName.replace("ShoulderRoll", "ShoulderYaw");

				effectorValue = csvContents.get(i)[arrayLen];
				double valueD = Double.parseDouble(effectorValue);
				valueD = -Math.toDegrees(valueD);
				// Negate some joints
				if (effectorName.contains("Roll")
						|| effectorName.contains("ShoulderYaw")
						|| effectorName.contains("YawPitch")) {
					valueD = -valueD;
				}
				Float value = new Float(valueD);
				poseNameAndValue.put(effectorName, value);
			}
			formattedCSV.add(poseNameAndValue);
		}
	}
}

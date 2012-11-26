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

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;

import magma.agent.agentmodel.IAgentModel;
import magma.agent.agentmodel.IHingeJoint;
import magma.agent.behavior.ICoordinator;
import magma.agent.behavior.basic.BehaviorParameter;
import magma.agent.worldmodel.IGlobalMap;
import magma.util.logging.CSVFormatter;

/**
 * @author dorer
 * 
 */
public class MotorFileBehavior extends MotorBehavior
{
	/** values of each joint angles (in degrees) for each step */
	private ArrayList<HashMap<String, Float>> steps;

	private int slowDownFactor;

	private int startSlowDownFactor;

	private int currentStep;

	private boolean startModus = true;

	public MotorFileBehavior(String name, ICoordinator coordinator,
			IGlobalMap model, IAgentModel agentModel, BehaviorParameter params,
			String filepath, int slowDown, int startSlowDown) throws IOException
	{
		super(name, model, agentModel, coordinator);

		ReadCSV valuesFromFile = new ReadCSV(filepath);
		this.steps = valuesFromFile.getFormattedCSV();

		this.currentStep = 0;
		this.slowDownFactor = slowDown;
		this.startSlowDownFactor = startSlowDown;
		this.finished = false;
		if (LOG) {
			initLogger(Level.INFO);
		}
	}

	@Override
	public void init()
	{
		super.init();
		currentStep = 0;
		startModus = true;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.behavior.IBehavior#perform(float)
	 */
	@Override
	public void perform(float intensity)
	{
		if (startModus) {
			performSlowDown(startSlowDownFactor);

			currentStep++;
			if (currentStep >= startSlowDownFactor) {
				startModus = false;
				currentStep = slowDownFactor;
			}
		} else {
			performSlowDown(slowDownFactor);

			currentStep++;
			if (currentStep >= (steps.size() * slowDownFactor)) {
				finished = true;
				currentStep = 0;
			}
		}
	}

	private void performSlowDown(int slowDown)
	{
		float speedFactor = slowDown - (currentStep % slowDown);
		IHingeJoint hingeJoint;
		float currentAngle;
		float desiredAngle;
		float delta;
		float speed;

		StringBuilder buffer = new StringBuilder();
		int realStep = currentStep / slowDown;
		Map<String, Float> desiredAngles = steps.get(realStep);

		// loop through all joints affected
		for (String name : desiredAngles.keySet()) {

			// calculate speed
			desiredAngle = desiredAngles.get(name).floatValue();
			hingeJoint = agentModel.getHJ(name);

			if (hingeJoint == null) {
				logger.log(Level.SEVERE, "unknown hinge joint: {0}", name);
			}

			currentAngle = hingeJoint.getAxis();
			delta = (desiredAngle - currentAngle);
			speed = delta / 2.0f;
			speed /= speedFactor;

			if (speed > -0.2 && speed < 0.2) {
				speed = 0.0f;
			}

			buffer.append(desiredAngle).append(";");
			buffer.append(currentAngle).append(";");
			buffer.append(speed).append(";");

			// set axis speed
			coordinator.performAxisSpeed(name, speed);
		}
		if (LOG) {
			Logger.getLogger(getName()).log(Level.INFO, buffer.toString());
		}
	}

	/**
	 * Initializes logging functionality
	 * @throws IOException if logfile can not be opened
	 */
	private void initLogger(Level level)
	{
		try {
			Logger loggerCSV = Logger.getLogger(getName());
			FileHandler handler = new FileHandler("log/" + getName() + ".csv");
			handler.setFormatter(new CSVFormatter());
			loggerCSV.addHandler(handler);
			loggerCSV.setLevel(level);

			// write heading
			StringBuilder buffer = new StringBuilder();
			Map<String, Float> namesMap = steps.get(0);
			for (String name : namesMap.keySet()) {
				buffer.append(name).append(";");
				buffer.append("angleAsIs").append(";");
				buffer.append("speed").append(";");
			}
			loggerCSV.log(Level.INFO, buffer.toString());

		} catch (SecurityException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

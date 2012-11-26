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
import java.util.Collection;
import java.util.Map;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;

import magma.agent.agentmodel.IAgentModel;
import magma.agent.agentmodel.IHingeJoint;
import magma.agent.behavior.ICoordinator;
import magma.agent.behavior.basic.Step;
import magma.agent.worldmodel.IGlobalMap;
import magma.util.logging.CSVFormatter;

/**
 * Behavior representing sinoid repeated motor commands
 * @author dorer
 */
public abstract class BasicMotorBehavior extends MotorBehavior
{
	private Logger motorLogger;

	private float slowDownFactor;

	private float startSlowDownFactor;

	protected float currentStep;

	protected boolean startModus = true;

	/**
	 * Default constructor for motor behaviors
	 * @param name identifier for this behavior
	 * @param worldModel reference to the world model information
	 * @param agentModel reference to the agent's own information
	 * @param coordinator handle for action sending to server
	 */
	public BasicMotorBehavior(String name, IGlobalMap worldModel,
			IAgentModel agentModel, ICoordinator coordinator, float slowDown,
			float startSlowDown)
	{
		super(name, worldModel, agentModel, coordinator);
		this.currentStep = 0.0f;
		this.slowDownFactor = slowDown;
		this.startSlowDownFactor = startSlowDown;
		motorLogger = null;
	}

	@Override
	public void init()
	{
		super.init();
		currentStep = 0.0f;
		if (startSlowDownFactor > 0.0) {
			startModus = true;
		} else {
			startModus = false;
		}
	}

	@Override
	public Map<Integer, Step> getSteps()
	{
		return null;
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

			float increment = 1.0f / startSlowDownFactor;
			currentStep += increment;
			if (currentStep >= 1.0) {
				startModus = false;
				currentStep = 0.0f;
			}
		} else {
			performSlowDown(slowDownFactor);

			float increment = 1.0f / slowDownFactor;
			currentStep += increment;
			if (willFinish()) {
				finished = true;
				currentStep = 0.0f;
			}
		}
	}

	private void performSlowDown(float slowDown)
	{
		IHingeJoint hingeJoint;
		float currentAngle;
		float desiredAngle;
		float delta;
		float speed;

		StringBuilder buffer = new StringBuilder();

		Collection<String> jointNames = getInvolvedJointNames();
		// loop through all joints affected
		for (String name : jointNames) {

			// calculate speed
			desiredAngle = getDesiredAngle(name, currentStep);
			hingeJoint = agentModel.getHJ(name);
			if (hingeJoint == null) {
				logger.log(Level.SEVERE, "unknown hinge joint: {0}", name);
			}

			currentAngle = hingeJoint.getAxis();
			delta = (desiredAngle - currentAngle);
			speed = delta / 2.0f;

			if (startModus) {
				float speedFactor = slowDown * (1.0f - currentStep);
				speed /= speedFactor;
				speed *= 2.0f;
				logger
						.log(
								Level.FINEST,
								"motor: speed: {0} speedFactor: {1} currentAngle: {2} desiredAngle: {3} ",
								new Object[] { speed, speedFactor, currentAngle,
										desiredAngle });
			}

			if (speed > -0.02 && speed < 0.02) {
				speed = 0.0f;
			}

			if (LOG) {
				buffer.append(desiredAngle).append(";");
				buffer.append(currentAngle).append(";");
				buffer.append(speed).append(";");
			}
			// set axis speed
			coordinator.performAxisSpeed(name, speed);
		}
		if (LOG) {
			if (motorLogger == null) {
				initLogger(Level.INFO);
			}
			motorLogger.log(Level.INFO, buffer.toString());
		}
	}

	/**
	 * Initializes logging functionality
	 * @throws IOException if logfile can not be opened
	 */
	private void initLogger(Level level)
	{
		try {
			motorLogger = Logger.getLogger(getName());
			FileHandler handler = new FileHandler("log/" + getName() + ".csv");
			handler.setFormatter(new CSVFormatter());
			motorLogger.addHandler(handler);
			motorLogger.setLevel(level);

			// write heading
			StringBuilder buffer = new StringBuilder();
			for (String name : getInvolvedJointNames()) {
				buffer.append(name).append(";");
				buffer.append("angleAsIs").append(";");
				buffer.append("speed").append(";");
			}
			motorLogger.log(Level.INFO, buffer.toString());

		} catch (SecurityException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * @return true if this behavior will finish after this step
	 */
	abstract protected boolean willFinish();

	/**
	 * @return a collection of names of those joints that are moved in this
	 *         behavior
	 */
	abstract protected Collection<String> getInvolvedJointNames();

	/**
	 * Returns the joint angle (in degrees) where we want to have the joint with
	 * passed name at the passed time step
	 * @param name the name of the joint as specified in
	 *        IServerConfigFilesConstants.HINGEJOINT_NAMES
	 * @param step the time step at which to calculate the angle
	 * @return the joint angle (in degrees) where we want to have the joint with
	 */
	abstract protected float getDesiredAngle(String name, float step);
}

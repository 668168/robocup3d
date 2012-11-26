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

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import magma.agent.agentmodel.IAgentModel;
import magma.agent.behavior.ICoordinator;
import magma.agent.behavior.basic.Step;
import magma.agent.behavior.perform.IHingePerform;
import magma.agent.worldmodel.IGlobalMap;

public class XMLMotorBehavior extends MotorBehavior
{

	protected Step currentStep;

	protected Map<Integer, Step> steps;

	protected final Map<String, IHingePerform> activeHingePerforms;

	// protected final Map<String, IUniversalPerform> activeUniversalPerforms;

	/**
	 * Default constructor for XML motor behaviors
	 * 
	 * @param name identifier for this behavior
	 * @param worldModel reference to the world model information
	 * @param agentModel reference to the agent's own information
	 * @param coordinator handle for action sending to server
	 */
	public XMLMotorBehavior(String name, IGlobalMap worldModel,
			IAgentModel agentModel, ICoordinator coordinator,
			Map<Integer, Step> steps)
	{
		super(name, worldModel, agentModel, coordinator);
		// activeUniversalPerforms = new HashMap<String, IUniversalPerform>();
		activeHingePerforms = new HashMap<String, IHingePerform>();
		this.steps = steps;
	}

	@Override
	public void init()
	{
		// initialisize State Machine
		super.init();
		currentStep = steps.get(0);
		activeHingePerforms.clear();
		// activeUniversalPerforms.clear();
	}

	/**
	 * @return the steps
	 */
	@Override
	public Map<Integer, Step> getSteps()
	{
		return steps;
	}

	@Override
	public void perform(float intensity)
	{
		Set<String> performsToRemove = new HashSet<String>();
		float speed;
		IHingePerform hp;

		// check step state & change step
		if (checkStepState(currentStep)) {
			// Step reached --> begin new Step
			currentStep.setReached(false);

			// get next step or finish the behavior
			if (currentStep.getNextStepId() != 0) {
				currentStep = steps.get(currentStep.getNextStepId());
			} else {
				finished = true;
				return;
			}

			// initialize the step and activate the Performs
			currentStep.setReached(false);
			// activeUniversalPerforms.putAll(initUniversalPerforms(currentStep.getUniversalPerforms()));
			activeHingePerforms.putAll(initHingePerforms(currentStep
					.getHingePerforms()));
		}

		// perform active HingePerforms
		for (String name : activeHingePerforms.keySet()) {

			hp = activeHingePerforms.get(name);
			speed = hp.getNextSpeed(agentModel, worldModel);

			if (!hp.isReached()) {
				coordinator.performAxisSpeed(name, speed);
			} else {
				performsToRemove.add(name);
			}
		}

		// remove finished performs
		for (String name : performsToRemove) {
			activeHingePerforms.remove(name);
		}
	}

	/**
	 * checkStepState(Step step) - checks, if the given Step is reached
	 * 
	 * @param step - Step to check
	 * 
	 * @return <b>true</b> if Step is reached, else <b>false</b>
	 */
	public boolean checkStepState(Step step)
	{
		boolean stepReached = true;
		Map<String, float[]> triggers = step.getTriggers();

		for (String name : triggers.keySet()) {

			float[] x = triggers.get(name);

			// System.out.println("Check Trigger: " + name + " LastAxis:\t"
			// + agentModel.getHJ(name).getLastAxis() + "\tAxis\t"
			// + agentModel.getHJ(name).getAxis() + "\tTarget:\t" + x[0]);

			if (stepReached && activeHingePerforms.get(name) != null
					&& !activeHingePerforms.get(name).isReached()) {

				stepReached = agentModel.getHJ(name).checkTrigger(x[0], 5f);
			}
		}

		step.setReached(stepReached);

		return stepReached;
	}

	private Map<String, IHingePerform> initHingePerforms(
			Map<String, IHingePerform> hingePerforms)
	{
		if (hingePerforms != null) {
			for (IHingePerform hingePerform : hingePerforms.values()) {
				hingePerform.init();
			}
		}
		return hingePerforms;
	}

	// private Map<String, IUniversalPerform> initUniversalPerforms(
	// Map<String, IUniversalPerform> universalPerforms)
	// {
	// if (universalPerforms != null) {
	// for (IUniversalPerform universalPerform : universalPerforms.values()) {
	// universalPerform.setReached(false);
	// }
	// }
	// return universalPerforms;
	// }
}

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
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

import magma.agent.agentmodel.IAgentModel;
import magma.agent.behavior.ICoordinator;
import magma.agent.behavior.basic.BehaviorParameter;
import magma.agent.worldmodel.IGlobalMap;

/**
 * @author dorer
 * 
 */
public class FloatMotorFileBehavior extends BasicMotorBehavior
{

	/** values of each joint angles (in degrees) for each step */
	private ArrayList<HashMap<String, Float>> steps;

	public FloatMotorFileBehavior(String name, ICoordinator coordinator,
			IGlobalMap model, IAgentModel agentModel, BehaviorParameter params,
			String filepath, float slowDown, float startSlowDown)
			throws IOException
	{
		super(name, model, agentModel, coordinator, slowDown, startSlowDown);

		ReadCSV valuesFromFile = new ReadCSV(filepath);
		this.steps = valuesFromFile.getFormattedCSV();
	}

	@Override
	protected boolean willFinish()
	{
		return currentStep >= steps.size();
	}

	@Override
	protected Collection<String> getInvolvedJointNames()
	{
		return steps.get(0).keySet();
	}

	@Override
	protected float getDesiredAngle(String name, float step)
	{
		int realStep = (int) step;
		Map<String, Float> desiredAngles1 = steps.get(realStep);
		Map<String, Float> desiredAngles2 = null;
		float desiredAngle1 = desiredAngles1.get(name).floatValue();

		int x0 = realStep;
		int x1 = x0 + 1;
		if (realStep < steps.size() - 1 && !startModus) {
			// we have two values, so we do linear interpolation
			desiredAngles2 = steps.get(realStep + 1);
			float desiredAngle2 = desiredAngles2.get(name).floatValue();
			desiredAngle1 = desiredAngle1 + (desiredAngle2 - desiredAngle1)
					/ (x1 - x0) * (currentStep - x0);
		}

		return desiredAngle1;
	}
}

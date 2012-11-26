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
package magma.agent.behavior.basic;

import magma.agent.agentmodel.IAgentModel;
import magma.agent.behavior.ICoordinator;
import magma.agent.worldmodel.IGlobalMap;
import magma.util.FuzzyCompare;

/**
 * @author stilnox
 * 
 */
public class StepLeft extends Behavior
{

	private static boolean finished = false;

	private static int step;

	private static float startValues[] = { 0, 0, 0 };

	public StepLeft(String name, IGlobalMap worldModel, IAgentModel agentModel,
			ICoordinator coordinator)
	{
		super(name, worldModel, agentModel, coordinator);
	}

	@Override
	public void perform(float intensity)
	{
		if (intensity < 0)
			intensity *= -1;

		float speed = intensity;

		step++;
		if (!finished)
			if (step < intensity / 2) {
				coordinator.performAxisSpeed("LHipPitch", speed);
				coordinator.performAxisSpeed("LKneePitch", -speed * 2);
				coordinator.performAxisSpeed("LFootPitch", speed);
			} else if (step < intensity) {
				if (FuzzyCompare.gt(agentModel.getHJ("LHipPitch").getAxis(),
						startValues[0], 1))
					coordinator.performAxisSpeed("LHipPitch", -speed);
				if (FuzzyCompare.lt(agentModel.getHJ("LKneePitch").getAxis(),
						startValues[1], 1))
					coordinator.performAxisSpeed("LKneePitch", speed * 2);
				if (FuzzyCompare.gt(agentModel.getHJ("LFootPitch").getAxis(),
						startValues[2], 1))
					coordinator.performAxisSpeed("LFootPitch", -speed);
			} else {
				finished = true;
			}
	}

	@Override
	public void init()
	{
		startValues[0] = agentModel.getHJ("LHipPitch").getAxis();
		startValues[1] = agentModel.getHJ("LKneePitch").getAxis();
		startValues[2] = agentModel.getHJ("LFootPitch").getAxis();

		finished = false;
		step = 0;
	}

	@Override
	public boolean isFinished()
	{
		return finished;
	}
}

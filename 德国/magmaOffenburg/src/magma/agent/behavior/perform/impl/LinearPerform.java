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
package magma.agent.behavior.perform.impl;

import magma.agent.agentmodel.IAgentModel;
import magma.agent.worldmodel.IGlobalMap;

/**
 * @author Ingo Schindler, Stefan Glaser
 * 
 */
public class LinearPerform extends HingePerform
{
	private final float target;

	private final float nextSpeed;

	public LinearPerform(String name, float target, float speed)
	{
		super(name);
		this.target = target;
		this.nextSpeed = speed;
		this.reached = false;
	}

	/**
	 * @return the target
	 */
	public float getTarget()
	{
		return target;
	}

	public float getSpeed()
	{
		return nextSpeed;
	}

	/**
	 * @return the speed
	 */
	@Override
	public float getNextSpeed(IAgentModel agentModel, IGlobalMap worldModel)
	{
		float direction = agentModel.getHJ(name).checkTarget(target, nextSpeed);

		if (direction == 0f) {
			reached = true;
		}

		return direction * nextSpeed;
	}
}

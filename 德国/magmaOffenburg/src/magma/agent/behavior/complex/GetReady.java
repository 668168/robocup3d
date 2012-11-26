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
package magma.agent.behavior.complex;

import java.util.Map;

import magma.agent.agentmodel.IAgentModel;
import magma.agent.behavior.IBehavior;
import magma.agent.behavior.basic.BehaviorParameter;
import magma.agent.worldmodel.IGlobalMap;

/**
 * @author Ingo Schindler
 * 
 */
public class GetReady extends ComplexBehavior

{
	public GetReady(IGlobalMap model, IAgentModel agentModel,
			BehaviorParameter params, Map<String, IBehavior> behaviors)
	{
		super(IBehavior.GET_READY, model, agentModel, params, behaviors);
		currentBehavior = behaviors.get(IBehavior.GET_READY_PRIMITIVE);
	}

	@Override
	public void perform(float intensity)
	{
		if (!currentBehavior.isFinished()) {
			currentBehavior.perform(intensity);
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.behavior.complex.ComplexBehavior#init()
	 */
	@Override
	public void init()
	{
		currentBehavior.init();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.behavior.impl.Behavior#isFinished()
	 */
	@Override
	public boolean isFinished()
	{
		if (currentBehavior.isFinished()) {
			checkGyro();

			return true;
		}
		return false;
	}

}

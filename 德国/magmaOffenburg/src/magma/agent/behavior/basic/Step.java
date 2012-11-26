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

import java.util.Map;

import magma.agent.behavior.perform.IHingePerform;
import magma.agent.behavior.perform.IUniversalPerform;

public class Step
{
	private boolean reached;

	private int nextStepId;

	private final Map<String, IHingePerform> hingePerforms;

	private final Map<String, IUniversalPerform> universalPerforms;

	private final Map<String, float[]> triggers;

	public Step(int nextStepId, Map<String, IHingePerform> hingePerforms,
			Map<String, IUniversalPerform> universalPerforms,
			Map<String, float[]> triggers)
	{
		this.reached = false;
		this.nextStepId = nextStepId;
		this.hingePerforms = hingePerforms;
		this.universalPerforms = universalPerforms;
		this.triggers = triggers;
	}

	public boolean isReached()
	{
		return reached;
	}

	public void setReached(boolean reached)
	{
		this.reached = reached;
	}

	public int getNextStepId()
	{
		return nextStepId;
	}

	public Map<String, IHingePerform> getHingePerforms()
	{
		return hingePerforms;
	}

	public Map<String, IUniversalPerform> getUniversalPerforms()
	{
		return universalPerforms;
	}

	public Map<String, float[]> getTriggers()
	{
		return triggers;
	}
}

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
package magma.agent.agentmodel.impl;

/**
 * @author Stefan Glaser
 * 
 */
public class AgentModelNAO extends AgentModel
{

	/** id for serialization */
	private static final long serialVersionUID = -6774414358351339194L;

	public AgentModelNAO()
	{
	}

	@Override
	public float checkHJTarget(String name, float targetposition, float range)
	{
		return getHJ(name).checkTarget(targetposition, range);
	}

	@Override
	public boolean checkHJTrigger(String name, float targetposition, float range)
	{
		return getHJ(name).checkTrigger(targetposition, range);
	}
}

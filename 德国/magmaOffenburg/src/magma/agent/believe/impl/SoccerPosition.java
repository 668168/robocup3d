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
package magma.agent.believe.impl;

import magma.agent.IServerConfigFilesConstants;
import magma.agent.agentmodel.IAgentModel;
import magma.agent.believe.IBelieve;
import magma.agent.worldmodel.IGlobalMap;
import magma.util.FuzzyCompare;

/**
 * Checks if the robot is ready to walk or kick
 * @author Klaus Dorer
 */
public class SoccerPosition extends Believe
{
	/** cached truth value that changes only in certain positions */
	private float truthValue;

	/**
	 * Default constructor
	 * 
	 * @param agent Agent model
	 * @param worldModel World model
	 */
	public SoccerPosition(IAgentModel agent, IGlobalMap worldModel)
	{
		super(IBelieve.SOCCER_POSITION, agent, worldModel);
		truthValue = 0.0f;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.believe.impl.Believe#getTruthValue()
	 */
	@Override
	public float getTruthValue()
	{
		double angleRight = agent.getHJ(
				IServerConfigFilesConstants.HINGEJOINT_NAMES[16]).getAxis();
		double angleLeft = agent.getHJ(
				IServerConfigFilesConstants.HINGEJOINT_NAMES[17]).getAxis();

		if (FuzzyCompare.eq((float) angleRight, (float) Math.toDegrees(-1.05),
				1.5f)
				&& FuzzyCompare.eq((float) angleLeft,
						(float) Math.toDegrees(-1.05), 1.5f)) {
			// switch to ready for soccer playing
			truthValue = 1.0f;

		} else if (FuzzyCompare.eq((float) angleRight, (float) Math.toDegrees(0),
				0.5f)
				&& FuzzyCompare.eq((float) angleLeft, (float) Math.toDegrees(0),
						0.5f)) {
			// switch to standing upright
			truthValue = 0.0f;
		}

		return truthValue;
	}
}

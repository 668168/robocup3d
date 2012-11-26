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
package magma.agent.decision.simple;

import java.util.Map;

import magma.agent.behavior.IBehavior;
import magma.agent.believe.IBelieve;

/**
 * Simple decision maker for primitive field player
 * @author dorer
 */
public class SoccerDecisionMaker extends DecisionMakerBase
{
	/** The version of the soccer server used */
	protected int serverVersion;

	/**
	 * Default constructor
	 * @param believes map of believes we can decide on
	 * @param behaviors map of behaviors we can decide for
	 * @param serverVersion the version of the soccer server used
	 */
	public SoccerDecisionMaker(Map<String, IBelieve> believes,
			Map<String, IBehavior> behaviors, int serverVersion)
	{
		super(believes, behaviors);
		this.serverVersion = serverVersion;
	}

	@Override
	protected IBehavior decideSoccer()
	{
		IBehavior toExecute = null;
		IBehavior result = super.decideSoccer();
		if (result != null) {
			return result;
		}

		// beam
		result = beamHome();
		if (result != null) {
			return result;
		}

		// wait till game starts
		result = waitForGameStart();
		if (result != null) {
			return result;
		}

		result = getUp();
		if (result != null) {
			return result;
		}

		// get ready
		result = getReady();
		if (result != null) {
			return result;
		}

		// kick
		result = doKickBehavior();
		if (result != null) {
			return result;
		}

		// walk
		toExecute = movement();
		if (toExecute != null) {
			return toExecute;
		}

		// stop any running motors and do nothing
		return behaviors.get(IBehavior.NONE);
	}

	/**
	 * Called to decide if we should beam us to our home position
	 * @return the behavior to execute, null if this part of decision does not
	 *         trigger a behavior currently
	 */
	protected IBehavior beamHome()
	{
		IBelieve beamTime = believes.get(IBelieve.BEAM_TIME);
		if (beamTime.getTruthValue() > 0.5) {
			return behaviors.get(IBehavior.BEAM_HOME);
		}
		return null;
	}

	/**
	 * Called to decide if we should wait for game start or not. Default
	 * implementation waits.
	 * @return the behavior to execute, null if this part of decision does not
	 *         trigger a behavior currently
	 */
	protected IBehavior waitForGameStart()
	{
		IBelieve gameRunning = believes.get(IBelieve.GAME_RUNNING);
		if (gameRunning.getTruthValue() < 0.5) {
			return behaviors.get(IBehavior.NONE);
		}
		return null;
	}

	/**
	 * Called to decide if we should stand up from laying on ground
	 * @return the behavior to execute, null if this part of decision does not
	 *         trigger a behavior currently
	 */
	protected IBehavior getUp()
	{
		// get up back
		IBelieve onBack = believes.get(IBelieve.LAY_ON_BACK);
		if (onBack.getTruthValue() > 0.5) {
			return behaviors.get(IBehavior.GET_UP_BACK);
		}

		// get up front
		IBelieve onFront = believes.get(IBelieve.LAY_ON_FRONT);
		if (onFront.getTruthValue() > 0.5) {
			return behaviors.get(IBehavior.GET_UP_FRONT);
		}

		// get up side
		IBelieve onSide = believes.get(IBelieve.LAY_ON_SIDE);
		if (onSide.getTruthValue() > 0.5) {
			return behaviors.get(IBehavior.MOVE_ARM_TO_FALL_BACK);
		}
		return null;
	}

	/**
	 * Called to decide if we should get into ready position
	 * @return the behavior to execute, null if this part of decision does not
	 *         trigger a behavior currently
	 */
	protected IBehavior getReady()
	{
		IBelieve soccerPosition = believes.get(IBelieve.SOCCER_POSITION);
		if (soccerPosition.getTruthValue() < 0.5) {
			return behaviors.get(IBehavior.GET_READY);
		}
		return null;
	}

	/**
	 * Called to decide if we should kick the ball
	 * @return the behavior to execute, null if this part of decision does not
	 *         trigger a behavior currently
	 */
	protected IBehavior doKickBehavior()
	{
		IBelieve ballKickable = believes.get(IBelieve.BALL_KICKABLE);
		if (ballKickable.getTruthValue() > 0.5) {
			return behaviors.get(IBehavior.SHOOT_TO_GOAL);
		}
		return null;
	}

	/**
	 * Called to decide if movement is necessary
	 * @return walk behavior if no team mate is closer to ball
	 */
	protected IBehavior movement()
	{
		IBelieve teammateCloser = believes.get(IBelieve.TEAMMATE_CLOSER_TO_BALL);
		if (teammateCloser.getTruthValue() < 0.5) {
			return behaviors.get(IBehavior.GET_IN_SCORE_POSITION);
		}

		IBelieve offensiveMode = believes.get(IBelieve.PLAY_OFFENSE);
		if (offensiveMode.getTruthValue() > 0.5) {
			return behaviors.get(IBehavior.MOVE_WITH_BALL);
		}

		return null;
	}

}

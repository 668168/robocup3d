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
package magma.agent.behavior;

/**
 * Interface to access all behaviors of the agent
 */
public interface IBehavior
{
	static final String INIT_BEHAVIOR = "init";

	static final String COLLAPSE_BACK_BEHAVIOR = "collapseBack";

	static final String COLLAPSE_FRONT_BEHAVIOR = "collapseFront";

	static final String DANCE1_BEHAVIOR = "dance1";

	static final String GET_UP_BEHAVIOR = "getUp";

	static final String TURN_AROUND_BEHAVIOR = "turnAround";

	static final String STANDARD_POSITION = "standardPosition";

	static final String SIMPLE_KICK_RIGHT = "simpleKickRight";

	static final String KICK_RIGHT = "kickRight";

	static final String SIDE_KICK_RIGHT = "sideKickRight";

	static final String SIDE_KICK_LEFT = "sideKickLeft";

	static final String NONE = "none";

	static final String STOP = "stop";

	static final String TURN_LEFT_60 = "turnLeft60";

	static final String TURN_LEFT_40 = "turnLeft40";

	static final String TURN_LEFT_20 = "turnLeft20";

	static final String TURN_RIGHT_60 = "turnRight60";

	static final String TURN_RIGHT_40 = "turnRight40";

	static final String TURN_RIGHT_20 = "turnRight20";

	static final String WALK = "walk";

	static final String FORWARD = "forwards";

	static final String START_WALK = "startWalk";

	static final String CONTINUE_WALK = "continueWalk";

	static final String CONTINUE_RUN = "continueRun";

	static final String CONTINUE_WALK_RIGHT = "continueWalkRight";

	static final String CONTINUE_WALK_LEFT = "continueWalkLeft";

	static final String STOP_WALK = "stopWalk";

	static final String SHOOT_LEFT = "shoot";

	static final String SHOOT_TO_GOAL = "shootToGoal";

	static final String GET_UP_BACK = "getUpBack";

	static final String GET_UP_FRONT = "getUpFront";

	static final String GET_READY = "getReady";

	static final String GET_READY_PRIMITIVE = "getReadyPrimitive";

	static final String RUN_TO_BALL = "runToBall";

	static final String RUN_TO_POSITION = "runToPosition";

	static final String MOVE_WITH_BALL = "moveWithBall";

	static final String STEP_FORWARD = "stepFront";

	static final String STEP_BACKWARD = "stepBack";

	static final String STEP_LEFT = "stepLeft";

	static final String STEP_RIGHT = "stepRight";

	static final String BEAM_HOME = "beamHome";

	static final String BEAM_TO_POSITION = "beamToPosition";

	static final String TURN_HEAD = "turnHead";

	static final String MOVE_ARM_TO_FALL_BACK = "moveArmToFallBack";

	static final String SAY_BEHAVIOR = "say";

	static final String LOOK_DOWN = "lookDown";

	static final String SHOOT_RIGHT = "shootRight";

	static final String GET_IN_SCORE_POSITION = "getInScorePosition";

	static final String FALL_ON_SIDE = "fallOnSide";

	static final String GOALIE_BEHAVIOR = "goalieBehavior";

	static final String INWARD_TURN_LEFT45 = "inwardTurnLeft45";

	static final String INWARD_TURN_LEFT60 = "inwardTurnLeft60";

	static final String INWARD_TURN_RIGHT45 = "inwardTurnRight45";

	static final String INWARD_TURN_RIGHT60 = "inwardTurnRight60";

	static final String GET_TO_INITIAL_POSITION = "getToInitialPosition";

	/**
	 * reinitializes the Behavior-StateMachine if present
	 */
	public void init();

	/**
	 * Called to perform the behavior
	 * 
	 * @param intensity the intensity with which to perform the behavior<br>
	 */
	public void perform(float intensity);

	/**
	 * @return the name of the behavior
	 */
	public String getName();

	/**
	 * @return true if this behavior is fully finished
	 */
	public boolean isFinished();

	/**
	 * @return the number of times this behavior has been performed (inited)
	 */
	public int getPerforms();
}

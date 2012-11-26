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
package magma.agent.general;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import magma.agent.action.IAction;
import magma.agent.action.impl.Action;
import magma.agent.agentmodel.IAgentModel;
import magma.agent.agentmodel.impl.AgentModelNAO;
import magma.agent.behavior.IBehavior;
import magma.agent.behavior.ICoordinator;
import magma.agent.behavior.basic.BeamHomeBehavior;
import magma.agent.behavior.basic.BehaviorParameter;
import magma.agent.behavior.basic.InitBehavior;
import magma.agent.behavior.basic.NoneBehavior;
import magma.agent.behavior.basic.SayBehavior;
import magma.agent.behavior.basic.StopBehavior;
import magma.agent.behavior.complex.GetInScorePosition;
import magma.agent.behavior.complex.GetReady;
import magma.agent.behavior.complex.GetToInitialPosition;
import magma.agent.behavior.complex.GoalieBehavior;
import magma.agent.behavior.complex.MoveWithBall;
import magma.agent.behavior.complex.RunToBall;
import magma.agent.behavior.complex.RunToPosition;
import magma.agent.behavior.complex.ShootToGoal;
import magma.agent.behavior.coordinator.Coordinator;
import magma.agent.behavior.function.FunctionBehavior;
import magma.agent.behavior.motor.MotorFileBehavior;
import magma.agent.believe.IBelieve;
import magma.agent.believe.impl.BallInCriticalArea;
import magma.agent.believe.impl.BallKickable;
import magma.agent.believe.impl.BeamTime;
import magma.agent.believe.impl.GameRunning;
import magma.agent.believe.impl.LayOnBack;
import magma.agent.believe.impl.LayOnFront;
import magma.agent.believe.impl.LayOnSide;
import magma.agent.believe.impl.PlayDefense;
import magma.agent.believe.impl.PlayOffense;
import magma.agent.believe.impl.ResourceBelieve;
import magma.agent.believe.impl.SoccerPosition;
import magma.agent.believe.impl.TeammateCloserToBall;
import magma.agent.connection.IServerConnection;
import magma.agent.connection.impl.ServerConnection;
import magma.agent.decision.IDecisionMaker;
import magma.agent.decision.simple.GoalieDecisionMaker;
import magma.agent.decision.simple.SoccerPlayerDecisionMaker;
import magma.agent.perception.IPerception;
import magma.agent.perception.impl.Perception;
import magma.agent.worldmodel.IGlobalMap;
import magma.agent.worldmodel.impl.GlobalMap;
import magma.agent.worldmodel.localizer.ILocalizer;
import magma.agent.worldmodel.localizer.impl.LocalizerTriangulation;

/**
 * Factory class for the components of our RoboCup player
 * 
 * @author Klaus Dorer
 */
public class ComponentFactory
{
	/**
	 * Create a ServerConnection
	 * 
	 * @param host Host name/IP
	 * @param port Server port
	 * @return New Server connection
	 */
	public IServerConnection createConnection(String host, int port)
	{
		return new ServerConnection(host, port);
	}

	/**
	 * Create a Perception object
	 * 
	 * @return New Perception
	 */
	public IPerception createPerception()
	{
		return new Perception();
	}

	/**
	 * Create an new Action
	 * 
	 * @param connection Server connection
	 * @param scene Scene name
	 * @param teamname Team name
	 * @param playerNumber Player number
	 * @return New Action object
	 */
	public IAction createAction(IServerConnection connection, String scene,
			String teamname, int playerNumber)
	{
		return new Action(connection, scene, teamname, playerNumber);
	}

	/**
	 * Create a new AgentModel
	 * 
	 * @return New AgentModel object
	 */
	public IAgentModel createAgentModel()
	{
		return new AgentModelNAO();
	}

	/**
	 * Create a new GlobalMap
	 * 
	 * @param teamname Team name
	 * @param playerNumber Player number
	 * @return New GlobalMap object
	 */
	public IGlobalMap createWorldModel(String teamname, int playerNumber)
	{
		return new GlobalMap(createLocalizer(), teamname, playerNumber);
	}

	/**
	 * Create a new Localizer
	 * 
	 * @return New Localizer
	 */
	protected ILocalizer createLocalizer()
	{
		return new LocalizerTriangulation();
	}

	/**
	 * Create a new Coordinator
	 * 
	 * @param action Action object
	 * @param agentModel Agent model
	 * @param worldModel World model
	 * @return New Coordinator object
	 */
	public ICoordinator createCoordinator(IAction action,
			IAgentModel agentModel, IGlobalMap worldModel)
	{
		return new Coordinator(action, agentModel, worldModel);
	}

	/**
	 * Create a new DecisionMaker
	 * 
	 * @param believes Agent believes
	 * @param behaviors Agenet behaviors
	 * @param playerNumber Player number
	 * @param serverVersion Server version
	 * @return new DecisionMaker object
	 */
	public IDecisionMaker createDecisionMaker(Map<String, IBelieve> believes,
			Map<String, IBehavior> behaviors, int playerNumber, int serverVersion)
	{
		// return new SimpleDecisionMaker(believes, behaviors);

		if (playerNumber == 1) {
			return new GoalieDecisionMaker(believes, behaviors, serverVersion);
		} else {
			return new SoccerPlayerDecisionMaker(believes, behaviors,
					serverVersion);
		}
	}

	/**
	 * Creates all believe objects
	 * 
	 * @param agentModel Agent model
	 * @param worldModel World model
	 * @return A map with all believes that may be used
	 */
	public Map<String, IBelieve> createBelieves(IAgentModel agentModel,
			IGlobalMap worldModel)
	{
		Map<String, IBelieve> believes = new HashMap<String, IBelieve>();

		IBelieve believe = new ResourceBelieve("resourceBody", 1);
		believes.put(believe.getName(), believe);

		believe = new TeammateCloserToBall(agentModel, worldModel);
		believes.put(believe.getName(), believe);

		believe = new BallKickable(agentModel, worldModel);
		believes.put(believe.getName(), believe);

		believe = new SoccerPosition(agentModel, worldModel);
		believes.put(believe.getName(), believe);

		believe = new LayOnBack(agentModel, worldModel);
		believes.put(believe.getName(), believe);

		believe = new LayOnFront(agentModel, worldModel);
		believes.put(believe.getName(), believe);

		believe = new LayOnSide(agentModel, worldModel);
		believes.put(believe.getName(), believe);

		believe = new GameRunning(agentModel, worldModel);
		believes.put(believe.getName(), believe);

		believe = new BeamTime(agentModel, worldModel);
		believes.put(believe.getName(), believe);

		believe = new PlayOffense(agentModel, worldModel);
		believes.put(believe.getName(), believe);

		believe = new PlayDefense(agentModel, worldModel);
		believes.put(believe.getName(), believe);

		believe = new BallInCriticalArea(agentModel, worldModel);
		believes.put(believe.getName(), believe);

		return believes;
	}

	/**
	 * Create all behavior objects
	 * 
	 * @param playerNumber Player ID within its own team
	 * @param params Behavior parametrization, null if default should be used
	 * @return A map of available behaviors
	 */
	public Map<String, IBehavior> createBehaviors(IAgentModel agentModel,
			IGlobalMap worldModel, ICoordinator coordinator, int playerNumber,
			BehaviorParameter params)
	{
		Map<String, IBehavior> behaviors = new HashMap<String, IBehavior>();

		IBehavior behavior = new NoneBehavior();
		behaviors.put(behavior.getName(), behavior);

		behavior = new StopBehavior(coordinator);
		behaviors.put(behavior.getName(), behavior);

		behavior = new InitBehavior(coordinator);
		behaviors.put(behavior.getName(), behavior);

		behavior = new BeamHomeBehavior(IBehavior.BEAM_HOME, worldModel,
				agentModel, coordinator);
		behaviors.put(behavior.getName(), behavior);

		behavior = new SayBehavior(IBehavior.SAY_BEHAVIOR, worldModel,
				agentModel, coordinator);
		behaviors.put(behavior.getName(), behavior);

		// TODO: add meta information to motor files and then load all from folder
		try {
			behaviors.put(IBehavior.START_WALK, new MotorFileBehavior(
					IBehavior.START_WALK, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/StartWalk.txt", 2, 3));

			behaviors.put(IBehavior.CONTINUE_WALK, new MotorFileBehavior(
					IBehavior.CONTINUE_WALK, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/ContinueWalk.txt", 2, 2));

			behaviors.put(IBehavior.CONTINUE_RUN, new FunctionBehavior(
					IBehavior.CONTINUE_RUN, coordinator, worldModel, agentModel,
					"behaviors/FunctionBehaviors/continueRun.txt", 1.0f, 0.0f));

			// behaviors
			// .put(IBehavior.CONTINUE_WALK, new FunctionBehavior(
			// IBehavior.CONTINUE_WALK, coordinator, worldModel,
			// agentModel, "behaviors/FunctionBehaviors/walkSpline.txt",
			// 1.0f, 0.0f, 42.0f));

			behaviors.put(IBehavior.STOP_WALK, new MotorFileBehavior(
					IBehavior.STOP_WALK, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/StopWalk.txt", 2, 2));

			behaviors.put(IBehavior.WALK, new MotorFileBehavior(IBehavior.WALK,
					coordinator, worldModel, agentModel, params,
					"behaviors/BehaviourValues/Forwards50.txt", 2, 3));

			behaviors.put(IBehavior.FORWARD, new MotorFileBehavior(
					IBehavior.FORWARD, coordinator, worldModel, agentModel, params,
					"behaviors/BehaviourValues/Forwards.txt", 2, 3));

			behaviors
					.put(IBehavior.GET_UP_BACK, new MotorFileBehavior(
							IBehavior.GET_UP_BACK, coordinator, worldModel,
							agentModel, params,
							"behaviors/BehaviourValues/StandUpFromBack.txt", 12, 16));

			behaviors.put(IBehavior.GET_UP_FRONT,
					new MotorFileBehavior(IBehavior.GET_UP_FRONT, coordinator,
							worldModel, agentModel, params,
							"behaviors/BehaviourValues/StandUpFromFront.txt", 12, 16));

			behaviors.put(IBehavior.STEP_LEFT, new MotorFileBehavior(
					IBehavior.STEP_LEFT, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/SideStepLeft.txt", 4, 4));

			behaviors.put(IBehavior.STEP_RIGHT, new MotorFileBehavior(
					IBehavior.STEP_RIGHT, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/SideStepRight.txt", 4, 4));

			behaviors.put(IBehavior.INWARD_TURN_LEFT45, new MotorFileBehavior(
					IBehavior.INWARD_TURN_LEFT45, coordinator, worldModel,
					agentModel, params,
					"behaviors/BehaviourValues/InwardsLeft45.txt", 3, 5));

			behaviors.put(IBehavior.INWARD_TURN_LEFT60, new MotorFileBehavior(
					IBehavior.INWARD_TURN_LEFT60, coordinator, worldModel,
					agentModel, params,
					"behaviors/BehaviourValues/InwardsLeft60.txt", 3, 5));

			behaviors.put(IBehavior.INWARD_TURN_RIGHT45, new MotorFileBehavior(
					IBehavior.INWARD_TURN_RIGHT45, coordinator, worldModel,
					agentModel, params,
					"behaviors/BehaviourValues/InwardsRight45.txt", 3, 5));

			behaviors.put(IBehavior.INWARD_TURN_RIGHT60, new MotorFileBehavior(
					IBehavior.INWARD_TURN_RIGHT60, coordinator, worldModel,
					agentModel, params,
					"behaviors/BehaviourValues/InwardsRight60.txt", 3, 5));

			behaviors.put(IBehavior.TURN_LEFT_60, new MotorFileBehavior(
					IBehavior.TURN_LEFT_60, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/TurnLeft60.txt", 2, 4));

			behaviors.put(IBehavior.TURN_LEFT_40, new MotorFileBehavior(
					IBehavior.TURN_LEFT_40, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/TurnLeft40.txt", 2, 4));

			behaviors.put(IBehavior.TURN_LEFT_20, new MotorFileBehavior(
					IBehavior.TURN_LEFT_20, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/TurnLeft20.txt", 2, 4));

			behaviors.put(IBehavior.TURN_RIGHT_60, new MotorFileBehavior(
					IBehavior.TURN_RIGHT_60, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/TurnRight60.txt", 2, 4));

			behaviors.put(IBehavior.TURN_RIGHT_40, new MotorFileBehavior(
					IBehavior.TURN_RIGHT_40, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/TurnRight40.txt", 2, 4));

			behaviors.put(IBehavior.TURN_RIGHT_20, new MotorFileBehavior(
					IBehavior.TURN_RIGHT_20, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/TurnRight20.txt", 2, 4));

			behaviors.put(IBehavior.SHOOT_LEFT, new MotorFileBehavior(
					IBehavior.SHOOT_LEFT, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/ShootLeft3meter.txt", 1, 55));

			// behaviors.put(IBehavior.SHOOT, new FunctionBehavior(IBehavior.SHOOT,
			// coordinator, worldModel, agentModel,
			// "behaviors/FunctionBehaviors/kickParameter.txt", 1.0f, 2.0f));

			behaviors
					.put(IBehavior.SHOOT_RIGHT, new MotorFileBehavior(
							IBehavior.SHOOT_RIGHT, coordinator, worldModel,
							agentModel, params,
							"behaviors/BehaviourValues/ShootRight3meter.txt", 1, 55));

			behaviors.put(IBehavior.SIDE_KICK_LEFT, new MotorFileBehavior(
					IBehavior.SIDE_KICK_LEFT, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/SideKickLeft.txt", 2, 2));

			behaviors.put(IBehavior.SIDE_KICK_RIGHT, new MotorFileBehavior(
					IBehavior.SIDE_KICK_RIGHT, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/SideKickRight.txt", 2, 2));

			behaviors.put(IBehavior.GET_READY_PRIMITIVE, new MotorFileBehavior(
					IBehavior.GET_READY_PRIMITIVE, coordinator, worldModel,
					agentModel, params, "behaviors/BehaviourValues/GetReady.txt", 6,
					18));

			behaviors.put(IBehavior.TURN_HEAD, new FunctionBehavior(
					IBehavior.TURN_HEAD, coordinator, worldModel, agentModel,
					"behaviors/FunctionBehaviors/turnHead.txt", 1.0f, 1.0f));

			behaviors.put(IBehavior.FALL_ON_SIDE, new MotorFileBehavior(
					IBehavior.FALL_ON_SIDE, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/FallRightSide.txt", 16, 8));

			behaviors.put(IBehavior.MOVE_ARM_TO_FALL_BACK, new MotorFileBehavior(
					IBehavior.MOVE_ARM_TO_FALL_BACK, coordinator, worldModel,
					agentModel, params,
					"behaviors/BehaviourValues/MoveArmToFallBack.txt", 6, 14));

			behaviors.put(IBehavior.LOOK_DOWN, new MotorFileBehavior(
					IBehavior.LOOK_DOWN, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/LookDown.txt", 1, 2));

			behaviors.put("raiseLeftLeg", new MotorFileBehavior(
					IBehavior.LOOK_DOWN, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/RaiseLeftLeg.txt", 1, 2));

			behaviors.put("raiseRightLeg", new MotorFileBehavior(
					IBehavior.LOOK_DOWN, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/RaiseRightLeg.txt", 1, 2));

			behaviors.put(IBehavior.STEP_FORWARD, new MotorFileBehavior(
					IBehavior.STEP_FORWARD, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/Forwards.txt", 2, 4));

			behaviors.put(IBehavior.STEP_BACKWARD, new MotorFileBehavior(
					IBehavior.STEP_BACKWARD, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/Backwards.txt", 2, 6));

			behaviors.put(IBehavior.STEP_LEFT, new MotorFileBehavior(
					IBehavior.STEP_LEFT, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/SideStepLeft.txt", 2, 4));

			behaviors.put(IBehavior.STEP_RIGHT, new MotorFileBehavior(
					IBehavior.STEP_RIGHT, coordinator, worldModel, agentModel,
					params, "behaviors/BehaviourValues/SideStepRight.txt", 2, 4));

		} catch (IOException e) {
			e.printStackTrace();
			System.out.println("Rule file not found");
		}

		behavior = new RunToBall(worldModel, agentModel, params, behaviors);
		behaviors.put(behavior.getName(), behavior);

		behavior = new RunToPosition(worldModel, agentModel, params, behaviors);
		behaviors.put(behavior.getName(), behavior);

		behavior = new GetInScorePosition(worldModel, agentModel, params,
				behaviors);
		behaviors.put(behavior.getName(), behavior);

		behavior = new ShootToGoal(worldModel, agentModel, params, behaviors);
		behaviors.put(behavior.getName(), behavior);

		behavior = new MoveWithBall(worldModel, agentModel, params, behaviors);
		behaviors.put(behavior.getName(), behavior);

		// behavior = new Balance(worldModel, agentModel, params, behaviors,
		// coordinator);
		// behaviors.put(behavior.getName(), behavior);

		behavior = new GoalieBehavior(worldModel, agentModel, params, behaviors);
		behaviors.put(behavior.getName(), behavior);

		behavior = new GetToInitialPosition(worldModel, agentModel, params,
				behaviors);
		behaviors.put(behavior.getName(), behavior);

		behavior = new GetReady(worldModel, agentModel, params, behaviors);
		behaviors.put(behavior.getName(), behavior);

		return behaviors;
	}
}

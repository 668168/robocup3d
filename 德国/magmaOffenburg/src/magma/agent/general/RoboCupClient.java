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
import java.util.Map;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;

import magma.agent.IMagmaConstants;
import magma.agent.IServerConfigFilesConstants;
import magma.agent.action.IAction;
import magma.agent.agentmodel.IAgentModel;
import magma.agent.agentmodel.impl.AgentModel;
import magma.agent.behavior.IBehavior;
import magma.agent.behavior.ICoordinator;
import magma.agent.behavior.basic.BehaviorParameter;
import magma.agent.believe.IBelieve;
import magma.agent.connection.IServerConnection;
import magma.agent.decision.IDecisionMaker;
import magma.agent.perception.IPerception;
import magma.agent.worldmodel.IGlobalMap;
import magma.agent.worldmodel.impl.GlobalMap;
import magma.util.logging.PreciseFormatter;

/**
 * This is the main class of the application used to start the magma Robocup
 * agent.
 */
public class RoboCupClient implements IWorldModelInteract
{
	private final IServerConnection connection;

	/** low level perception processing of the agent */
	private final IPerception perception;

	/** low level action processing of the agent */
	private final IAction action;

	/** the model for all visible objects */
	private final IGlobalMap worldModel;

	/** decision making instance */
	private final IDecisionMaker decisionMaker;

	private final ICoordinator coordinator;

	private final IAgentModel agentModel;

	// creates and starts a RoboCupClient object
	public static void main(String[] args)
	{
		// System.out.println("goalie opp");
		String teamname = IMagmaConstants.OUR_TEAMNAME;
		int id = 0;
		String host = IServerConnection.SERVER_IP;
		int port = IServerConnection.SERVER_PORT;

		if (args.length > 0) {
			teamname = args[0];
		}

		if (args.length > 1) {
			id = new Integer(args[1]).intValue();
			if (id < 0 || id >= IMagmaConstants.startPositionsOwnKickoff.length) {
				System.out.println("Invalid player ID: " + id + "! Maximum is: "
						+ (IMagmaConstants.startPositionsOwnKickoff.length - 1));
				System.exit(-1);
			}
		}

		if (args.length > 2) {
			host = args[2];
		}

		if (args.length > 3) {
			port = new Integer(args[3]).intValue();
			if (id < 0) {
				System.out.println("Invalid port: " + port);
				System.exit(-1);
			}
		}

		Level level = Level.SEVERE;
		if (args.length > 4) {
			String loglevel = args[4];
			if (loglevel.equalsIgnoreCase("fine")) {
				level = Level.FINE;
			} else if (loglevel.equalsIgnoreCase("finer")) {
				level = Level.FINER;
			} else if (loglevel.equalsIgnoreCase("finer")) {
				level = Level.FINER;
			} else if (loglevel.equalsIgnoreCase("finest")) {
				level = Level.FINEST;
			} else if (loglevel.equalsIgnoreCase("warning")) {
				level = Level.WARNING;
			} else if (loglevel.equalsIgnoreCase("info")) {
				level = Level.INFO;
			}
		}

		int serverVersion = IServerConfigFilesConstants.DEFAULT_SERVER_VERSION;
		if (args.length > 5) {
			serverVersion = new Integer(args[5]).intValue();
			if (id < 0) {
				System.out.println("Invalid server version: " + serverVersion);
				System.exit(-1);
			}
		}

		RoboCupClient client = new RoboCupClient(new PlayerParameters(teamname,
				id, host, port, null, level, serverVersion, null));
		client.startClient();
	}

	// starts the initialization of the communication, the main loop and the
	// ending procedure
	public RoboCupClient()
	{
		this(new PlayerParameters(IMagmaConstants.OUR_TEAMNAME, 0,
				IServerConnection.SERVER_IP, IServerConnection.SERVER_PORT, null,
				Level.FINE, IServerConfigFilesConstants.DEFAULT_SERVER_VERSION,
				null));
	}

	/**
	 * Creates a new robocup player. Call startClient() to connect it to the
	 * server and start the action loop.
	 * @param params parameters controlling the creation of this agent
	 */
	public RoboCupClient(PlayerParameters params)
	{
		if (params.getLevel() != Level.OFF) {
			initLogger(params.getLevel(), params.getTeamname(), params
					.getPlayerNumber());
		}

		ComponentFactory factory = params.getComponentFactory();

		// communication layer
		connection = factory.createConnection(params.getHost(), params.getPort());

		// protocol layer
		perception = factory.createPerception();
		connection.attach(perception);

		action = factory.createAction(connection,
				IServerConfigFilesConstants.ACTION_SCENE_NAO, params.getTeamname(),
				params.getPlayerNumber());

		// model layer
		agentModel = factory.createAgentModel();

		worldModel = factory.createWorldModel(params.getTeamname(), params
				.getPlayerNumber());

		coordinator = factory.createCoordinator(action, agentModel, worldModel);

		// control layer
		Map<String, IBelieve> believes = factory.createBelieves(agentModel,
				worldModel);

		BehaviorParameter behaviorParams = params.getBehaviorParams();
		Map<String, IBehavior> behaviors = factory.createBehaviors(agentModel,
				worldModel, coordinator, params.getPlayerNumber(), behaviorParams);

		// decision making layer
		decisionMaker = factory.createDecisionMaker(believes, behaviors, params
				.getPlayerNumber(), params.getServerVersion());

		// it is important to keep this order of observer attaching
		perception.attach((AgentModel) agentModel);
		perception.attach((GlobalMap) worldModel);
		worldModel.attach(decisionMaker);
		worldModel.attach(coordinator);
	}

	/**
	 * Starts the connection to the server, will only return after disconnection
	 * Uses default IP and port
	 */
	public void startClient()
	{
		if (connection.establishConnection()) {
			action.sendSceneString();
			connection.startReceiveLoop();
		}
	}

	/**
	 * Starts the connection to the server, will only return after disconnection
	 * @param ip the ip of the server to connect to
	 * @param port the port of the server
	 */
	public void startClient(String ip, int port)
	{
		connection.setConnectionAddress(ip, port);
		startClient();
	}

	public boolean isConnected()
	{
		return connection.isConnected();
	}

	/**
	 * Stops the connection to the server after the next message was received
	 */
	public void stopClient()
	{
		connection.stopReceiveLoop();
	}

	/**
	 * @return the worldModel
	 */
	public IGlobalMap getWorldModel()
	{
		return worldModel;
	}

	/**
	 * @return read only access to the agent model
	 */
	public IAgentModel getAgentModel()
	{
		return agentModel;
	}

	public void beam(float x, float y, float rot)
	{
		action.sendBeamString(x, y, rot);
	}

	public void moveto(float x, float y, float rot)
	{
		System.out.println("Currently not supported to move to x: " + x + " y: "
				+ y + " rot: " + rot);
	}

	/**
	 * Initializes logging functionality
	 * @throws IOException if logfile can not be opened
	 */
	private static void initLogger(Level level, String teamname, int playerNumber)
	{
		try {
			Logger logger = Logger.getLogger("");
			FileHandler handler = new FileHandler("log/" + teamname + playerNumber
					+ ".log");
			handler.setFormatter(new PreciseFormatter());
			logger.addHandler(handler);
			logger.setLevel(level);
			// to console we only want to log errors
			logger.getHandlers()[0].setLevel(Level.SEVERE);
			logger.log(Level.INFO, "Start client: {0}", teamname);

		} catch (SecurityException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * @return the decisionMaker
	 */
	public IDecisionMaker getDecisionMaker()
	{
		return decisionMaker;
	}

	/**
	 * @return the perception
	 */
	public IPerception getPerception()
	{
		return this.perception;
	}
}

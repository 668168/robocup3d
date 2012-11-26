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
package magma.agent.perception.impl;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

import magma.agent.IMagmaConstants;
import magma.agent.IServerConfigFilesConstants;
import magma.agent.perception.IForceResistancePerceptor;
import magma.agent.perception.IGameStatePerceptor;
import magma.agent.perception.IHingeJointPerceptor;
import magma.agent.perception.IPerception;
import magma.agent.perception.ITimerPerceptor;
import magma.agent.perception.IUniversalJointPerceptor;
import magma.agent.perception.IVisibleObjectPerceptor;
import magma.util.observer.IObserver;
import magma.util.observer.IPublishSubscribe;
import magma.util.observer.Subject;

public class Perception implements IPerception
{
	/** handle for logging */
	private static Logger logger = Logger.getLogger("");

	// If true info is printed to console
	public static boolean perceptorInfo = false;

	// Parsing layer
	private final ServerMessageParser parser;

	// Map for all named sensors
	private final Map<String, Perceptor> perceptors;

	// Map for all visible objects
	private Map<String, VisibleObjectPerceptor> visibleObjects;

	// List of visible players
	private List<PlayerPos> visiblePlayers;

	// Time information from the server
	private final TimePerceptor time;

	// Actual Game State
	private GameStatePerceptor gameState;

	// Actual Agent State
	private AgentStatePerceptor agentState;

	// Hearing
	private HearPerceptor hear;

	// the observers that want to be updated after perception parsing
	private IPublishSubscribe<IPerception> observer;

	/**
	 * initializes all perceptors that appear in the simulation without the
	 * visions of the other players
	 */
	public Perception()
	{
		parser = new ServerMessageParser();

		perceptors = new HashMap<String, Perceptor>(40);

		initPlayers();
		initVisions();
		initPerceptors();

		time = new TimePerceptor();
		gameState = new GameStatePerceptor();
		agentState = new AgentStatePerceptor();
		hear = new HearPerceptor();

		observer = new Subject<IPerception>();
	}

	/**
	 * Initialize visible players
	 */
	private void initPlayers()
	{
		visiblePlayers = new ArrayList<PlayerPos>(
				IMagmaConstants.NUMBER_OF_PLAYERS_PER_TEAM * 2);
	}

	/**
	 * Initialize known visible objects
	 */
	private void initVisions()
	{
		visibleObjects = new HashMap<String, VisibleObjectPerceptor>(20);
	}

	/**
	 * Initializes all agent perceptors
	 */
	private void initPerceptors()
	{

		initUniversalJointPerceptors();
		initHingeJointPerceptors();
		initForceResistancePerceptors();
		initGyroPerceptors();
	}

	/**
	 * Initializes all universal joint perceptors
	 */
	private void initUniversalJointPerceptors()
	{
		for (int i = 0; i < IServerConfigFilesConstants.UNIVERSALJOINT_PERCEPTORS.length; i++) {
			perceptors.put(
					IServerConfigFilesConstants.UNIVERSALJOINT_PERCEPTORS[i],
					new UniversalJointPerceptor(
							IServerConfigFilesConstants.UNIVERSALJOINT_PERCEPTORS[i]));
		}
	}

	/**
	 * Initializes all hinge joint perceptors
	 */
	private void initHingeJointPerceptors()
	{
		for (int i = 0; i < IServerConfigFilesConstants.HINGEJOINT_PERCEPTORS.length; i++) {
			perceptors.put(IServerConfigFilesConstants.HINGEJOINT_PERCEPTORS[i],
					new HingeJointPerceptor(
							IServerConfigFilesConstants.HINGEJOINT_PERCEPTORS[i]));
		}
	}

	/**
	 * Initializes all force resistance perceptors
	 */
	private void initForceResistancePerceptors()
	{
		for (int i = 0; i < IServerConfigFilesConstants.FORCERESISTANCE_PERCEPTORS.length; i++) {
			perceptors
					.put(
							IServerConfigFilesConstants.FORCERESISTANCE_PERCEPTORS[i],
							new ForceResistancePerceptor(
									IServerConfigFilesConstants.FORCERESISTANCE_PERCEPTORS[i]));
		}
	}

	/**
	 * initializes all GyroRate perceptors
	 */
	private void initGyroPerceptors()
	{
		for (int i = 0; i < IServerConfigFilesConstants.GYRORATE_PERCEPTORS.length; i++) {
			perceptors.put(IServerConfigFilesConstants.GYRORATE_PERCEPTORS[i],
					new GyroPerceptor(
							IServerConfigFilesConstants.GYRORATE_PERCEPTORS[i]));
		}
	}

	/**
	 * Called when the server message is parsed
	 */
	@Override
	public void update(String message)
	{
		try {
			parse(message);

			// inform observers
			observer.onStateChange(this);
		} catch (PerceptorConversionException e) {
			// TODO: we should be able to recognize. At least we should explicitly
			// specify which exceptions we ignore on purpose
			logger.log(Level.INFO, "not able to Parse: {0}", e);
		} catch (RuntimeException e) {
			logger.log(Level.SEVERE, "Error parsing message: {0}", message);
			logger.log(Level.SEVERE, "Error parsing message: {0}", e);
			assert false : "Parsing problem";
		}

	}

	protected void parse(String message) throws PerceptorConversionException
	{
		if (message == null) {
			// nothing to do, might happen at disconnection
			return;
		}

		// Clear list of visible players
		visiblePlayers.clear();
		visibleObjects.clear();

		List<Perceptor> perceptors = parser.parseString(message);

		// Process
		for (Perceptor perceptor : perceptors)
			processInputPerceptor(perceptor);
	}

	private void processInputPerceptor(Perceptor perceptor)
	{
		// Handle sensor perceptors
		if (perceptor instanceof GyroPerceptor
				|| perceptor instanceof HingeJointPerceptor
				|| perceptor instanceof UniversalJointPerceptor
				|| perceptor instanceof ForceResistancePerceptor
				|| perceptor instanceof TouchPerceptor)
			processNamedPerceptor(perceptor);

		if (perceptor instanceof VisionPerceptor)
			processVisibleObjects((VisionPerceptor) perceptor);

		if (perceptor instanceof GameStatePerceptor)
			gameState.assign(perceptor);

		if (perceptor instanceof AgentStatePerceptor)
			agentState.assign(perceptor);

		if (perceptor instanceof HearPerceptor)
			hear.assign(perceptor);

		if (perceptor instanceof TimePerceptor)
			time.assign(perceptor);
	}

	/**
	 * Updates the given perceptor in the sensor list, adds the sensor if it
	 * didn't already exist
	 * 
	 * @param perceptor Perceptor object
	 */
	private void processNamedPerceptor(Perceptor input)
	{
		Perceptor perceptor = perceptors.get(input.getName());

		if (perceptor != null)
			perceptor.assign(input);
		else if (Perception.perceptorInfo)
			System.out
					.println("Got unknown perceptor \"" + input.getName() + "\"");
	}

	/**
	 * Updates visible objects (Flags, Goals, Players, ...) from the vision
	 * 
	 * @param perceptor Vision perceptor
	 */
	private void processVisibleObjects(VisionPerceptor perceptor)
	{
		for (IVisibleObjectPerceptor object : perceptor.getObjects()) {
			if (object instanceof PlayerPos) {
				visiblePlayers.add((PlayerPos) object);
			} else {
				visibleObjects.put(object.getName(), new VisibleObjectPerceptor(
						object.getName(), object.getPosition()));
			}
		}
	}

	@Override
	public IUniversalJointPerceptor getUniversalJointPerceptor(String name)
	{
		return (IUniversalJointPerceptor) perceptors.get(name);
	}

	@Override
	public IHingeJointPerceptor getHingeJointPerceptor(String name)
	{
		return (IHingeJointPerceptor) perceptors.get(name);
	}

	@Override
	public GyroPerceptor getGyroRatePerceptor(String name)
	{
		return (GyroPerceptor) perceptors.get(name);
	}

	@Override
	public IForceResistancePerceptor getForceResistancePerceptor(String name)
	{
		return (IForceResistancePerceptor) perceptors.get(name);
	}

	@Override
	public VisibleObjectPerceptor getObject(String name)
	{
		return visibleObjects.get(name);
	}

	@Override
	public ITimerPerceptor getTime()
	{
		return time;
	}

	@Override
	public IGameStatePerceptor getGameState()
	{
		return gameState;
	}

	@Override
	public HearPerceptor getHearPerceptor()
	{
		return hear;
	}

	@Override
	public List<PlayerPos> getVisiblePlayers()
	{
		return visiblePlayers;
	}

	@Override
	public void attach(IObserver<IPerception> newObserver)
	{
		observer.attach(newObserver);
	}
}
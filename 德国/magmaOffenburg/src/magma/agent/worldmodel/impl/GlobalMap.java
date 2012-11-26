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
package magma.agent.worldmodel.impl;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

import magma.agent.IMagmaConstants;
import magma.agent.IServerConfigFilesConstants;
import magma.agent.perception.IHearPerceptor;
import magma.agent.perception.IHingeJointPerceptor;
import magma.agent.perception.IPerception;
import magma.agent.perception.IPlayerPos;
import magma.agent.perception.IVisibleObjectPerceptor;
import magma.agent.perception.impl.PlayerPos;
import magma.agent.worldmodel.IGlobalMap;
import magma.agent.worldmodel.ILandmark;
import magma.agent.worldmodel.IPlayer;
import magma.agent.worldmodel.IThisPlayer;
import magma.agent.worldmodel.localizer.ILocalizationFlag;
import magma.agent.worldmodel.localizer.ILocalizer;
import magma.util.geometry.PositionOrientation;
import magma.util.observer.IObserver;
import magma.util.observer.IPublishSubscribe;
import magma.util.observer.Subject;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Container class for all visible objects on the field, for the time and game
 * state
 */
public class GlobalMap implements IObserver<IPerception>, IGlobalMap,
		IServerConfigFilesConstants, Serializable
{
	// handle for logging
	private static Logger logger = Logger.getLogger("");

	/** id of this class for serialization */
	private static final long serialVersionUID = 182243462936086603L;

	/** observers of world model */
	private final transient IPublishSubscribe<IGlobalMap> observer;

	/** the localizer that is able to calculate the absolute position */
	private final transient ILocalizer localizer;

	/** the ball of the game */
	private Ball ball;

	/** the landmarks used for orientation (flags and goal posts */
	private Map<String, ILandmark> landmarks;

	/** the list of all visible players */
	private List<IPlayer> visiblePlayers;

	/** reference to the own players */
	private IPlayer[] ownPlayer;

	/** reference to the opponent players */
	private IPlayer[] otherPlayer;

	/** the time on the global clock in (units?). Not the game time */
	private float globalTime;

	/** the time the game is running now */
	private float gameTime;

	/** the playmode the game is running now */
	private String playmode;

	/** the playmode the game was running previously */
	private String previousPlaymode;

	/** the global coordinates of the agent */
	ThisPlayer thisPlayer;

	/** goals scored by the opponent */
	private int goalsTheyScored = 0;

	/** goals scored by us */
	private int goalsWeScored = 0;

	/**
	 * Default constructor
	 * @param localizer the module that calculates the agent's global position
	 */
	public GlobalMap(ILocalizer localizer, String teamname, int playerNumber)
	{
		this.localizer = localizer;
		thisPlayer = new ThisPlayer(teamname, playerNumber);
		observer = new Subject<IGlobalMap>();
		createObjects();
	}

	/**
	 * Creates all objects. We do not create new objects each time on update, but
	 * update the existing objects
	 */
	private void createObjects()
	{
		ball = new Ball();

		// landmarks
		landmarks = new HashMap<String, ILandmark>();
		int i = 0;
		for (String name : LANDMARK_NAMES) {
			landmarks.put(name, new Landmark(new Vector3D(
					LANDMARK_POSITIONS[i][0], LANDMARK_POSITIONS[i][1], 0.0)));
			i++;
		}

		// Players
		int numberOfPlayersPerTeam = IMagmaConstants.NUMBER_OF_PLAYERS_PER_TEAM;
		visiblePlayers = new ArrayList<IPlayer>(numberOfPlayersPerTeam * 2);
		ownPlayer = new Player[numberOfPlayersPerTeam + 1];
		otherPlayer = new Player[numberOfPlayersPerTeam + 1];
		for (int player = 0; player < numberOfPlayersPerTeam; player++) {
			ownPlayer[player + 1] = new Player(player + 1,
					IMagmaConstants.OUR_TEAMNAME, true);
			otherPlayer[player + 1] = new Player(player + 1,
					IMagmaConstants.UNKNOWN_PLAYER_TEAMNAME, false);
		}
	}

	/**
	 * Called once perception is finished parsing a new incoming message
	 * @param perception the object containing the result from parsing
	 */
	public void update(IPerception perception)
	{
		// we have to pre update the landmarks for position calculation
		preUpdateLandmarks(perception);

		// calculate the new position of the agent
		calculatePosition(perception);

		globalTime = perception.getTime().getTime();
		gameTime = perception.getGameState().getTime();
		playmode = perception.getGameState().getPlaymode();
		if (IServerConfigFilesConstants.PLAY_MODE[0].equalsIgnoreCase(playmode)
				|| IServerConfigFilesConstants.PLAY_MODE[1]
						.equalsIgnoreCase(playmode)) {
			updateGoalsScored(perception);
		}

		// update this players own information (has to be before updating other
		// visible objects
		getThisPlayer().updateThisPlayer(perception);
		updateBall(perception);
		updateLandmarks(perception);
		updatePlayers(perception);

		if (ball.getAge(globalTime) > 3.0f) {
			processHear(perception, ball);
		}

		// now inform observers about changes
		observer.onStateChange(this);
	}

	private void processHear(IPerception perception, Ball ball)
	{
		IHearPerceptor hear = perception.getHearPerceptor();
		String name = hear.getName();

		if ("self".equalsIgnoreCase(name)) {
			// message from ourselves
			return;
		}

		try {
			String message = hear.getMessage();
			int index = message.indexOf('-');
			if (index < 0) {
				// no message from us
				return;
			}

			int x = new Integer(message.substring(0, index));
			int y = new Integer(message.substring(index + 1));

			float xlong = (x / 100.0f) - 10;
			float ylong = (y / 100.0f) - 5;
			ball
					.setPosition(new Vector3D(xlong, ylong, ball.getPosition()
							.getZ()));
			logger.log(Level.FINER, "hear ball: ({0}, {1})", new Object[] { xlong,
					ylong });

		} catch (Exception e) {
			// might happen with opponent messages
		}
	}

	/**
	 * @param perception the object containing the result from parsing
	 */
	void updateGoalsScored(IPerception perception)
	{

		previousPlaymode = playmode;
		playmode = perception.getGameState().getPlaymode();
		if ((getThisPlayer().getSide() == IMagmaConstants.LEFT_SIDE
				&& IServerConfigFilesConstants.PLAY_MODE[1]
						.equalsIgnoreCase(playmode) && !IServerConfigFilesConstants.PLAY_MODE[1]
				.equalsIgnoreCase(previousPlaymode))
				|| getThisPlayer().getSide() == IMagmaConstants.RIGHT_SIDE
				&& (IServerConfigFilesConstants.PLAY_MODE[0]
						.equalsIgnoreCase(playmode) && !IServerConfigFilesConstants.PLAY_MODE[0]
						.equalsIgnoreCase(previousPlaymode)))
			goalsWeScored++;

		else if ((getThisPlayer().getSide() == IMagmaConstants.LEFT_SIDE
				&& IServerConfigFilesConstants.PLAY_MODE[0]
						.equalsIgnoreCase(playmode) && !IServerConfigFilesConstants.PLAY_MODE[0]
				.equalsIgnoreCase(previousPlaymode))
				|| (getThisPlayer().getSide() == IMagmaConstants.RIGHT_SIDE
						&& IServerConfigFilesConstants.PLAY_MODE[1]
								.equalsIgnoreCase(playmode) && !IServerConfigFilesConstants.PLAY_MODE[1]
						.equalsIgnoreCase(previousPlaymode)))
			goalsTheyScored++;
	}

	/**
	 * @param perception the object containing the result from parsing
	 * 
	 */
	private void calculatePosition(IPerception perception)
	{
		HashMap<String, ILocalizationFlag> flags = new HashMap<String, ILocalizationFlag>();
		IHingeJointPerceptor neckYaw = perception
				.getHingeJointPerceptor(HINGEJOINT_PERCEPTORS[0]);
		IHingeJointPerceptor neckPitch = perception
				.getHingeJointPerceptor(HINGEJOINT_PERCEPTORS[1]);

		Vector3D gyroVector = perception.getGyroRatePerceptor(
				GYRORATE_PERCEPTORS[0]).getGyro();

		float neckYawAngle = 0.0f;
		if (neckYaw != null) {
			neckYawAngle = neckYaw.getAxis();
		}
		neckYawAngle = (float) Math.toRadians(neckYawAngle);

		float neckPitchAngle = 0.0f;
		if (neckPitch != null) {
			neckPitchAngle = neckPitch.getAxis();
		}
		neckPitchAngle = (float) Math.toRadians(neckPitchAngle);

		int i = 0;
		for (String name : LANDMARK_NAMES) {
			IVisibleObjectPerceptor landmarkSeen = perception.getObject(name);
			if (landmarkSeen != null) {
				Landmark landmark = (Landmark) landmarks.get(name);
				// add the new flag into the array
				flags.put(name, landmark);
			}
			i++;
		}

		PositionOrientation localizeInfo;
		try {
			localizeInfo = localizer.localize(flags, neckYawAngle, neckPitchAngle,
					gyroVector);
		} catch (RuntimeException e) {
			logger.log(Level.SEVERE, "Localization problem {0}", e);
			return;
		}

		if (localizeInfo != null) {
			// TODO may be we want to filter once sensors have noise
			thisPlayer.setPosition(localizeInfo.getPosition());
			// TODO add view angle direction(s)
			thisPlayer.setHorizontalAngle(localizeInfo.getOrientationX());
		}
	}

	/**
	 * @param perception the object containing the result from parsing
	 */
	private void updateBall(IPerception perception)
	{
		IVisibleObjectPerceptor ballVision = perception
				.getObject(IPerception.BALL);
		if (ballVision == null) {
			// this landmark is not visible currently
			ball.setVisible(false);
		} else {
			ball.update(ballVision, getGlobalTime(), getThisPlayer());
		}
	}

	/**
	 * Called to take over the distance and direction information
	 * @param perception
	 */
	private void preUpdateLandmarks(IPerception perception)
	{
		for (String name : LANDMARK_NAMES) {
			Landmark landmark = (Landmark) landmarks.get(name);
			IVisibleObjectPerceptor landmarkSeen = perception.getObject(name);
			if (landmarkSeen == null) {
				// this landmark is not visible currently
				landmark.setVisible(false);
			} else {
				landmark.preUpdate(landmarkSeen);
			}
		}
	}

	/**
	 * @param perception the object containing the result from parsing
	 */
	private void updateLandmarks(IPerception perception)
	{
		for (String name : LANDMARK_NAMES) {
			Landmark landmark = (Landmark) landmarks.get(name);
			IVisibleObjectPerceptor landmarkSeen = perception.getObject(name);
			if (landmarkSeen == null) {
				// this landmark is not visible currently
				landmark.setVisible(false);
			} else {
				landmark.update(landmarkSeen, getGlobalTime(), getThisPlayer());
			}
		}
	}

	/**
	 * @param perception the object containing the result from parsing
	 */
	void updatePlayers(IPerception perception)
	{
		List<PlayerPos> playersVision = perception.getVisiblePlayers();
		if (playersVision.isEmpty()) {
			return;
		}
		// we only remove visible players with the next see perception
		visiblePlayers.clear();
		for (IPlayerPos playerVision : playersVision) {
			Player newPlayer = new Player(playerVision.getId(), playerVision
					.getTeamname(), thisPlayer.getTeamname().equals(
					playerVision.getTeamname()));
			newPlayer.update(playerVision, getGlobalTime(), getThisPlayer());
			visiblePlayers.add(newPlayer);
		}

		matchVisiblePlayers();
	}

	private void matchVisiblePlayers()
	{
		for (IPlayer player : visiblePlayers) {
			String team = player.getTeamname();
			if (getThisPlayer().getTeamname().equals(team)) {
				int id = player.getID();
				if (id >= 0 && id < ownPlayer.length) {
					ownPlayer[id] = player;
				}
			}
		}
		// TODO match visible players to numbered players
		// PlayerPos current;
		// if (RoboCupClient.OUR_TEAMNAME.equals(teamname)) {
		// current = ownPlayer[id];
		// } else {
		// current = otherPlayer[id];
		// current.steTeamname(teamname);
		// }
		// current.parse(tokenizer);
	}

	/**
	 * @return the average error of known position and calculated position,
	 *         Double.MAX_VALUE if we do not see any flags
	 */
	public double getLandmarkError()
	{
		double result = 0.0;
		int count = 0;
		for (String name : LANDMARK_NAMES) {
			Landmark landmark = (Landmark) landmarks.get(name);
			// this landmark is not visible currently
			if (landmark.isVisible()) {
				result += landmark.getPosition().subtract(
						landmark.getKnownPosition()).getNorm();
				count++;
			}
		}
		if (count < 1) {
			return Double.MAX_VALUE;
		} else {
			return result / count;
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.worldmodel.IGloabalMap#getBall()
	 */
	public Ball getBall()
	{
		return ball;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.worldmodel.IGloabalMap#getLandmarks()
	 */
	public Collection<ILandmark> getLandmarks()
	{
		return Collections.unmodifiableCollection(landmarks.values());
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.worldmodel.IGloabalMap#getVisiblePlayers()
	 */
	public List<IPlayer> getVisiblePlayers()
	{
		return Collections.unmodifiableList(visiblePlayers);
	}

	/**
	 * @return an unmodifiable list of the own players
	 */
	public List<IPlayer> getOwnPlayers()
	{
		return Collections.unmodifiableList(Arrays.asList(ownPlayer));
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.worldmodel.IGloabalMap#getGlobalTime()
	 */
	public float getGlobalTime()
	{
		return globalTime;
	}

	/**
	 * @return the time the game is running now
	 */
	public float getGameTime()
	{
		return gameTime;
	}

	/**
	 * @return the current mode of the game as String
	 */
	public String getPlaymode()
	{
		return playmode;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * magma.agent.worldmodel.IGloabalMap#attach(magma.util.observer.IObserver)
	 */
	public void attach(IObserver<IGlobalMap> newObserver)
	{
		observer.attach(newObserver);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * magma.agent.worldmodel.IGloabalMap#detach(magma.util.observer.IObserver)
	 */
	public boolean detach(IObserver<IGlobalMap> oldObserver)
	{
		return observer.detach(oldObserver);
	}

	/**
	 * @return the global position of the agent
	 */
	public Vector3D getAgentPosition()
	{
		return thisPlayer.getPosition();
	}

	public IPlayer getOwnPlayer(int id)
	{
		return ownPlayer[id];
	}

	public IPlayer getOtherPlayer(int id)
	{
		return otherPlayer[id];
	}

	/**
	 * @return the thisPlayer
	 */
	public IThisPlayer getThisPlayer()
	{
		return thisPlayer;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object o)
	{
		if (!(o instanceof GlobalMap)) {
			return false;
		}
		GlobalMap other = (GlobalMap) o;

		if (!ball.equals(other.ball)) {
			return false;
		}

		if (!ball.equals(other.ball)) {
			return false;
		}

		if (!landmarks.equals(other.landmarks)) {
			return false;
		}

		if (!visiblePlayers.equals(other.visiblePlayers)) {
			return false;
		}

		return true;
	}

	@Override
	public int getGoalsTheyScored()
	{
		return goalsTheyScored;
	}

	@Override
	public int getGoalsWeScored()
	{
		return goalsWeScored;
	}

	@Override
	public Vector3D getOwnGoalPosition()
	{
		if (thisPlayer.getSide() == IMagmaConstants.LEFT_SIDE) {
			return new Vector3D(IServerConfigFilesConstants.LEFTGOAL_POSITION[0],
					IServerConfigFilesConstants.LEFTGOAL_POSITION[1], 0);
		} else {
			return new Vector3D(IServerConfigFilesConstants.RIGHTGOAL_POSITION[0],
					IServerConfigFilesConstants.RIGHTGOAL_POSITION[1], 0);
		}
	}

	@Override
	public Vector3D getOtherGoalPosition()
	{
		if (thisPlayer.getSide() == IMagmaConstants.RIGHT_SIDE) {
			return new Vector3D(IServerConfigFilesConstants.LEFTGOAL_POSITION[0],
					IServerConfigFilesConstants.LEFTGOAL_POSITION[1], 0);
		} else {
			return new Vector3D(IServerConfigFilesConstants.RIGHTGOAL_POSITION[0],
					IServerConfigFilesConstants.RIGHTGOAL_POSITION[1], 0);
		}
	}

	@Override
	public boolean isInOtherHalf(Vector3D position)
	{

		char side = getThisPlayer().getSide();
		double ballX = position.getX();

		return ((side == IMagmaConstants.LEFT_SIDE && ballX > 0) || (side == IMagmaConstants.RIGHT_SIDE && ballX < 0));
	}

	@Override
	public boolean isInOwnHalf(Vector3D position)
	{
		return !isInOtherHalf(position);
	}

}
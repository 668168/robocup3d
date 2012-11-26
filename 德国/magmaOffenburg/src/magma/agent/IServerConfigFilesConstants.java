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
package magma.agent;

/**
 * Constants extracted from server config files
 */
public interface IServerConfigFilesConstants
{
	/**
	 * the server version against which this agent will play if no command line
	 * parameter is specified
	 */
	int DEFAULT_SERVER_VERSION = 61;

	int SERVER_VERSION_60 = 60;

	// possible Scenes for Action
	String ACTION_SCENE_RSG = "rsg/agent/soccerbot058/soccerbot.rsg";

	String ACTION_SCENE_NAO = "rsg/agent/nao/nao.rsg";

	double BALL_DECAY = 0.94;

	float MAX_JOINT_SPEED = 7.03f;

	float FIELD_LENGTH = 6.0f;

	// float MAX_JOINT_SPEED = 4.0f;

	/** make sure to keep this and LANDMARK_POSITIONS in same order */
	public String[] LANDMARK_NAMES = { "G1L", "G2L", "G1R", "G2R", "F1L", "F2L",
			"F1R", "F2R" };

	/** the positions of the visible landmarks in order of LANDMARK_NAMES */
	public double[][] LANDMARK_POSITIONS = { { -6.0, 0.7, 0.4 },
			{ -6.0, -0.7, 0.4 }, { 6.0, 0.7, 0.4 }, { 6.0, -0.7, 0.4 },
			{ -6.0, 4.0, 0.0 }, { -6.0, -4.0, 0.0 }, { 6.0, 4.0, 0.0 },
			{ 6.0, -4.0, 0.0 } };

	/** the left goals position */
	public double[] LEFTGOAL_POSITION = { -FIELD_LENGTH, 0.0 };

	/** the right goals position */
	public double[] RIGHTGOAL_POSITION = { FIELD_LENGTH, 0.0 };

	// UniversalJoint-Constants
	/** make sure to keep this and all UNIVERSALJOINT_* - Constants in same order */
	public String[] UNIVERSALJOINT_NAMES = {};

	/** make sure to keep this and all UNIVERSALJOINT_* - Constants in same order */
	public String[] UNIVERSALJOINT_PERCEPTORS = {};

	/** make sure to keep this and all UNIVERSALJOINT_* - Constants in same order */
	public String[] UNIVERSALJOINT_EFFECTORS = {};

	/** make sure to keep this and all UNIVERSALJOINT_* - Constants in same order */
	public float[][] UNIVERSALJOINT_BOUNDS = {};

	// HingeJoint-Constants
	// TODO enable direct access of name constants
	/** make sure to keep this and all HINGEJOINT_* - Constants in same order */
	public String[] HINGEJOINT_NAMES = { "NeckYaw", "NeckPitch",
			"RShoulderPitch", "LShoulderPitch", "RShoulderYaw", "LShoulderYaw",
			"RArmRoll", "LArmRoll", "RArmYaw", "LArmYaw", "RHipYawPitch",
			"LHipYawPitch", "RHipRoll", "LHipRoll", "RHipPitch", "LHipPitch",
			"RKneePitch", "LKneePitch", "RFootPitch", "LFootPitch", "RFootRoll",
			"LFootRoll" };

	public final static String NeckYaw = "NeckYaw";

	public final static String NeckPitch = "NeckPitch";

	public final static String RShoulderPitch = "RShoulderPitch";

	public final static String LShoulderPitch = "LShoulderPitch";

	public final static String RShoulderYaw = "RShoulderYaw";

	public final static String LShoulderYaw = "LShoulderYaw";

	public final static String RArmRoll = "RArmRoll";

	public final static String LArmRoll = "LArmRoll";

	public final static String RArmYaw = "RArmYaw";

	public final static String LArmYaw = "LArmYaw";

	public final static String RHipYawPitch = "RHipYawPitch";

	public final static String LHipYawPitch = "LHipYawPitch";

	public final static String RHipRoll = "RHipRoll";

	public final static String LHipRoll = "LHipRoll";

	public final static String RHipPitch = "RHipPitch";

	public final static String LHipPitch = "LHipPitch";

	public final static String RKneePitch = "RKneePitch";

	public final static String LKneePitch = "LKneePitch";

	public final static String RFootPitch = "RFootPitch";

	public final static String LFootPitch = "LFootPitch";

	public final static String RFootRoll = "RFootRoll";

	public final static String LFootRoll = "LFootRoll";

	/** make sure to keep this and all HINGEJOINT_* - Constants in same order */
	public String[] HINGEJOINT_PERCEPTORS = { "hj1", "hj2", "raj1", "laj1",
			"raj2", "laj2", "raj3", "laj3", "raj4", "laj4", "rlj1", "llj1",
			"rlj2", "llj2", "rlj3", "llj3", "rlj4", "llj4", "rlj5", "llj5",
			"rlj6", "llj6" };

	/** make sure to keep this and all HINGEJOINT_* - Constants in same order */
	public String[] HINGEJOINT_EFFECTORS = { "he1", "he2", "rae1", "lae1",
			"rae2", "lae2", "rae3", "lae3", "rae4", "lae4", "rle1", "lle1",
			"rle2", "lle2", "rle3", "lle3", "rle4", "lle4", "rle5", "lle5",
			"rle6", "lle6" };

	/** make sure to keep this and all HINGEJOINT_* - Constants in same order */
	public float[][] HINGEJOINT_BOUNDS = { { -120, 120 }, { -45, 45 }, // hj1,hj2
			{ -120, 120 }, { -120, 120 }, // xaj1 (r,l) shoulder pitch
			{ -95, 1 }, { -1, 95 }, // xaj2 (r,l) shoulder yaw
			{ -120, 120 }, { -120, 120 }, // xaj3 (r,l) arm roll
			{ -1, 90 }, { -90, 1 }, // xaj4 (r,l) arm yaw
			{ -90, 1 }, { -90, 1 }, // xlj1 (r,l) hip yaw pitch
			{ -45, 25 }, { -25, 45 }, // xlj2 (r,l) hip roll
			{ -25, 100 }, { -25, 100 }, // xlj3 (r,l) hip pitch
			{ -130, 1 }, { -130, 1 }, // xlj4 (r,l) knee pitch
			{ -45, 75 }, { -45, 75 }, // xlj5 (r,l) foot pitch
			{ -25, 45 }, { -45, 25 } };// xlj6 (r,l) foot roll

	// ForceResistance-Constants
	/**
	 * make sure to keep this and all FORCERESISTANCE_* - Constants in same order
	 */
	public String[] FORCERESISTANCE_NAMES = { "RFootForce", "LFootForce" };

	public static final String RFootForce = "RFootForce";

	public static final String LFootForce = "LFootForce";

	/**
	 * make sure to keep this and all FORCERESISTANCE_* - Constants in same order
	 */
	public String[] FORCERESISTANCE_PERCEPTORS = { "rf", "lf" };

	// GyroRate-Constants
	/**
	 * make sure to keep this and all GYRORATE_* - Constants in same order
	 */
	public String[] GYRORATE_NAMES = { "TorsoGyro" };

	/**
	 * make sure to keep this and all GYRORATE_* - Constants in same order
	 */
	public String[] GYRORATE_PERCEPTORS = { "torso" };

	/**
	 * referee messages when a goal is scored
	 */
	public String[] PLAY_MODE = { "goal_r", "goal_l" };

	public String PLAYMODE_GOAL_RIGHT = "Goal_Right";

	public String PLAYMODE_GOAL_LEFT = "Goal_Left";

	public String PLAYMODE_BEFORE_KICK_OFF = "BeforeKickOff";

}

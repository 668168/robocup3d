#ifndef __INC_BATS_WORLDMODEL_HH_
#define __INC_BATS_WORLDMODEL_HH_

//#include <iostream>


#include <map>
#include <sstream>

#include "predicate.hh"
#include "rf.hh"
#include "vector4.hh"
#include "socketcomm.hh"
#include "hashclasses.hh"
#include "normaldistribution1.hh"
#include "normaldistribution3d.hh"
#include "matrix4d.hh"

#include "gamepadinput.hh"

namespace bats {

/**
 *  The Almighty WorldModel (think of a Futurama voice)
 */
class WorldModel {

public:

	/**
	 *  This is more like a token id than a world element id,
	 *  but it can be used as an world element id, so it doesn't
	 *  really matter I guess.
	 *  Altough it still needs to be integrated with the SocketComm.
	 */
	enum InfoID {

		iNone,

		iGameState, // 1
		iUnum,
		iTeam,
		iGameTime,
		iPlayMode,

		iTime,
		iNow, ///< The current playing time.
		iStep, ///< The time step (dt?)
		iVision, // 9
		iVisionFlag1L, ///< First flag on the left side.
		iVisionFlag2L, ///< Second flag on the left side.
		iVisionFlag1R, ///< First flag on the right side.
		iVisionFlag2R, ///< Second flag on the right side.
		iVisionGoal1L, ///< First
		iVisionGoal2L, ///<
		iVisionGoal1R, ///<
		iVisionGoal2R, ///<
		iVisionPlayer1,
		iVisionPlayer2,
		iVisionPlayer3, //20
		iVisionPlayer4,
		iVisionPlayer5,
		iVisionPlayer6,
		iVisionPlayer7,
		iVisionPlayer8,
		iVisionPlayer9,
		iVisionPlayer10,
		iVisionPlayer11,
		iVisionPlayerNone,
		iVisionOpponent1,
		iVisionOpponent2,
		iVisionOpponent3,
		iVisionOpponent4,
		iVisionOpponent5,
		iVisionOpponent6,
		iVisionOpponent7,
		iVisionOpponent8,
		iVisionOpponent9,
		iVisionOpponent10,
		iVisionOpponent11,
		iVisionOpponentNone,
		iVisionBall, ///< Position of the ball.
		iUJ,
		iHJ, // 32
		iName,
		iAxis,
		iRate,
		iAxis1,
		iRate1,
		iAxis2,
		iRate2,

		iHeadJoint1, // 40
		iHeadJoint2,

		iLLegJoint1,
		iLLegJoint2,
		iLLegJoint3,
		iLLegJoint4,
		iLLegJoint5,
		iLLegJoint6,

		iRLegJoint1,
		iRLegJoint2,
		iRLegJoint3,
		iRLegJoint4,
		iRLegJoint5,
		iRLegJoint6, // 52

		iLArmJoint1, ///<
		iLArmJoint2, ///<
		iLArmJoint3,
		iLArmJoint4,

		iRArmJoint1,
		iRArmJoint2,
		iRArmJoint3,
		iRArmJoint4, // 60

		iGyro, // 61 (GYR)
		iTorsoGyro,
		iTouch,
		iFootLeft, // 64
		iFootLeft2, /// dummy
		iFootRight, // 66
		iFootRight2,
		iVal,
		iAcceleration,

		iForceResistancePerceptor, // 69 (FRP)
		iContact,
		iForce,

		iP, /// Player vision info.

		iHead,
		iRLowerArm,
		iLLowerArm,
		iRFoot,
		iLFoot,

		iHear,
		iHearMessage1,
		iHearMessage2,
		iHearMessage3,

		iMyPos,

		// Should always have the highest numeric value.
		iInfoID,

	};
	/*
	 # STR_PM_BeforeKickOff "BeforeKickOff"
	 # STR_PM_KickOff_Left "KickOff_Left"
	 # STR_PM_KickOff_Right "KickOff_Right"
	 # STR_PM_PlayOn "PlayOn"
	 # STR_PM_KickIn_Left "KickIn_Left"
	 # STR_PM_KickIn_Right "KickIn_Right"
	 # STR_PM_CORNER_KICK_LEFT "corner_kick_left"
	 # STR_PM_CORNER_KICK_RIGHT "corner_kick_right"
	 # STR_PM_GOAL_KICK_LEFT "goal_kick_left"
	 # STR_PM_GOAL_KICK_RIGHT "goal_kick_right"
	 # STR_PM_OFFSIDE_LEFT "offside_left"
	 # STR_PM_OFFSIDE_RIGHT "offside_right"
	 # STR_PM_GameOver "GameOver"
	 # STR_PM_Goal_Left "Goal_Left"
	 # STR_PM_Goal_Right "Goal_Right"
	 # STR_PM_FREE_KICK_LEFT "free_kick_left"
	 # STR_PM_FREE_KICK_RIGHT "free_kick_right"
	 # STR_PM_Unknown "unknown"
	 */

	/**
	 *  The possible play modes.
	 */
	enum PlayMode {
		UNKNOWN = 0, BEFORE_KICKOFF,

		KICKOFF_LEFT, KICKOFF_RIGHT, KICKOFF_US, KICKOFF_THEM,

		PLAY_ON,

		FREEKICK_LEFT, FREEKICK_RIGHT, FREEKICK_US, FREEKICK_THEM,

		GOAL_LEFT, GOAL_RIGHT, GOAL_US, GOAL_THEM,

		GOAL_KICK_LEFT, GOAL_KICK_RIGHT, GOAL_KICK_US, GOAL_KICK_THEM,

		CORNER_KICK_LEFT, CORNER_KICK_RIGHT, CORNER_KICK_US, CORNER_KICK_THEM,

		KICKIN_LEFT, KICKIN_RIGHT, KICKIN_US, KICKIN_THEM,

	};

	/**
	 *  Sides of the feeld.
	 */
	enum Side {
		LEFT, RIGHT, NO_SIDE
	};

	enum KPBlockDirection {
		NOTBLOCK, FINISHED, B_FORWARD, B_RIGHT, B_LEFT
	};

	enum DebugMessage {
		BEHAVIOR, COMMENT, DM_NUM
	};

	enum Zone {
		NEAR_LEFT, NEAR_RIGHT, NEAR_FRONT, NEAR_BACK, NOZONE
	};

private:

	WorldModel(WorldModel const &); // NI
	WorldModel &operator=(WorldModel const &); // NI


	SocketComm &d_comm;
	unsigned int d_unum;
	Vector4F d_info[iInfoID];

	double d_time;
	std::string d_teamName;

	double d_gameTime;
	double d_prevGameTime;
	double d_timeStep;
	PlayMode d_playMode;
	std::string d_playModeString;
	Side d_team;

	Vector3D d_fieldNormal;
	double d_distToField;

	Vector3D d_gyro;
	Vector3D d_velocity;
	Vector3D d_acceleration;
	Matrix4D d_transform;
	static std::map<Types::Object, Vector3D> s_globalFlagCoordMap;
	double d_lastCoordUpdate;
	bool d_first;
	bool isCheck;
	Vector3D d_oldBallPos;

	Vector3D d_footForceContacts[2];
	Vector3D d_footForces[2];

	Vector3D d_myPos; // for GA

	Vector3D d_worldUnitX;
	Vector3D d_worldUnitY;
	Vector3D d_worldUnitXtest;
	Vector3D d_worldUnitYtest;

	NormalDistribution1D d_jointAngles[Types::NJOINTS];
	NormalDistribution1D d_jointRates[Types::NJOINTS];

	std::pair<double, double> d_jointConstraints[Types::NJOINTS];

	NormalDistribution3D d_objectPositions[Types::NOBJECTS];
	NormalDistribution3D d_objectPositionsW[Types::NOBJECTS];
	// NormalDistribution3D d_objectPositionsArchive[Types::NOBJECTS];
	// int d_archiveNum; // the number of avairable archive data.
	bool d_worldCoordAvailable;
	NormalDistribution3D d_objectSpeeds[Types::NOBJECTS];

	double d_lastVisionUpdate[Types::NOBJECTS];

	//  std::vector<NormalDistribution3D[Types::NOBJECTS]> d_objectPositionHistory;

	bool d_allObjectPosAvailable;

	Vector4F d_bodyPartPositions[Types::NBODYPARTS];
	Vector3D d_bodyConnectionPositions[Types::BC_NUM];

	std::map<unsigned, unsigned> d_playerUnums;

	std::map<unsigned, unsigned> d_opponentUnums;

	double d_firstTime;
	unsigned int d_numMsgReceived;

	double d_bodyPartPeakTime1[Types::NBODYPARTS];
	double d_bodyPartPeakTime2[Types::NBODYPARTS];
	double d_bodyPartPeakTime3[Types::NBODYPARTS];
	double d_bodyPartPeakTime4[Types::NBODYPARTS];

	bool d_isUnstable[Types::NBODYPARTS];
	Vector3D d_lastBodyPartPos[Types::NBODYPARTS]; // 2 count mae

	bool d_freeze;
	bool d_visionUpdated;

	// target angle of head(camera)
	double d_neck; // horizontal
	double d_head; // vertical

	// whether camera angle update or not
	bool d_neckDirUpdate;

	int d_onFeetCount;
	int d_onLeftLeg;
	int d_onRightLeg;

	// say and hear
	double d_hearTime[3];
	double d_hearDirection[3];
	std::string d_hearMessage[3];

	KPBlockDirection d_KP_blocking;
	bool d_KP_positioning;
	double d_KP_startBlockTime;
	//Vector4D d_relativeFieldPlane;

	bool d_AT_attacking;

	// should searching motion
	bool d_searching;

	// current position cant be calculated
	bool d_negativePosition;

	// which side to round the ball (default: NO_SIDE)
	Side d_roundDirection;

	//Test is the boal is on our side of the field
	bool d_ballOnOurSide;

	//0 = team; 1=opponent
	//sort player from shortest distance to the ball the longest.
	int sortDistPlayerBall[6][2];
	//sort players (begining by me) by their distance to me
	int sortDistPlayerPlayer[12];
	//unum of the closest player to the ball
	int closestPlayer[2];
	//distance of the closest player to the ball
	float closestPlayerDist[2];
	//distances from player to ball by unum
	float distToBall[6][2];
	//distances from me of players by unum
	//unum=0-5 -> team; unum=6-11 -> opponent
	float distToPlayer[12];
	//distance of team players from the goal
	float distToGoal[6];
	//sort player from the shortest distance to the goal to the longest.
	int sortDistPlayerGoal[6];
	//store angle of players to xAxis
	float d_angleToPlayer[12];
	//zone where the ball is situated regarding player X-axis
	Zone d_ballZone;
	std::map<unsigned, Zone> d_playerZone;

	InfoID translateInfo(std::string const &name) {
		return s_infoMap[name];
	}

	Vector4F parseVect(rf<Predicate> const &pred) {
		assert(pred);

		Vector4F res;
		for (unsigned i = 0; i < pred->size(); ++i)
			res.set(i, *rf_cast<Predicate> (pred->getChild(i)));
		return res;
	}

	Vector4F parseScalar(rf<Predicate> const &pred) {
		Vector4F res;
		res.setX(*rf_cast<Predicate> (pred->getChild(0)));
		return res;
	}

	void destroy();

	static WorldModel *s_instance;
	static double s_fieldLength;
	static double s_fieldWidth;
	static double s_goalWidth;
	static std::map<unsigned, Types::PlayerType> s_playerTypeMap;

	void updateJoints();

	void updateVision();

	void updatePosture();

	void updateAttackerState();

	void updateNaoFRef();

	void updateDistances();

	void flagNaoToField();

	// bool canEstimateInvisibleObject();
	void convertToWorldCoord();
	void estimateInvisibleObject();
	void estimateInvisibleObjectFromUnit();

	WorldModel(SocketComm &comm);

	void initBodyPartPeakTime() {
		for (int i = 0; i < Types::NBODYPARTS; i++) {
			d_bodyPartPeakTime1[i] = 0;
			d_bodyPartPeakTime2[i] = 0;
			d_bodyPartPeakTime3[i] = 0;
			d_bodyPartPeakTime4[i] = 0;
			d_isUnstable[i] = false;
		}
	}

	void updateBodyPartPeakTime(Types::BodyPart bp);

	void checkStability(Types::BodyPart bp);

	void updateNeckDir();

	// for debugger
	std::string d_debugMessage[DM_NUM];
	std::vector<Vector3D> d_debugPoint;
	std::multimap<Vector3D, std::string> d_debugPointl;
	std::multimap<Vector3D, double> d_debugCircle;
	std::multimap<Vector3D, Vector3D> d_debugLine;

	void initDebugMessage() {
		for (int i = 0; i < DM_NUM; i++) {
			d_debugMessage[i] = "";
		}
		d_debugMessage[BEHAVIOR] = "behavior";
		d_debugPoint.clear();
		d_debugPointl.clear();
		d_debugCircle.clear();
		d_debugLine.clear();
	}

public:

	static FBB::StringCaseHash<InfoID> s_infoMap;
	static FBB::StringCaseHash<PlayMode> s_playModeMap;

	/**
	 *  The WorldModel is a Singleton, first call this method to initialize it!
	 */
	static void initialize(SocketComm &comm);

	/**
	 *  Use this to get an instance of the WorldModel.
	 */
	static WorldModel &getInstance();

	~WorldModel() {
		destroy();
	}

	/**
	 *   Integrates the predicate into the world model.
	 */
	void intergrate(rf<Predicate> const &pred);

	/**
	 *  @returns the current simulation time.
	 */
	float getTime() const {
		return d_time;
	}

	/**
	 *  Sets the team name, which is used later on to identify which player
	 *  is our and which player is theirs.
	 */
	void setTeamName(std::string const &name) {
		d_teamName = name;
	}

	/**
	 *  @returns our team name.
	 */
	std::string getTeamName() const {
		return d_teamName;
	}

	/**
	 *  @returns the value of the world element with id.
	 */
	Vector4F const &get(InfoID id) const {
		return d_info[id];
	}

	/**
	 *  @returns the gamestate
	 */
	PlayMode const &getPlayMode() const {
		//TODO create sensible return value
		return d_playMode;
	}

	std::string const getPlayModeString() const {
		return d_playModeString;
	}

	Side const &getSide() const {
		return d_team;
	}

	/**
	 * @returns the position of object object relative to the agent
	 */
	NormalDistribution3D getObjectPosition(Types::Object object) {
		// if( d_worldCoordAvailable )
		return d_objectPositionsW[object];
		// return d_objectPositions[object];
	}

	NormalDistribution3D getObjectLocalPosition(Types::Object object) {
		return d_objectPositions[object];
	}

	bool worldCoordAvailable() {
		return d_worldCoordAvailable;
	}

	bool allObjectPosAvailable() {
		return d_allObjectPosAvailable;
	}

	/**
	 * @returns the vector of object object relative to the agent
	 */
	NormalDistribution3D getObjectVector(Types::Object object) {
		return d_objectSpeeds[object];
	}

	/**
	 *  @returns the game time when an object was last updated.
	 */
	double getObjectLastUpdate(Types::Object object) {
		return d_lastVisionUpdate[object];
	}

	/**
	 *  @returns true if an object is updated within the last two time steps.
	 *
	 *  Use this to check if the object information is still current.
	 */
	bool isObjectAlive(Types::Object object) {
		return d_lastVisionUpdate[object] >= d_time - 2 * d_timeStep;
	}

	/**
	 *  @returns the current game time.
	 */
	double getGameTime() const {
		return d_gameTime;
	}

	/**
	 *  @returns the previous game time.
	 */
	double getPrevGameTime() const {
		return d_prevGameTime;
	}

	/**
	 *  @returns the amount of time between the previous and the current game time.
	 */
	double getTimeStep() const {
		return d_timeStep;
	}

	/**
	 * @returns The normal vector of the field relative to our torso
	 */
	Vector3D getFieldNormal() {
		return d_fieldNormal;
	}

	/**
	 * @returns The distance of the center of the torso to the field
	 * ** unavirable on server0.6.4
	 */
	double getDistToField() {
		return d_distToField;
	}

	/**
	 * @returns The current gyro measurement
	 */
	Vector3D getGyro() {
		return d_gyro;
	}

	Vector3D getAcceleration() {
		return d_acceleration;
	}

	// for GA (this function cannot use in competition)
	Vector3D getMyPos() {
		return d_myPos;
	}

	/**
	 *  @returns the force vector of the force perceptor on the left foot
	 */
	Vector3D getForceLeftFoot() {
		return d_footForces[0];
	}

	/**
	 *  @returns the force vector of the force perceptor on the right foot
	 */
	Vector3D getForceRightFoot() {
		return d_footForces[1];
	}

	/**
	 *  @returns the center of force on the left foot
	 */
	Vector3D getForceContactLeftFoot() {
		return d_footForceContacts[0];
	}

	/**
	 *  @returns the center of force on the right foot
	 */
	Vector3D getForceContactRightFoot() {
		return d_footForceContacts[1];
	}

	/**
	 * @returns The first time recieved by the server ever
	 */
	double getFirstTime() {
		return d_firstTime;
	}

	/// \todo Can this be removed?
	unsigned testFindID(std::string const &name) {
		return translateInfo(name);
	}

	/**
	 * Update the world model. This updates the SocketComm, reads all messages and integrates them into the model.
	 */
	void update();

	/**
	 *  @returns our unum (player number within our team).
	 */
	unsigned getUnum() const {
		return d_unum;
	}

	// returns teammate player ID of Object o
	unsigned getPlayerUnum(Types::Object o) {
		unsigned unum = 0;
		for (unsigned i = 1; i <= 11; i++) {
			if (d_playerUnums[i] - 1 + Types::PLAYER1 == o) {
				unum = i;
				break;
			}
		}
		return unum;
	}

	// returns opponent player ID of Object o
	unsigned getOpponentUnum(Types::Object o) {
		unsigned unum = 0;
		for (unsigned i = 1; i <= 11; i++) {
			if (d_opponentUnums[i] - 1 + Types::OPPONENT1 == o) {
				unum = i;
				break;
			}
		}
		return unum;
	}

	// returns player type from Object (Types::PLAYER*)
	Types::PlayerType getPlayerType(Types::Object o) {
		return s_playerTypeMap[getPlayerUnum(o)];
	}

	// returns player type from uniform number
	Types::PlayerType getPlayerType(int unum) {
		return s_playerTypeMap[unum];
	}

	//Return the position of a defender given its unum
	Vector3D getDefenderPosition(unsigned unum) {
		return getObjectPosition((Types::Object) (d_playerUnums[unum] - 1
				+ Types::PLAYER1)).getMu();
	}

	//Return the position of the further attackant from our goal
	Vector3D getFurtherAttackerPosition() {
		Vector3D goalPos = (d_objectPositionsW[Types::GOAL1US].getMu() + d_objectPositionsW[Types::GOAL2US].getMu())/2;

		Vector3D att1 = (d_objectPositionsW[d_playerUnums[2] - 1
				+ Types::PLAYER1]).getMu() - goalPos;
		att1.setZ(0);
		Vector3D att2 = (d_objectPositionsW[d_playerUnums[3] - 1
				+ Types::PLAYER1]).getMu() - goalPos;
		att2.setZ(0);
		double datt1 = att1.length();
		double datt2 = att2.length();

		if (datt1 > datt2)
			return att1;
		else
			return att2;
	}

	//Return the position of a player, given its unum
	//team 0 = player; team 1 = opponent
	Vector3D getPlayerByUnum(unsigned team, unsigned unum) {
		Vector3D pos(0, 0, 0);

		switch (team) {
		case 0:
			pos
					= (d_objectPositionsW[d_playerUnums[unum] - 1
							+ Types::PLAYER1]).getMu();
			break;
		case 1:
			pos = (d_objectPositionsW[d_opponentUnums[unum] - 1
					+ Types::OPPONENT1]).getMu();
			break;
		default:
			break;
		}

		return pos;
	}

	Vector3D getPlayerByUnum(unsigned unum) {
		if (unum < 1 || unum > 12)
			return Vector3D(0, 0, 0);
		if (unum < 7)
			return (d_objectPositionsW[d_playerUnums[unum] - 1 + Types::PLAYER1]).getMu();
		else
			return (d_objectPositionsW[d_opponentUnums[unum - 6] - 1
					+ Types::OPPONENT1]).getMu();
	}

	NormalDistribution3D getOpponentVectorByUnum(unsigned unum) {
		return d_objectSpeeds[d_opponentUnums[unum] - 1 + Types::OPPONENT1];
	}

	//indicates if the defender is visible or not
	bool visibleDefender(unsigned unum) {
		return visibleObject((Types::Object) (d_playerUnums[unum] - 1
				+ Types::PLAYER1));
	}

	//TODO to change with new functions
	//indicates if the distance between the ball and an enemy is inferior to 0.8
	bool enemyNearBall() {
		Vector3D distBall = getObjectPosition(Types::BALL).getMu();
		for (int i = Types::OPPONENT1; i <= Types::OPPONENT6; i++) {
			if (visibleObject((Types::Object) i)) {
				Vector3D distEnemy =
						getObjectPosition((Types::Object) i).getMu();
				if ((distBall - distEnemy).length() < 0.8)
					return true;
			}
		}
		return false;
	}

	//TODO but I don't know how for now
	//indicates if the ball is in the penalty area
	bool ballInPenaltyArea() {
		bool bou = false;
		return bou;
	}

	//TODO doesn't work for now
	Vector3D convertInFieldCoord(Types::Object o) {
		const Vector3F pos = getObjectPosition(o).getMu();
		Vector3F fn = d_transform * Vector4F(pos.getX(), pos.getY(),
				pos.getZ(), 1);

		return fn;
	}

	/**
	 *  Sets our unum.
	 */
	void setUnum(unsigned unum) {
		d_unum = unum;
	}

	/**
	 *  @returns the number of messages received by the agent.
	 */
	unsigned getNumMsgReceived() const {
		return d_numMsgReceived;
	}

	/**
	 *  @returns the angle of joint in radians (@see Types::Joint).
	 */
	NormalDistribution1D getJointAngle(Types::Joint joint) {
		return d_jointAngles[joint];
	}

	/**
	 *  @returns the rate of joint in radians (@see Types::Joint).
	 */
	NormalDistribution1D getJointRate(Types::Joint joint) {
		return d_jointRates[joint];
	}

	/**
	 *  @returns true when the agent lies on its belly.
	 */
	bool onMyBelly();

	/**
	 *  @returns true when the agent lies on its back.
	 */
	bool onMyBack();

	/**
	 *  @returns true when the agent stands on its feet.
	 */
	bool onMyFeet();

	/**
	 *  @returns true when the agent lies on one of its sides.
	 */
	bool onMySide();

	/**
	 *  Sets the angle constraints of joint to min and max.
	 */
	void setJointConstraints(Types::Joint joint, double min, double max) {
		d_jointConstraints[joint] = std::pair<double, double>(min, max);
	}

	/**
	 *  @returns the max angle of joint.
	 */
	double getJointMax(Types::Joint joint) {
		return d_jointConstraints[joint].second;
	}

	/**
	 *  @returns the min angle of joint.
	 */
	double getJointMin(Types::Joint joint) {
		return d_jointConstraints[joint].first;
	}

	Vector4F getBodyPartPosition(Types::BodyPart part) {
		return d_bodyPartPositions[part];
	}
	Vector3D getBodyConnectionPosition(Types::BodyConnection part) {
		return d_bodyConnectionPositions[part];
	}

	bool isUnstable(Types::BodyPart part) {
		return d_isUnstable[part];
	}

	bool shouldFreeze() {
		return d_freeze;
	}

	void setFreeze(bool f) {
		d_freeze = f;
	}

	Vector3D worldUnitX() {
		return d_worldUnitX;
	}
	Vector3D worldUnitY() {
		return d_worldUnitY;
	}

	double getLastVisionUpdateTime();

	bool visibleObject(Types::Object o) {
		if (d_lastVisionUpdate[o] + 0.06 > d_time)
			return true;
		return false;
	}

	int visibleLandmarkNum() {
		int num = 0;
		if (visibleObject(Types::FLAG1L))
			num++;
		if (visibleObject(Types::FLAG1R))
			num++;
		if (visibleObject(Types::FLAG2L))
			num++;
		if (visibleObject(Types::FLAG2R))
			num++;
		if (visibleObject(Types::GOAL1L))
			num++;
		if (visibleObject(Types::GOAL1R))
			num++;
		if (visibleObject(Types::GOAL2L))
			num++;
		if (visibleObject(Types::GOAL2R))
			num++;
		return num;
	}

	void setNeckDir(double n, double h) {
		d_neck = n;
		d_head = h;
		std::stringstream ss;
		ss << "Neck=" << n << ", Head=" << h;
		addDebugMessage(COMMENT, ss.str());
	}

	void setNeckDirUpdate(bool up) {
		up ? addDebugMessage(COMMENT, " neckUpdate=true ") : addDebugMessage(
				COMMENT, " neckUpdate=false ");
		d_neckDirUpdate = up;
	}

	double getHearTime(int n) {
		if (n > 2 || n < 0) {
			std::cerr << "WorldModel::getHearTime  argument invalid"
					<< std::endl;
			return -1;
		}
		return d_hearTime[n];
	}

	double getHearDirection(int n) {
		if (n > 2 || n < 0) {
			std::cerr << "WorldModel::getHearDirection  argument invalid"
					<< std::endl;
			return -1;
		}
		return d_hearDirection[n];
	}

	std::string getHearMessage(int n) {
		if (n > 2 || n < 0) {
			std::cerr << "WorldModel::getHearMessage  argument invalid"
					<< std::endl;
			return "";
		}
		return d_hearMessage[n];
	}

	void sayMessage(std::string message);
	/*
	 void sendDebugMessage(std::string filename){
	 std::ofstream ofs(filename.c_str(), std::ios::app);
	 for(int i=0;i<DM_NUM;i++)
	 {
	 ofs << d_debugMessage[i];
	 if((DebugMessage)i == BEHAVIOR)
	 ofs << " end";
	 ofs << std::endl;
	 }
	 ofs.close();
	 }
	 */

	// for debugger
	std::string getDebugMessage(DebugMessage dm) {
		return d_debugMessage[dm];
	}

	std::string getDebugDrawMessage() {
		std::string mes = "";
		std::stringstream ss;
		// point
		for (int i = 0; i < d_debugPoint.size(); i++) {
			ss.str("");
			ss << " point " << d_debugPoint.at(i).getX() << " "
					<< d_debugPoint.at(i).getY() << " "
					<< d_debugPoint.at(i).getZ();
			mes += ss.str();
		}
		// point with label
		std::multimap<Vector3D, std::string>::iterator it0 =
				d_debugPointl.begin();
		while (it0 != d_debugPointl.end()) {
			ss.str("");
			ss << " pointl " << (*it0).second << " " << (*it0).first.getX()
					<< " " << (*it0).first.getY() << " " << (*it0).first.getZ();
			mes += ss.str();
			it0++;
		}
		// circle
		std::multimap<Vector3D, double>::iterator it1 = d_debugCircle.begin();
		while (it1 != d_debugCircle.end()) {
			ss.str("");
			ss << " circle " << (*it1).first.getX() << " "
					<< (*it1).first.getY() << " " << (*it1).first.getZ() << " "
					<< (*it1).second;
			mes += ss.str();
			it1++;
		}
		// line
		std::multimap<Vector3D, Vector3D>::iterator it2 = d_debugLine.begin();
		while (it2 != d_debugLine.end()) {
			ss.str("");
			ss << " line " << (*it2).first.getX() << " " << (*it2).first.getY()
					<< " " << (*it2).first.getZ() << " "
					<< (*it2).second.getX() << " " << (*it2).second.getY()
					<< " " << (*it2).second.getZ();
			mes += ss.str();

			it2++;
		}

		return mes;
	}

	void setDebugMessage(DebugMessage dm, std::string message) {
		d_debugMessage[dm] = " " + message + " ";
	}

	void addDebugMessage(DebugMessage dm, std::string message) {
		d_debugMessage[dm] += " " + message + " ";
	}

	void setDebugPoint(Vector3D point) {
		d_debugPoint.push_back(point);
	}

	void setDebugPointWithLabel(Vector3D point, std::string label) {
		d_debugPointl.insert(std::pair<Vector3D, std::string>(point, label));
	}

	void setDebugCircle(Vector3D centor, double r) {
		d_debugCircle.insert(std::pair<Vector3D, double>(centor, r));
	}

	void setDebugLine(Vector3D start, Vector3D end) {
		d_debugLine.insert(std::pair<Vector3D, Vector3D>(start, end));
	}

	// for keeper
	KPBlockDirection kpBlocking() {
		return d_KP_blocking;
	}
	void kpBlocking(KPBlockDirection blk) {
		d_KP_blocking = blk;
	}

	bool kpGoodPosition() {
		return d_KP_positioning;
	}
	void kpGoodPosition(bool gdpos) {
		d_KP_positioning = gdpos;
	}

	double kpStartBlockTime() {
		return d_KP_startBlockTime;
	}
	void kpStartBlockTimeUpdate() {
		d_KP_startBlockTime = d_time;
	}

	// for attacker
	bool getATattacking() {
		return d_AT_attacking;
	}

	bool getProcessingOppAttack() {
		return d_ballOnOurSide;
	}

	void setProcessingOppAttack(bool ballOnOurSide) {
		d_ballOnOurSide = ballOnOurSide;
	}

	// for camera moving
	bool nowSearching() {
		return d_searching;
	}
	void searching(bool s) {
		d_searching = s;
	}

	// field size
	double fieldLength() {
		return s_fieldLength;
	}
	double fieldWidth() {
		return s_fieldWidth;
	}
	double goalWidth() {
		return s_goalWidth;
	}

	void setFirst() {
		if (!isCheck) {
			std::cout << "on met tout à true" << std::endl;
			d_first = true;
			isCheck = true;
		}
	}

	// for GA
	double d_deadTime;
	double getDeadTime() {
		return d_deadTime;
	}
	void setDeadTime(double d) {
		d_deadTime = d;
	}

	int getClosestTeamUnum() {
		//std::cout << "getClosestTeamUnum " << closestPlayer[0] << std::endl;
		return closestPlayer[0];
	}

	int getClosestOpponentUnum() {
		//std::cout << "getClosestOpponentUnum " << closestPlayer[1] << std::endl;
		return closestPlayer[1];
	}

	float getClosestTeamDist() {
		//std::cout << "getClosestTeamDist " << closestPlayerDist[0] << std::endl;
		return closestPlayerDist[0];
	}

	float getClosestOpponentDist() {
		//std::cout << "getClosestOpponentDist " << closestPlayerDist[1] << std::endl;
		return closestPlayerDist[1];
	}

	int getSortedPlayerPlayerUnum(int place) {
		//std::cout << "getSortedPlayerPlayerUnum " << sortDistPlayerPlayer[place-1] << std::endl;
		return sortDistPlayerPlayer[place - 1];
	}

	int getSortedTeamBallUnum(int place) {
		//std::cout << "getSortedTeamBallUnum " << sortDistPlayerBall[place-1][0] << std::endl;
		return sortDistPlayerBall[place - 1][0];
	}

	int getSortedOpponentBallUnum(int place) {
		//std::cout << "getSortedOpponentBallUnum " << sortDistPlayerBall[place-1][1] << std::endl;
		return sortDistPlayerBall[place - 1][1];
	}

	float getTeamDistToBall(int unum) {
		//std::cout << "getTeamDistToBall " << distToBall[unum-1][0] << std::endl;
		return distToBall[unum - 1][0];
	}

	float getOpponentDistToBall(int unum) {
		//std::cout << "getOpponentDistToBall " << distToBall[unum-1][1] << std::endl;
		return distToBall[unum - 1][1];
	}

	//player: 0-5, opponent: 6-11
	float getPlayerDistToPlayer(int unum) {
		//std::cout << "getPlayerDistToPlayer " << distToPlayer[unum-1] << std::endl;
		return distToPlayer[unum - 1];
	}

	float getTeamDistToGoal(int unum) {
		//std::cout << "getTeamDistToGoal " << distToGoal[unum-1] << std::endl;
		return distToGoal[unum - 1];
	}

	int getSortedTeamGoalUnum(int place) {
		//std::cout << "getSortedTeamGoalUnum " << sortedDistPlayerGoal[place -1] << std::endl;
		return sortDistPlayerGoal[place - 1];
	}
	void setPlayersZone() {
		for (int i = 1; i < 12; i++) {
			if (d_angleToPlayer[i] < M_PI / 4
					&& getPlayerByUnum((unsigned) i).getX() > 0)
				d_playerZone[i] = NEAR_FRONT;
			else if (d_angleToPlayer[i] >= M_PI / 4 && getPlayerByUnum(
					(unsigned) i).getY() > 0)
				d_playerZone[i] = NEAR_LEFT;
			else if (d_angleToPlayer[i] >= M_PI / 4 && getPlayerByUnum(
					(unsigned) i).getY() < 0)
				d_playerZone[i] = NEAR_RIGHT;
			else if (d_angleToPlayer[i] < M_PI / 4 && getPlayerByUnum(
					(unsigned) i).getX() < 0)
				d_playerZone[i] = NEAR_BACK;
			else
				d_playerZone[i] = NOZONE;
		}
	}

	int getClosestZonePlayer(Zone myZone) {
    std::map<unsigned, Zone>::iterator it;
		float dist = 1000;
		int unum = -1;
		for (it = d_playerZone.begin(); it != d_playerZone.end(); it++) {
			float myDist = getPlayerByUnum((*it).first).length();
			if ((*it).second == myZone && myDist < dist) {
				dist = myDist;
				unum = (*it).first;
			}
		}
		return unum;
	}

	Zone getZone(Vector3D pos) {
		double angle = Vector3D(1, 0, 0).angle(pos);
		if (angle < M_PI / 4 && pos.getX() > 0)
			return NEAR_FRONT;
		if (angle >= M_PI / 4 && pos.getY() > 0)
			return NEAR_LEFT;
		if(angle  >= M_PI / 4 && pos.getY() < 0)
			return NEAR_RIGHT;
		if(angle < M_PI / 4 && pos.getX() < 0)
			return NEAR_BACK;
		return NOZONE;
	}

};

}
;

#endif // __INC_BATS_WORLDMODEL_HH_

#include "worldmodel.ih"

WorldModel *WorldModel::s_instance = 0;

FBB::StringCaseHash<WorldModel::InfoID> WorldModel::s_infoMap;
FBB::StringCaseHash<WorldModel::PlayMode> WorldModel::s_playModeMap;

void WorldModel::initialize(SocketComm &comm)
{
  if (s_instance)
    throw runtime_error("worldmodel was already initialized");

  s_infoMap["GS"] = WorldModel::iGameState;
  s_infoMap["unum"] = WorldModel::iUnum;
  s_infoMap["team"] = WorldModel::iTeam;
  s_infoMap["t"] = WorldModel::iGameTime;
  s_infoMap["pm"] = WorldModel::iPlayMode;
  s_infoMap["ax"            ] = WorldModel::iAxis        ;
  s_infoMap["ax1"           ] = WorldModel::iAxis1       ;
  s_infoMap["ax2"           ] = WorldModel::iAxis2       ;
  s_infoMap["B"             ] = WorldModel::iVisionBall  ;
  s_infoMap["F1L"           ] = WorldModel::iVisionFlag1L;
  s_infoMap["F1R"           ] = WorldModel::iVisionFlag1R;
  s_infoMap["F2L"           ] = WorldModel::iVisionFlag2L;
  s_infoMap["F2R"           ] = WorldModel::iVisionFlag2R;
  s_infoMap["G1L"           ] = WorldModel::iVisionGoal1L;
  s_infoMap["G1R"           ] = WorldModel::iVisionGoal1R;
  s_infoMap["G2L"           ] = WorldModel::iVisionGoal2L;
  s_infoMap["G2R"           ] = WorldModel::iVisionGoal2R;
  s_infoMap["HJ"            ] = WorldModel::iHJ          ;
//  s_infoMap["laj1_2"] = WorldModel::iLArmJoint1  ;
  s_infoMap["laj1"] = WorldModel::iLArmJoint1  ;
  s_infoMap["laj2"] = WorldModel::iLArmJoint2  ;
  s_infoMap["laj3"  ] = WorldModel::iLArmJoint3  ;
  s_infoMap["laj4"  ] = WorldModel::iLArmJoint4  ;
  s_infoMap["llj1"  ] = WorldModel::iLLegJoint1  ;
//  s_infoMap["llj2_3"] = WorldModel::iLLegJoint2  ;
  s_infoMap["llj2"] = WorldModel::iLLegJoint2  ;
  s_infoMap["llj3"] = WorldModel::iLLegJoint3  ;
  s_infoMap["llj4"  ] = WorldModel::iLLegJoint4  ;
//  s_infoMap["llj5_6"] = WorldModel::iLLegJoint5  ;
  s_infoMap["llj5"] = WorldModel::iLLegJoint5  ;
  s_infoMap["llj6"] = WorldModel::iLLegJoint6  ;
  s_infoMap["n"          ] = WorldModel::iName        ;
  s_infoMap["now"           ] = WorldModel::iNow         ;
//  s_infoMap["raj1_2"] = WorldModel::iRArmJoint1  ;
  s_infoMap["raj1"] = WorldModel::iRArmJoint1  ;
  s_infoMap["raj2"] = WorldModel::iRArmJoint2  ;
  s_infoMap["raj3"  ] = WorldModel::iRArmJoint3  ;
  s_infoMap["raj4"  ] = WorldModel::iRArmJoint4  ;
  s_infoMap["rt"          ] = WorldModel::iRate        ;
  s_infoMap["rate1"         ] = WorldModel::iRate1       ;
  s_infoMap["rate2"         ] = WorldModel::iRate2       ;
  s_infoMap["rlj1"  ] = WorldModel::iRLegJoint1  ;
//  s_infoMap["rlj2_3"] = WorldModel::iRLegJoint2  ;
  s_infoMap["rlj2"] = WorldModel::iRLegJoint2  ;
  s_infoMap["rlj3"] = WorldModel::iRLegJoint3  ;
  s_infoMap["rlj4"  ] = WorldModel::iRLegJoint4  ;
//  s_infoMap["rlj5_6"] = WorldModel::iRLegJoint5  ;
  s_infoMap["rlj5"] = WorldModel::iRLegJoint5  ;
  s_infoMap["rlj6"] = WorldModel::iRLegJoint6  ;
  s_infoMap["step"          ] = WorldModel::iStep        ;
  s_infoMap["time"          ] = WorldModel::iTime        ;
  s_infoMap["UJ"            ] = WorldModel::iUJ          ;
  s_infoMap["See"           ] = WorldModel::iVision      ;
  s_infoMap["GYR"           ] = WorldModel::iGyro        ;
  s_infoMap["torsogyro"     ] = WorldModel::iTorsoGyro   ;
  s_infoMap["TCH"           ] = WorldModel::iTouch       ;
  s_infoMap["lf"      ] = WorldModel::iFootLeft    ;
  s_infoMap["rf"     ] = WorldModel::iFootRight   ;
  s_infoMap["val"           ] = WorldModel::iVal         ;
  s_infoMap["FRP"] = WorldModel::iForceResistancePerceptor;
  s_infoMap["c"] = WorldModel::iContact;
  s_infoMap["f"] = WorldModel::iForce;
  s_infoMap["P"] = WorldModel::iP;
  
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

  s_playModeMap["BeforeKickOff"] = WorldModel::BEFORE_KICKOFF;
  s_playModeMap["KickOff_Left"] = WorldModel::KICKOFF_LEFT;
  s_playModeMap["KickOff_Right"] = WorldModel::KICKOFF_RIGHT;
  s_playModeMap["PlayOn"] = WorldModel::PLAY_ON;
  s_playModeMap["free_kick_left"] = WorldModel::FREEKICK_LEFT;
  s_playModeMap["free_kick_right"] = WorldModel::FREEKICK_RIGHT;
  s_playModeMap["Goal_Left"] = WorldModel::GOAL_LEFT;
  s_playModeMap["Goal_Right"] = WorldModel::GOAL_RIGHT;
  s_playModeMap["goal_kick_left"] = WorldModel::GOAL_KICK_LEFT;
  s_playModeMap["goal_kick_right"] = WorldModel::GOAL_KICK_RIGHT;
  s_playModeMap["corner_kick_left"] = WorldModel::CORNER_KICK_LEFT;
  s_playModeMap["corner_kick_right"] = WorldModel::CORNER_KICK_RIGHT;
  s_playModeMap["KickIn_Left"] = WorldModel::KICKIN_LEFT;
  s_playModeMap["KickIn_Right"] = WorldModel::KICKIN_RIGHT;
  
  s_instance = new WorldModel(comm);
}

WorldModel &WorldModel::getInstance()
{
	assert(s_instance);
  return *s_instance;
}

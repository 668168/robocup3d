#include "vd3connector.hh"

VD3Connector *VD3Connector::m_instance = 0;

map<VD3::MessageType, string> s_messageTypeMap;
map<VD3::JointType, string> s_jointTypeMap;
map<VD3::ObjectType, string> s_objectTypeMap;

void VD3Connector::initializeMap()
{
/*
  s_messageTypeMap[VD3::OBJECT] = "object";
  s_messageTypeMap[VD3::JOINT] = "joint";
  s_messageTypeMap[VD3::GAME_TIME] = "time";
  s_messageTypeMap[VD3::PLAY_MODE] = "playmode";
  s_messageTypeMap[VD3::GYRO] = "gyro";
  s_messageTypeMap[VD3::FIELD_NORMAL] = "fieldnormal";
  s_messageTypeMap[VD3::POINT] = "point";
  s_messageTypeMap[VD3::POINT_WITH_LABEL] = "pointl";
  s_messageTypeMap[VD3::CIRCLE] = "circle";
  s_messageTypeMap[VD3::LINE] = "line";
  s_messageTypeMap[VD3::BEHAVIOR] = "behavior";
  s_messageTypeMap[VD3::COMMENT_BEGIN] = "comment";
  s_messageTypeMap[VD3::COMMENT_END] = "commentend";

  s_messageTypeMap[VD3::SAY] = "say";
  s_messageTypeMap[VD3::HEAR] = "hear";

  s_jointTypeMap[VD3::NECK] = "hj1";
  s_jointTypeMap[VD3::HEAD] = "hj2";

  s_jointTypeMap[VD3::L_ARM1] = "laj1";
  s_jointTypeMap[VD3::L_ARM2] = "laj2";
  s_jointTypeMap[VD3::L_ARM3] = "laj3";
  s_jointTypeMap[VD3::L_ARM4] = "laj4";

  s_jointTypeMap[VD3::R_ARM1] = "raj1";
  s_jointTypeMap[VD3::R_ARM2] = "raj2";
  s_jointTypeMap[VD3::R_ARM3] = "raj3";
  s_jointTypeMap[VD3::R_ARM4] = "raj4";

  s_jointTypeMap[VD3::L_LEG1] = "llj1";
  s_jointTypeMap[VD3::L_LEG2] = "llj2";
  s_jointTypeMap[VD3::L_LEG3] = "llj3";
  s_jointTypeMap[VD3::L_LEG4] = "llj4";
  s_jointTypeMap[VD3::L_LEG5] = "llj5";
  s_jointTypeMap[VD3::L_LEG6] = "llj6";

  s_jointTypeMap[VD3::R_LEG1] = "rlj1";
  s_jointTypeMap[VD3::R_LEG2] = "rlj2";
  s_jointTypeMap[VD3::R_LEG3] = "rlj3";
  s_jointTypeMap[VD3::R_LEG4] = "rlj4";
  s_jointTypeMap[VD3::R_LEG5] = "rlj5";
  s_jointTypeMap[VD3::R_LEG6] = "rlj6";

  s_objectTypeMap[VD3::BALL] = "ball";

  s_objectTypeMap[VD3::FLAG1_RIGHT] = "flag1right";
  s_objectTypeMap[VD3::FLAG2_RIGHT] = "flag2right";
  s_objectTypeMap[VD3::FLAG1_LEFT] = "flag1left";
  s_objectTypeMap[VD3::FLAG2_LEFT] = "flag2left";

  s_objectTypeMap[VD3::GOAL1_RIGHT] = "goal1right";
  s_objectTypeMap[VD3::GOAL2_RIGHT] = "goal2right";
  s_objectTypeMap[VD3::GOAL1_LEFT] = "goal1left";
  s_objectTypeMap[VD3::GOAL2_LEFT] = "goal2left";

  s_objectTypeMap[VD3::TEAMMATE] = "teammate";

  s_objectTypeMap[VD3::OPPONENT] = "opponent";
*/
}

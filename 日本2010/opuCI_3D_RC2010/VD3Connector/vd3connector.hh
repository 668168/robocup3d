#ifndef VD3CONNECTOR_HH

#define VD3CONNECTOR_HH

#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include <map>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "vector3.hh"

using namespace std;

// for opuciplayer
using namespace bats;

class VD3
{
public :
  enum ObjectType
  {
    BALL,
    
    FLAG1_RIGHT,
    FLAG2_RIGHT,
    FLAG1_LEFT,
    FLAG2_LEFT,

    GOAL1_RIGHT,
    GOAL2_RIGHT,
    GOAL1_LEFT,
    GOAL2_LEFT,

    TEAMMATE,
    OPPONENT,

    ObjectNum
  };

  enum JointType
  {
    NECK,
    HEAD,

    L_ARM1,
    L_ARM2,
    L_ARM3,
    L_ARM4,

    R_ARM1,
    R_ARM2,
    R_ARM3,
    R_ARM4,

    L_LEG1,
    L_LEG2,
    L_LEG3,
    L_LEG4,
    L_LEG5,
    L_LEG6,

    R_LEG1,
    R_LEG2,
    R_LEG3,
    R_LEG4,
    R_LEG5,
    R_LEG6,

    JointNum
  };

  enum MessageType
  {
    OBJECT,
    JOINT,

    GAME_TIME,
    PLAY_MODE,

    GYRO,
    FIELD_NORMAL,

    POINT,
    POINT_WITH_LABEL,
    CIRCLE,
    LINE,

    BEHAVIOR,
    COMMENT_BEGIN,
    COMMENT_END,

    SAY,
    HEAR,

    MessageNum
  };
};

class VD3Connector
{
private :
  static VD3Connector* m_instance;
  int m_sock;
  unsigned m_port;
  string m_host;

  vector<string> m_messages;
  string m_message;
  string m_comment;

  bool m_connecting;

  VD3Connector();
  ~VD3Connector();
  void connection();


public :
  static VD3Connector* getInstance(){
    if(m_instance == 0)
      m_instance = new VD3Connector();
    return m_instance;
  }

  static map<VD3::MessageType, string> s_messageTypeMap;
  static map<VD3::JointType, string> s_jointTypeMap;
  static map<VD3::ObjectType, string> s_objectTypeMap;

  void initialize(unsigned port=8492, string host="127.0.0.1");
  void initializeMap();
  void initializeMessage(){
    m_message.clear();
    m_comment.clear();
  }

  void closeConnection();

/*
  void setMessage(VD3::MessageType type, string mes){
    m_message += " " + s_messageTypeMap[type] + " " + mes;
  }

  void setDoubleMessage(VD3::MessageType type, double d){
    stringstream ss;
    ss << d;
    m_message += " " + s_messageTypeMap[type] + " " + ss.str();
  }

  void setStringMessage(VD3::MessageType type, string str){
    setMessage(type, str);
  }

  void setVector3DMessage(VD3::MessageType type, Vector3D vec);
  void setVector3DMessage(VD3::MessageType type, double* vec){
    Vector3D v(vec[0], vec[1], vec[2]);
    setVector3DMessage(type, v);
  }

  void setPoint(Vector3D p, string label = "");
  void setPoint(double* p, string label = ""){
    Vector3D pv(p[0], p[1], p[2]);
    setPoint(pv, label);
  }

  void setCircle(Vector3D center, double r);
  void setCircle(double* center, double r){
    Vector3D c(center[0], center[1], center[2]);
    setCircle(c, r);
  }

  void setLine(Vector3D start, Vector3D end);
  void setLine(double* start, double* end){
    Vector3D s(start[0], start[1], start[2]);
    Vector3D e(end[0], end[1], end[2]);
    setLine(s, e);
  }
  void setLine(Vector3D start){
    setLine(start, Vector3D(0, 0, 0));
  }
  void setLine(double* start){
    Vector3D s(start[0], start[1], start[2]);
    Vector3D e(0,0,0);
    setLine(s, e);
  }

  void setComment(string str){
    m_comment += " " + str + " ";
  }
  void setComment(stringstream ss){
    setComment(ss.str());
  }

  void setJointAngle(VD3::JointType type, double angle){
    stringstream ss;
    ss << angle;
    m_message += " " + s_jointTypeMap[type] + " " + ss.str();
  }

  void setObjectPosition(VD3::ObjectType type, bool inSight, Vector3D pos);

  void sendMessage();
*/
  void sendMessage(string mes);
};

#endif

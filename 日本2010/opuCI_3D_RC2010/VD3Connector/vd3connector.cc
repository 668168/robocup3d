#include "vd3connector.hh"

string vec3D2str(Vector3D v)
{
  stringstream ss;
  ss << v.getX() << " " << v.getY() << " " << v.getZ();
  return ss.str();
}

VD3Connector::VD3Connector()
  : m_port(8492),
    m_host("127.0.0.1"),
    m_connecting(false)
{}

VD3Connector::~VD3Connector()
{
  closeConnection();
}

void VD3Connector::initialize(unsigned port, string host)
{
  m_port = port;
  m_host = host;

  initializeMap();
  initializeMessage();
  connection();
}

void VD3Connector::connection()
{
  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons( m_port );
  addr.sin_addr.s_addr = inet_addr( m_host.c_str() );
  m_sock = socket(AF_INET, SOCK_STREAM, 0);

  if(connect(m_sock, (struct sockaddr *)&addr, sizeof(addr))<0)
  {
    cerr << "connection failed!!" << endl;
    m_connecting = false;
    return;
  }
  else
  {
    m_connecting = true;
    cerr << "connection =>" << endl;
  }
}

void VD3Connector::closeConnection()
{
  close(m_sock);
  m_connecting = false;
}

void VD3Connector::sendMessage(string mes)
{
  if( !m_connecting )
    return;

  write(m_sock, mes.c_str(), mes.length());

}
/*
void VD3Connector::sendMessage()
{
  if( !m_connecting )
    return;

  string mes = m_message + " "
    + s_messageTypeMap[VD3::COMMENT_BEGIN] + " "
    + m_comment + " "
    + s_messageTypeMap[VD3::COMMENT_END] + "\n";

  sendMessage(mes);
  m_messages.push_back(mes);

  initializeMessage();
}

void VD3Connector::setVector3DMessage(VD3::MessageType type, Vector3D vec)
{
  m_message += " " + s_messageTypeMap[type] + " " + vec3D2str(vec);
}

void VD3Connector::setPoint(Vector3D p, string label)
{
  if( label.empty() )
    m_message += s_messageTypeMap[VD3::POINT];
  else
    m_message += s_messageTypeMap[VD3::POINT_WITH_LABEL]
      + " " + label;

  m_message += " " + vec3D2str(p);

}

void VD3Connector::setCircle(Vector3D center, double r)
{
  stringstream ss;
  ss << r;
  m_message += s_messageTypeMap[VD3::CIRCLE]
    + " " + vec3D2str(center) + " " + ss.str();
}

void VD3Connector::setLine(Vector3D start, Vector3D end)
{
  m_message += s_messageTypeMap[VD3::LINE]
    + " " + vec3D2str(start) + " " + vec3D2str(end);

}

void VD3Connector::setObjectPosition(VD3::ObjectType type, bool inSight, Vector3D pos)
{
  m_message += s_objectTypeMap[type];

  if( inSight )
    m_message += " true ";
  else
    m_message += " false ";

  m_message += vec3D2str(pos);

}
*/

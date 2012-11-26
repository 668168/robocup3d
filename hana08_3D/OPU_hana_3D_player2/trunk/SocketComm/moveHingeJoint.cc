#include "socketcomm.ih"

void SocketComm::moveHingeJoint(Types::Joint joint, double deltaAngle)
{
  send(makeMoveHingeJointMessage(joint, deltaAngle));

}

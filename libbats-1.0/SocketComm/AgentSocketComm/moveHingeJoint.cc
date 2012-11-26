#include "agentsocketcomm.ih"

void AgentSocketComm::moveHingeJoint(Types::Joint joint, double deltaAngle)
{
  send(makeMoveHingeJointMessage(joint, deltaAngle));
}

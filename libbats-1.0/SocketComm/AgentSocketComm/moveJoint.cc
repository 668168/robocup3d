#include "agentsocketcomm.ih"

void AgentSocketComm::moveJoint(Types::Joint joint, double deltaAngle)
{
  send(makeMoveJointMessage(joint, deltaAngle));
}

rf<Predicate> AgentSocketComm::makeMoveJointMessage(Types::Joint joint, double deltaAngle)
{
  AgentModel& am = SAgentModel::getInstance();

  rf<Predicate> msg;
  
  rf<AgentModel::Joint> j = am.getJoint(joint);
  if (j->universal)
    if (j->ujindex == 0)
      msg = makeMoveUniversalJointMessage(joint, deltaAngle, 0);
    else
      msg = makeMoveUniversalJointMessage(joint, 0, deltaAngle);
  else
    msg = makeMoveHingeJointMessage(joint, deltaAngle);

  return msg;
}

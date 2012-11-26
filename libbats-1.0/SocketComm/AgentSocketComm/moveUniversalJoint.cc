#include "agentsocketcomm.ih"

void AgentSocketComm::moveUniversalJoint(Types::Joint joint, double deltaAngle1, double deltaAngle2)
{
  send(makeMoveUniversalJointMessage(joint, deltaAngle1, deltaAngle2));
}

rf<Predicate> AgentSocketComm::makeMoveUniversalJointMessage(Types::Joint joint, double deltaAngle1, double deltaAngle2)
{
  AgentModel& am = SAgentModel::getInstance();
  
  deltaAngle1 = deltaAngle1 / M_PI * 180.0;
  deltaAngle2 = deltaAngle2 / M_PI * 180.0;

  rf<Predicate> message = new Predicate("", Predicate::type_list);
  rf<Predicate>  pred = message->push(new Predicate(am.getJoint(joint)->effector));
  pred->pushLeaf(deltaAngle1);
  pred->pushLeaf(deltaAngle2);
  
  _debugLevel4(*message);
  
  return message;
}

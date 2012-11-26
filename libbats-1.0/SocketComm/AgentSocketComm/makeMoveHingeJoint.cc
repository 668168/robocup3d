#include "agentsocketcomm.ih"
rf<Predicate> AgentSocketComm::makeMoveHingeJointMessage(Types::Joint joint, double deltaAngle)
{
  AgentModel& am = SAgentModel::getInstance();

  deltaAngle = deltaAngle / M_PI * 180.0;
  
  rf<Predicate> message = new Predicate("", Predicate::type_list);
  rf<Predicate> pred = message->push(new Predicate(am.getJoint(joint)->effector));
  pred->pushLeaf(deltaAngle);

  return message;  
}

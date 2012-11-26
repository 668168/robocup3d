#include "socketcomm.ih"

rf<Predicate> SocketComm::makeMoveHingeJointMessage(Types::Joint joint, double deltaAngle)
{
  deltaAngle = deltaAngle / M_PI * 180.0;
  WorldModel& wm = WorldModel::getInstance();
  
  rf<Predicate> message = new Predicate("", Predicate::type_list);
  rf<Predicate> jointname = new Predicate(s_jointNames[joint]);
  rf<Predicate> pred = message->push(jointname);
  pred->pushLeaf(deltaAngle);


  return message;  
}

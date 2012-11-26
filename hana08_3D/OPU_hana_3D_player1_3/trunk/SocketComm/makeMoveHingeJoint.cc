#include "socketcomm.ih"

rf<Predicate> SocketComm::makeMoveHingeJointMessage(Types::Joint joint, double deltaAngle)
{
  deltaAngle = deltaAngle / M_PI * 180.0;
  WorldModel& wm = WorldModel::getInstance();
  
  rf<Predicate> message = new Predicate("", Predicate::type_list);
  rf<Predicate> jointname = new Predicate(s_jointNames[joint]);
  rf<Predicate> pred = message->push(jointname);
  pred->pushLeaf(deltaAngle);

/*
  std::cout << "makeMoveHingeJointMessage::jointname=" << s_jointNames[joint] << ", deltaAngle=" << deltaAngle << std::endl;
//  std::cout << "makeMoveHingeJointMessage::message:: makeMoveHingeJoint" << *message << std::endl;
  std::cout << "Joint " << s_jointNames[joint] << " Angle..." // << wm.getJointAngle(joint) 
	    << wm.getJointAngle(joint).getSigma() << ":" << wm.getJointAngle(joint).getMu() << std::endl;
*/

  return message;  
}

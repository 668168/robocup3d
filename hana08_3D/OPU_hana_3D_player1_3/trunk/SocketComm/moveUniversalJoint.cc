#include "socketcomm.ih"

void SocketComm::moveUniversalJoint(Types::Joint joint, double deltaAngle1, double deltaAngle2)
{
    send(makeMoveUniversalJointMessage(joint, deltaAngle1, deltaAngle2));
}


rf<Predicate> SocketComm::makeMoveUniversalJointMessage(Types::Joint joint, double deltaAngle1, double deltaAngle2)
{

  deltaAngle1 = deltaAngle1 / M_PI * 180.0;
  deltaAngle2 = deltaAngle2 / M_PI * 180.0;
  WorldModel& wm = WorldModel::getInstance();
  std::string jointName = s_jointNames[joint];
  rf<Predicate> message = new Predicate("", Predicate::type_list);
//  rf<Predicate>  pred = message->push(new Predicate(jointName));
//  pred->pushLeaf(deltaAngle1);
//  pred->pushLeaf(deltaAngle2);

  if(jointName == "lle2_3")
  {
      rf<Predicate> pred1 = message->push(new Predicate("lle2"));
      pred1->pushLeaf(deltaAngle1);
      rf<Predicate> pred2 = message->push(new Predicate("lle3"));
      pred2->pushLeaf(deltaAngle2);
//      std::cout << "moveUniversalJoint::jointName=" << jointName << ", deltaAngle1=" << deltaAngle1 << ", deltaAngle2=" << deltaAngle2 << std::endl; 
  }
  else if(jointName == "rle2_3")
  {
      rf<Predicate> pred1 = message->push(new Predicate("rle2"));
      pred1->pushLeaf(deltaAngle1);
      rf<Predicate> pred2 = message->push(new Predicate("rle3"));
      pred2->pushLeaf(deltaAngle2);
//      std::cout << "moveUniversalJoint::jointName=" << jointName << ", deltaAngle1=" << deltaAngle1 << ", deltaAngle2=" << deltaAngle2 << std::endl; 
  }
  else if(jointName == "lle5_6")
  {
      rf<Predicate> pred1 = message->push(new Predicate("lle5"));
      pred1->pushLeaf(deltaAngle1);
      rf<Predicate> pred2 = message->push(new Predicate("lle6"));
      pred2->pushLeaf(deltaAngle2);
//      std::cout << "moveUniversalJoint::jointName=" << jointName << ", deltaAngle1=" << deltaAngle1 << ", deltaAngle2=" << deltaAngle2 << std::endl; 
  }
  else if(jointName == "rle5_6")
  {
      rf<Predicate> pred1 = message->push(new Predicate("rle5"));
      pred1->pushLeaf(deltaAngle1);
      rf<Predicate> pred2 = message->push(new Predicate("rle6"));
      pred2->pushLeaf(deltaAngle2);
//      std::cout << "moveUniversalJoint::jointName=" << jointName << ", deltaAngle1=" << deltaAngle1 << ", deltaAngle2=" << deltaAngle2 << std::endl; 
  }
  else if(jointName == "lae1_2")
  {
      rf<Predicate> pred1 = message->push(new Predicate("lae1"));
      pred1->pushLeaf(deltaAngle1);
      rf<Predicate> pred2 = message->push(new Predicate("lae2"));
      pred2->pushLeaf(deltaAngle2);
//     std::cout << "moveUniversalJoint::jointName=" << jointName << ", deltaAngle1=" << deltaAngle1 << ", deltaAngle2=" << deltaAngle2 << std::endl; 
  }
  else if(jointName == "rae1_2")
  {
      rf<Predicate> rarm1 = new Predicate("rae1");
      rf<Predicate> pred1 = message->push(rarm1);
      pred1->pushLeaf(deltaAngle1);
      rf<Predicate> rarm2 = new Predicate("rae2");
      rf<Predicate> pred2 = message->push(rarm2);
      pred2->pushLeaf(deltaAngle2);
//      std::cout << "moveUniversalJoint::jointName=" << jointName << ", deltaAngle1=" << deltaAngle1 << ", deltaAngle2=" << deltaAngle2 << std::endl; 
  }


  if(jointName == "lle2" || jointName == "lle5" || jointName == "lae1" || jointName == "rle2" || jointName == "rle5" || jointName == "rae1")
  {
        rf<Predicate>  pred1 = message->push(new Predicate(jointName));
	pred1->pushLeaf(deltaAngle1);
//	std::cout << "moveUniversalJoint:(1): jointName=" << jointName << ", deltaAngle1=" << deltaAngle1 << ", deltaAngle2=" << deltaAngle2 << std::endl; 
  }
  else if(jointName == "lle3" || jointName == "lle6" || jointName == "lae2" || jointName == "rle3" || jointName == "rle6" || jointName == "rae2")
  {
      rf<Predicate>  pred1 = message->push(new Predicate(jointName));
      pred1->pushLeaf(deltaAngle2);
//      std::cout << "moveUniversalJoint:(2): jointName=" << jointName << ", deltaAngle1=" << deltaAngle1 << ", deltaAngle2=" << deltaAngle2 << std::endl; 
  }

  _debugLevel4(*message);
//  std::cout << "makeMoveUniversalJoint::message :" << *message << std::endl;
//  std::cout << "Joint " << jointName << " Angle..." // << wm.getJointAngle(joint) 
//	    << wm.getJointAngle(joint).getSigma() << ":" << wm.getJointAngle(joint).getMu() << std::endl;
  
  return message;
}

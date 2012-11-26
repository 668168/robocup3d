#include "socketcomm.ih"

void SocketComm::moveJoint(Types::Joint joint, double deltaAngle)
{
  send(makeMoveJointMessage(joint, deltaAngle));
}

rf<Predicate> SocketComm::makeMoveJointMessage(Types::Joint joint, double deltaAngle)
{
  rf<Predicate> msg;

// ----------- enhanced ------------
// ダメだった. てかココに来てないみたい
//  msg = makeMoveHingeJointMessage(joint, deltaAngle);

// ----------- /enhanced -----------


// ----------- original ------------

  switch (joint)
  {
    case Types::HEAD_1:
    case Types::LLEG1:
    case Types::LLEG4:
    case Types::RLEG1:
    case Types::RLEG4:
    case Types::LARM3:
    case Types::LARM4:
    case Types::RARM3:
    case Types::RARM4:
      msg = makeMoveHingeJointMessage(joint, deltaAngle);
      break;
    
    case Types::LLEG2:
    case Types::LLEG5:
    case Types::RLEG2:
    case Types::RLEG5:
    case Types::LARM1:
    case Types::RARM1:
      msg = makeMoveUniversalJointMessage(joint, deltaAngle, 0);
      break;
    
    case Types::LLEG3:
    case Types::LLEG6:
    case Types::RLEG3:
    case Types::RLEG6:
    case Types::LARM2:
    case Types::RARM2:
      msg = makeMoveUniversalJointMessage(joint, 0, deltaAngle);
      break;

  case Types::NJOINTS:
    break;
  }

// ------------- /original -------------
  
  std::cout << "moveJoint::msg : " << *msg << std::endl;

  return msg;
}

#include "cerebellum.hh"

#define DEBUGLEVEL 0
#include "debug.hh"

#include <numeric>

using namespace bats;
using namespace std;

void Cerebellum::outputCommands(SocketComm& comm)
{
  rf<Action> actions[Types::NJOINTS];
  double counts[Types::NJOINTS];
  
  memset(reinterpret_cast<char*>(counts), 0, Types::NJOINTS * sizeof(double));

  rf<MoveJointAction> mja;
  //rf<MoveHingeJointAction> mhja;
  //rf<MoveUniversalJointAction> muja;
  rf<BeamAction> ba;

  for (vector<rf<Action> >::iterator iter = d_actions.begin(); iter != d_actions.end(); ++iter)
  {
    _debugLevel4("action type: " << (*iter)->type);
//    std::cout << "action type: " << (*iter)->type << std::endl;
    
    switch ((*iter)->type)
    {
      case Action::MOVEJOINT:
        mja = rf_cast<MoveJointAction>(*iter);
      	_debugLevel4("joint: " << (int)mja->joint << " " << mja->speed);
//	std::cout << "joint: " << (int)(mja->joint) << ", spd: " << mja->speed;
        if (!actions[mja->joint])
        {
          actions[mja->joint] = mja;
          counts[mja->joint] = 1;
        }
        else
        {
          rf_cast<MoveJointAction>(actions[mja->joint])->speed += mja->speed;
          counts[mja->joint]++;
//	  std::cout << "counts++!!";
//	  int num;
//	  std::cin >> num;
//	  std::cout << num;
        }
//	std::cout << "| counts[" << (int)(mja->joint) << "] = " << counts[mja->joint] << std::endl; 
        break;
        
      case Action::BEAM:
        ba = rf_cast<BeamAction>(*iter);
        _debugLevel4("beam: " << ba->pos);	
//	std::cout << "beam to " << ba->pos << std::endl;
        comm.beam(ba->pos);
        break;
        
      default:
        break;
    }
  }
  
  ostringstream msg;
  double speed1 = 0, speed2 = 0;
//  std::cout << "Types::NJOINTS = " << Types::NJOINTS << std::endl;
  for (unsigned i = 0; i < Types::NJOINTS; ++i)
  {
    speed1 = speed2 = 0;
    Types::Joint joint = (Types::Joint)i;

    if (Types::isUniversalJoint(joint))
    {
      bool moveIt = false;
      if (actions[i])
      {

        speed1 = rf_cast<MoveJointAction>(actions[i])->speed / counts[i];
//	std::cout << "joint:" << i << ", spd1:" << speed1 << std::endl;
        moveIt = true;
      }
      ++i;
      if (actions[i])
      {
        speed2 = rf_cast<MoveJointAction>(actions[i])->speed / counts[i];
//	std::cout << "joint:" << i << ", spd2:" << speed2 << std::endl;
        moveIt = true;

      }
      if (moveIt)
      {
        _debugLevel4("speed: " << speed1);
        _debugLevel4("speed: " << speed2);
//	std::cout << "joint=" << joint << ", speed1: " 
//		  << speed1 << ", speed2: " << speed2 << std::endl;
        comm.moveUniversalJoint(joint, speed1, speed2);
        comm.moveUniversalJoint((Types::Joint)(joint+1), speed1, speed2);
      }
    }
    else
    {

      Types::Joint joint = (Types::Joint)i;
      if (actions[i])
      {
//	  std::cout << "joint=" << i << ", speed: " 
//		    << rf_cast<MoveJointAction>(actions[i])->speed 
//		    << ", counts[i]: " << counts[i] << std::endl;
        speed1 = rf_cast<MoveJointAction>(actions[i])->speed / counts[i];
        _debugLevel4("speed: " << speed1);
        comm.moveHingeJoint(joint, speed1);
      }
    }
 //    int nm;
//     std::cin >> nm;
//     std::cout << nm << std::endl;
  }
  d_actions.clear();
}

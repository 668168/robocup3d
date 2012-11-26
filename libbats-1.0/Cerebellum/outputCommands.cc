#include "cerebellum.ih"

void Cerebellum::outputCommands(AgentSocketComm& comm)
{
  rf<Action> actions[Types::NJOINTS];
  double counts[Types::NJOINTS];
  
  memset(reinterpret_cast<char*>(counts), 0, Types::NJOINTS * sizeof(double));

  rf<MoveJointAction> mja;
  //rf<MoveHingeJointAction> mhja;
  //rf<MoveUniversalJointAction> muja;
  rf<BeamAction> ba;

  string sayMessage = "";
  
  for (vector<rf<Action> >::iterator iter = d_actions.begin(); iter != d_actions.end(); ++iter)
  {
    _debugLevel4("action type: " << (*iter)->type);
    
    switch ((*iter)->type)
    {
      case Action::MOVEJOINT:
        mja = rf_cast<MoveJointAction>(*iter);
      	_debugLevel4("joint: " << (int)mja->joint << " " << mja->speed);
        if (!actions[mja->joint])
        {
          actions[mja->joint] = mja;
          counts[mja->joint] = 1;
        }
        else
        {
          rf_cast<MoveJointAction>(actions[mja->joint])->speed += mja->speed;
          counts[mja->joint]++;
        }
        break;
        
      case Action::BEAM:
        ba = rf_cast<BeamAction>(*iter);
        _debugLevel4("beam: " << ba->pos);
        comm.beam(ba->pos);
        break;
      
      case Action::SAY:
        sayMessage += rf_cast<SayAction>(*iter)->message;
        break;
        
      default:
        break;
    }
  }
  
  ostringstream msg;
  double speed1 = 0, speed2 = 0;
  AgentModel& am = SAgentModel::getInstance();
  
  for (unsigned i = 0; i < Types::NJOINTS; ++i)
  {
    speed1 = speed2 = 0;
    Types::Joint joint = (Types::Joint)i;
    _debugLevel4(joint << " " << am.getJoint(joint));
    if (am.getJoint(joint))
    {
      if (am.getJoint(joint)->universal)
      {
        bool moveIt = false;
        if (actions[i])
        {
          speed1 = rf_cast<MoveJointAction>(actions[i])->speed;// / counts[i];
          moveIt = true;
        }
        ++i;
        if (actions[i])
        {
          speed2 = rf_cast<MoveJointAction>(actions[i])->speed;// / counts[i];
          _debugLevel4("speed: " << speed2);
          moveIt = true;
        }
        if (true || moveIt)
        {
          _debugLevel4("speed: " << speed1);
          _debugLevel4("speed: " << speed2);
          comm.moveUniversalJoint(joint, speed1, speed2);
        }
      }
      else
      {
        Types::Joint joint = (Types::Joint)i;
        if (actions[i])
        {
          speed1 = rf_cast<MoveJointAction>(actions[i])->speed;// / counts[i];
          _debugLevel4("speed: " << speed1);
        }
        comm.moveHingeJoint(joint, speed1);
      }
    }
  }
  
  if (sayMessage.size() > 0)
    comm.say(sayMessage);
  
  //comm.sendMessage("(graph (g hoi)(val 75))(graph (g doei)(val 90))");
  
	d_actions.clear();
}

#include "worldmodel.ih"

void WorldModel::updateAttackerState()
{
  GamepadInput* pad = GamepadInput::getInstance();
  if( pad->isInitialized() )
    return;

  // To consider easily, set DistanceToBall in integer
  int distToBall = (int)(d_objectPositions[Types::BALL].getMu().length() * 100.0);

  if(!visibleObject(Types::BALL))
    distToBall = 1000;

  Vector3D ballPos = getObjectPosition(Types::BALL).getMu();
  Vector3D goaluPos = getObjectPosition(Types::GOAL1US).getMu() + getObjectPosition(Types::GOAL2US).getMu();
  Vector3D goaltPos = getObjectPosition(Types::GOAL1THEM).getMu() + getObjectPosition(Types::GOAL2THEM).getMu();

  int angBallandUGoal = (int)(ballPos.angle(goaluPos) / M_PI * 180.0);

  bool visible = d_allObjectPosAvailable;

  // ball and our goal are existed in same direction,
  // not attack.
  if(visible && angBallandUGoal < 50)
  {
    //std::cout << "our goal can be seen... not good..." << std::endl;
    distToBall = 800;
  }

  // set say message
  stringstream ss;
  ss << "opuuuuch.v." << distToBall; // identify code + distance
  sayMessage(ss.str());

  double time, dir;
  int oDistToBall = distToBall+1;
  std::string message;
  ss.str("<br>");

  for(int i=0;i<=2;i++)
  {
    time    = getHearTime(i);
    dir     = getHearDirection(i);
    message = getHearMessage(i);

    ss << " Message: [" << message << "] from [" << dir << "] at [" << time << "]<br> ";

    if(time + 0.1 >= d_gameTime && dir <= 180) // other agent's recent message 
    {
      if(message.find("opuuuuch.v.") != std::string::npos) // message includes 'opuuuuch.v.'
      {
        // get the distance between other agent and ball.
        oDistToBall = (int)atof(message.substr(11).c_str());

        if(distToBall < oDistToBall) // nearer ball than other agent
        {
          //std::cout << " I should attack!" << std::endl;
          d_AT_attacking = true;
        }
        else if(distToBall == oDistToBall)
        {
          //std::cout << " draw!! unum 3 player should attack!" << std::endl;
          if(d_unum == 3)
            d_AT_attacking = true;
          else
            d_AT_attacking = false;
        }
        else
        {
          //std::cout << " orz" << std::endl;
          d_AT_attacking = false;
        }
        break;
      }
    }
  }
  addDebugMessage(COMMENT, ss.str());
/*
  if(distToBall < oDistToBall) // nearer ball than other agent
  {
    //std::cout << " I should attack!" << std::endl;
    d_AT_attacking = true;
  }
  else if(distToBall == oDistToBall)
  {
    //std::cout << " draw!! unum 3 player should attack!" << std::endl;
    if(d_unum == 3)
      d_AT_attacking = true;
    else
      d_AT_attacking = false;
  }
  else
  {
    //std::cout << " orz" << std::endl;
    d_AT_attacking = false;
  }
*/
  if(d_AT_attacking)
    addDebugMessage(COMMENT, "<font color=red>ATTACKKK!!!!</font>");
  else
    addDebugMessage(COMMENT, "<font color=blue>ill OTL llii</font>");

}

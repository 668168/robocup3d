#include "worldmodel.ih"

void WorldModel::intergrate(rf<Predicate> const &pred)
{
  _debugLevel4("Intergrating: " << *pred);
//  std::cerr << "Intergrating: " << *pred << std::endl;

  ++d_numMsgReceived;

  Vector4F vect, vect2;

  InfoID HJID,UJID, TID;

  unsigned pid, tmp, messageNum=0;

  string str;

  Vector4F now;

  PlayMode mode;

  for (unsigned i = 0; i < iInfoID; ++i)
    d_info[i] = Vector4F(0,0,0,0);
    
  //double val = 0;
  
  // I have a slightly better idea for the following algorithm
  // but that would take more time to implement.

  for (Predicate::const_iterator i = pred->begin();
       i != pred->end(); ++i) {


    InfoID id = translateInfo(rf_cast<Predicate>(*i)->getStr());
    _debugLevel4(rf_cast<Predicate>(*i)->getStr() << ", id: " << id);
//    std::cout << rf_cast<Predicate>(*i)->getStr() << ", id: " << id  << std::endl;
    
    switch (id) {
   
    case iGameState:
      for (Predicate::const_iterator j = (*i)->begin();
           j != (*i)->end(); ++j) {
     
        id = translateInfo(rf_cast<Predicate>(*j)->getStr());
     
        switch (id) {
       
        case iUnum:
          d_info[iUnum] = parseScalar(rf_cast<Predicate>(*j));
          d_unum = (unsigned)d_info[iUnum].getX();
          _debugLevel4("unum: " << d_unum);
          break;
       
        case iTeam:
          d_team = rf_cast<Predicate>((*j)->getChild(0))->getStr() == "left" ? LEFT : RIGHT;
          _debugLevel4("team: " << d_team);
          break;
       
        case iGameTime:
          d_info[iGameTime] = parseScalar(rf_cast<Predicate>(*j));
          d_prevGameTime = d_gameTime;
          d_gameTime = d_info[iGameTime].getX();
          d_timeStep = d_gameTime-d_prevGameTime;
          _debugLevel4("gametime: " << d_gameTime);
          _debugLevel4("timestep: " << d_timeStep);
          break;
       
        case iPlayMode:
          d_playModeString = rf_cast<Predicate>((*j)->getChild(0))->getStr();
          mode = s_playModeMap[rf_cast<Predicate>((*j)->getChild(0))->getStr()];
          switch (mode)
          {
          case KICKOFF_LEFT:
            d_playMode = d_team == LEFT ? KICKOFF_US : KICKOFF_THEM;
            break;
    
          case KICKOFF_RIGHT:
            d_playMode = d_team == RIGHT ? KICKOFF_US : KICKOFF_THEM;
            break;
    
          case FREEKICK_LEFT:
            d_playMode = d_team == LEFT ? FREEKICK_US : FREEKICK_THEM;
            break;
    
          case FREEKICK_RIGHT:
            d_playMode = d_team == RIGHT ? FREEKICK_US : FREEKICK_THEM;
            break;
    
          case GOAL_LEFT:
            d_playMode = d_team == LEFT ? GOAL_US : GOAL_THEM;
            break;
    
          case GOAL_RIGHT:
            d_playMode = d_team == RIGHT ? GOAL_US : GOAL_THEM;
            break;
    
          case GOAL_KICK_LEFT:
            d_playMode = d_team == LEFT ? GOAL_KICK_US : GOAL_KICK_THEM;
            break;
    
          case GOAL_KICK_RIGHT:
            d_playMode = d_team == RIGHT ? GOAL_KICK_US : GOAL_KICK_THEM;
            break;
    
          case CORNER_KICK_LEFT:
            d_playMode = d_team == LEFT ? CORNER_KICK_US : CORNER_KICK_THEM;
            break;
    
          case CORNER_KICK_RIGHT:
            d_playMode = d_team == RIGHT ? CORNER_KICK_US : CORNER_KICK_THEM;
            break;
    
          case KICKIN_LEFT:
            d_playMode = d_team == LEFT ? KICKIN_US : KICKIN_THEM;
            break;
    
          case KICKIN_RIGHT:
            d_playMode = d_team == RIGHT ? KICKIN_US : KICKIN_THEM;
            break;
    
          default:
            d_playMode = mode;
            break;
          }
          _debugLevel4("playmode: " << d_playMode);
          break;
       
        default:
          break;    
        }
      }
   
      break;
   
    case iVision:
      d_playerUnums.clear();
      d_opponentUnums.clear();

      for (Predicate::const_iterator j = (*i)->begin();
           j != (*i)->end(); ++j) {
     
        id = translateInfo(rf_cast<Predicate>(*j)->getStr());
     
        switch (id) {
       
        case iVisionFlag1L:
          d_info[iVisionFlag1L] = parseVect(rf_cast<Predicate>((*j)->getChild(0)));
          break;
       
        case iVisionFlag1R:
          d_info[iVisionFlag1R] = parseVect(rf_cast<Predicate>((*j)->getChild(0)));
          break;
       
        case iVisionFlag2L:
          d_info[iVisionFlag2L] = parseVect(rf_cast<Predicate>((*j)->getChild(0)));
          break;
       
        case iVisionFlag2R:
          d_info[iVisionFlag2R] = parseVect(rf_cast<Predicate>((*j)->getChild(0)));
          break;
       
        case iVisionGoal1L:
          d_info[iVisionGoal1L] = parseVect(rf_cast<Predicate>((*j)->getChild(0)));
          break;
       
        case iVisionGoal1R:
          d_info[iVisionGoal1R] = parseVect(rf_cast<Predicate>((*j)->getChild(0)));
          break;
       
        case iVisionGoal2L:
          d_info[iVisionGoal2L] = parseVect(rf_cast<Predicate>((*j)->getChild(0)));
          break;
       
        case iVisionGoal2R:
          d_info[iVisionGoal2R] = parseVect(rf_cast<Predicate>((*j)->getChild(0)));
          break;
       
        case iVisionBall:
          d_info[iVisionBall] = parseVect(rf_cast<Predicate>((*j)->getChild(0)));
          break;
       
        case iP:
          str = rf_cast<Predicate>((*j)->getChild(0)->getChild(0))->getStr();
          pid = rf_cast<Predicate>((*j)->getChild(1)->getChild(0))->getInt();
          // std::cout << "iP str="<< str << ", pid=" << pid << std::endl;
          if (str == d_teamName) { // teammate

            if( d_unum != pid ) // not me
            {
              if (d_playerUnums.find(pid) == d_playerUnums.end()) {
                // std::cout << "Unum us " << pid << " -> " << d_playerUnums.size() << std::endl;;
                tmp = d_playerUnums.size()+1; // player number

                if (d_playerUnums.size() > 10)
                  d_playerUnums[pid] = 11;
                else
                  d_playerUnums[pid] = tmp;
              }
              // TODO: every parts of agent should be avilable
              // 位置情報は得られてる．格納場所が準備できていない．
              for (int k=2;k<(*j)->size();k++){
                InfoID joint =
                  translateInfo(rf_cast<Predicate>((*j)->getChild(k))->getStr());
              }

              d_info[iVisionPlayer1 + d_playerUnums[pid]-1] = parseVect(rf_cast<Predicate>((*j)->getChild(2)->getChild(0)));
              // d_info[iVisionPlayer1 + d_playerUnums[pid]] = tmpv;
              d_lastVisionUpdate[Types::PLAYER1 + d_playerUnums[pid]-1] = d_time;
            }

          }
          else // opponent
          {
            if (d_opponentUnums.find(pid) == d_opponentUnums.end()) {

              tmp = d_opponentUnums.size()+1;
              if (d_opponentUnums.size() > 10)
                d_opponentUnums[pid] = 11;
              else
                d_opponentUnums[pid] = tmp;

            }
            d_info[iVisionOpponent1 + d_opponentUnums[pid]-1] = parseVect(rf_cast<Predicate>((*j)->getChild(2)->getChild(0)));
            // d_info[iVisionOpponent1 + d_opponentUnums[pid]] = tmpv;
            d_lastVisionUpdate[Types::OPPONENT1 + d_opponentUnums[pid]-1] = d_time;

          }
          break;

        case iMyPos:
          d_info[iMyPos] = parseVect(rf_cast<Predicate>((*j)));
          break;

        default:
          break;
       
        };
     
      }
      break;

    case iGyro:
      d_info[iTorsoGyro] = parseVect(rf_cast<Predicate>((*i)->getChild(1)));
//      std::cout << "d_info[iTorsoGyro]: " << d_info[iTorsoGyro] << std::endl;
      
/*      for (Predicate::const_iterator j = (*i)->begin();
 j != (*i)->end(); ++j) {

        id = translateInfo(rf_cast<Predicate>(*j)->getStr());
        switch (id) {
 case iGyroBody:
 d_info[iGyroBody] = parseVect(rf_cast<Predicate>((*j)->getChild(0)));
 break;
          
 default:
 break;
        }
 }*/
      break;
          
    case iAcceleration:
      d_info[iAcceleration] = parseVect(rf_cast<Predicate>((*i)->getChild(1)));

      break;

    
    case iForceResistancePerceptor:
      TID = iNone;
      _debugLevel4("iForceResistancePerceptor");
      for (Predicate::const_iterator j = (*i)->begin();
           j != (*i)->end(); ++j)
      {
        id = translateInfo(rf_cast<Predicate>(*j)->getStr());

        switch (id) {
        case iName:
          TID = translateInfo(rf_cast<Predicate>((*j)->getChild(0))->getStr());
          _debugLevel4("TID: " << TID);
          break;
        
        case iContact:
          vect = parseVect(rf_cast<Predicate>(*j));
          //  std::cout << "vect: " << vect << std::endl;
          break;
          
        case iForce:
          vect2 = parseVect(rf_cast<Predicate>(*j));
          //  std::cout << "vect2: " << vect2 << std::endl;
          break;

        default:
          break;
        }
      }
      
      d_info[TID] = vect;
      d_info[TID + 1] = vect2;
      break;
      
    case iTime:
      for (Predicate::const_iterator j = (*i)->begin();
           j != (*i)->end(); ++j) {

        id = translateInfo(rf_cast<Predicate>(*j)->getStr());

        switch (id) {

        case iNow:
          now = parseScalar(rf_cast<Predicate>(*j));
          // skip if we have already seen this
          if (d_info[iNow].getX() == now.getX())
            return;
          if (d_firstTime < 0)
            d_firstTime = now.getX();
          d_info[iNow]  = now;
          d_time = now.getX();
          
          break;

        case iStep:
          d_info[iStep] = parseScalar(rf_cast<Predicate>(*j));
          break;

        default:
          break;


        };


      }
      break;

    case iUJ:
      vect = Vector4F(0.0,0.0,0.0,0.0);
      vect2 = Vector4F(0.0,0.0,0.0,0.0);

      UJID = iNone;
      //     std::cout << "iUJ " << std::endl;
      for (Predicate::const_iterator j = (*i)->begin();
           j != (*i)->end(); ++j) {
//   std::cout << "for loop naka" << std::endl;
        id = translateInfo(rf_cast<Predicate>(*j)->getStr());

        switch (id) {
        case iName:
          UJID = translateInfo(rf_cast<Predicate>((*j)->getChild(0))->getStr());
          _debugLevel4(rf_cast<Predicate>((*j)->getChild(0))->getStr());
          break;

        case iAxis1:
          vect.setX(*rf_cast<Predicate>((*j)->getChild(0)));
          _debugLevel4("joint: " << vect.getX());
//   std:: cout << "ijoint: " << vect.getX() << std::endl;
          break;

        case iRate1:
          vect.setY(*rf_cast<Predicate>((*j)->getChild(0)));
          break;

        case iAxis2:
          vect2.setX(*rf_cast<Predicate>((*j)->getChild(0)));
          _debugLevel4("joint: " << vect2.getX());
          break;

        case iRate2:
          vect2.setY(*rf_cast<Predicate>((*j)->getChild(0)));
          break;

        default:
          _debugLevel4("Unknown id: " << rf_cast<Predicate>(*j)->getStr());
          //     std::cout << "Unknown id: " << rf_cast<Predicate>(*j)->getStr() << std::endl;
          break;
        };

      }

      if (UJID) {
        d_info[UJID] = vect;
        d_info[UJID+1] = vect2;
      } else
        _debugLevel4("Unknown UJID!");
      break;

    case iHJ:
      vect = Vector4F(0.0,0.0,0.0,0.0);

      HJID = iNone;

      for (Predicate::const_iterator j = (*i)->begin();
           j != (*i)->end(); ++j) {

        id = translateInfo(rf_cast<Predicate>(*j)->getStr());
// std::cout << "ID=" << id << std::endl;

        switch (id) {
        case iName:
          HJID = translateInfo(rf_cast<Predicate>((*j)->getChild(0))->getStr());
          break;

        case iAxis:
          vect.setX(*rf_cast<Predicate>((*j)->getChild(0)));
          _debugLevel4("joint: " << vect.getX());
          break;

        case iRate:
          vect.setY(*rf_cast<Predicate>((*j)->getChild(0)));
          break;

        case iAxis1:
          vect.setX(*rf_cast<Predicate>((*j)->getChild(0)));
          _debugLevel4("joint: " << vect.getX());
//   std:: cout << "ijoint: " << vect.getX() << std::endl;
          break;

        case iRate1:
          vect.setY(*rf_cast<Predicate>((*j)->getChild(0)));
          break;

        case iAxis2:
          vect.setX(*rf_cast<Predicate>((*j)->getChild(0)));
          _debugLevel4("joint: " << vect.getX());
          break;

        case iRate2:
          vect.setY(*rf_cast<Predicate>((*j)->getChild(0)));
          break;

        default:
          break;
        };
// std::cout << "iHJ jointname:"<< HJID << ", x=" << vect.getX() << ", y=" << vect.getY() << std::endl;
      }

      if (HJID)
        d_info[HJID] = vect;
      else
        _debugLevel4("Unknown HJID!");
      break;

// say and hear command
    case iHear:
      d_hearTime[messageNum] = *rf_cast<Predicate>((*i)->getChild(0));
      str = (std::string)*rf_cast<Predicate>((*i)->getChild(1));
      if(str == "self")
        d_hearDirection[messageNum] = 1000;
      else
        d_hearDirection[messageNum] = atof(str.c_str());
      d_hearMessage[messageNum] = (std::string)*rf_cast<Predicate>((*i)->getChild(2));
      //std::cout << "hear" << messageNum << "! time:" << d_info[iHear].getX()
      //   << ", dir:" << d_hearDirection[messageNum]
      //   << ", message:" << d_hearMessage[messageNum] << std::endl;
      messageNum++;
      break;

    default:
      break;


    };


  }
}

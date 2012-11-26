#include "cochlea.ih"

void Cochlea::integrate(rf<Predicate> const &pred)
{
  _debugLevel1("Intergrating: " << *pred);

  Vector4F vect, vect2;

  InfoID HJID,UJID, TID;

  string str;
  unsigned pid;
  
  Vector4F now;

  double hearTime, hearAngle;
  string hearMessage;

  for (unsigned i = 0; i < iInfoID; ++i)
    d_info[i] = Vector4F(0,0,0,0);
  
  //double val = 0;
  
  // I have a slightly better idea for the following algorithm
  // but that would take more time to implement.

  for (Predicate::const_iterator i = pred->begin();
       i != pred->end(); ++i) {


    InfoID id = translateInfo(rf_cast<Predicate>(*i)->getStr());
    _debugLevel4(rf_cast<Predicate>(*i)->getStr() << ", id: " << id);
    
    
    switch (id) {

    case iGameState:
      for (Predicate::const_iterator j = (*i)->begin();
           j != (*i)->end(); ++j) {

        id = translateInfo(rf_cast<Predicate>(*j)->getStr());

        switch (id) {
        
        case iUnum:
          d_info[iUnum] = parseScalar(rf_cast<Predicate>(*j));
          break;
          
        case iTeam:
          d_info[iTeam].setX(rf_cast<Predicate>((*j)->getChild(0))->getStr() == "left" ? Types::LEFT : Types::RIGHT);
          break;
          
        case iGameTime:
          d_info[iGameTime] = parseScalar(rf_cast<Predicate>(*j));
          break;
          
        case iPlayMode:
          d_info[iPlayMode].setX(d_playModeMap[rf_cast<Predicate>((*j)->getChild(0))->getStr()]);
          break;

        default:
          break;    
        }
      }

      break;
      
    case iVision:
      for (Predicate::const_iterator j = (*i)->begin();
           j != (*i)->end(); ++j) {

        id = translateInfo(rf_cast<Predicate>(*j)->getStr());

        switch (id) {

        case iVisionFlag1L:
        case iVisionFlag1R:
        case iVisionFlag2L:
        case iVisionFlag2R:
        case iVisionGoal1L:
        case iVisionGoal1R:
        case iVisionGoal2L:
        case iVisionGoal2R:
        case iVisionBall:
          vect = parseVect(rf_cast<Predicate>((*j)->getChild(0)));
          vect.setY(vect.getY() / 180.0 * M_PI);
          vect.setZ(vect.getZ() / 180.0 * M_PI);
          d_info[id] = vect;
          break;

        case iP:
          str = rf_cast<Predicate>((*j)->getChild(0)->getChild(0))->getStr();
          pid = rf_cast<Predicate>((*j)->getChild(1)->getChild(0))->getInt();

          vect = parseVect(rf_cast<Predicate>((*j)->getChild(2)));
          vect.setY(vect.getY() / 180.0 * M_PI);
          vect.setZ(vect.getZ() / 180.0 * M_PI);

		  if (pid < 9) {
			if (str == d_teamName) {
			  d_info[iVisionPlayer1 + pid - 1] = vect;
			  //d_lastVisionUpdate[Types::PLAYER1 + pid - 1] = d_info[iNow];
			} else {
			  d_info[iVisionOpponent1 + pid - 1] = vect;
			  //d_lastVisionUpdate[Types::OPPONENT1 + pid - 1] = d_info[iNow];
			}
		  }// else
		  //	_flog("WARNING: UNUM CHEATER DETECTED!!");
          break;

        default:
          break;

        };

      }
      break;

    case iGyro:
      d_info[iTorsoGyro] = parseVect(rf_cast<Predicate>((*i)->getChild(1)));
      _debugLevel4("d_info[iTorsoGyro]: " << d_info[iTorsoGyro]);
      
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
          _debugLevel4("vect: " << vect);
          break;
          
        case iForce:
          vect2 = parseVect(rf_cast<Predicate>(*j));
          _debugLevel4("vect2: " << vect2);
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
          d_info[iNow] = parseScalar(rf_cast<Predicate>(*j));          
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

      for (Predicate::const_iterator j = (*i)->begin();
           j != (*i)->end(); ++j) {

        id = translateInfo(rf_cast<Predicate>(*j)->getStr());

        switch (id) {
        case iName:
          UJID = translateInfo(rf_cast<Predicate>((*j)->getChild(0))->getStr());
          _debugLevel4(rf_cast<Predicate>((*j)->getChild(0))->getStr());
          break;

        case iAxis1:
          vect.setX(*rf_cast<Predicate>((*j)->getChild(0)));
          _debugLevel4("joint: " << vect.getX());
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

        switch (id) {
        case iName:
          HJID = translateInfo(rf_cast<Predicate>((*j)->getChild(0))->getStr());
          break;

        case iAxis:
          vect.setX(*rf_cast<Predicate>((*j)->getChild(0)));
          _debugLevel4("joint: " << HJID << " " << vect.getX());
          break;

        case iRate:
          vect.setY(*rf_cast<Predicate>((*j)->getChild(0)));
          break;

        default:
          break;
        };

      }

      if (HJID)
        d_info[HJID] = vect;
      else
        _debugLevel4("Unknown HJID!");
      break;

    case iHear:
      hearTime = *rf_cast<Predicate>((*i)->getChild(0));
      hearAngle = *rf_cast<Predicate>((*i)->getChild(1));
      hearMessage = rf_cast<Predicate>((*i)->getChild(2))->getStr();
      d_hearMessages.push_back(HearMessage(hearTime, hearAngle, hearMessage));
      break;
      
    default:
      break;


    };


  }

}

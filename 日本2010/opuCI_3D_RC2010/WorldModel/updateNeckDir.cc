#include "worldmodel.ih"

enum Direction{
  Dir_HOLD,
  Dir_RIGHT,
  Dir_LEFT,
  Dir_UP,
  Dir_DOWN,

  Dir_UNKNOWN,
};

void WorldModel::updateNeckDir()
{
  if(!d_neckDirUpdate){
    addDebugMessage(COMMENT, "(updateNeckDir) <font color=red>NOT</font> update neck!");
    rf<Predicate> message = new Predicate( "", Predicate::type_list);
    rf<Predicate> pred = message->push(new Predicate("he1"));
    pred->pushLeaf("0");
    rf<Predicate> pred2 = message->push(new Predicate("he2"));
    pred2->pushLeaf("0");
    d_comm.send(message);
    return;
  }

  std::stringstream ss;
  ss << "(updateNeckDir) update neckdir! <font color=yellow>"
     << d_neck << ", " << d_head << "</font>";

  addDebugMessage(COMMENT, ss.str());

  rf<Predicate> message = new Predicate( "", Predicate::type_list);
  rf<Predicate> pred = message->push(new Predicate("he1"));
  double neckAngle =  d_jointAngles[Types::NECK].getMu() / M_PI * 180.0;
  double deltaAngle = d_neck - neckAngle;
  double gain = 0.1;
  
  Direction neckTurnTo = Dir_UNKNOWN;
  if(fabs(deltaAngle) < 3 ||
     (neckAngle >= 119.9 && d_neck > neckAngle) ||
     (neckAngle <= -119.9 && d_neck < neckAngle))
    neckTurnTo = Dir_HOLD;
  else if(deltaAngle > 0 )
    neckTurnTo = Dir_LEFT;
  else if(deltaAngle < 0 )
    neckTurnTo = Dir_RIGHT;
  
  double speed = deltaAngle * gain;

  ss.str("");

  switch(neckTurnTo){
  case Dir_RIGHT:
    speed--;
    ss.str("");
    ss << speed;
    pred->pushLeaf(ss.str());
    //    pred->pushLeaf("-10");
    break;
      
  case Dir_LEFT:
    speed++;
    ss.str("");
    ss << speed;
    pred->pushLeaf(ss.str());
    //    pred->pushLeaf("10");
    break;
      
  case Dir_HOLD:
  default:
    pred->pushLeaf("0");
    break;
      
  }
  
  rf<Predicate> pred2 = message->push(new Predicate("he2"));
  double headAngle = d_jointAngles[Types::HEAD].getMu() / M_PI * 180.0;
  deltaAngle = d_head - headAngle;
  //   std::cout << "updateNeckDir d_head : " << d_head 
  //      << ", delta: " << deltaAngle << std::endl;
  
  Direction headTurnTo = Dir_UNKNOWN;
  if(fabs(deltaAngle) < 1 ||
     (headAngle >= 44.9 && d_head > headAngle) ||
     (headAngle <= -44.9 && d_head < headAngle) )
    headTurnTo = Dir_HOLD;
  else if(deltaAngle > 0)
    headTurnTo = Dir_UP;
  else if(deltaAngle < 0)
    headTurnTo = Dir_DOWN;
  
  speed = deltaAngle / 10;
  //    std::cout << "headTurnTo " << headTurnTo << std::endl;
  switch(headTurnTo)
  {
  case Dir_UP:
    speed++;
    ss.str("");
    ss << speed;
    pred2->pushLeaf(ss.str());
    break;
      
  case Dir_DOWN:
    speed--;
    ss.str("");
    ss << speed;
    pred2->pushLeaf(ss.str());
    break;
      
  case Dir_HOLD:
  default:
    pred2->pushLeaf("0");
    break;
      
  }
  
  d_comm.send(message);
  //    std::cout << "update neck dir!" << std::endl;
}

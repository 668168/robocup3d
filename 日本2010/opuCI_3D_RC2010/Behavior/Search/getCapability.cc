#include "search.ih"

Behavior::ConfidenceInterval Search::getCapability(rf<State> s, rf<Goal> g)
{
  // if agent cannot see ball and 2 landmarks,
  // (that is, cannot calculate invisible landmark's position,)
  // do "Search"

  WorldModel& wm = WorldModel::getInstance();

  if( ! wm.allObjectPosAvailable() && ! wm.visibleObject(Types::BALL) ){
    // wm.addDebugMessage(WorldModel::COMMENT, "@w@ !");
/*
   wm.searching(false);
  }
  if( wm.nowSearching() )
*/
    return ConfidenceInterval(0.8, 0);
  }
 
 return ConfidenceInterval(0.0, 0);
}

#include "defense.ih"

Behavior::ConfidenceInterval Defense::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();

  if(wm.getProcessingOppAttack())
    return ConfidenceInterval(0.95, 0.0);

  else if(d_minTimeUpdate){
	  return ConfidenceInterval(0.75, 0.0);
  }
/*
  if( wm.nowSearching() )
    return ConfidenceInterval(0.2, 0.0);
  else if( wm.visibleLandmarkNum() < 2 ){
    wm.searching(true);
    return ConfidenceInterval(0.5, 0.0);
  }
*/
  if( wm.onMyBack() || wm.onMyBelly() || wm.onMySide() )
    return ConfidenceInterval(0.0, 0.0);

  wm.setNeckDirUpdate(true);
  return ConfidenceInterval(0.2, 0.0);
}

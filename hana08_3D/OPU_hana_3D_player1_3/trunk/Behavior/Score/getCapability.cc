#include "score.ih"

Behavior::ConfidenceInterval Score::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  WorldModel::PlayMode pm = wm.getPlayMode();

  
//  return wm.onMyBack() || wm.onMyBelly() || wm.onMySide() ? ConfidenceInterval(0.0, 0.0) : ConfidenceInterval(0.5, 0.2);

  if( wm.onMyBack() || wm.onMyBelly() || wm.onMySide() )
      return ConfidenceInterval(0.0, 0.0);
  else{
	if( fabs(wm.getDistToField()) < 0.2)
	    return ConfidenceInterval(0.0, 0.0);
	else if(wm.getSide() == WorldModel::RIGHT && wm.getUnum() == 3 && pm == WorldModel::KICKOFF_THEM)
	    return ConfidenceInterval(0.0, 0.0);
	else
	    return ConfidenceInterval(0.5, 0.2);
  }
}

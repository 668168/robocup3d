#include "score.ih"

Behavior::ConfidenceInterval Score::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  WorldModel::PlayMode pm = wm.getPlayMode();

/*
  if( wm.nowSearching() )
    return ConfidenceInterval(0.0, 0.0);
  else if( ! wm.allObjectPosAvailable() ){
    wm.searching(true);
    return ConfidenceInterval(0.5, 0.0);
  }
*/
  Vector3D ballPos = wm.getObjectPosition(Types::BALL).getMu();

  if( wm.onMyBack() || wm.onMyBelly() || wm.onMySide() )
    return ConfidenceInterval(0.0, 0.0);

  else if( wm.getUnum() != 1 && pm == WorldModel::KICKOFF_THEM)
    return ConfidenceInterval(0.0, 0.0);

  else {
    wm.setNeckDirUpdate(true);
    return ConfidenceInterval(0.7, 0.0);
  }
}

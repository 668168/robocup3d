#include "beamto.ih"

Behavior::ConfidenceInterval BeamTo::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();

  WorldModel::PlayMode pm = wm.getPlayMode(); 

  _debugLevel4("PlayMode: " << pm);
  // If we aren't in BEFORE_KICKOFF, our capability is -1.0 with infinite confidence
  if (pm != WorldModel::BEFORE_KICKOFF && pm != WorldModel::GOAL_US && pm != WorldModel::GOAL_THEM && pm != WorldModel::GOAL_LEFT && pm != WorldModel::GOAL_RIGHT){
    return ConfidenceInterval(-1.0, 0.0);
  }

  // Else we can certainly do it
  wm.kpGoodPosition(true);
  wm.kpBlocking(WorldModel::NOTBLOCK);
  return ConfidenceInterval(1.0, 0.0);

}

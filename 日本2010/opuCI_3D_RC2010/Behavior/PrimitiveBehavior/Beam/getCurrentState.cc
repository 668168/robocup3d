#include "beam.ih"

rf<Behavior::State> Beam::getCurrentState()
{
  WorldModel& wm = WorldModel::getInstance();
//  double gameState = wm.getGameState();
  double playMode = wm.getPlayMode();
  
  rf<State> state = new State;
  rf<OrNode> dis = state->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  con->addVar("PlayMode", playMode, playMode);
  
  return state;
//  return 0;
}

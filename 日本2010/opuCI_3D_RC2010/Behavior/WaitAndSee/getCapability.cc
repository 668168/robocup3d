#include "waitandsee.ih"

Behavior::ConfidenceInterval WaitAndSee::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  Types::PlayerType myType = wm.getPlayerType(wm.getUnum());

  if((!wm.getATattacking() && myType == Types::ATTACKER )|| // for attacker
     ( !wm.getProcessingOppAttack() && myType == Types::DEFENDER)) // for defender
  {
//    std::cerr << "WaitAndSee::getCapability  My Turn is over..." << std::endl;
    return ConfidenceInterval(0.75, 0.0);
  }

  return ConfidenceInterval(0.0, 0.0);
}


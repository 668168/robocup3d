#include "readytoguard.ih"

rf<Behavior::State> ReadyToGuard::getCurrentState()
{
  rf<State> state = new State();
  rf<OrNode> dis = state->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  // con->addVar("Var", 0, 1);
  return state;
}

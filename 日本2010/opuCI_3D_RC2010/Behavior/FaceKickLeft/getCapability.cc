#include "facekickleft.ih"

Behavior::ConfidenceInterval FaceKickLeft::getCapability(rf<State> s, rf<Goal> g)
{
  return ConfidenceInterval(0.5, 0.2);
}

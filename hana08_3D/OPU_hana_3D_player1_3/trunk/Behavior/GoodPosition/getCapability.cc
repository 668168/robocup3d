#include "goodposition.ih"

Behavior::ConfidenceInterval GoodPosition::getCapability(rf<State> s, rf<Goal> g)
{
    Vector3D pos = g->getVector("Pos"); // ballPos?
  
  _debugLevel4(ident() << ": " << pos << " " << pos.length());
  
  if (pos.length() > 0.8){

    return ConfidenceInterval(0.0, 0.2);
  }

  return ConfidenceInterval(0.5, 0.2);
}

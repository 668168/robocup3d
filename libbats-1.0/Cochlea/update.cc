#include "cochlea.ih"

void Cochlea::update()
{
  rf<Predicate> pred = SAgentSocketComm::getInstance().getPred();
  if (pred)
    integrate(pred);
}


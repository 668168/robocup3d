#include "trainersocketcomm.ih"

void TrainerSocketComm::kickOff()
{
  send(makeKickOffMessage());
}

rf<Predicate> TrainerSocketComm::makeKickOffMessage()
{
  rf<Predicate> msg = new Predicate("kickOff");
  return msg;
}


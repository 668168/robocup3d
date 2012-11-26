#include "agentsocketcomm.ih"

void AgentSocketComm::say(string message)
{
  send(makeSayMessage(message));
}

rf<Predicate> AgentSocketComm::makeSayMessage(string message)
{
  rf<Predicate> pred = new Predicate("say");
  pred->pushLeaf(message);
  return pred;
}


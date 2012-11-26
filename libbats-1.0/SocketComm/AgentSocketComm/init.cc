#include "agentsocketcomm.ih"

void AgentSocketComm::init(unsigned unum, string team)
{
  send(makeInitMesage(unum, team));
}

rf<Predicate> AgentSocketComm::makeInitMesage(unsigned unum, string team)
{
  rf<Predicate> initPred = new Predicate("init");
  rf<Predicate> unumPred = rf_cast<Predicate>(initPred->addChild(new Predicate("unum")));
  unumPred->pushLeaf(unum);
  rf<Predicate> teamPred = rf_cast<Predicate>(initPred->addChild(new Predicate("teamname")));
  teamPred->pushLeaf(team);
  return initPred;
}


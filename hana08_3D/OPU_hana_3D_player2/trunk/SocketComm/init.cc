#include "socketcomm.ih"

void SocketComm::init(unsigned unum, string team)
{
//  std::cout << "init() start" << std::endl;
  send(makeInitMesage(unum, team));
}


rf<Predicate> SocketComm::makeInitMesage(unsigned unum, string team)
{
  rf<Predicate> initPred = new Predicate("init");
  rf<Predicate> unumPred = rf_cast<Predicate>(initPred->addChild(new Predicate("unum")));
  unumPred->pushLeaf(unum);
  rf<Predicate> teamPred = rf_cast<Predicate>(initPred->addChild(new Predicate("teamname")));
  teamPred->pushLeaf(team);
//  std::cout << *initPred << std::endl;
  return initPred;
}


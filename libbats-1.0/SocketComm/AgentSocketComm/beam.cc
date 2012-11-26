#include "agentsocketcomm.ih"

void AgentSocketComm::beam(Vector3D const& pos)
{
  send(makeBeamMessage(pos));
}

rf<Predicate> AgentSocketComm::makeBeamMessage(Vector3D const& pos)
{
  rf<Predicate> beamPred = new Predicate("beam");
  beamPred->pushLeafs(pos);
  _debugLevel4(*beamPred);
  return beamPred;
}

